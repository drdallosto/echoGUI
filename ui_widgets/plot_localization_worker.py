#plot_localization_worker.py
from ui_widgets.send_msg_id_stream import sendMsgIdStream
from ui_widgets.create_sound_loc_plot import small_rad
from PyQt6.QtCore import QObject, pyqtSignal, pyqtSlot
import numpy as np


class PlotLocalizationWorker(QObject):

    progress  = pyqtSignal(str)
    error     = pyqtSignal(str)
    finished  = pyqtSignal()
    dataReady = pyqtSignal(str, float, float,float)  # (device_name, azimuth_deg, active_intensity)

    def __init__(self, getDevConns, azimuth_lines, dev_positions, canvas, act_int_thresh_entry):
        super().__init__()
        self.connection           = getDevConns
        self.azimuth_lines        = azimuth_lines
        self.dev_positions        = dev_positions
        self.canvas               = canvas
        self.act_int_thresh_entry = act_int_thresh_entry
        self.running              = True

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

        # for marker in self.azimuth_markers.values():
        #     marker.set_data([], [])
        for line in self.azimuth_lines.values():
            line.set_data([], [])
        self.canvas.draw_idle()

    def getAzimuth(self):
        message_id = 297
        for name, connection in self.connection.items():
            self.progress.emit(f"--- streaming azimuth for {name} ---")
            sendMsgIdStream(connection, message_id)

        while self.running:
            for name, connection in self.connection.items():
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False, timeout=0.1)
                if msg:
                    self.dataReady.emit(name, float(msg.azimuth_deg), float(msg.active_intensity), float(msg.yaw)) 

    @pyqtSlot(str, float, float,float)
    def plotAzimuth(self, name, azimuth_deg, active_intensity, yaw):
        if name not in self.azimuth_lines:
            return

        # so gui doesn't crash when typing the entry in 
        try:
            threshold = int(self.act_int_thresh_entry.text())
        except ValueError:
            return
        
        scale_lines = 8
        if active_intensity >= threshold:
            x0, y0 = self.dev_positions[name]
            #print(name,yaw,azimuth_deg)
            #azimuth_deg = 45
            rad = np.radians((90 - azimuth_deg)) # - yaw)
            x = x0 + scale_lines * small_rad * np.cos(rad)
            y = y0 + scale_lines * small_rad * np.sin(rad)      
            self.azimuth_lines[name].set_data([x0, x], [y0, y]) #draw line beetween points
        else:
            self.azimuth_lines[name].set_data([], [])

        self.canvas.draw_idle()
