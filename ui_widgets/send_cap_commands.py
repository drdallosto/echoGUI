#send_cap_commands.py

import struct
import time
from pymavlink import mavutil
from PyQt6.QtCore import QObject, pyqtSignal


def sendCapCommand(connection, param_name):
    param_type  = mavutil.mavlink.MAV_PARAM_TYPE_INT32
    bytes_value = struct.pack('i', 1)
    param_value = struct.unpack('f', bytes_value)[0]

    #print(f"{param_name}")

    connection.mav.param_set_send(
        connection.target_system,
        connection.target_component,
        param_name.encode('utf-8'),
        param_value,
        param_type)

    print(f"\n{param_name} sent\n")


class CapWorker(QObject):
    finished = pyqtSignal()

    def __init__(self, connections, timer):
        super().__init__()
        self.connections = connections
        self.timer       = timer

    def run(self):
        for conn in self.connections.values():
            sendCapCommand(conn, 'AVS_SEND_CAP_ON')
        time.sleep(self.timer)
        for conn in self.connections.values():
            sendCapCommand(conn, 'AVS_SEND_CAP_OFF')
        self.finished.emit()


class CapOffWorker(QObject):
    finished = pyqtSignal()

    def __init__(self, connections):
        super().__init__()
        self.connections = connections

    def run(self):
        for conn in self.connections.values():
            sendCapCommand(conn, 'AVS_SEND_CAP_OFF')
        self.finished.emit()
