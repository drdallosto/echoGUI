#plot_NED_worker_qt5.py
from pymavlink import mavutil
from collections import deque
from PyQt5.QtCore import QObject, QThread, pyqtSignal, pyqtSlot
import numpy as np


class PlotNEDWorker(QObject):

    progress      = pyqtSignal(str)
    error         = pyqtSignal(str)
    finished      = pyqtSignal()
    ned_dataReady = pyqtSignal(str, float, float, float, int)

    def __init__(self, getDevconns, ned_lines, axNED, canvasNED):
        super().__init__()
        self.connection = getDevconns
        self.running    = True

        self.ned_lines  = ned_lines
        self.axNED      = axNED
        self.canvasNED  = canvasNED

        max_data = 2000
        self.north_data = {name: deque(maxlen=max_data) for name in self.connection}
        self.east_data  = {name: deque(maxlen=max_data) for name in self.connection}
        self.down_data  = {name: deque(maxlen=max_data) for name in self.connection}

        self.ned_dataReady.connect(self.plotNED)

    def run(self):
        try:
            self.getNED_data()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    def stop(self):
        self.running = False
        for name in self.connection:
            self.north_data[name].clear()
            self.east_data[name].clear()
            self.down_data[name].clear()
            self.ned_lines[name].set_data([], [])
            self.ned_lines[name].set_3d_properties([])

    def getNED_data(self):
        message_id = 297

        for name, connection in self.connection.items():
            while connection.recv_match(blocking=False) is not None:
                pass

        for name, connection in self.connection.items():
            cmd = connection.mav.command_long_encode(
                connection.target_system,
                connection.target_component,
                mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,
                0, message_id, 0, 0, 0, 0, 0, 0)
            connection.mav.send(cmd)

        for name, connection in self.connection.items():
            connection.recv_match(type='COMMAND_ACK', blocking=True, timeout=3)
            self.progress.emit(f"--- streaming NED for {name} ---")

        while self.running:
            changed = False
            for name, connection in self.connection.items():
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False, timeout=0.1)
                if msg:
                    self.ned_dataReady.emit(name, msg.north, msg.east, msg.down, msg.time_utc_usec)
                    changed = True
            if changed:
                self.canvasNED.draw_idle()

    @pyqtSlot(str, float, float, float, int)
    def plotNED(self, name, north, east, down, t):
        self.north_data[name].append(north)
        self.east_data[name].append(east)
        self.down_data[name].append(down)

        self.ned_lines[name].set_data(self.north_data[name], self.east_data[name])
        self.ned_lines[name].set_3d_properties(self.down_data[name])

        all_north = [v for n in self.connection for v in self.north_data[n]]
        all_east  = [v for n in self.connection for v in self.east_data[n]]
        all_down  = [v for n in self.connection for v in self.down_data[n]]

        if len(all_north) > 1:
            self.axNED.set_xlim(min(all_north), max(all_north))
            self.axNED.set_ylim(min(all_east),  max(all_east))
            self.axNED.set_zlim(min(all_down),  max(all_down))
