#plot_localization_worker_qt5.py
from ui_widgets.send_msg_id_stream import sendMsgIdStream
from ui_widgets.create_sound_loc_plot_qt5 import small_rad
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot
import numpy as np
import os, csv, datetime, time


class PlotLocalizationWorker(QObject):

    progress   = pyqtSignal(str)
    error      = pyqtSignal(str)
    finished   = pyqtSignal()
    dataReady  = pyqtSignal(str, float, float, float, float, float)
    logStopped = pyqtSignal()

    def __init__(self, getDevConns, azimuth_lines, dev_positions, canvas,
                 act_int_thresh_entry, q_thresh_entry, hist_thresh_entry):
        super().__init__()
        self.connection           = getDevConns
        self.azimuth_lines        = azimuth_lines
        self.dev_positions        = dev_positions
        self.canvas               = canvas
        self.act_int_thresh_entry = act_int_thresh_entry
        self.q_thresh_entry       = q_thresh_entry
        self.hist_thresh_entry    = hist_thresh_entry
        self.running              = True
        self._logging             = False
        self._csv_file            = None
        self._csv_writer          = None
        self._log_end_timer       = None

        self.dataReady.connect(self.plotAzimuth)

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
        self.canvas.draw_idle()

    def start_logging(self, end_timer):
        dirName = 'sensor_avs_logging_data'
        os.makedirs(dirName, exist_ok=True)
        timestamp_str = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        csv_path = os.path.join(dirName, f"{timestamp_str}.csv")
        fieldnames = ['device', 'node_id', 'time_utc_usec', 'active_intensity', 'q_factor',
                      'histogram_count', 'azimuth', 'elevation', 'yaw', 'pitch', 'roll',
                      'north', 'east', 'down']
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

    def getAzimuth(self):
        message_id = 297
        for name, connection in self.connection.items():
            self.progress.emit(f"--- streaming azimuth for {name} ---")
            sendMsgIdStream(connection, message_id)

        while self.running:
            changed = False
            for name, connection in self.connection.items():
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False, timeout=0.1)
                if msg:
                    self.dataReady.emit(name, float(msg.azimuth_deg), float(msg.active_intensity), float(msg.yaw), float(msg.q_factor), float(msg.histogram_count))
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
                self.canvas.draw_idle()

    @pyqtSlot(str, float, float, float, float, float)
    def plotAzimuth(self, name, azimuth_deg, active_intensity, yaw, q_factor, histogram_count):
        if name not in self.azimuth_lines:
            return

        try:
            act_threshold  = int(self.act_int_thresh_entry.text())
            q_threshold    = float(self.q_thresh_entry.text())
            hist_threshold = float(self.hist_thresh_entry.text())
        except ValueError:
            return

        scale_lines = 8
        if active_intensity >= act_threshold and q_factor >= q_threshold and histogram_count >= hist_threshold:
            x0, y0 = self.dev_positions[name]
            rad = np.radians((90 - azimuth_deg))
            x = x0 + scale_lines * small_rad * np.cos(rad)
            y = y0 + scale_lines * small_rad * np.sin(rad)
            self.azimuth_lines[name].set_data([x0, x], [y0, y])
        else:
            self.azimuth_lines[name].set_data([], [])
