#send_msg_id_stream.py

from pymavlink import mavutil


def sendMsgIdStream(connection, message_id):

    # ------ start MAVLink stream ------

    #message_id = 297 #message ID for SENSOR_AVS_LITE_EXT

    # drain messages in buffer before starting stream to avoid processing old messages
    # Use a tiny timeout to ensure the OS network buffer completely flushes
    while connection.recv_match(blocking=False, timeout= 0.001) is not None:
        pass

    message2 = connection.mav.command_long_encode(  
            connection.target_system,  # Target system ID
            connection.target_component,  # Target component ID
            mavutil.mavlink.MAV_CMD_SET_MESSAGE_INTERVAL,  # ID of command to send  
            0,  # Confirmation
            message_id,   # param1: Message ID to be streamed
            100000, # param2: Interval in microseconds
            0,0,0,0,0)
    
    #print(str(message2))

    # # Send the command
    connection.mav.send(message2)

    # Catch the ACK safely with a timeout
    # This prevents an infinite loop if the message is lost or dropped
    msg2 = connection.recv_match(type='COMMAND_ACK',blocking=True, timeout=2.0)  # acknowledge command 
    #print((f"ACK: {msg2}"))

    print('')
   
    if msg2 is None:
        print(f"Error: Timeout waiting for ACK for message {message_id}")
        return False
        
    if msg2.result != mavutil.mavlink.MAV_RESULT_ACCEPTED:
        print(f"Command rejected by vehicle. Result code: {msg2.result}")
        return False

    print(f"Stream successfully started for message {message_id}")
    return True