#set_sync_time.py

import time
import datetime
import os 
import csv
from pymavlink import mavutil

# CSV write lock for thread safety
#csv_lock = threading.Lock()

def setTimer(timerEntry):
    
    t = int(timerEntry.text()) # access user input  

    # Record start time for 1-minute timer
    start_timer = time.time()
    end_timer = start_timer + t  # 1 minute from now

    print()
    print(f"Collecting data for: {t} seconds")
    print(f"Data collection start time: {time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(start_timer))}")

    return end_timer

#------------------------------------------------------------------------------
# Time synchronization thread
def syncTime(connection, end_timer):
    """Send SYSTEM_TIME messages to both flight controllers"""

    while time.time() < end_timer: 
        # Get current UTC time in microseconds
        time_unix_usec =  int(time.time() * 1e6)

        # Send 
        if connection:
            connection.mav.system_time_send(time_unix_usec, 0)

        time.sleep(1.0)  # Send at 1 Hz

