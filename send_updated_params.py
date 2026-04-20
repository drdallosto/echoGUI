#update_params.py

import struct
from pymavlink import mavutil

def sendUpdatedParams(connection, updateHapParams, updateAvsParams):

    all_updated_params = updateHapParams | updateAvsParams # combine the two dictionaries into one
    #print(all_updated_params)

    print("---- Updated Haptic Parameters ----")

    for param_name, entry_field in all_updated_params.items():
        get_param_value = entry_field.text()   # get the text from the entry field

        if (param_name in ('HAP_SENSE_AVS_R', 'HAP_MODE', 'HAP_IMU_UP_DOWN',
                                  'HAP_SENSE_AVS_L', 'HAP_SENSE_IMU', 'HAP_MULTIPLEX',
                                  'HAP_DRV_EFFECT_T', 'HAP_DRV_EFFECT_B') or param_name.startswith('AVS_')):

            param_type =  mavutil.mavlink.MAV_PARAM_TYPE_INT32
            bytes_value = struct.pack('i', int(get_param_value))  # convert python values into binary data (bytes
            param_value = struct.unpack('f', bytes_value)[0] # convert binary data into python values 

        else:
            param_type = mavutil.mavlink.MAV_PARAM_TYPE_REAL32
            param_value = float(get_param_value)

        print(f"{param_name}: {param_value}")

        # send updated parameters to px4
        connection.mav.param_set_send(
        connection.target_system,
        connection.target_component,
        param_name.encode('utf-8'),
        param_value,
        param_type)


    # wait for PX4 to confirm the parameter was stored
    ack = connection.recv_match(type='PARAM_VALUE', blocking=True, timeout=2)
    if ack is None:
        print(f"WARNING: No ack received for {param_name}")
    else:
        print("ACK received")




