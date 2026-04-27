#stopFPVStream.py

import time
from pymavlink import mavutil


"'------------------ STOP FPV SENSOR STREAMS ------------------------"

def disableStreams(connection):

    ''' maybe implement a for loop instead to loop throug message IDs'''

    print('Stopping all sensor avs streams...')
    print('')
    
    message_id = 292
    message = connection.mav.command_long_encode(
        connection.target_system,
        connection.target_component,
        mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,
        0,
        message_id,
        -1,  # -1 = disable the stream
        0,0,0,0,0)
    connection.mav.send(message)
    time.sleep(0.1)  # let it settle

    message_id = 296
    message = connection.mav.command_long_encode(
        connection.target_system,
        connection.target_component,
        mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,
        0,
        message_id,
        -1,  # -1 = disable the stream
        0,0,0,0,0)
    connection.mav.send(message)
    time.sleep(0.1)  # let it settle

    message_id = 297
    message = connection.mav.command_long_encode(
        connection.target_system,
        connection.target_component,
        mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,
        0,
        message_id,
        -1,  # -1 = disable the stream
        0,0,0,0,0)
    connection.mav.send(message)
    time.sleep(0.1)  # let it settle