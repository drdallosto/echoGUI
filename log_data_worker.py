#LogDataWorker.py
 
from PyQt6.QtCore import QObject, QThread, pyqtSignal
import os, csv, time, datetime
from pymavlink import mavutil

mavutil.set_dialect("development")

class LogDataWorker(QObject):

    ''' Worker class for logging data in a separate thread '''

    progress = pyqtSignal(str) # signal to send progress updates to the main thread
    error    = pyqtSignal(str)
    finished = pyqtSignal()

    def __init__(self, connection, end_timer):
        super().__init__()
        self.connection = connection
        self.end_timer  = end_timer

    def run(self):
        try:
            self.log_data()
        except Exception as e:
            self.error.emit(str(e))
        finally:
            self.finished.emit()

    #@pyqtSlot()
    def log_data(self):
        connection = self.connection
        end_timer  = self.end_timer

        self.progress.emit(f"Logging for {end_timer - time.time():.1f} seconds")

        # create directory to store logging data
        dirName = 'sensor_avs_logging_data'

        # Create the directory
        try:
            os.mkdir(dirName)
            self.progress.emit(f"Directory '{dirName}' created successfully.")
            self.progress.emit('')
        except FileExistsError:
            self.progress.emit(f"Directory '{dirName}' already exists.")
            self.progress.emit('')

        # ------ write to CSV (logging) ------

        fieldnames = ['node_id','time_utc_usec', 'active_intensity', 'q_factor','histogram_count', 
                      'azimuth', 'elevation', 'yaw', 'pitch','roll', 'north', 'east', 'down']
        
        timestamp_str = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        csv_file_name = f"{timestamp_str}.csv"

        # Open CSV once at start (append mode)
        # csv_file = open(os.path.join(dirName,csv_file_name), mode='a', newline='')
        # csv_writer = csv.writer(csv_file) # 
        # csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

        # # Write header only if file is empty
        # if csv_file.tell() == 0:
        #     csv_writer.writeheader()  

        # fix - check file size instead
        csv_file = open(os.path.join(dirName, csv_file_name), mode='a', newline='')
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        if os.path.getsize(os.path.join(dirName, csv_file_name)) == 0:
            csv_writer.writeheader()

        # ------ start MAVLink stream ------

        message_id = 297 #message ID for SENSOR_AVS_LITE_EXT

        # drain messages in buffer before starting stream to avoid processing old messages
        while connection.recv_match(blocking=False) is not None:
            pass

        message2 = connection.mav.command_long_encode(  
                connection.target_system,  # Target system ID
                connection.target_component,  # Target component ID
                mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,  # ID of command to send  
                0,  # Confirmation
                message_id,   # param1: Message ID to be streamed
                0, # param2: Interval in microseconds
                0,0,0,0,0)
        self.progress.emit(str(message2))

        # # Send the COMMAND_LONG
        connection.mav.send(message2)

        msg2 = connection.recv_match(type='COMMAND_ACK',blocking=True)  # acknowledge command 
        self.progress.emit(f"ACK: {msg2}")
        self.progress.emit('')


        "data acquisition thread"
        "write to queue and csv file"
        
        if not connection:
            return
        

        # ---------- data acquisition loop ----------
        self.progress.emit('writing to csv..')

        while time.time() < end_timer:               
            msg = connection.recv_match(type='SENSOR_AVS_LITE_EXT', blocking=True, timeout=0.1)   
            #print(msg)

            #check if msg arrived 
            if msg: 
                t = msg.time_utc_usec
                id = msg.device_id
                act = msg.active_intensity
                az = msg.azimuth_deg
                el = msg.elevation_deg

                yaw = msg.yaw
                pitch = msg.pitch
                roll = msg.roll
                north = msg.north
                east = msg.east
                down = msg.down

                hist_count = msg.histogram_count
                q_factor = msg.q_factor

                csv_writer.writerow({
                    'node_id': id,
                    'time_utc_usec': t,
                    'active_intensity': act,
                    'q_factor': q_factor,
                    'histogram_count': hist_count,
                    'azimuth': az, 
                    'elevation': el,
                    'yaw': yaw,
                    'pitch': pitch, 
                    'roll': roll,
                    'north': north, 
                    'east': east,
                    'down': down
                })
                csv_file.flush()

        csv_file.close()

        self.progress.emit('')
        self.progress.emit('stopped logging')
        


# @pyqtSlot()
# def do_work(self):
#     # runs in the thread it was moved to
#     for i in range(10):
#         time.sleep(0.3)
#         self.progress.emit(i + 1)
#     self.finished.emit()