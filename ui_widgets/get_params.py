#get_params.py

import time
import struct
from pymavlink import mavutil

''' Function to get both haptic and ares parameters from the vehicle '''

def getParams(connection, all_params, storeHapParams, dev_name=None):

    print(f'\n---- getting parameters from {dev_name or "device"} ----\n')
    

    for name in all_params:
        print('getting params...')
        connection.mav.param_request_read_send(
            connection.target_system,
            connection.target_component,
            name.encode('utf-8'),
            -1)

        time.sleep(2.5) #0.08)

        message = connection.recv_match(type='PARAM_VALUE', blocking=True, timeout=1.5)

        if message is None:
            # print(f'WARNING: no response for {name}')
            # continue
            break

        #print(f"{message.param_id}: {message.param_type}, {message.param_value}\n")

        if ((message.param_id in ('HAP_SENSE_AVS_R', 'HAP_MODE', 'HAP_IMU_UP_DOWN',
                                  'HAP_SENSE_AVS_L', 'HAP_SENSE_IMU', 'HAP_MULTIPLEX',
                                  'HAP_DRV_EFFECT_T', 'HAP_DRV_EFFECT_B'))
                and message.param_type == 6):
            bytes_value = struct.pack('f', message.param_value)
            int_value = struct.unpack('i', bytes_value)[0]
            storeHapParams[message.param_id] = int_value

        elif message.param_type == 9:
            storeHapParams[message.param_id] = round(message.param_value, 2)

        # else:
        #     bytes_value = struct.pack('f', message.param_value)
        #     int_value = struct.unpack('i', bytes_value)[0]
        #     storeAvsParams[message.param_id] = int_value