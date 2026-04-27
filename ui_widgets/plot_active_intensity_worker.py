#plot_active_intensity_worker.py
from pymavlink import mavutil
from ui_widgets.send_msg_id_stream import sendMsgIdStream
from collections import deque
from ui_widgets.create_act_int_plot import createActIntPlot
from PyQt6.QtCore import QObject, QThread, pyqtSignal,pyqtSlot
import numpy as np


max_data = 100
window=10  # rolling x-axis window (seconds)

class PlotActiveIntensityWorker(QObject):

    ''' Worker class to plot active intensity and azimuth plots using a separate thread '''

    progress   = pyqtSignal(str)
    error      = pyqtSignal(str)
    finished   = pyqtSignal()
    dataReady  = pyqtSignal(str, int, int, float, float, int, float)
    plotUpdated = pyqtSignal()  # triggers canvas redraw on the main thread

    def __init__(self, getDevConns, act_int_lines, azm_lines,intAx, azAx, intCanvas, act_int_thresh_entry, q_thresh_entry, hist_thresh_entry):
        super().__init__()
        self.connection = getDevConns
        self.running = True 

        # plot objects from createActIntPlot
        self.act_int_lines = act_int_lines
        self.azm_lines     = azm_lines
        self.azAx          = azAx
        self.intAx         = intAx
        self.intCanvas     = intCanvas
 
        # thresholds
        self.threshAct  = int(act_int_thresh_entry.text())
        self.threshQ    = int(q_thresh_entry.text())
        self.threshHst  = int(hist_thresh_entry.text())

        self.tt   = {name: deque(maxlen=max_data) for name in self.connection}
        self.actv = {name: deque(maxlen=max_data) for name in self.connection}
        self.az   = {name: deque(maxlen=max_data) for name in self.connection}
        self.hist = {name: deque(maxlen=max_data) for name in self.connection}
        self.qfct = {name: deque(maxlen=max_data) for name in self.connection}
 
        self.act_start_time = None
 
        # connect signal to plot slot
        self.dataReady.connect(self.plotActiveIntensity)

    def run(self):
        try:
            self.getActiveIntensity()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    def stop(self):
        self.running = False  # call this to stop the loop

        # clear old data
        for name in self.connection:
            self.tt[name].clear()
            self.actv[name].clear()
            self.az[name].clear() #clear data for new run

            self.act_int_lines[name].set_data([], [])
            self.azm_lines[name].set_data([], [])  #clear line data
   

    #@pyqtSlot()
    def getActiveIntensity(self):
        connection = self.connection

        # ------ start MAVLink stream ------
        self.progress.emit('')
        self.progress.emit("--- sending message to stream active intensity---")  
        self.progress.emit('')

        message_id = 297 #message ID for SENSOR_AVS_LITE_EXT
        for name, connection in self.connection.items():
            self.progress.emit('')
            self.progress.emit(f"--- streaming ative intensity for {name} ---")
            self.progress.emit('')
            sendMsgIdStream(connection, message_id)
    
        "data acquisition thread"
        "get active intenisty data"
    
        # ---------- data acquisition loop ----------
        self.progress.emit('')

        while self.running: 
            for name, connection in self.connection.items():               
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False, timeout=0.1)   #blocking=False to cycle through all drones instead of blocking on one
                #print(msg)

                #check if msg arrived 
                if msg: 
                    # emit data via signal instead of putting it in a queue
                    self.dataReady.emit(name, msg.time_utc_usec, msg.device_id, msg.active_intensity, msg.azimuth_deg, msg.histogram_count, msg.q_factor)

    @pyqtSlot(str,int, int, float, float, int, float) 
    def plotActiveIntensity(self, name,t, id, act, az, hist_count, q_factor):

        # Set start time on first message
        if self.act_start_time is None:
            self.act_start_time = t

        # Convert to elapsed seconds
        t_elapsed = (t - self.act_start_time) / 1e6  # microseconds -> seconds

        self.tt[name].append(t_elapsed)
        self.actv[name].append(act)
        self.az[name].append(az)
        self.hist[name].append(hist_count)
        self.qfct[name].append(q_factor)

        # --- update line data --- 
        self.act_int_lines[name].set_data(np.array(self.tt[name]), np.array(self.actv[name]))

        azThresh = np.array(self.az[name], dtype=float)

        #print("THRESHOLDS: ", self.threshAct,self.threshHst, self.threshQ)

        # plot azimuth point when exceeding all 3 thresholds 
        azThresh[np.array(self.actv[name]) < self.threshAct] = np.nan
        azThresh[np.array(self.hist[name]) < self.threshHst] = np.nan
        azThresh[np.array(self.qfct[name]) < self.threshQ] = np.nan

        self.azm_lines[name].set_data(np.array(self.tt[name]), azThresh)

        # --- sliding x-axis window ---
        curr_time = (self.tt[name][-1] if self.tt[name] else 0) #,  # grab last (most recent) timestamp from node 1 (or 0 if no data)
        
        if curr_time <= window:
            t_min = 0
            t_max = window
        else:
            t_min = curr_time - window
            t_max = curr_time + 1

        self.intAx.set_xlim(t_min, t_max)
        self.azAx.set_xlim(t_min, t_max)

        self.plotUpdated.emit()  # redraws canvas on the main thread


#        # full redraw so axes update
#         self.intCanvas.draw_idle()    # OR
#        #self.intCanvas.draw()