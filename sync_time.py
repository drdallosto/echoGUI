#sync_time.py

import time 

# Time synchronization for button 
def sync_time(connection):
    """Send SYSTEM_TIME messages to flight controller"""

    print()
    print('-- time synced --')
    print()

    time_unix_usec = int(time.time() * 1e6)     # Get current UTC time in microseconds
    connection.mav.system_time_send(time_unix_usec, 0) # send time to FC