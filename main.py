#main.py

import sys
from PyQt6.QtWidgets import QMainWindow, QApplication, QWidget, QHBoxLayout, QTabWidget, QPushButton, QVBoxLayout
from PyQt6.QtSerialPort import QSerialPortInfo
from PyQt6.QtCore import Qt, QSize, QObject, QThread, pyqtSignal
from pymavlink import mavutil

from parameters import all_params, hap_description, avs_description
from get_params import getParams
from display_params import displayParams
from update_params import sendUpdatedParams
from stop_sensor_avs_streams import disableStreams

from set_sync_time import set_timer #, sync_time, log_data

from sync_time import sync_time

from log_data_worker import LogDataWorker


# or subclass QMainWindow 
class MainWindow(QWidget): # subclass QWidget to create a custom window for our app
    def __init__(self): # self is the instance of the class, __init__ is the constructor method that initializes the object
        super().__init__() #
 
        self.setWindowTitle("ECHO")
        #self.showMaximized() 
        self.setFixedSize(QSize(1150, 975))

        # w/ QMainWindow, 
        #self.central_widget = QWidget(self) #
        #self.setCentralWidget(self.central_widget) 

        self.portList = []  
        self.storeHapParams = {} #dictionary 
        self.storeAvsParams = {} 
        self.updateHapParams = {}
        self.updateAvsParams = {}

        self.get_available_ports()
        self.setupUI()

        # Connect to the flight controller
        self.connection = mavutil.mavlink_connection(device=self.portList[0], baud=57600)
        self.connection.wait_heartbeat(timeout=8)
        print("Heartbeat received\n")

        getParams(self.connection, all_params, self.storeHapParams, self.storeAvsParams)
    
        self.updateHapParams, self.updateAvsParams, self.timerEntry = displayParams(self.tab1, self.storeHapParams, self.storeAvsParams, 
                                                                                    hap_description, avs_description, self.update_param_btn, 
                                                                                    self.log_data_btn, self.sync_time_btn) # pass the button instances to displayParams to connect them to their respective functions

        # self.getFPV_data()
        # sync_time(self.connection)
        # self.end_timer = set_timer(self.connection)
        # log_data(self.connection)

    

    def get_available_ports(self):
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            self.portList.append(port.portName())
        print("Available Serial Ports:", self.portList)


    def setupUI(self):
        self.layout_tabs = QVBoxLayout()
        
        self.tabs = QTabWidget()  
        self.tab1 = QWidget()
        self.tab2 = QWidget()

        self.tabs.addTab(self.tab1, "PARAMETERS")
        self.tabs.addTab(self.tab2, "VISUALS")

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

        self.layout_tabs.addWidget(self.tabs)
        self.setLayout(self.layout_tabs)

    def setup_log_data_thread(self):
       
        self.thread = QThread()  #Create a QThread object
        self.worker = LogDataWorker(self.connection, self.end_timer) #Create a worker object
        self.worker.moveToThread(self.thread) #Move worker to the thread

        # Connect signals and slots
        self.thread.started.connect(self.worker.run)
        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        self.worker.progress.connect(self.on_log_message)  # optional
        # self.worker.error.connect(self.on_log_error)    
    
        self.thread.start()  # Start the thread

    def on_log_message(self, msg: str):
        print(msg)  # or append to a QTextEdit

    # def on_log_error(self, err: str):
    #     print(f"[ERROR] {err}")

    def onUpdateParamsClicked(self):
        #self.update_param_btn.setStyleSheet("background-color: light gray; color: black;font-weight: bold;  font-size: 14px;")
        sendUpdatedParams(self.connection, self.updateHapParams, self.updateAvsParams)

    def onSyncTimeClicked(self):
        #disableStreams(self.connection) # stop sensor and avs streams before logging to avoid conflicts
        sync_time(self.connection)
      
    def onLogDataClicked(self):
        #disableStreams(self.connection) # stop sensor and avs streams before logging to avoid conflicts
        self.end_timer = set_timer(self.connection, self.timerEntry)  # store on self
        self.setup_log_data_thread()   

if __name__ == "__main__":
    app = QApplication(sys.argv) # only need one QApplication instance 
    window = MainWindow() 
    window.show()
    sys.exit(app.exec())