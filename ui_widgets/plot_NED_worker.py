#plot_NED_worker.py
from pymavlink import mavutil
from ui_widgets.send_msg_id_stream import sendMsgIdStream
from collections import deque
from ui_widgets.create_act_int_plot import createActIntPlot
from PyQt6.QtCore import QObject, QThread, pyqtSignal,pyqtSlot
import numpy as np



class PlotNEDWorker(QObject):

    ''' Worker class to plot the trajectory using a separate thread. Multiple devices can be plugged in
        and plotted simultaneously'''

    progress = pyqtSignal(str) # signal to send progress updates to the main thread
    error    = pyqtSignal(str)
    finished = pyqtSignal()
    ned_dataReady  = pyqtSignal(str,float, float, float, int)  # emits: (north,east,down,t)

    def __init__(self, getDevconns, ned_lines, axNED, canvasNED):
        super().__init__()
        self.connection = getDevconns
        self.running = True 

        self.ned_lines  = ned_lines
        self.axNED     = axNED
        self.canvasNED = canvasNED

        # data storage 
        max_data = 2000
        self.north_data = {name: deque(maxlen=max_data) for name in self.connection}
        self.east_data  = {name: deque(maxlen=max_data) for name in self.connection}
        self.down_data  = {name: deque(maxlen=max_data) for name in self.connection}

        # connect signal to plot slot
        self.ned_dataReady.connect(self.plotNED)

    def run(self):
        try:
            self.getNED_data()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    def stop(self):
        self.running = False  # call this to stop the loop

         # clear old data
        for name in self.connection:
            self.north_data[name].clear()
            self.east_data[name].clear()
            self.down_data[name].clear()  
            self.ned_lines[name].set_data([], [])
            self.ned_lines[name].set_3d_properties([]) 
   

    def getNED_data(self):
        connection = self.connection

        # ------ start MAVLink stream ------
        message_id = 297
        for name, connection in self.connection.items():
            self.progress.emit('')
            self.progress.emit(f"--- streaming NED for {name} ---")
            self.progress.emit('')
            sendMsgIdStream(connection, message_id)
        
        "data acquisition thread"
        " get NED data "
        
        # if not connection:
        #     return
        
        while self.running:
            changed = False
            for name, connection in self.connection.items():
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False, timeout=0.1)

                if msg:
                    self.ned_dataReady.emit(name, msg.north, msg.east, msg.down, msg.time_utc_usec)
                    changed = True

            if changed:
                self.canvasNED.draw_idle()

    @pyqtSlot(str,float, float, float, int) 
    def plotNED(self,name,north,east,down,t):

        self.north_data[name].append(north)
        self.east_data[name].append(east)
        self.down_data[name].append(down)

        self.ned_lines[name].set_data(self.north_data[name], self.east_data[name])
        self.ned_lines[name].set_3d_properties(self.down_data[name])

        # update axis limits across all drones
        all_north = []
        for n in self.connection:
            for v in self.north_data[n]:
                all_north.append(v)

        all_east = []
        for n in self.connection:
            for v in self.east_data[n]:
                all_east.append(v)

        all_down = []
        for n in self.connection:
            for v in self.down_data[n]:
                all_down.append(v)

        # manually set limits based on current data
        if len(all_north) > 1:
            self.axNED.set_xlim(min(all_north), max(all_north))
            self.axNED.set_ylim(min(all_east), max(all_east))
            self.axNED.set_zlim(min(all_down), max(all_down))