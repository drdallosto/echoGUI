#pragma once
// MESSAGE SENSOR_AVS_LITE_EXT PACKING

#define MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT 297


typedef struct __mavlink_sensor_avs_lite_ext_t {
 uint64_t time_utc_usec; /*<  Timestamp (microseconds, UTC)*/
 uint64_t timestamp; /*<  time since system start (microseconds)*/
 uint32_t device_id; /*<  unique device ID for the sensor that does not change between power cycles*/
 uint32_t timestamp_sample; /*<  AVS sensor sample index since system SYNC*/
 float azimuth_deg; /*<  azimuth in degrees*/
 float elevation_deg; /*<  elevation in degrees*/
 float active_intensity; /*<  active intensity level re: 1 pW*/
 float q_factor; /*<  Q-factor of the histogram peak for this detected source*/
 float north; /*<   local north coordinate */
 float east; /*<   local east coordinate*/
 float down; /*<   local down coordinate*/
 float yaw; /*<   yaw*/
 float pitch; /*<   pitch*/
 float roll; /*<   roll*/
 uint16_t histogram_count; /*<  number of hits for this azim/elev histogram bin*/
} mavlink_sensor_avs_lite_ext_t;

#define MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN 66
#define MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN 66
#define MAVLINK_MSG_ID_297_LEN 66
#define MAVLINK_MSG_ID_297_MIN_LEN 66

#define MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC 146
#define MAVLINK_MSG_ID_297_CRC 146



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SENSOR_AVS_LITE_EXT { \
    297, \
    "SENSOR_AVS_LITE_EXT", \
    15, \
    {  { "device_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_sensor_avs_lite_ext_t, device_id) }, \
         { "time_utc_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_sensor_avs_lite_ext_t, time_utc_usec) }, \
         { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_sensor_avs_lite_ext_t, timestamp) }, \
         { "timestamp_sample", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_sensor_avs_lite_ext_t, timestamp_sample) }, \
         { "azimuth_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_sensor_avs_lite_ext_t, azimuth_deg) }, \
         { "elevation_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_sensor_avs_lite_ext_t, elevation_deg) }, \
         { "active_intensity", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_sensor_avs_lite_ext_t, active_intensity) }, \
         { "q_factor", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_sensor_avs_lite_ext_t, q_factor) }, \
         { "histogram_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 64, offsetof(mavlink_sensor_avs_lite_ext_t, histogram_count) }, \
         { "north", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_sensor_avs_lite_ext_t, north) }, \
         { "east", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_sensor_avs_lite_ext_t, east) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_sensor_avs_lite_ext_t, down) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_sensor_avs_lite_ext_t, yaw) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_sensor_avs_lite_ext_t, pitch) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_sensor_avs_lite_ext_t, roll) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SENSOR_AVS_LITE_EXT { \
    "SENSOR_AVS_LITE_EXT", \
    15, \
    {  { "device_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_sensor_avs_lite_ext_t, device_id) }, \
         { "time_utc_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_sensor_avs_lite_ext_t, time_utc_usec) }, \
         { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_sensor_avs_lite_ext_t, timestamp) }, \
         { "timestamp_sample", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_sensor_avs_lite_ext_t, timestamp_sample) }, \
         { "azimuth_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_sensor_avs_lite_ext_t, azimuth_deg) }, \
         { "elevation_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_sensor_avs_lite_ext_t, elevation_deg) }, \
         { "active_intensity", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_sensor_avs_lite_ext_t, active_intensity) }, \
         { "q_factor", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_sensor_avs_lite_ext_t, q_factor) }, \
         { "histogram_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 64, offsetof(mavlink_sensor_avs_lite_ext_t, histogram_count) }, \
         { "north", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_sensor_avs_lite_ext_t, north) }, \
         { "east", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_sensor_avs_lite_ext_t, east) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_sensor_avs_lite_ext_t, down) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_sensor_avs_lite_ext_t, yaw) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_sensor_avs_lite_ext_t, pitch) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_sensor_avs_lite_ext_t, roll) }, \
         } \
}
#endif

/**
 * @brief Pack a sensor_avs_lite_ext message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param north   local north coordinate 
 * @param east   local east coordinate
 * @param down   local down coordinate
 * @param yaw   yaw
 * @param pitch   pitch
 * @param roll   roll
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t device_id, uint64_t time_utc_usec, uint64_t timestamp, uint32_t timestamp_sample, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t histogram_count, float north, float east, float down, float yaw, float pitch, float roll)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN];
    _mav_put_uint64_t(buf, 0, time_utc_usec);
    _mav_put_uint64_t(buf, 8, timestamp);
    _mav_put_uint32_t(buf, 16, device_id);
    _mav_put_uint32_t(buf, 20, timestamp_sample);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_float(buf, 40, north);
    _mav_put_float(buf, 44, east);
    _mav_put_float(buf, 48, down);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, pitch);
    _mav_put_float(buf, 60, roll);
    _mav_put_uint16_t(buf, 64, histogram_count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#else
    mavlink_sensor_avs_lite_ext_t packet;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp = timestamp;
    packet.device_id = device_id;
    packet.timestamp_sample = timestamp_sample;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.roll = roll;
    packet.histogram_count = histogram_count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
}

/**
 * @brief Pack a sensor_avs_lite_ext message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param north   local north coordinate 
 * @param east   local east coordinate
 * @param down   local down coordinate
 * @param yaw   yaw
 * @param pitch   pitch
 * @param roll   roll
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t device_id, uint64_t time_utc_usec, uint64_t timestamp, uint32_t timestamp_sample, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t histogram_count, float north, float east, float down, float yaw, float pitch, float roll)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN];
    _mav_put_uint64_t(buf, 0, time_utc_usec);
    _mav_put_uint64_t(buf, 8, timestamp);
    _mav_put_uint32_t(buf, 16, device_id);
    _mav_put_uint32_t(buf, 20, timestamp_sample);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_float(buf, 40, north);
    _mav_put_float(buf, 44, east);
    _mav_put_float(buf, 48, down);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, pitch);
    _mav_put_float(buf, 60, roll);
    _mav_put_uint16_t(buf, 64, histogram_count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#else
    mavlink_sensor_avs_lite_ext_t packet;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp = timestamp;
    packet.device_id = device_id;
    packet.timestamp_sample = timestamp_sample;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.roll = roll;
    packet.histogram_count = histogram_count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#endif
}

/**
 * @brief Pack a sensor_avs_lite_ext message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param north   local north coordinate 
 * @param east   local east coordinate
 * @param down   local down coordinate
 * @param yaw   yaw
 * @param pitch   pitch
 * @param roll   roll
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t device_id,uint64_t time_utc_usec,uint64_t timestamp,uint32_t timestamp_sample,float azimuth_deg,float elevation_deg,float active_intensity,float q_factor,uint16_t histogram_count,float north,float east,float down,float yaw,float pitch,float roll)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN];
    _mav_put_uint64_t(buf, 0, time_utc_usec);
    _mav_put_uint64_t(buf, 8, timestamp);
    _mav_put_uint32_t(buf, 16, device_id);
    _mav_put_uint32_t(buf, 20, timestamp_sample);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_float(buf, 40, north);
    _mav_put_float(buf, 44, east);
    _mav_put_float(buf, 48, down);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, pitch);
    _mav_put_float(buf, 60, roll);
    _mav_put_uint16_t(buf, 64, histogram_count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#else
    mavlink_sensor_avs_lite_ext_t packet;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp = timestamp;
    packet.device_id = device_id;
    packet.timestamp_sample = timestamp_sample;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.roll = roll;
    packet.histogram_count = histogram_count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
}

/**
 * @brief Encode a sensor_avs_lite_ext struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sensor_avs_lite_ext C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sensor_avs_lite_ext_t* sensor_avs_lite_ext)
{
    return mavlink_msg_sensor_avs_lite_ext_pack(system_id, component_id, msg, sensor_avs_lite_ext->device_id, sensor_avs_lite_ext->time_utc_usec, sensor_avs_lite_ext->timestamp, sensor_avs_lite_ext->timestamp_sample, sensor_avs_lite_ext->azimuth_deg, sensor_avs_lite_ext->elevation_deg, sensor_avs_lite_ext->active_intensity, sensor_avs_lite_ext->q_factor, sensor_avs_lite_ext->histogram_count, sensor_avs_lite_ext->north, sensor_avs_lite_ext->east, sensor_avs_lite_ext->down, sensor_avs_lite_ext->yaw, sensor_avs_lite_ext->pitch, sensor_avs_lite_ext->roll);
}

/**
 * @brief Encode a sensor_avs_lite_ext struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sensor_avs_lite_ext C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sensor_avs_lite_ext_t* sensor_avs_lite_ext)
{
    return mavlink_msg_sensor_avs_lite_ext_pack_chan(system_id, component_id, chan, msg, sensor_avs_lite_ext->device_id, sensor_avs_lite_ext->time_utc_usec, sensor_avs_lite_ext->timestamp, sensor_avs_lite_ext->timestamp_sample, sensor_avs_lite_ext->azimuth_deg, sensor_avs_lite_ext->elevation_deg, sensor_avs_lite_ext->active_intensity, sensor_avs_lite_ext->q_factor, sensor_avs_lite_ext->histogram_count, sensor_avs_lite_ext->north, sensor_avs_lite_ext->east, sensor_avs_lite_ext->down, sensor_avs_lite_ext->yaw, sensor_avs_lite_ext->pitch, sensor_avs_lite_ext->roll);
}

/**
 * @brief Encode a sensor_avs_lite_ext struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param sensor_avs_lite_ext C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_sensor_avs_lite_ext_t* sensor_avs_lite_ext)
{
    return mavlink_msg_sensor_avs_lite_ext_pack_status(system_id, component_id, _status, msg,  sensor_avs_lite_ext->device_id, sensor_avs_lite_ext->time_utc_usec, sensor_avs_lite_ext->timestamp, sensor_avs_lite_ext->timestamp_sample, sensor_avs_lite_ext->azimuth_deg, sensor_avs_lite_ext->elevation_deg, sensor_avs_lite_ext->active_intensity, sensor_avs_lite_ext->q_factor, sensor_avs_lite_ext->histogram_count, sensor_avs_lite_ext->north, sensor_avs_lite_ext->east, sensor_avs_lite_ext->down, sensor_avs_lite_ext->yaw, sensor_avs_lite_ext->pitch, sensor_avs_lite_ext->roll);
}

/**
 * @brief Send a sensor_avs_lite_ext message
 * @param chan MAVLink channel to send the message
 *
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param north   local north coordinate 
 * @param east   local east coordinate
 * @param down   local down coordinate
 * @param yaw   yaw
 * @param pitch   pitch
 * @param roll   roll
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sensor_avs_lite_ext_send(mavlink_channel_t chan, uint32_t device_id, uint64_t time_utc_usec, uint64_t timestamp, uint32_t timestamp_sample, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t histogram_count, float north, float east, float down, float yaw, float pitch, float roll)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN];
    _mav_put_uint64_t(buf, 0, time_utc_usec);
    _mav_put_uint64_t(buf, 8, timestamp);
    _mav_put_uint32_t(buf, 16, device_id);
    _mav_put_uint32_t(buf, 20, timestamp_sample);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_float(buf, 40, north);
    _mav_put_float(buf, 44, east);
    _mav_put_float(buf, 48, down);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, pitch);
    _mav_put_float(buf, 60, roll);
    _mav_put_uint16_t(buf, 64, histogram_count);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT, buf, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
#else
    mavlink_sensor_avs_lite_ext_t packet;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp = timestamp;
    packet.device_id = device_id;
    packet.timestamp_sample = timestamp_sample;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.roll = roll;
    packet.histogram_count = histogram_count;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT, (const char *)&packet, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
#endif
}

/**
 * @brief Send a sensor_avs_lite_ext message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sensor_avs_lite_ext_send_struct(mavlink_channel_t chan, const mavlink_sensor_avs_lite_ext_t* sensor_avs_lite_ext)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sensor_avs_lite_ext_send(chan, sensor_avs_lite_ext->device_id, sensor_avs_lite_ext->time_utc_usec, sensor_avs_lite_ext->timestamp, sensor_avs_lite_ext->timestamp_sample, sensor_avs_lite_ext->azimuth_deg, sensor_avs_lite_ext->elevation_deg, sensor_avs_lite_ext->active_intensity, sensor_avs_lite_ext->q_factor, sensor_avs_lite_ext->histogram_count, sensor_avs_lite_ext->north, sensor_avs_lite_ext->east, sensor_avs_lite_ext->down, sensor_avs_lite_ext->yaw, sensor_avs_lite_ext->pitch, sensor_avs_lite_ext->roll);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT, (const char *)sensor_avs_lite_ext, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
#endif
}

#if MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sensor_avs_lite_ext_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t device_id, uint64_t time_utc_usec, uint64_t timestamp, uint32_t timestamp_sample, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t histogram_count, float north, float east, float down, float yaw, float pitch, float roll)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_utc_usec);
    _mav_put_uint64_t(buf, 8, timestamp);
    _mav_put_uint32_t(buf, 16, device_id);
    _mav_put_uint32_t(buf, 20, timestamp_sample);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_float(buf, 40, north);
    _mav_put_float(buf, 44, east);
    _mav_put_float(buf, 48, down);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, pitch);
    _mav_put_float(buf, 60, roll);
    _mav_put_uint16_t(buf, 64, histogram_count);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT, buf, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
#else
    mavlink_sensor_avs_lite_ext_t *packet = (mavlink_sensor_avs_lite_ext_t *)msgbuf;
    packet->time_utc_usec = time_utc_usec;
    packet->timestamp = timestamp;
    packet->device_id = device_id;
    packet->timestamp_sample = timestamp_sample;
    packet->azimuth_deg = azimuth_deg;
    packet->elevation_deg = elevation_deg;
    packet->active_intensity = active_intensity;
    packet->q_factor = q_factor;
    packet->north = north;
    packet->east = east;
    packet->down = down;
    packet->yaw = yaw;
    packet->pitch = pitch;
    packet->roll = roll;
    packet->histogram_count = histogram_count;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT, (const char *)packet, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_CRC);
#endif
}
#endif

#endif

// MESSAGE SENSOR_AVS_LITE_EXT UNPACKING


/**
 * @brief Get field device_id from sensor_avs_lite_ext message
 *
 * @return  unique device ID for the sensor that does not change between power cycles
 */
static inline uint32_t mavlink_msg_sensor_avs_lite_ext_get_device_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field time_utc_usec from sensor_avs_lite_ext message
 *
 * @return  Timestamp (microseconds, UTC)
 */
static inline uint64_t mavlink_msg_sensor_avs_lite_ext_get_time_utc_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field timestamp from sensor_avs_lite_ext message
 *
 * @return  time since system start (microseconds)
 */
static inline uint64_t mavlink_msg_sensor_avs_lite_ext_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field timestamp_sample from sensor_avs_lite_ext message
 *
 * @return  AVS sensor sample index since system SYNC
 */
static inline uint32_t mavlink_msg_sensor_avs_lite_ext_get_timestamp_sample(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field azimuth_deg from sensor_avs_lite_ext message
 *
 * @return  azimuth in degrees
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_azimuth_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field elevation_deg from sensor_avs_lite_ext message
 *
 * @return  elevation in degrees
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_elevation_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field active_intensity from sensor_avs_lite_ext message
 *
 * @return  active intensity level re: 1 pW
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_active_intensity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field q_factor from sensor_avs_lite_ext message
 *
 * @return  Q-factor of the histogram peak for this detected source
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_q_factor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field histogram_count from sensor_avs_lite_ext message
 *
 * @return  number of hits for this azim/elev histogram bin
 */
static inline uint16_t mavlink_msg_sensor_avs_lite_ext_get_histogram_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  64);
}

/**
 * @brief Get field north from sensor_avs_lite_ext message
 *
 * @return   local north coordinate 
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_north(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field east from sensor_avs_lite_ext message
 *
 * @return   local east coordinate
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_east(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field down from sensor_avs_lite_ext message
 *
 * @return   local down coordinate
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field yaw from sensor_avs_lite_ext message
 *
 * @return   yaw
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field pitch from sensor_avs_lite_ext message
 *
 * @return   pitch
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field roll from sensor_avs_lite_ext message
 *
 * @return   roll
 */
static inline float mavlink_msg_sensor_avs_lite_ext_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Decode a sensor_avs_lite_ext message into a struct
 *
 * @param msg The message to decode
 * @param sensor_avs_lite_ext C-struct to decode the message contents into
 */
static inline void mavlink_msg_sensor_avs_lite_ext_decode(const mavlink_message_t* msg, mavlink_sensor_avs_lite_ext_t* sensor_avs_lite_ext)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sensor_avs_lite_ext->time_utc_usec = mavlink_msg_sensor_avs_lite_ext_get_time_utc_usec(msg);
    sensor_avs_lite_ext->timestamp = mavlink_msg_sensor_avs_lite_ext_get_timestamp(msg);
    sensor_avs_lite_ext->device_id = mavlink_msg_sensor_avs_lite_ext_get_device_id(msg);
    sensor_avs_lite_ext->timestamp_sample = mavlink_msg_sensor_avs_lite_ext_get_timestamp_sample(msg);
    sensor_avs_lite_ext->azimuth_deg = mavlink_msg_sensor_avs_lite_ext_get_azimuth_deg(msg);
    sensor_avs_lite_ext->elevation_deg = mavlink_msg_sensor_avs_lite_ext_get_elevation_deg(msg);
    sensor_avs_lite_ext->active_intensity = mavlink_msg_sensor_avs_lite_ext_get_active_intensity(msg);
    sensor_avs_lite_ext->q_factor = mavlink_msg_sensor_avs_lite_ext_get_q_factor(msg);
    sensor_avs_lite_ext->north = mavlink_msg_sensor_avs_lite_ext_get_north(msg);
    sensor_avs_lite_ext->east = mavlink_msg_sensor_avs_lite_ext_get_east(msg);
    sensor_avs_lite_ext->down = mavlink_msg_sensor_avs_lite_ext_get_down(msg);
    sensor_avs_lite_ext->yaw = mavlink_msg_sensor_avs_lite_ext_get_yaw(msg);
    sensor_avs_lite_ext->pitch = mavlink_msg_sensor_avs_lite_ext_get_pitch(msg);
    sensor_avs_lite_ext->roll = mavlink_msg_sensor_avs_lite_ext_get_roll(msg);
    sensor_avs_lite_ext->histogram_count = mavlink_msg_sensor_avs_lite_ext_get_histogram_count(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN? msg->len : MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN;
        memset(sensor_avs_lite_ext, 0, MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_LEN);
    memcpy(sensor_avs_lite_ext, _MAV_PAYLOAD(msg), len);
#endif
}
