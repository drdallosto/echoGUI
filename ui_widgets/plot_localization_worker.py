# ui_widgets/plot_localization_worker.py
import time
import os
import csv
import datetime

import numpy as np
from PyQt6.QtCore import QObject, pyqtSignal, pyqtSlot
from pymavlink import mavutil

from ui_widgets.create_sound_loc_plot import small_rad, HEAT_GRID_N, PLOT_RANGE
from ui_widgets.dev_style import dev_color

_MIN_LINES_FOR_ESTIMATE = 2

# Pre-build the XY grid once (shared across all worker instances)
_grid_x, _grid_y = np.meshgrid(
    np.linspace(-PLOT_RANGE, PLOT_RANGE, HEAT_GRID_N),
    np.linspace(-PLOT_RANGE, PLOT_RANGE, HEAT_GRID_N),
)


def _least_squares_intersection(origins, directions):
    """Least-squares closest point to N rays."""
    A = np.zeros((2, 2))
    b = np.zeros(2)
    for (ox, oy), (dx, dy) in zip(origins, directions):
        P = np.eye(2) - np.outer([dx, dy], [dx, dy])
        A += P
        b += P @ np.array([ox, oy])
    try:
        return np.linalg.solve(A, b)
    except np.linalg.LinAlgError:
        return None


def _beam_wedge_vertices(ox, oy, center_rad, half_bw_rad, length=8.0, n=30):
    """
    Build the polygon vertices for a beam wedge.
    Returns an (n+2, 2) array: tip + arc points.
    """
    angles = np.linspace(center_rad - half_bw_rad,
                         center_rad + half_bw_rad, n)
    arc_x = ox + length * np.cos(angles)
    arc_y = oy + length * np.sin(angles)
    verts = np.column_stack([arc_x, arc_y])
    tip   = np.array([[ox, oy]])
    return np.vstack([tip, verts, tip])


def _beam_intensity_map(ox, oy, center_rad, half_bw_rad, gx, gy):
    """
    Soft Gaussian beam: 1.0 on the centre ray, falling to ~0 at ±half_bw.
    Returns a 2-D array (same shape as gx/gy) in [0, 1].
    """
    # angle from origin to each grid point
    ang = np.arctan2(gy - oy, gx - ox)

    # angular difference, wrapped to [-π, π]
    diff = ang - center_rad
    diff = (diff + np.pi) % (2 * np.pi) - np.pi

    # Gaussian with σ = half_bw / 2  (so ±half_bw ≈ 2σ → ~0.14)
    sigma = half_bw_rad / 2.0
    beam  = np.exp(-0.5 * (diff / sigma) ** 2)

    # zero out everything behind the origin
    ahead = ((gx - ox) * np.cos(center_rad) +
             (gy - oy) * np.sin(center_rad)) > 0
    beam[~ahead] = 0.0
    return beam


class PlotLocalizationWorker(QObject):

    progress   = pyqtSignal(str)
    error      = pyqtSignal(str)
    finished   = pyqtSignal()
    dataReady  = pyqtSignal(str, float, float, float, float, float)
    logStopped = pyqtSignal()

    def __init__(self, getDevConns,
                 azimuth_lines, dev_positions, canvas,
                 act_int_thresh_entry, q_thresh_entry, hist_thresh_entry,
                 source_point, source_ring, source_status,
                 heatmap_img, beam_patches,
                 beam_width_entry, time_const_entry):
        super().__init__()

        self.connection           = getDevConns
        self.azimuth_lines        = azimuth_lines
        self.dev_positions        = dev_positions
        self.canvas               = canvas
        self.act_int_thresh_entry = act_int_thresh_entry
        self.q_thresh_entry       = q_thresh_entry
        self.hist_thresh_entry    = hist_thresh_entry
        self.source_point         = source_point
        self.source_ring          = source_ring
        self.source_status        = source_status
        self.heatmap_img          = heatmap_img
        self.beam_patches         = beam_patches
        self.beam_width_entry     = beam_width_entry
        self.time_const_entry     = time_const_entry

        self.running        = True
        self._logging       = False
        self._csv_file      = None
        self._csv_writer    = None
        self._log_end_timer = None

        # per-device ray state for triangulation
        self._active_rays: dict[str, tuple] = {}

        # persistent heatmap accumulator — shape (N, N), float32
        self._heat_accum    = np.zeros((HEAT_GRID_N, HEAT_GRID_N), dtype=np.float32)
        self._last_heat_t   = time.time()

        # per-device color map (RGBA tuples for heatmap blending)
        self._dev_colors: dict[str, np.ndarray] = {}
        for i, name in enumerate(getDevConns.keys()):
            hex_c  = dev_color(i).lstrip("#")
            r, g, b = (int(hex_c[j:j+2], 16) / 255.0 for j in (0, 2, 4))
            self._dev_colors[name] = np.array([r, g, b], dtype=np.float32)

        self.dataReady.connect(self.plotAzimuth)

    # ── lifecycle ────────────────────────────────────────────────────

    def run(self):
        try:
            self.getAzimuth()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    def stop(self):
        self.running = False
        if self._logging:
            self.stop_logging()
        for line in self.azimuth_lines.values():
            line.set_data([], [])
        for patch in self.beam_patches.values():
            patch.set_visible(False)
        self._heat_accum[:] = 0
        self._update_heatmap_image()
        self._clear_source_estimate()
        self.canvas.draw_idle()

    # ── logging ──────────────────────────────────────────────────────

    def start_logging(self, end_timer):
        dirName = "sensor_avs_logging_data"
        os.makedirs(dirName, exist_ok=True)
        timestamp_str = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        csv_path = os.path.join(dirName, f"{timestamp_str}.csv")
        fieldnames = [
            "device", "node_id", "time_utc_usec",
            "active_intensity", "q_factor", "histogram_count",
            "azimuth", "elevation", "yaw", "pitch", "roll",
            "north", "east", "down",
        ]
        self._csv_file   = open(csv_path, mode="a", newline="")
        self._csv_writer = csv.DictWriter(self._csv_file, fieldnames=fieldnames)
        self._csv_writer.writeheader()
        self._log_end_timer = end_timer
        self._logging = True
        self.progress.emit(f"writing to csv: {csv_path}")

    def stop_logging(self):
        self._logging = False
        if self._csv_file:
            self._csv_file.close()
            self._csv_file   = None
            self._csv_writer = None
            self.progress.emit("stopped logging")

    # ── MAVLink receive loop ──────────────────────────────────────────

    def getAzimuth(self):
        message_id = 297

        for connection in self.connection.values():
            while connection.recv_match(blocking=False) is not None:
                pass

        for connection in self.connection.values():
            cmd = connection.mav.command_long_encode(
                connection.target_system,
                connection.target_component,
                mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,
                0, message_id, 0, 0, 0, 0, 0, 0,
            )
            connection.mav.send(cmd)

        for connection in self.connection.values():
            connection.recv_match(type="COMMAND_ACK", blocking=True, timeout=3)

        while self.running:
            changed = False
            for name, connection in self.connection.items():
                msg = connection.recv_match(
                    type="SENSOR_AVS_LITE_EXT", blocking=False, timeout=0.1
                )
                if msg:
                    self.dataReady.emit(
                        name,
                        float(msg.azimuth_deg),
                        float(msg.active_intensity),
                        float(msg.yaw),
                        float(msg.q_factor),
                        float(msg.histogram_count),
                    )
                    changed = True

                    if self._logging and self._csv_writer:
                        if time.time() < self._log_end_timer:
                            self._csv_writer.writerow({
                                "device":           name,
                                "node_id":          msg.device_id,
                                "time_utc_usec":    msg.time_utc_usec,
                                "active_intensity": msg.active_intensity,
                                "q_factor":         msg.q_factor,
                                "histogram_count":  msg.histogram_count,
                                "azimuth":          msg.azimuth_deg,
                                "elevation":        msg.elevation_deg,
                                "yaw":              msg.yaw,
                                "pitch":            msg.pitch,
                                "roll":             msg.roll,
                            })
                            self._csv_file.flush()
                        else:
                            self.stop_logging()
                            self.logStopped.emit()

            if changed:
                self._decay_heatmap()
                self.canvas.draw_idle()

    # ── plot slot ─────────────────────────────────────────────────────

    @pyqtSlot(str, float, float, float, float, float)
    def plotAzimuth(self, name, azimuth_deg, active_intensity, yaw,
                    q_factor, histogram_count):
        if name not in self.azimuth_lines:
            return

        try:
            act_threshold  = float(self.act_int_thresh_entry.text())
            q_threshold    = float(self.q_thresh_entry.text())
            hist_threshold = float(self.hist_thresh_entry.text())
            beam_width_deg = float(self.beam_width_entry.text())
        except ValueError:
            return

        x0, y0    = self.dev_positions[name]
        center_rad = np.radians(90 - azimuth_deg)# - yaw)
        half_bw    = np.radians(beam_width_deg / 2.0)
        scale      = 8 * small_rad

        passes = (active_intensity >= act_threshold
                  and q_factor       >= q_threshold
                  and histogram_count >= hist_threshold)

        if passes:
            # ── centre-line ray ───────────────────────────────────────
            dx = np.cos(center_rad)
            dy = np.sin(center_rad)
            self.azimuth_lines[name].set_data(
                [x0, x0 + scale * dx],
                [y0, y0 + scale * dy],
            )

            # ── beam wedge patch ──────────────────────────────────────
            verts = _beam_wedge_vertices(x0, y0, center_rad, half_bw, length=scale)
            self.beam_patches[name].set_xy(verts)
            self.beam_patches[name].set_visible(True)

            # ── add beam to heatmap accumulator ───────────────────────
            beam = _beam_intensity_map(
                x0, y0, center_rad, half_bw, _grid_x, _grid_y
            )
            self._heat_accum += beam.astype(np.float32) * 0.15   # inject strength

            self._active_rays[name] = ((x0, y0), (dx, dy))
        else:
            self.azimuth_lines[name].set_data([], [])
            self.beam_patches[name].set_visible(False)
            self._active_rays.pop(name, None)

        self._update_heatmap_image()
        self._update_source_estimate()

    # ── heatmap helpers ───────────────────────────────────────────────

    def _decay_heatmap(self):
        """Exponential decay — time constant read from UI entry."""
        try:
            tc = float(self.time_const_entry.text())
            tc = max(tc, 0.1)
        except ValueError:
            tc = 5.0

        now = time.time()
        dt  = now - self._last_heat_t
        self._last_heat_t = now

        decay = np.exp(-dt / tc)
        self._heat_accum *= decay

    def _update_heatmap_image(self):
        """Convert accumulator → RGBA image and push to imshow."""
        raw = self._heat_accum

        # soft-clip: tanh keeps values in (0,1) without hard clipping
        norm = np.tanh(raw)          # shape (N, N)

        # Build RGBA:  use a hot-fire colormap (black → red → yellow → white)
        r = np.clip(norm * 2.0,        0, 1)
        g = np.clip(norm * 2.0 - 0.8,  0, 1)
        b = np.clip(norm * 2.0 - 1.6,  0, 1)
        a = np.clip(norm * 1.4,        0, 1)   # alpha ramps up with intensity

        rgba = np.stack([r, g, b, a], axis=-1).astype(np.float32)
        self.heatmap_img.set_data(rgba)

    # ── triangulation ────────────────────────────────────────────────

    def _update_source_estimate(self):
        rays = list(self._active_rays.values())
        if len(rays) < _MIN_LINES_FOR_ESTIMATE:
            self._clear_source_estimate()
            if len(rays) == 1:
                self.source_status.set_text("Waiting for 2nd device…")
            return

        origins    = [r[0] for r in rays]
        directions = [r[1] for r in rays]
        pt = _least_squares_intersection(origins, directions)
        if pt is None:
            self.source_status.set_text("Parallel lines — no intersection")
            self._clear_source_estimate()
            return

        # residuals
        residuals = []
        for (ox, oy), (dx, dy) in zip(origins, directions):
            ex, ey = pt[0] - ox, pt[1] - oy
            perp   = abs(ex * (-dy) + ey * dx)
            residuals.append(perp)
        mean_res = float(np.mean(residuals))

        confidence = ("high" if mean_res < 0.3
                      else "medium" if mean_res < 0.7
                      else "low")

        self.source_point.set_data([pt[0]], [pt[1]])
        self.source_ring.center  = (pt[0], pt[1])
        self.source_ring.radius  = max(mean_res, 0.05)
        self.source_ring.set_visible(True)
        self.source_status.set_text(
            f"Estimated from {len(rays)} devices  |  "
            f"spread: {mean_res:.2f} m  |  {confidence} confidence"
        )

    def _clear_source_estimate(self):
        self.source_point.set_data([], [])
        self.source_ring.set_visible(False)
        self.source_status.set_text("")
