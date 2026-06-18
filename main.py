# main.py
import sys

from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QTabWidget, QPushButton
from PyQt6.QtSerialPort import QSerialPortInfo
from PyQt6.QtCore import QSize, QThread, QTimer
from pymavlink import mavutil

from ui_widgets.stop_sensor_avs_streams import disableStreams
from ui_widgets.send_cap_commands import CapWorker, CapOffWorker
from ui_widgets.set_sync_time import setTimer
from ui_widgets.sync_time_at_start import syncTimeAtStart
from ui_widgets.log_data_worker import LogDataWorker
from ui_widgets.plot_active_intensity_worker import PlotActiveIntensityWorker
from ui_widgets.create_act_int_plot import createActIntPlot
from ui_widgets.create_sound_loc_plot import createSoundLoc
from ui_widgets.plot_localization_worker import PlotLocalizationWorker


# Button style constants
_BTN_ACTIVE  = "background-color: gray;  color: white; font-weight: bold; font-size: 14px;"
_BTN_RUNNING = "background-color: white; color: gray;  font-weight: bold; font-size: 14px;"

# Add the exact description strings reported by get_available_ports() below.
_KNOWN_PORT_DESCRIPTIONS = {
    "Silicon Labs CP210x USB to UART Bridge Silicon Labs",
    "ARK FPV.x ARK",
    "Silicon Labs CP210x USB to UART Bridge",
    "CP2102 USB to UART Bridge Controller",
    "FT231X USB UART",
}


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("ECHO")
        self.setMinimumSize(QSize(1000, 900))

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
         self.log_data_entry) = createActIntPlot(
            self.tab2,
            self.plot_act_int_btn,
            self.cap_btn,
            self.log_csv_data_btn,
            self.cap_off_data_btn,
            list(self.getDevConns.keys()),
        )

        (self.azimuth_lines,
         self.dev_positions,
         self.devLocCanvas,
         self.loc_act_int_thresh_entry,
         self.loc_q_thresh_entry,
         self.loc_hist_thresh_entry,
         self.source_point,
         self.source_ring,
         self.source_status,
         self.heatmap_img,
         self.beam_patches,
         self.beam_width_entry,
         self.time_const_entry,
         self.enable_drag,          # called when worker stops
         self.disable_drag,         # called when worker starts
         ) = createSoundLoc(
            self.tab3,
            list(self.getDevConns.keys()),
            self.sound_loc_btn,
            self.log_data_btn_loc,
        )

        QTimer.singleShot(0, lambda: syncTimeAtStart(self.getDevConns))

    # ── port discovery ────────────────────────────────────────────────

    def get_available_ports(self):
        all_ports = QSerialPortInfo.availablePorts()

        if not all_ports:
            print("No serial ports detected by Qt at all.")
        else:
            print(f"{'Port':<12} {'Description':<50} {'Manufacturer':<35} {'VID':>6} {'PID':>6}")
            print("-" * 115)
            for p in all_ports:
                vid = f"0x{p.vendorIdentifier():04X}" if p.hasVendorIdentifier()  else "  N/A"
                pid = f"0x{p.productIdentifier():04X}" if p.hasProductIdentifier() else "  N/A"
                print(f"{p.portName():<12} {p.description():<50} {p.manufacturer():<35} {vid:>6} {pid:>6}")
        print()

        for port in all_ports:
            if port.description() in _KNOWN_PORT_DESCRIPTIONS:
                self.portList.append(port.portName())

        print("Matched ports:", self.portList)
        print()

    def get_connected(self):
        self.port_map = {f"dev{i+1}": port for i, port in enumerate(self.portList)}

        for name, port in self.port_map.items():
            connection = mavutil.mavlink_connection(device=port, baud=57600)
            connection.wait_heartbeat(timeout=8)
            self.getDevConns[name] = connection
            print(f"Heartbeat received from {name}")
            disableStreams(connection)

    # ── UI setup ──────────────────────────────────────────────────────

    def _make_button(self, label: str, width: int, slot) -> QPushButton:
        btn = QPushButton(label)
        btn.setFixedWidth(width)
        btn.setFixedHeight(30)
        btn.setStyleSheet(_BTN_ACTIVE)
        btn.clicked.connect(slot)
        return btn

    def _set_btn(self, btn: QPushButton, label: str, active: bool):
        btn.setText(label)
        btn.setStyleSheet(_BTN_ACTIVE if active else _BTN_RUNNING)

    def setupUI(self):
        self.tabs = QTabWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()

        self.tabs.addTab(self.tab2, "VISUALS")
        self.tabs.addTab(self.tab3, "SOUND LOCALIZATION")

        self.log_data_btn     = self._make_button("LOG DATA",              110, self.onLogDataClicked)
        self.plot_act_int_btn = self._make_button("PLOT ACTIVE INTENSITY", 175, self.onPlotActIntClicked)
        self.sound_loc_btn    = self._make_button("SOUND LOCALIZATION",    200, self.onSoundLocClicked)
        self.log_data_btn_loc = self._make_button("LOG DATA",              110, self.onLogDataLocClicked)
        self.cap_btn          = self._make_button("CAP ON",                120, self.onCapClicked)
        self.log_csv_data_btn = self._make_button("LOG CSV DATA",          120, self.onLogCsvDataClicked)
        self.cap_off_data_btn = self._make_button("CAP OFF",               120, self.onCapOffClicked)

        layout = QVBoxLayout()
        layout.addWidget(self.tabs)
        self.setLayout(layout)

    # ── thread helpers ────────────────────────────────────────────────

    def setup_log_csv_data_thread(self):
        self.log_csv_thread = QThread()
        self.log_csv_worker = LogDataWorker(self.getDevConns, self.end_timer)
        self.log_csv_worker.moveToThread(self.log_csv_thread)
        self.log_csv_thread.started.connect(self.log_csv_worker.run)
        self.log_csv_worker.finished.connect(self.log_csv_thread.quit)
        self.log_csv_worker.finished.connect(
            lambda: self._set_btn(self.log_csv_data_btn, "LOG CSV DATA", active=True)
        )
        self.log_csv_worker.progress.connect(self.on_log_message)
        self.log_csv_thread.start()
        self._set_btn(self.log_csv_data_btn, "STOP", active=False)

    def setup_log_data_loc_thread(self):
        self.log_thread_loc = QThread()
        self.log_worker_loc = LogDataWorker(self.getDevConns, self.end_timer)
        self.log_worker_loc.moveToThread(self.log_thread_loc)
        self.log_thread_loc.started.connect(self.log_worker_loc.run)
        self.log_worker_loc.finished.connect(self.log_thread_loc.quit)
        self.log_worker_loc.finished.connect(
            lambda: self._set_btn(self.log_data_btn_loc, "LOG DATA", active=True)
        )
        self.log_worker_loc.progress.connect(self.on_log_message)
        self.log_thread_loc.start()
        self._set_btn(self.log_data_btn_loc, "STOP", active=False)

    def setup_plot_act_int_thread(self):
        self.act_worker = PlotActiveIntensityWorker(
            self.getDevConns,
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
            self.cap_off_data_btn,
        )
        self.act_thread = QThread()
        self.act_worker.moveToThread(self.act_thread)
        self.act_thread.started.connect(self.act_worker.run)
        self.act_worker.finished.connect(self.act_thread.quit)
        self.act_worker.plotUpdated.connect(self.intCanvas.draw_idle)
        self.act_thread.start()
        self._set_btn(self.plot_act_int_btn, "STOP", active=False)

    def setup_localization_thread(self):
        self.loc_thread = QThread()
        self.loc_worker = PlotLocalizationWorker(
            self.getDevConns,
            self.azimuth_lines,
            self.dev_positions,
            self.devLocCanvas,
            self.loc_act_int_thresh_entry,
            self.loc_q_thresh_entry,
            self.loc_hist_thresh_entry,
            self.source_point,
            self.source_ring,
            self.source_status,
            self.heatmap_img,
            self.beam_patches,
            self.beam_width_entry,
            self.time_const_entry,
        )
        self.loc_worker.moveToThread(self.loc_thread)
        self.loc_thread.started.connect(self.loc_worker.run)
        self.loc_worker.finished.connect(self.loc_thread.quit)
        self.loc_worker.progress.connect(self.on_log_message)
        self.loc_thread.start()

        self.disable_drag()
        self._set_btn(self.sound_loc_btn, "STOP", active=False)

    # ── logging helpers ───────────────────────────────────────────────

    def on_log_message(self, msg: str):
        print(msg)

    # ── button handlers ───────────────────────────────────────────────

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
        self._set_btn(self.cap_btn, "CAPTURING...", active=False)
        self.cap_btn.setEnabled(False)

    def onCapDone(self):
        self._set_btn(self.cap_btn, "CAP ON", active=True)
        self.cap_btn.setEnabled(True)

    def onCapOffClicked(self):
        self.cap_off_thread = QThread()
        self.cap_off_worker = CapOffWorker(self.getDevConns)
        self.cap_off_worker.moveToThread(self.cap_off_thread)
        self.cap_off_thread.started.connect(self.cap_off_worker.run)
        self.cap_off_worker.finished.connect(self.cap_off_thread.quit)
        self.cap_off_thread.start()

    def onLogDataClicked(self):
        # TODO: wire self.timerEntry when Parameters tab is re-enabled
        pass

    def onLogCsvDataClicked(self):
        act_running = hasattr(self, 'act_worker') and self.act_thread.isRunning()

        if self.log_csv_data_btn.text() == "STOP":
            if act_running:
                self.act_worker.stop_logging()
            else:
                self.log_csv_worker.stop()
                self.log_csv_thread.quit()
                self.log_csv_thread.wait()
            self._set_btn(self.log_csv_data_btn, "LOG CSV DATA", active=True)
        else:
            self.end_timer = setTimer(self.log_data_entry)
            if act_running:
                self.act_worker.logStopped.connect(self.onActLogStopped)
                self.act_worker.start_logging(self.end_timer)
            else:
                self.setup_log_csv_data_thread()
            self._set_btn(self.log_csv_data_btn, "STOP", active=False)

    def onActLogStopped(self):
        self._set_btn(self.log_csv_data_btn, "LOG CSV DATA", active=True)
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
            self._set_btn(self.log_data_btn_loc, "LOG DATA", active=True)
        else:
            # TODO: wire self.timerEntry when Parameters tab is re-enabled
            self.end_timer = setTimer(self.log_data_entry)
            if loc_running:
                self.loc_worker.logStopped.connect(self.onLocLogStopped)
                self.loc_worker.start_logging(self.end_timer)
            else:
                self.setup_log_data_loc_thread()
            self._set_btn(self.log_data_btn_loc, "STOP", active=False)

    def onLocLogStopped(self):
        self._set_btn(self.log_data_btn_loc, "LOG DATA", active=True)
        self.loc_worker.logStopped.disconnect(self.onLocLogStopped)

    def onPlotActIntClicked(self):
        if hasattr(self, 'act_worker') and self.act_thread.isRunning():
            self.act_worker.stop()
            self.act_thread.quit()
            self.act_thread.wait()
            self._set_btn(self.plot_act_int_btn, "PLOT ACTIVE INTENSITY", active=True)
        else:
            self.setup_plot_act_int_thread()

    def onSoundLocClicked(self):
        if hasattr(self, 'loc_worker') and self.loc_thread.isRunning():
            # --- stop ---
            self.loc_worker.stop()
            self.loc_thread.quit()
            self.loc_thread.wait()
            self.enable_drag()
            self._set_btn(self.sound_loc_btn, "SOUND LOCALIZATION", active=True)
        else:
            # --- start ---
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


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
