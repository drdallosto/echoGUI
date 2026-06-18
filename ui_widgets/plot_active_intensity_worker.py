# ui_widgets/plot_active_intensity_worker.py
from pymavlink import mavutil
from collections import deque
from PyQt6.QtCore import QObject, pyqtSignal, pyqtSlot
import numpy as np
import os, csv, datetime, time


max_data = 100
window   = 10   # rolling x-axis window (seconds)


class PlotActiveIntensityWorker(QObject):
    """Worker class to plot active intensity and azimuth in a separate thread."""

    progress    = pyqtSignal(str)
    error       = pyqtSignal(str)
    finished    = pyqtSignal()
    logStopped  = pyqtSignal()
    dataReady   = pyqtSignal(str, int, int, float, float, int, float)
    plotUpdated = pyqtSignal()

    def __init__(self, getDevConns,
                 act_int_lines, azm_lines,
                 intAx, azAx, intCanvas,
                 act_int_thresh_entry, q_thresh_entry, hist_thresh_entry,
                 log_data_entry,
                 cap_btn, log_csv_data_btn, cap_off_data_btn):
        super().__init__()
        self.connection = getDevConns
        self.running    = True

        # plot objects
        self.act_int_lines = act_int_lines
        self.azm_lines     = azm_lines
        self.azAx          = azAx
        self.intAx         = intAx
        self.intCanvas     = intCanvas

        # threshold entries
        self.act_int_thresh_entry = act_int_thresh_entry
        self.q_thresh_entry       = q_thresh_entry
        self.hist_thresh_entry    = hist_thresh_entry

        self.logDataTimer     = int(log_data_entry.text())
        self.cap_btn          = cap_btn
        self.log_csv_data_btn = log_csv_data_btn
        self.cap_off_data_btn = cap_off_data_btn

        self._logging       = False
        self._csv_file      = None
        self._csv_writer    = None
        self._log_end_timer = None

        # per-device rolling buffers
        self.tt   = {name: deque(maxlen=max_data) for name in self.connection}
        self.actv = {name: deque(maxlen=max_data) for name in self.connection}
        self.az   = {name: deque(maxlen=max_data) for name in self.connection}
        self.hist = {name: deque(maxlen=max_data) for name in self.connection}
        self.qfct = {name: deque(maxlen=max_data) for name in self.connection}

        self.act_start_time = None

        self.dataReady.connect(self.plotActiveIntensity)

    # ── lifecycle ─────────────────────────────────────────────────────

    def run(self):
        try:
            self.getActiveIntensity()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    def stop(self):
        self.running = False
        if self._logging:
            self.stop_logging()
        for name in self.connection:
            self.tt[name].clear()
            self.actv[name].clear()
            self.az[name].clear()
            self.act_int_lines[name].set_data([], [])
            self.azm_lines[name].set_data([], [])

    # ── logging ──────────────────────────────────────────────────────

    def start_logging(self, end_timer):
        dirName = 'sensor_avs_logging_data'
        os.makedirs(dirName, exist_ok=True)
        timestamp_str = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        csv_path = os.path.join(dirName, f"{timestamp_str}.csv")
        fieldnames = [
            'device', 'node_id', 'time_utc_usec', 'active_intensity', 'q_factor',
            'histogram_count', 'azimuth', 'elevation', 'yaw', 'pitch', 'roll',
            'north', 'east', 'down',
        ]
        self._csv_file   = open(csv_path, mode='a', newline='')
        self._csv_writer = csv.DictWriter(self._csv_file, fieldnames=fieldnames)
        self._csv_writer.writeheader()
        self._log_end_timer = end_timer
        self._logging = True
        self.progress.emit(f'writing to csv: {csv_path}')

    def stop_logging(self):
        self._logging = False
        if self._csv_file:
            self._csv_file.close()
            self._csv_file   = None
            self._csv_writer = None
            self.progress.emit('stopped logging')

    # ── MAVLink receive loop ──────────────────────────────────────────

    def getActiveIntensity(self):
        self.progress.emit('')
        self.progress.emit("--- sending message to stream active intensity ---")
        self.progress.emit('')

        message_id = 297
        self.streaming_devices = set()

        # step 1: drain stale messages
        for connection in self.connection.values():
            while connection.recv_match(blocking=False) is not None:
                pass

        # step 2: request streaming from all devices
        for connection in self.connection.values():
            cmd = connection.mav.command_long_encode(
                connection.target_system,
                connection.target_component,
                mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,
                0, message_id, 0, 0, 0, 0, 0, 0,
            )
            connection.mav.send(cmd)

        # step 3: collect ACKs
        for name, connection in self.connection.items():
            connection.recv_match(type='COMMAND_ACK', blocking=True, timeout=3)
            self.streaming_devices.add(name)
            self.progress.emit(f"--- streaming active intensity for {name} ---")

        self.progress.emit('')

        # step 4: data loop — drain ALL buffered messages per device each iteration
        while self.running:
            changed = False

            for name, connection in self.connection.items():
                # inner drain: keep reading until the buffer is empty
                while True:
                    msg = connection.recv_match(
                        type='SENSOR_AVS_LITE_EXT', blocking=False
                    )
                    if msg is None:
                        break

                    self.dataReady.emit(
                        name,
                        msg.time_utc_usec, msg.device_id,
                        msg.active_intensity, msg.azimuth_deg,
                        msg.histogram_count, msg.q_factor,
                    )
                    changed = True

                    if self._logging and self._csv_writer:
                        if time.time() < self._log_end_timer:
                            self._csv_writer.writerow({
                                'device':           name,
                                'node_id':          msg.device_id,
                                'time_utc_usec':    msg.time_utc_usec,
                                'active_intensity': msg.active_intensity,
                                'q_factor':         msg.q_factor,
                                'histogram_count':  msg.histogram_count,
                                'azimuth':          msg.azimuth_deg,
                                'elevation':        msg.elevation_deg,
                                'yaw':              msg.yaw,
                                'pitch':            msg.pitch,
                                'roll':             msg.roll,
                                'north':            msg.north,
                                'east':             msg.east,
                                'down':             msg.down,
                            })
                            self._csv_file.flush()
                        else:
                            self.stop_logging()
                            self.logStopped.emit()

            if changed:
                self.plotUpdated.emit()
            else:
                # no data arrived — yield CPU rather than busy-spinning
                time.sleep(0.001)

    # ── plot slot ─────────────────────────────────────────────────────

    @pyqtSlot(str, int, int, float, float, int, float)
    def plotActiveIntensity(self, name, t, dev_id, act, az, hist_count, q_factor):
        now = time.time()
        if self.act_start_time is None:
            self.act_start_time = now
        t_elapsed = now - self.act_start_time

        self.tt[name].append(t_elapsed)
        self.actv[name].append(act)
        self.az[name].append(az)
        self.hist[name].append(hist_count)
        self.qfct[name].append(q_factor)

        # active intensity line — always plotted
        self.act_int_lines[name].set_data(
            np.array(self.tt[name]), np.array(self.actv[name])
        )

        # azimuth line — NaN out points that don't pass thresholds
        azThresh = np.array(self.az[name], dtype=float)
        try:
            threshAct = int(self.act_int_thresh_entry.text())
            threshQ   = int(self.q_thresh_entry.text())
            threshHst = int(self.hist_thresh_entry.text())
        except ValueError:
            return

        azThresh[np.array(self.actv[name]) < threshAct] = np.nan
        azThresh[np.array(self.hist[name]) < threshHst] = np.nan
        azThresh[np.array(self.qfct[name]) < threshQ]   = np.nan

        self.azm_lines[name].set_data(np.array(self.tt[name]), azThresh)

        # sliding x-axis window
        all_times = [self.tt[n][-1] for n in self.connection if self.tt[n]]
        curr_time = max(all_times) if all_times else 0

        if curr_time <= window:
            t_min, t_max = 0, window
        else:
            t_min = curr_time - window
            t_max = curr_time + 1

        self.intAx.set_xlim(t_min, t_max)
        self.azAx.set_xlim(t_min, t_max)
