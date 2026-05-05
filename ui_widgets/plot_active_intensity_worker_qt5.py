#plot_active_intensity_worker_qt5.py
from pymavlink import mavutil
from ui_widgets.send_msg_id_stream import sendMsgIdStream
from collections import deque
from PyQt5.QtCore import QObject, QThread, pyqtSignal, pyqtSlot
import numpy as np
import os, csv, datetime, time


max_data = 100
window = 10

class PlotActiveIntensityWorker(QObject):

    progress    = pyqtSignal(str)
    error       = pyqtSignal(str)
    finished    = pyqtSignal()
    logStopped  = pyqtSignal()
    dataReady   = pyqtSignal(str, int, int, float, float, int, float)
    plotUpdated = pyqtSignal()

    def __init__(self, getDevConns, act_int_lines, azm_lines, intAx, azAx, intCanvas,
                 act_int_thresh_entry, q_thresh_entry, hist_thresh_entry, log_data_entry,
                 cap_btn, log_csv_data_btn, log_raw_data_btn):
        super().__init__()
        self.connection = getDevConns
        self.running    = True

        self.act_int_lines = act_int_lines
        self.azm_lines     = azm_lines
        self.azAx          = azAx
        self.intAx         = intAx
        self.intCanvas     = intCanvas

        self.threshAct  = int(act_int_thresh_entry.text())
        self.threshQ    = int(q_thresh_entry.text())
        self.threshHst  = int(hist_thresh_entry.text())

        self.logDataTimer = int(log_data_entry.text())

        self.cap_btn          = cap_btn
        self.log_csv_data_btn = log_csv_data_btn
        self.log_raw_data_btn = log_raw_data_btn

        self._logging       = False
        self._csv_file      = None
        self._csv_writer    = None
        self._log_end_timer = None

        self.tt   = {name: deque(maxlen=max_data) for name in self.connection}
        self.actv = {name: deque(maxlen=max_data) for name in self.connection}
        self.az   = {name: deque(maxlen=max_data) for name in self.connection}
        self.hist = {name: deque(maxlen=max_data) for name in self.connection}
        self.qfct = {name: deque(maxlen=max_data) for name in self.connection}

        self.act_start_time = None

        self.dataReady.connect(self.plotActiveIntensity)

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

    def start_logging(self, end_timer):
        dirName = 'sensor_avs_logging_data'
        os.makedirs(dirName, exist_ok=True)
        timestamp_str = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        csv_path = os.path.join(dirName, f"{timestamp_str}.csv")
        fieldnames = ['device', 'node_id', 'time_utc_usec', 'active_intensity', 'q_factor',
                      'histogram_count', 'azimuth', 'elevation', 'yaw', 'pitch', 'roll',
                      'north', 'east', 'down']
        self._csv_file      = open(csv_path, mode='a', newline='')
        self._csv_writer    = csv.DictWriter(self._csv_file, fieldnames=fieldnames)
        self._csv_writer.writeheader()
        self._log_end_timer = end_timer
        self._logging       = True
        self.progress.emit(f'writing to csv: {csv_path}')

    def stop_logging(self):
        self._logging = False
        if self._csv_file:
            self._csv_file.close()
            self._csv_file   = None
            self._csv_writer = None
            self.progress.emit('stopped logging')

    def getActiveIntensity(self):
        message_id = 297
        for name, connection in self.connection.items():
            self.progress.emit(f"--- streaming active intensity for {name} ---")
            sendMsgIdStream(connection, message_id)

        while self.running:
            changed = False
            for name, connection in self.connection.items():
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False)

                if msg:
                    self.dataReady.emit(name, msg.time_utc_usec, msg.device_id, msg.active_intensity, msg.azimuth_deg, msg.histogram_count, msg.q_factor)
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
                                'down':             msg.down
                            })
                            self._csv_file.flush()
                        else:
                            self.stop_logging()
                            self.logStopped.emit()

            if changed:
                self.plotUpdated.emit()

    @pyqtSlot(str, int, int, float, float, int, float)
    def plotActiveIntensity(self, name, t, id, act, az, hist_count, q_factor):

        now = time.time()
        if self.act_start_time is None:
            self.act_start_time = now

        t_elapsed = now - self.act_start_time

        self.tt[name].append(t_elapsed)
        self.actv[name].append(act)
        self.az[name].append(az)
        self.hist[name].append(hist_count)
        self.qfct[name].append(q_factor)

        self.act_int_lines[name].set_data(np.array(self.tt[name]), np.array(self.actv[name]))

        azThresh = np.array(self.az[name], dtype=float)
        azThresh[np.array(self.actv[name]) < self.threshAct] = np.nan
        azThresh[np.array(self.hist[name]) < self.threshHst] = np.nan
        azThresh[np.array(self.qfct[name]) < self.threshQ]   = np.nan

        self.azm_lines[name].set_data(np.array(self.tt[name]), azThresh)

        all_times = [self.tt[n][-1] for n in self.connection if self.tt[n]]
        curr_time = max(all_times) if all_times else 0

        if curr_time <= window:
            t_min = 0
            t_max = window
        else:
            t_min = curr_time - window
            t_max = curr_time + 1

        self.intAx.set_xlim(t_min, t_max)
        self.azAx.set_xlim(t_min, t_max)
