#sync_time_at_start.py

import time 

# Time synchronization for button 
def syncTimeAtStart(getDevConns):
    """Send SYSTEM_TIME messages to all connected devices"""

    time_unix_usec = int(time.time() * 1e6)
    for name, connection in getDevConns.items():
        connection.mav.system_time_send(time_unix_usec, 0)
        print(f'-- time synced: {name} --')