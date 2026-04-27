#send_msg_id_stream.py

from pymavlink import mavutil


def sendMsgIdStream(connection, message_id):

    # ------ start MAVLink stream ------

    #message_id = 297 #message ID for SENSOR_AVS_LITE_EXT

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
    
    #print(str(message2))


    # # Send the COMMAND_LONG
    connection.mav.send(message2)

    msg2 = connection.recv_match(type='COMMAND_ACK',blocking=True)  # acknowledge command 
    #print((f"ACK: {msg2}"))
   