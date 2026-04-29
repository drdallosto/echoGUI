#LogDataWorker.py
 
from PyQt6.QtCore import QObject, pyqtSignal
import os, csv, time, datetime
from pymavlink import mavutil
from ui_widgets.send_msg_id_stream import sendMsgIdStream

mavutil.set_dialect("development")

class LogDataWorker(QObject):

    ''' Worker class for logging data using a separate thread '''

    progress = pyqtSignal(str) # signal to send progress updates to the main thread
    error    = pyqtSignal(str)
    finished = pyqtSignal()

    def __init__(self, connections, end_timer):
        super().__init__()
        self.connections = connections  # dict of {name: connection}
        self.end_timer   = end_timer
        self.running     = True

    def stop(self):
        self.running = False

    def run(self):
        try:
            self.log_data()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    def log_data(self):
        self.progress.emit(f"Logging for {self.end_timer - time.time():.1f} seconds")

        dirName = 'sensor_avs_logging_data'
        try:
            os.mkdir(dirName)
            self.progress.emit(f"Directory '{dirName}' created successfully.")
        except FileExistsError:
            self.progress.emit(f"Directory '{dirName}' already exists.")

        fieldnames = ['device', 'node_id', 'time_utc_usec', 'active_intensity', 'q_factor',
                      'histogram_count', 'azimuth', 'elevation', 'yaw', 'pitch', 'roll',
                      'north', 'east', 'down']

        timestamp_str = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        csv_file_name = f"{timestamp_str}.csv"
        csv_path = os.path.join(dirName, csv_file_name)

        csv_file = open(csv_path, mode='a', newline='')
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        if os.path.getsize(csv_path) == 0:
            csv_writer.writeheader()

        message_id = 297
        for name, connection in self.connections.items():
            self.progress.emit(f"--- streaming for {name} ---")
            sendMsgIdStream(connection, message_id)

        self.progress.emit('')
        self.progress.emit('writing to csv..')

        while self.running and time.time() < self.end_timer:
            for name, connection in self.connections.items():
                msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=False, timeout=0.1)
                if msg:
                    csv_writer.writerow({
                        'device':           name,
                        'node_id':          msg.device_id,
                        'time_utc_usec':    msg.time_utc_usec,
                        'active_intensity': msg.active_intensity,
                        'q_factor':         msg.q_factor,
                        'histogram_count':  msg.histogram_count,
                        'azimuth':          msg.azimuth_deg,
                        'elevation':        msg.elevation_deg,
                        'yaw':              msg.yaw,
                        'pitch':            msg.pitch,
                        'roll':             msg.roll,
                        'north':            msg.north,
                        'east':             msg.east,
                        'down':             msg.down
                    })
                    csv_file.flush()

        csv_file.close()
        self.progress.emit('')
        self.progress.emit('stopped logging')
        
