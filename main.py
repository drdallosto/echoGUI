#main.py

import sys
from PyQt6.QtWidgets import QMainWindow, QApplication, QWidget, QHBoxLayout, QTabWidget, QPushButton, QVBoxLayout
from PyQt6.QtSerialPort import QSerialPortInfo
from PyQt6.QtCore import Qt, QSize, QObject, QThread, pyqtSignal, QTimer
from pymavlink import mavutil

from ui_widgets.parameters import all_params, hap_description #, avs_description
from ui_widgets.get_params import getParams
from ui_widgets.display_params import displayParams
from ui_widgets.send_updated_params import sendUpdatedParams
from ui_widgets.stop_sensor_avs_streams import disableStreams

from ui_widgets.set_sync_time import setTimer #, sync_time, log_data
from ui_widgets.sync_time_at_start import syncTimeAtStart
from ui_widgets.log_data_worker import LogDataWorker
from ui_widgets.plot_active_intensity_worker import PlotActiveIntensityWorker

from ui_widgets.create_act_int_plot import createActIntPlot
from ui_widgets.create_NED_plot import createNEDPlot
from ui_widgets.plot_NED_worker import PlotNEDWorker
from ui_widgets.create_sound_loc_plot import createSoundLoc
from ui_widgets.plot_localization_worker import PlotLocalizationWorker

# or subclass QMainWindow 
class MainWindow(QWidget): # subclass QWidget to create a custom window for our app
    def __init__(self): # self is the instance of the class, __init__ is the constructor method that initializes the object
        super().__init__() #
 
        self.setWindowTitle("ECHO")
        #self.showMaximized() 
        self.setFixedSize(QSize(1000, 900 ))

        # w/ QMainWindow, 
        #self.central_widget = QWidget(self) #
        #self.setCentralWidget(self.central_widget) 

        self.portList           = []  
        self.port_map           = {}
        self.getDevConns        = {} # {'dev1': 'COM6', 'dev2': 'COM15'}
        self.storeHapParams     = {} 
        # self.storeAvsParams     = {} 
        self.updateHapParams    = {}
        # self.updateAvsParams    = {}

        self.get_available_ports()
        self.get_connected()
        self.setupUI()

        # # Connect to the flight controller
        # self.connection = mavutil.mavlink_connection(device=self.portList[0], baud=57600)
        # self.connection.wait_heartbeat(timeout=8)
        # print("Heartbeat received\n")

        first_conn = next(iter(self.getDevConns.values())) #gets first connection without needing to know its key name
        getParams(first_conn, all_params, self.storeHapParams) #, self.storeAvsParams)
        self.updateHapParams, self.timerEntry, self.dev_combo = displayParams(self.tab1,
                                                              self.storeHapParams,
                                                              hap_description,
                                                              self.update_param_btn,
                                                              self.log_data_btn,
                                                              self.sync_time_btn,
                                                              list(self.getDevConns.keys())) 
                                                             # pass the button instances to displayParams to connect them to their respective functions
        (self.act_int_lines,
        self.azm_lines,
        self.intAx,
        self.azAx,
        self.intCanvas,
        self.act_int_thresh_entry,
        self.q_thresh_entry,
        self.hist_thresh_entry) = createActIntPlot(self.tab2,self.plot_act_int_btn,list(self.getDevConns.keys()))
        
        self.ned_lines,self.axNED, self.canvasNED = createNEDPlot(self.tab3,self.plot_ned_btn,list(self.getDevConns.keys()))

        self.azimuth_lines, self.dev_positions, self.devLocCanvas, self.loc_act_int_thresh_entry = createSoundLoc(self.tab4, 
                                                                                                                  list(self.getDevConns.keys()), 
                                                                                                                  self.sound_loc_btn)

        QTimer.singleShot(0, lambda: syncTimeAtStart(self.getDevConns))  # sync time once gui is launched

    def get_available_ports(self):
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            self.portList.append(port.portName())
        print("Available Serial Ports:", self.portList)
        print('')


    def get_connected(self):
        for i, port in enumerate(self.portList):
            self.port_map.update({f"dev{i+1}": port })   #{'dev1': 'COM6', 'dev2': 'COM15'}
    
        for name,port in self.port_map.items():

            # Connect to the flight controller
            connection = mavutil.mavlink_connection(device=port, baud=57600)
            connection.wait_heartbeat(timeout=8)
            self.getDevConns[name]=connection
            print(f"Heartbeat received from {name}")

            disableStreams(connection)

    def setupUI(self):
        self.layout_tabs = QVBoxLayout()
        
        self.tabs = QTabWidget()  
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()
        self.tab4 = QWidget()

        self.tabs.addTab(self.tab1, "PARAMETERS")
        self.tabs.addTab(self.tab2, "VISUALS")
        self.tabs.addTab(self.tab3, "NED")
        self.tabs.addTab(self.tab4, "SOUND LOCALIZATION")

        self.update_param_btn = QPushButton("UPDATE PARAMS")
        self.update_param_btn.setFixedWidth(140)
        self.update_param_btn.setFixedHeight(30)
        self.update_param_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 14px;")
        self.update_param_btn.clicked.connect(self.onUpdateParamsClicked)

        self.log_data_btn = QPushButton("LOG DATA")
        self.log_data_btn.setFixedWidth(110)
        self.log_data_btn.setFixedHeight(30)
        self.log_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 14px;")
        self.log_data_btn.clicked.connect(self.onLogDataClicked)

        self.sync_time_btn = QPushButton("SYNC TIME")
        self.sync_time_btn.setFixedWidth(110)
        self.sync_time_btn.setFixedHeight(30)
        self.sync_time_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 14px;")
        self.sync_time_btn.clicked.connect(self.onSyncTimeClicked)
        
        self.plot_act_int_btn = QPushButton("PLOT ACTIVE INTENSITY")
        self.plot_act_int_btn.setFixedWidth(175)
        self.plot_act_int_btn.setFixedHeight(30)
        self.plot_act_int_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 14px;")
        self.plot_act_int_btn.clicked.connect(self.onPlotActIntClicked)

        self.plot_ned_btn = QPushButton("PLOT NED")
        self.plot_ned_btn.setFixedWidth(175)
        self.plot_ned_btn.setFixedHeight(30)
        self.plot_ned_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 14px;")
        self.plot_ned_btn.clicked.connect(self.onPlotNedClicked)

        self.sound_loc_btn = QPushButton("SOUND LOCALIZATION")
        self.sound_loc_btn.setFixedWidth(200)
        self.sound_loc_btn.setFixedHeight(30)
        self.sound_loc_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 14px;")
        self.sound_loc_btn.clicked.connect(self.onSoundLocClicked)

        self.layout_tabs.addWidget(self.tabs)
        self.setLayout(self.layout_tabs)

    def setup_log_data_thread(self):
       
        self.thread = QThread()
        first_conn = next(iter(self.getDevConns.values()))
        self.worker = LogDataWorker(first_conn, self.end_timer)
        self.worker.moveToThread(self.thread) #Move worker to the thread

        # Connect signals and slots
        self.thread.started.connect(self.worker.run)
        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        self.worker.progress.connect(self.on_log_message)  # optional
        # self.worker.error.connect(self.on_log_error)    
    
        self.thread.start()  # Start the thread

    def setup_plot_act_int_thread(self):
       
        self.act_worker = PlotActiveIntensityWorker(self.getDevConns,       # ALL drones in one worker
                                                    self.act_int_lines,  
                                                    self.azm_lines, 
                                                    self.intAx,  
                                                    self.azAx,  
                                                    self.intCanvas, 
                                                    self.act_int_thresh_entry, 
                                                    self.q_thresh_entry, 
                                                    self.hist_thresh_entry)
        self.act_thread = QThread()   
        self.act_worker.moveToThread(self.act_thread)
        self.act_thread.started.connect(self.act_worker.run)
        self.act_worker.finished.connect(self.act_thread.quit)
        self.act_worker.plotUpdated.connect(self.intCanvas.draw_idle)
        # self.act_worker.finished.connect(self.act_worker.deleteLater)
        # self.act_thread.finished.connect(self.act_thread.deleteLater)
        #self.act_worker.progress.connect(self.on_log_message)

        self.act_thread.start()
        self.plot_act_int_btn.setText("STOP")
        self.plot_act_int_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 14px;")


    def setup_ned_plot_thread(self):

        # one thread, one worker, and pass all connections
        self.ned_thread = QThread()
        self.ned_worker = PlotNEDWorker(
            self.getDevConns,       # ALL drones in one worker
            self.ned_lines,         # ALL lines
            self.axNED,
            self.canvasNED
        )
        self.ned_worker.moveToThread(self.ned_thread)
        self.ned_thread.started.connect(self.ned_worker.run)
        self.ned_worker.finished.connect(self.ned_thread.quit)
        # self.ned_worker.finished.connect(self.ned_worker.deleteLater)
        # self.ned_thread.finished.connect(self.ned_thread.deleteLater)

        self.ned_thread.start()
        self.plot_ned_btn.setText("STOP")
        self.plot_ned_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 14px;")


    def setup_localization_thread(self):
        self.loc_thread = QThread()
        self.loc_worker = PlotLocalizationWorker(self.getDevConns, 
                                                 self.azimuth_lines, 
                                                 self.dev_positions, 
                                                 self.devLocCanvas, 
                                                 self.loc_act_int_thresh_entry)
        self.loc_worker.moveToThread(self.loc_thread)
        self.loc_thread.started.connect(self.loc_worker.run)
        self.loc_worker.finished.connect(self.loc_thread.quit)
        
        self.loc_thread.start()
        self.sound_loc_btn.setText("STOP")
        self.sound_loc_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 14px;")

    def on_log_message(self, msg: str):
        print(msg)  # or append to a QTextEdit

    # def on_log_error(self, err: str):
    #     print(f"[ERROR] {err}")

    def onUpdateParamsClicked(self):
        first_conn = next(iter(self.getDevConns.values()))
        sendUpdatedParams(first_conn, self.updateHapParams) #, self.updateAvsParams)

    def onSyncTimeClicked(self):
        syncTimeAtStart(self.getDevConns)
      
    def onLogDataClicked(self):
        #disableStreams(self.connection) # stop sensor and avs streams before logging to avoid conflicts
        self.end_timer = setTimer(self.timerEntry)  # store on self
        self.setup_log_data_thread()   

    def onPlotActIntClicked(self):
        # #disableStreams(self.connection) # stop sensor and avs streams before logging to avoid conflicts

        if hasattr(self, 'act_worker') and self.act_thread.isRunning(): 
            # --- stop ---
            self.act_worker.stop()
            self.act_thread.quit()
            self.act_thread.wait()
            self.plot_act_int_btn.setText("PLOT ACTIVE INTENSITY")
            self.plot_act_int_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 14px;")
        else:
            # --- start ---
            self.setup_plot_act_int_thread()


    def onSoundLocClicked(self):
        if hasattr(self, 'loc_worker') and self.loc_thread.isRunning():
            self.loc_worker.stop()
            self.loc_thread.quit()
            self.loc_thread.wait()
            self.sound_loc_btn.setText("SOUND LOCALIZATION")
            self.sound_loc_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 14px;")
        else:
            self.setup_localization_thread()

    def onPlotNedClicked(self):
        if hasattr(self, 'ned_worker') and self.ned_thread.isRunning():
            self.ned_worker.stop()
            self.ned_thread.quit()
            self.ned_thread.wait()
            self.plot_ned_btn.setText("PLOT NED")
            self.plot_ned_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 14px;")
        else:
            self.setup_ned_plot_thread()

if __name__ == "__main__":
    app = QApplication(sys.argv) # only need one QApplication instance 
    window = MainWindow() 
    window.show()
    sys.exit(app.exec())