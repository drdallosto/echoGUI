#main_qt5.py

import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QHBoxLayout, QTabWidget, QPushButton, QVBoxLayout
from PyQt5.QtSerialPort import QSerialPortInfo
from PyQt5.QtCore import Qt, QSize, QObject, QThread, pyqtSignal, QTimer
from pymavlink import mavutil

from ui_widgets.stop_sensor_avs_streams import disableStreams
from ui_widgets.send_cap_commands_qt5 import CapWorker, CapOffWorker

from ui_widgets.parameters_cap import cap_params_description, cap_params, cap_params_values

from ui_widgets.set_sync_time import setTimer
from ui_widgets.sync_time_at_start import syncTimeAtStart
from ui_widgets.log_data_worker_qt5 import LogDataWorker
from ui_widgets.plot_active_intensity_worker_qt5 import PlotActiveIntensityWorker

from ui_widgets.create_act_int_plot_qt5 import createActIntPlot
from ui_widgets.create_NED_plot_qt5 import createNEDPlot
from ui_widgets.plot_NED_worker_qt5 import PlotNEDWorker
from ui_widgets.create_sound_loc_plot_qt5 import createSoundLoc
from ui_widgets.plot_localization_worker_qt5 import PlotLocalizationWorker


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("ECHO")
        self.setFixedSize(QSize(1000, 900))

        self.portList        = []
        self.port_map        = {}
        self.getDevConns     = {}
        self.storeHapParams  = {}
        self.updateHapParams = {}

        self.get_available_ports()
        self.get_connected()
        self.setupUI()

        (self.act_int_lines,
        self.azm_lines,
        self.intAx,
        self.azAx,
        self.intCanvas,
        self.act_int_thresh_entry,
        self.q_thresh_entry,
        self.hist_thresh_entry,
        self.log_data_entry) = createActIntPlot(self.tab2, self.plot_act_int_btn, self.cap_btn,
                                                self.log_csv_data_btn, self.cap_off_data_btn,
                                                list(self.getDevConns.keys()))

        self.ned_lines, self.axNED, self.canvasNED = createNEDPlot(self.tab3, self.plot_ned_btn, list(self.getDevConns.keys()))

        (self.azimuth_lines,
        self.dev_positions,
        self.devLocCanvas,
        self.loc_act_int_thresh_entry,
        self.loc_q_thresh_entry,
        self.loc_hist_thresh_entry) = createSoundLoc(self.tab4,
                                                      list(self.getDevConns.keys()),
                                                      self.sound_loc_btn,
                                                      self.log_data_btn_loc)

        QTimer.singleShot(0, lambda: syncTimeAtStart(self.getDevConns))

    def get_available_ports(self):
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            if port.description() == "Silicon Labs CP210x USB to UART Bridge Silicon Labs" or "ARK FPV.x ARK" or "Silicon Labs CP210x USB to UART Bridge" or "CP2102 USB to UART Bridge Controller":
                self.portList.append(port.portName())
        print("Available Serial Ports:", self.portList)
        print('')

    def get_connected(self):
        for i, port in enumerate(self.portList):
            self.port_map.update({f"dev{i+1}": port})

        for name, port in self.port_map.items():
            connection = mavutil.mavlink_connection(device=port, baud=57600)
            connection.wait_heartbeat(timeout=8)
            self.getDevConns[name] = connection
            print(f"Heartbeat received from {name}")
            disableStreams(connection)

    def setupUI(self):
        self.layout_tabs = QVBoxLayout()

        self.tabs = QTabWidget()
        self.tabs.setStyleSheet("QTabBar::tab { font-size: 10px; }")
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()
        self.tab4 = QWidget()

        self.tabs.addTab(self.tab2, "VISUALS")
        self.tabs.addTab(self.tab3, "NED")
        self.tabs.addTab(self.tab4, "SOUND LOCALIZATION")

        self.log_data_btn = QPushButton("LOG DATA")
        self.log_data_btn.setFixedWidth(110)
        self.log_data_btn.setFixedHeight(30)
        self.log_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.log_data_btn.clicked.connect(self.onLogDataClicked)

        self.plot_act_int_btn = QPushButton("PLOT ACTIVE INTENSITY")
        self.plot_act_int_btn.setFixedWidth(175)
        self.plot_act_int_btn.setFixedHeight(30)
        self.plot_act_int_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.plot_act_int_btn.clicked.connect(self.onPlotActIntClicked)

        self.plot_ned_btn = QPushButton("PLOT NED")
        self.plot_ned_btn.setFixedWidth(175)
        self.plot_ned_btn.setFixedHeight(30)
        self.plot_ned_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.plot_ned_btn.clicked.connect(self.onPlotNedClicked)

        self.sound_loc_btn = QPushButton("SOUND LOCALIZATION")
        self.sound_loc_btn.setFixedWidth(200)
        self.sound_loc_btn.setFixedHeight(30)
        self.sound_loc_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        self.sound_loc_btn.clicked.connect(self.onSoundLocClicked)

        self.log_data_btn_loc = QPushButton("LOG DATA")
        self.log_data_btn_loc.setFixedWidth(110)
        self.log_data_btn_loc.setFixedHeight(30)
        self.log_data_btn_loc.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        self.log_data_btn_loc.clicked.connect(self.onLogDataLocClicked)

        self.cap_btn = QPushButton("CAP ON")
        self.cap_btn.setFixedWidth(120)
        self.cap_btn.setFixedHeight(30)
        self.cap_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.cap_btn.clicked.connect(self.onCapClicked)

        self.log_csv_data_btn = QPushButton("LOG CSV DATA")
        self.log_csv_data_btn.setFixedWidth(120)
        self.log_csv_data_btn.setFixedHeight(30)
        self.log_csv_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.log_csv_data_btn.clicked.connect(self.onLogCsvDataClicked)

        self.cap_off_data_btn = QPushButton("CAP OFF")
        self.cap_off_data_btn.setFixedWidth(120)
        self.cap_off_data_btn.setFixedHeight(30)
        self.cap_off_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.cap_off_data_btn.clicked.connect(self.onCapOffClicked)

        self.layout_tabs.addWidget(self.tabs)
        self.setLayout(self.layout_tabs)

    def setup_cap_thread(self):
        self.cap_thread = QThread()
        self.cap_worker = LogDataWorker(self.getDevConns, self.end_timer)
        self.cap_worker.moveToThread(self.cap_thread)
        self.cap_thread.started.connect(self.cap_worker.run)
        self.cap_worker.finished.connect(self.cap_thread.quit)
        self.cap_worker.finished.connect(self.cap_worker.deleteLater)
        self.cap_thread.finished.connect(self.cap_thread.deleteLater)
        self.cap_worker.progress.connect(self.on_log_message)
        self.cap_thread.start()

    def setup_log_csv_data_thread(self):
        self.log_csv_thread = QThread()
        self.log_csv_worker = LogDataWorker(self.getDevConns, self.end_timer)
        self.log_csv_worker.moveToThread(self.log_csv_thread)
        self.log_csv_thread.started.connect(self.log_csv_worker.run)
        self.log_csv_worker.finished.connect(self.log_csv_thread.quit)
        self.log_csv_worker.finished.connect(lambda: self.log_csv_data_btn.setText("LOG CSV DATA"))
        self.log_csv_worker.finished.connect(lambda: self.log_csv_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;"))
        self.log_csv_worker.progress.connect(self.on_log_message)
        self.log_csv_thread.start()
        self.log_csv_data_btn.setText("STOP")
        self.log_csv_data_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def setup_cap_off_thread(self):
        self.cap_off_thread = QThread()
        self.cap_off_worker = LogDataWorker(self.getDevConns, self.end_timer)
        self.cap_off_worker.moveToThread(self.cap_off_thread)
        self.cap_off_thread.started.connect(self.cap_off_worker.run)
        self.cap_off_worker.finished.connect(self.cap_off_thread.quit)
        self.cap_off_worker.finished.connect(self.cap_off_worker.deleteLater)
        self.cap_off_thread.finished.connect(self.cap_off_thread.deleteLater)
        self.cap_off_worker.progress.connect(self.on_log_message)
        self.cap_off_thread.start()

    def setup_log_data_loc_thread(self):
        self.log_thread_loc = QThread()
        self.log_worker_loc = LogDataWorker(self.getDevConns, self.end_timer)
        self.log_worker_loc.moveToThread(self.log_thread_loc)
        self.log_thread_loc.started.connect(self.log_worker_loc.run)
        self.log_worker_loc.finished.connect(self.log_thread_loc.quit)
        self.log_worker_loc.finished.connect(lambda: self.log_data_btn_loc.setText("LOG DATA"))
        self.log_worker_loc.finished.connect(lambda: self.log_data_btn_loc.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;"))
        self.log_worker_loc.progress.connect(self.on_log_message)
        self.log_thread_loc.start()
        self.log_data_btn_loc.setText("STOP")
        self.log_data_btn_loc.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def setup_plot_act_int_thread(self):
        self.act_worker = PlotActiveIntensityWorker(self.getDevConns,
                                                    self.act_int_lines,
                                                    self.azm_lines,
                                                    self.intAx,
                                                    self.azAx,
                                                    self.intCanvas,
                                                    self.act_int_thresh_entry,
                                                    self.q_thresh_entry,
                                                    self.hist_thresh_entry,
                                                    self.log_data_entry,
                                                    self.cap_btn,
                                                    self.log_csv_data_btn,
                                                    self.cap_off_data_btn)
        self.act_thread = QThread()
        self.act_worker.moveToThread(self.act_thread)
        self.act_thread.started.connect(self.act_worker.run)
        self.act_worker.finished.connect(self.act_thread.quit)
        self.act_worker.plotUpdated.connect(self.intCanvas.draw_idle)
        self.act_thread.start()
        self.plot_act_int_btn.setText("STOP")
        self.plot_act_int_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def setup_ned_plot_thread(self):
        self.ned_thread = QThread()
        self.ned_worker = PlotNEDWorker(self.getDevConns, self.ned_lines, self.axNED, self.canvasNED)
        self.ned_worker.moveToThread(self.ned_thread)
        self.ned_thread.started.connect(self.ned_worker.run)
        self.ned_worker.finished.connect(self.ned_thread.quit)
        self.ned_thread.start()
        self.plot_ned_btn.setText("STOP")
        self.plot_ned_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def setup_localization_thread(self):
        self.loc_thread = QThread()
        self.loc_worker = PlotLocalizationWorker(self.getDevConns,
                                                 self.azimuth_lines,
                                                 self.dev_positions,
                                                 self.devLocCanvas,
                                                 self.loc_act_int_thresh_entry,
                                                 self.loc_q_thresh_entry,
                                                 self.loc_hist_thresh_entry)
        self.loc_worker.moveToThread(self.loc_thread)
        self.loc_thread.started.connect(self.loc_worker.run)
        self.loc_worker.finished.connect(self.loc_thread.quit)
        self.loc_worker.progress.connect(self.on_log_message)
        self.loc_thread.start()
        self.sound_loc_btn.setText("STOP")
        self.sound_loc_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def on_log_message(self, msg: str):
        print(msg)

    def onSyncTimeClicked(self):
        syncTimeAtStart(self.getDevConns)

    def onCapClicked(self):
        timer = int(self.log_data_entry.text())
        self.cap_thread = QThread()
        self.cap_worker = CapWorker(self.getDevConns, timer)
        self.cap_worker.moveToThread(self.cap_thread)
        self.cap_thread.started.connect(self.cap_worker.run)
        self.cap_worker.finished.connect(self.cap_thread.quit)
        self.cap_worker.finished.connect(self.onCapDone)
        self.cap_thread.start()
        self.cap_btn.setText("CAPTURING...")
        self.cap_btn.setEnabled(False)
        self.cap_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def onCapDone(self):
        self.cap_btn.setText("CAP ON")
        self.cap_btn.setEnabled(True)
        self.cap_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")

    def onCapOffClicked(self):
        self.cap_off_thread = QThread()
        self.cap_off_worker = CapOffWorker(self.getDevConns)
        self.cap_off_worker.moveToThread(self.cap_off_thread)
        self.cap_off_thread.started.connect(self.cap_off_worker.run)
        self.cap_off_worker.finished.connect(self.cap_off_thread.quit)
        self.cap_off_thread.start()

    def onLogDataClicked(self):
        self.end_timer = setTimer(self.timerEntry)
        self.setup_log_data_thread()

    def onLogCsvDataClicked(self):
        act_running = hasattr(self, 'act_worker') and self.act_thread.isRunning()

        if self.log_csv_data_btn.text() == "STOP":
            if act_running:
                self.act_worker.stop_logging()
            else:
                self.log_csv_worker.stop()
                self.log_csv_thread.quit()
                self.log_csv_thread.wait()
            self.log_csv_data_btn.setText("LOG CSV DATA")
            self.log_csv_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        else:
            self.end_timer = setTimer(self.log_data_entry)
            if act_running:
                self.act_worker.logStopped.connect(self.onActLogStopped)
                self.act_worker.start_logging(self.end_timer)
            else:
                self.setup_log_csv_data_thread()
            self.log_csv_data_btn.setText("STOP")
            self.log_csv_data_btn.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def onActLogStopped(self):
        self.log_csv_data_btn.setText("LOG CSV DATA")
        self.log_csv_data_btn.setStyleSheet("background-color: gray; color: white;font-weight: bold;  font-size: 10px;")
        self.act_worker.logStopped.disconnect(self.onActLogStopped)

    def onLogDataLocClicked(self):
        loc_running = hasattr(self, 'loc_worker') and self.loc_thread.isRunning()

        if self.log_data_btn_loc.text() == "STOP":
            if loc_running:
                self.loc_worker.stop_logging()
            else:
                self.log_worker_loc.stop()
                self.log_thread_loc.quit()
                self.log_thread_loc.wait()
            self.log_data_btn_loc.setText("LOG DATA")
            self.log_data_btn_loc.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        else:
            self.end_timer = setTimer(self.timerEntry)
            if loc_running:
                self.loc_worker.logStopped.connect(self.onLocLogStopped)
                self.loc_worker.start_logging(self.end_timer)
            else:
                self.setup_log_data_loc_thread()
            self.log_data_btn_loc.setText("STOP")
            self.log_data_btn_loc.setStyleSheet("background-color: white; color: gray; font-weight: bold; font-size: 10px;")

    def onLocLogStopped(self):
        self.log_data_btn_loc.setText("LOG DATA")
        self.log_data_btn_loc.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        self.loc_worker.logStopped.disconnect(self.onLocLogStopped)

    def onPlotActIntClicked(self):
        if hasattr(self, 'act_worker') and self.act_thread.isRunning():
            self.act_worker.stop()
            self.act_thread.quit()
            self.act_thread.wait()
            self.plot_act_int_btn.setText("PLOT ACTIVE INTENSITY")
            self.plot_act_int_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        else:
            self.setup_plot_act_int_thread()

    def onSoundLocClicked(self):
        if hasattr(self, 'loc_worker') and self.loc_thread.isRunning():
            self.loc_worker.stop()
            self.loc_thread.quit()
            self.loc_thread.wait()
            self.sound_loc_btn.setText("SOUND LOCALIZATION")
            self.sound_loc_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        else:
            standalone_logging = self.log_data_btn_loc.text() == "STOP"
            if standalone_logging:
                remaining = self.end_timer
                self.log_worker_loc.stop()
                self.log_thread_loc.quit()
                self.log_thread_loc.wait()
            self.setup_localization_thread()
            if standalone_logging:
                self.loc_worker.logStopped.connect(self.onLocLogStopped)
                self.loc_worker.start_logging(remaining)

    def onPlotNedClicked(self):
        if hasattr(self, 'ned_worker') and self.ned_thread.isRunning():
            self.ned_worker.stop()
            self.ned_thread.quit()
            self.ned_thread.wait()
            self.plot_ned_btn.setText("PLOT NED")
            self.plot_ned_btn.setStyleSheet("background-color: gray; color: white; font-weight: bold; font-size: 10px;")
        else:
            self.setup_ned_plot_thread()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
