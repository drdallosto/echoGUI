#parametersGUI.py

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

from ui_widgets.param_fetch_worker import ParamFetchWorker


# or subclass QMainWindow
class MainWindow(QWidget): # subclass QWidget to create a custom window for our app
    def __init__(self): # self is the instance of the class, __init__ is the constructor method that initializes the object
        super().__init__() #
 
        self.setWindowTitle("PARAMETERS")
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

        first_name = next(iter(self.getDevConns.keys()))
        first_conn = self.getDevConns[first_name]
        while first_conn.recv_match(blocking=False) is not None:
            pass
        getParams(first_conn, all_params, self.storeHapParams, dev_name=first_name)
        self.updateHapParams, self.timerEntry, self.dev_combo = displayParams(self.tab1,
                                                              self.storeHapParams,
                                                              hap_description,
                                                              self.update_param_btn,
                                                              self.log_data_btn,
                                                              self.sync_time_btn,
                                                              list(self.getDevConns.keys())) 

        self.dev_combo.currentIndexChanged.connect(self.onDeviceChanged)
                                                             
    def get_available_ports(self):
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            if port.description() == "Silicon Labs CP210x USB to UART Bridge Silicon Labs" or "ARK FPV.x ARK" or "Silicon Labs CP210x USB to UART Bridge" or "CP2102 USB to UART Bridge Controller":
                self.portList.append(port.portName())
                # print(port.portName)
                # print(port.description())
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
        self.tabs.addTab(self.tab1, "PARAMETERS")

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

    def onDeviceChanged(self):
        selected = self.dev_combo.currentText()
        conn = self.getDevConns[selected]

        self.dev_combo.setEnabled(False)

        self.param_fetch_thread = QThread()
        self.param_fetch_worker = ParamFetchWorker(conn, all_params, selected)
        self.param_fetch_worker.moveToThread(self.param_fetch_thread)
        self.param_fetch_thread.started.connect(self.param_fetch_worker.run)
        self.param_fetch_worker.finished.connect(self.param_fetch_thread.quit)
        self.param_fetch_worker.finished.connect(self.applyParams)
        self.param_fetch_thread.start()

    def applyParams(self, new_params, dev_name):
        # discard result if user switched device again before fetch completed
        if dev_name != self.dev_combo.currentText():
            self.dev_combo.setEnabled(True)
            return
        for name, entry in self.updateHapParams.items():
            if name in new_params:
                entry.setText(str(new_params[name]))
        self.dev_combo.setEnabled(True)

    def onUpdateParamsClicked(self):
        selected = self.dev_combo.currentText()
        conn = self.getDevConns[selected]
        sendUpdatedParams(conn, self.updateHapParams)

    def onSyncTimeClicked(self):
        syncTimeAtStart(self.getDevConns)
      
    def onLogDataClicked(self):
        self.end_timer = setTimer(self.timerEntry)
        self.setup_log_data_thread()

if __name__ == "__main__":
    app = QApplication(sys.argv) # only need one QApplication instance 
    window = MainWindow() 
    window.show()
    sys.exit(app.exec())