# ui_widgets/create_sound_loc_plot.py
import numpy as np
from PyQt6.QtWidgets import (QVBoxLayout, QHBoxLayout, QSizePolicy,
                              QWidget, QLabel, QLineEdit, QPushButton)
from PyQt6.QtGui import QFont
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.ticker import MultipleLocator
from matplotlib.patches import Circle, Polygon as MplPolygon

from ui_widgets.dev_style import dev_color, dev_marker

small_rad   = 1
HEAT_GRID_N = 150       # heatmap grid resolution (150×150)
PLOT_RANGE  = 3.0       # plot spans -PLOT_RANGE … +PLOT_RANGE

# fixed corner positions: top-left, top-right, bottom-right, bottom-left
dev_x_pos  = [-1,  1,  1, -1]
dev_y_pos  = [ 1,  1, -1, -1]
dev_labels = [(-0.35,  0.20),
              ( 0.10,  0.20),
              ( 0.10, -0.30),
              (-0.35, -0.30)]

_BTN_STYLE        = "background-color: gray;  color: white; font-weight: bold; font-size: 13px;"
_TITLE_IDLE       = "Sound Localization"
_TITLE_DRAG_MODE  = "Sound Localization  [drag nodes to reposition]"
_DRAG_SNAP        = 0.35    # data-unit radius to pick up a node


def createSoundLoc(tab, dev_names, sound_loc_btn, log_data_btn):

    figure = Figure()
    canvas = FigureCanvas(figure)
    canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    layout = QVBoxLayout(tab)
    layout.setContentsMargins(0, 0, 0, 0)

    # ── threshold / control bar ────────────────────────────────────────
    top_widget = QWidget()
    top_widget.setStyleSheet("background-color: lightgray;")
    top_layout = QHBoxLayout(top_widget)

    bold_font = QFont()
    bold_font.setBold(True)

    def _labeled_entry(label_text, default_val):
        lbl = QLabel(label_text)
        lbl.setFont(bold_font)
        entry = QLineEdit(default_val)
        entry.setFixedWidth(75)
        entry.setStyleSheet("QLineEdit { background-color: white; }")
        return lbl, entry

    ai_lbl, act_int_thresh_entry = _labeled_entry("Active Intensity\n   Threshold", "20")
    q_lbl,  q_thresh_entry       = _labeled_entry("Q-Factor\nThreshold",             "2")
    h_lbl,  hist_thresh_entry    = _labeled_entry("Histogram\nThreshold",            "5")
    bw_lbl, beam_width_entry     = _labeled_entry("Beam Width\n    (deg)",           "30")
    tc_lbl, time_const_entry     = _labeled_entry("Time Const\n      (s)",           "5")

    for lbl, entry in [(ai_lbl, act_int_thresh_entry),
                       (q_lbl,  q_thresh_entry),
                       (h_lbl,  hist_thresh_entry),
                       (bw_lbl, beam_width_entry),
                       (tc_lbl, time_const_entry)]:
        top_layout.addWidget(lbl)
        top_layout.addWidget(entry)
        top_layout.addSpacing(20)

    # color-coded device chips
    sep = QLabel("│")
    sep.setStyleSheet("color: #888888;")
    top_layout.addWidget(sep)
    top_layout.addSpacing(10)
    for i, name in enumerate(dev_names):
        chip = QLabel(f"● {name}")
        chip.setFont(bold_font)
        chip.setStyleSheet(f"color: {dev_color(i)};")
        top_layout.addWidget(chip)
        top_layout.addSpacing(12)

    top_layout.addStretch()
    layout.addWidget(top_widget)
    layout.addWidget(canvas)

    # ── axes ──────────────────────────────────────────────────────────
    ax = figure.add_subplot(111)
    ax.set_aspect("equal", adjustable="box")

    theta = np.linspace(0, 2 * np.pi, 360)

    # ── heatmap layer (zorder=1, lowest) ──────────────────────────────
    heat_init = np.zeros((HEAT_GRID_N, HEAT_GRID_N, 4), dtype=np.float32)
    heatmap_img = ax.imshow(
        heat_init,
        extent=[-PLOT_RANGE, PLOT_RANGE, -PLOT_RANGE, PLOT_RANGE],
        origin="lower",
        aspect="equal",
        zorder=1,
        interpolation="bilinear",
    )

    # outer dashed reference circle
    ax.plot(2.6 * np.cos(theta), 2.6 * np.sin(theta),
            color="#cccccc", linewidth=0.6, linestyle="--", zorder=0)

    # compass rose
    for angle_deg, label, ha, va in [
        ( 90, "N", "center", "bottom"),
        (  0, "E", "left",   "center"),
        (270, "S", "center", "top"),
        (180, "W", "right",  "center"),
    ]:
        r = np.radians(angle_deg)
        ax.text(2.82 * np.cos(r), 2.82 * np.sin(r), label,
                ha=ha, va=va, fontsize=9, fontweight="bold", color="#999999")

    # ── beam wedge patches (zorder=2) ─────────────────────────────────
    beam_patches = {}
    for i, name in enumerate(dev_names):
        color = dev_color(i)
        patch = MplPolygon(
            np.zeros((3, 2)), closed=True,
            facecolor=color, alpha=0.13,
            edgecolor=color, linewidth=0.8,
            linestyle="--", zorder=2, visible=False,
        )
        ax.add_patch(patch)
        beam_patches[name] = patch

    # ── device artists ─────────────────────────────────────────────────
    azimuth_lines     = {}
    dev_positions     = {}
    dev_dots          = {}
    dev_label_texts   = {}
    dev_halos_dict    = {}
    dev_label_offsets = {}

    for i, name in enumerate(dev_names):
        color  = dev_color(i)
        marker = dev_marker(i)
        dx_off, dy_off = dev_labels[i]
        dev_label_offsets[name] = (dx_off, dy_off)

        # dot — use plot() so set_data() can reposition it
        dot, = ax.plot(dev_x_pos[i], dev_y_pos[i],
                       marker=marker, color=color, markersize=9,
                       linestyle="none", zorder=5)
        dev_dots[name] = dot

        # label
        lbl_txt = ax.text(dev_x_pos[i] + dx_off, dev_y_pos[i] + dy_off, name,
                          fontsize=8, fontweight="bold", color=color)
        dev_label_texts[name] = lbl_txt

        # halo circle
        halo = Circle((dev_x_pos[i], dev_y_pos[i]), small_rad,
                      fill=False, edgecolor=color, linewidth=0.9, alpha=0.30, zorder=3)
        ax.add_patch(halo)
        dev_halos_dict[name] = halo

        # azimuth centre-line ray
        line, = ax.plot([], [], "-", color=color, linewidth=1.6, alpha=0.95, zorder=4)
        azimuth_lines[name] = line
        dev_positions[name] = (dev_x_pos[i], dev_y_pos[i])

    # ── source estimate artists ────────────────────────────────────────
    source_point, = ax.plot([], [], "*", color="gold",
                            markersize=14, markeredgecolor="#b8860b",
                            markeredgewidth=0.6, zorder=10)

    source_ring = Circle((0, 0), 0.0, fill=True, facecolor="gold",
                         edgecolor="#b8860b", linewidth=0.8, alpha=0.20, zorder=9)
    source_ring.set_visible(False)
    ax.add_patch(source_ring)

    source_status = ax.text(0, -2.88, "", ha="center", va="bottom",
                            fontsize=8, color="#555555", style="italic")

    # ── grid / styling ────────────────────────────────────────────────
    ax.axhline(0, color="#dddddd", linewidth=0.7, zorder=0)
    ax.axvline(0, color="#dddddd", linewidth=0.7, zorder=0)
    ax.set_title(_TITLE_DRAG_MODE, fontsize=11, fontweight="bold", pad=8)
    ax.xaxis.set_major_locator(MultipleLocator(1))
    ax.yaxis.set_major_locator(MultipleLocator(1))
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.grid(True, color="#eeeeee", linewidth=0.5)
    ax.set_xlim(-PLOT_RANGE, PLOT_RANGE)
    ax.set_ylim(-PLOT_RANGE, PLOT_RANGE)
    for spine in ax.spines.values():
        spine.set_visible(False)

    canvas.draw()

    # ── button row ────────────────────────────────────────────────────
    reset_zoom_btn = QPushButton("RESET ZOOM")
    reset_zoom_btn.setFixedWidth(110)
    reset_zoom_btn.setFixedHeight(30)
    reset_zoom_btn.setStyleSheet(_BTN_STYLE)

    btn_row = QHBoxLayout()
    btn_row.addStretch()
    btn_row.addWidget(sound_loc_btn)
    btn_row.addSpacing(20)
    btn_row.addWidget(log_data_btn)
    btn_row.addSpacing(20)
    btn_row.addWidget(reset_zoom_btn)
    btn_row.addStretch()
    layout.addLayout(btn_row)

    # ── scroll zoom ───────────────────────────────────────────────────
    def _on_scroll(event):
        if event.inaxes != ax:
            return
        scale = 0.9 if event.button == "up" else 1.1
        ax.set_xlim([x * scale for x in ax.get_xlim()])
        ax.set_ylim([y * scale for y in ax.get_ylim()])
        canvas.draw_idle()

    canvas.mpl_connect("scroll_event", _on_scroll)

    # ── reset zoom ────────────────────────────────────────────────────
    def _on_reset_zoom():
        ax.set_xlim(-PLOT_RANGE, PLOT_RANGE)
        ax.set_ylim(-PLOT_RANGE, PLOT_RANGE)
        canvas.draw_idle()

    reset_zoom_btn.clicked.connect(_on_reset_zoom)

    # ── node drag ─────────────────────────────────────────────────────
    _drag = {'node': None, 'enabled': True}   # enabled by default (worker not running)

    def _pick_node(mx, my):
        """Return the name of the nearest device within snap radius, or None."""
        best, best_d = None, _DRAG_SNAP
        for name, (nx, ny) in dev_positions.items():
            d = np.hypot(mx - nx, my - ny)
            if d < best_d:
                best, best_d = name, d
        return best

    def _on_press(event):
        if not _drag['enabled'] or event.inaxes != ax:
            return
        _drag['node'] = _pick_node(event.xdata, event.ydata)

    def _on_motion(event):
        if _drag['node'] is None or event.inaxes != ax:
            return
        name = _drag['node']
        x, y = event.xdata, event.ydata

        # update shared position dict (worker reads this directly)
        dev_positions[name] = (x, y)

        # reposition dot
        dev_dots[name].set_data([x], [y])

        # reposition label
        dx_off, dy_off = dev_label_offsets[name]
        dev_label_texts[name].set_position((x + dx_off, y + dy_off))

        # reposition halo
        dev_halos_dict[name].set_center((x, y))

        canvas.draw_idle()

    def _on_release(event):
        _drag['node'] = None

    canvas.mpl_connect("button_press_event",   _on_press)
    canvas.mpl_connect("motion_notify_event",  _on_motion)
    canvas.mpl_connect("button_release_event", _on_release)

    # ── drag enable / disable (called from main.py) ───────────────────
    def enable_drag():
        _drag['enabled'] = True
        ax.set_title(_TITLE_DRAG_MODE, fontsize=11, fontweight="bold", pad=8)
        canvas.draw_idle()

    def disable_drag():
        _drag['enabled'] = False
        _drag['node'] = None
        ax.set_title(_TITLE_IDLE, fontsize=11, fontweight="bold", pad=8)
        canvas.draw_idle()

    return (azimuth_lines, dev_positions, canvas,
            act_int_thresh_entry, q_thresh_entry, hist_thresh_entry,
            source_point, source_ring, source_status,
            heatmap_img, beam_patches,
            beam_width_entry, time_const_entry,
            enable_drag, disable_drag)
