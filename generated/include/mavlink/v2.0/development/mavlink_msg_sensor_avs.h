#pragma once
// MESSAGE SENSOR_AVS PACKING

#define MAVLINK_MSG_ID_SENSOR_AVS 292


typedef struct __mavlink_sensor_avs_t {
 uint64_t timestamp; /*<  time since system start (microseconds)*/
 uint64_t time_utc_usec; /*<  Timestamp (microseconds, UTC)*/
 uint32_t timestamp_sample; /*<  AVS sensor sample index since system SYNC*/
 uint32_t device_id; /*<  unique device ID for the sensor that does not change between power cycles*/
 float azimuth_deg; /*<  azimuth in degrees*/
 float elevation_deg; /*<  elevation in degrees*/
 float active_intensity; /*<  active intensity level re: 1 pW*/
 float q_factor; /*<  Q-factor of the histogram peak for this detected source*/
 float mel_intensity[16]; /*<  MEL Intensity spectrum*/
 uint16_t source_index; /*<  index of detected source_index*/
 uint16_t histogram_count; /*<  number of hits for this azim/elev histogram bin*/
} mavlink_sensor_avs_t;

#define MAVLINK_MSG_ID_SENSOR_AVS_LEN 108
#define MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN 108
#define MAVLINK_MSG_ID_292_LEN 108
#define MAVLINK_MSG_ID_292_MIN_LEN 108

#define MAVLINK_MSG_ID_SENSOR_AVS_CRC 166
#define MAVLINK_MSG_ID_292_CRC 166

#define MAVLINK_MSG_SENSOR_AVS_FIELD_MEL_INTENSITY_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SENSOR_AVS { \
    292, \
    "SENSOR_AVS", \
    11, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_sensor_avs_t, timestamp) }, \
         { "timestamp_sample", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_sensor_avs_t, timestamp_sample) }, \
         { "time_utc_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_sensor_avs_t, time_utc_usec) }, \
         { "device_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_sensor_avs_t, device_id) }, \
         { "azimuth_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_sensor_avs_t, azimuth_deg) }, \
         { "elevation_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_sensor_avs_t, elevation_deg) }, \
         { "active_intensity", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_sensor_avs_t, active_intensity) }, \
         { "q_factor", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_sensor_avs_t, q_factor) }, \
         { "source_index", NULL, MAVLINK_TYPE_UINT16_T, 0, 104, offsetof(mavlink_sensor_avs_t, source_index) }, \
         { "histogram_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 106, offsetof(mavlink_sensor_avs_t, histogram_count) }, \
         { "mel_intensity", NULL, MAVLINK_TYPE_FLOAT, 16, 40, offsetof(mavlink_sensor_avs_t, mel_intensity) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SENSOR_AVS { \
    "SENSOR_AVS", \
    11, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_sensor_avs_t, timestamp) }, \
         { "timestamp_sample", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_sensor_avs_t, timestamp_sample) }, \
         { "time_utc_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_sensor_avs_t, time_utc_usec) }, \
         { "device_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_sensor_avs_t, device_id) }, \
         { "azimuth_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_sensor_avs_t, azimuth_deg) }, \
         { "elevation_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_sensor_avs_t, elevation_deg) }, \
         { "active_intensity", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_sensor_avs_t, active_intensity) }, \
         { "q_factor", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_sensor_avs_t, q_factor) }, \
         { "source_index", NULL, MAVLINK_TYPE_UINT16_T, 0, 104, offsetof(mavlink_sensor_avs_t, source_index) }, \
         { "histogram_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 106, offsetof(mavlink_sensor_avs_t, histogram_count) }, \
         { "mel_intensity", NULL, MAVLINK_TYPE_FLOAT, 16, 40, offsetof(mavlink_sensor_avs_t, mel_intensity) }, \
         } \
}
#endif

/**
 * @brief Pack a sensor_avs message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param source_index  index of detected source_index
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param mel_intensity  MEL Intensity spectrum
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_avs_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, uint32_t timestamp_sample, uint64_t time_utc_usec, uint32_t device_id, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t source_index, uint16_t histogram_count, const float *mel_intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint64_t(buf, 8, time_utc_usec);
    _mav_put_uint32_t(buf, 16, timestamp_sample);
    _mav_put_uint32_t(buf, 20, device_id);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_uint16_t(buf, 104, source_index);
    _mav_put_uint16_t(buf, 106, histogram_count);
    _mav_put_float_array(buf, 40, mel_intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#else
    mavlink_sensor_avs_t packet;
    packet.timestamp = timestamp;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp_sample = timestamp_sample;
    packet.device_id = device_id;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.source_index = source_index;
    packet.histogram_count = histogram_count;
    mav_array_assign_float(packet.mel_intensity, mel_intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_AVS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
}

/**
 * @brief Pack a sensor_avs message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param source_index  index of detected source_index
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param mel_intensity  MEL Intensity spectrum
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_avs_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t timestamp, uint32_t timestamp_sample, uint64_t time_utc_usec, uint32_t device_id, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t source_index, uint16_t histogram_count, const float *mel_intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint64_t(buf, 8, time_utc_usec);
    _mav_put_uint32_t(buf, 16, timestamp_sample);
    _mav_put_uint32_t(buf, 20, device_id);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_uint16_t(buf, 104, source_index);
    _mav_put_uint16_t(buf, 106, histogram_count);
    _mav_put_float_array(buf, 40, mel_intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#else
    mavlink_sensor_avs_t packet;
    packet.timestamp = timestamp;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp_sample = timestamp_sample;
    packet.device_id = device_id;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.source_index = source_index;
    packet.histogram_count = histogram_count;
    mav_array_memcpy(packet.mel_intensity, mel_intensity, sizeof(float)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_AVS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#endif
}

/**
 * @brief Pack a sensor_avs message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param source_index  index of detected source_index
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param mel_intensity  MEL Intensity spectrum
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_avs_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,uint32_t timestamp_sample,uint64_t time_utc_usec,uint32_t device_id,float azimuth_deg,float elevation_deg,float active_intensity,float q_factor,uint16_t source_index,uint16_t histogram_count,const float *mel_intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint64_t(buf, 8, time_utc_usec);
    _mav_put_uint32_t(buf, 16, timestamp_sample);
    _mav_put_uint32_t(buf, 20, device_id);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_uint16_t(buf, 104, source_index);
    _mav_put_uint16_t(buf, 106, histogram_count);
    _mav_put_float_array(buf, 40, mel_intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#else
    mavlink_sensor_avs_t packet;
    packet.timestamp = timestamp;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp_sample = timestamp_sample;
    packet.device_id = device_id;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.source_index = source_index;
    packet.histogram_count = histogram_count;
    mav_array_assign_float(packet.mel_intensity, mel_intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_AVS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
}

/**
 * @brief Encode a sensor_avs struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sensor_avs C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_avs_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sensor_avs_t* sensor_avs)
{
    return mavlink_msg_sensor_avs_pack(system_id, component_id, msg, sensor_avs->timestamp, sensor_avs->timestamp_sample, sensor_avs->time_utc_usec, sensor_avs->device_id, sensor_avs->azimuth_deg, sensor_avs->elevation_deg, sensor_avs->active_intensity, sensor_avs->q_factor, sensor_avs->source_index, sensor_avs->histogram_count, sensor_avs->mel_intensity);
}

/**
 * @brief Encode a sensor_avs struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sensor_avs C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_avs_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sensor_avs_t* sensor_avs)
{
    return mavlink_msg_sensor_avs_pack_chan(system_id, component_id, chan, msg, sensor_avs->timestamp, sensor_avs->timestamp_sample, sensor_avs->time_utc_usec, sensor_avs->device_id, sensor_avs->azimuth_deg, sensor_avs->elevation_deg, sensor_avs->active_intensity, sensor_avs->q_factor, sensor_avs->source_index, sensor_avs->histogram_count, sensor_avs->mel_intensity);
}

/**
 * @brief Encode a sensor_avs struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param sensor_avs C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_avs_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_sensor_avs_t* sensor_avs)
{
    return mavlink_msg_sensor_avs_pack_status(system_id, component_id, _status, msg,  sensor_avs->timestamp, sensor_avs->timestamp_sample, sensor_avs->time_utc_usec, sensor_avs->device_id, sensor_avs->azimuth_deg, sensor_avs->elevation_deg, sensor_avs->active_intensity, sensor_avs->q_factor, sensor_avs->source_index, sensor_avs->histogram_count, sensor_avs->mel_intensity);
}

/**
 * @brief Send a sensor_avs message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp  time since system start (microseconds)
 * @param timestamp_sample  AVS sensor sample index since system SYNC
 * @param time_utc_usec  Timestamp (microseconds, UTC)
 * @param device_id  unique device ID for the sensor that does not change between power cycles
 * @param azimuth_deg  azimuth in degrees
 * @param elevation_deg  elevation in degrees
 * @param active_intensity  active intensity level re: 1 pW
 * @param q_factor  Q-factor of the histogram peak for this detected source
 * @param source_index  index of detected source_index
 * @param histogram_count  number of hits for this azim/elev histogram bin
 * @param mel_intensity  MEL Intensity spectrum
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sensor_avs_send(mavlink_channel_t chan, uint64_t timestamp, uint32_t timestamp_sample, uint64_t time_utc_usec, uint32_t device_id, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t source_index, uint16_t histogram_count, const float *mel_intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_AVS_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint64_t(buf, 8, time_utc_usec);
    _mav_put_uint32_t(buf, 16, timestamp_sample);
    _mav_put_uint32_t(buf, 20, device_id);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_uint16_t(buf, 104, source_index);
    _mav_put_uint16_t(buf, 106, histogram_count);
    _mav_put_float_array(buf, 40, mel_intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS, buf, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
#else
    mavlink_sensor_avs_t packet;
    packet.timestamp = timestamp;
    packet.time_utc_usec = time_utc_usec;
    packet.timestamp_sample = timestamp_sample;
    packet.device_id = device_id;
    packet.azimuth_deg = azimuth_deg;
    packet.elevation_deg = elevation_deg;
    packet.active_intensity = active_intensity;
    packet.q_factor = q_factor;
    packet.source_index = source_index;
    packet.histogram_count = histogram_count;
    mav_array_assign_float(packet.mel_intensity, mel_intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS, (const char *)&packet, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
#endif
}

/**
 * @brief Send a sensor_avs message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sensor_avs_send_struct(mavlink_channel_t chan, const mavlink_sensor_avs_t* sensor_avs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sensor_avs_send(chan, sensor_avs->timestamp, sensor_avs->timestamp_sample, sensor_avs->time_utc_usec, sensor_avs->device_id, sensor_avs->azimuth_deg, sensor_avs->elevation_deg, sensor_avs->active_intensity, sensor_avs->q_factor, sensor_avs->source_index, sensor_avs->histogram_count, sensor_avs->mel_intensity);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS, (const char *)sensor_avs, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SENSOR_AVS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sensor_avs_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, uint32_t timestamp_sample, uint64_t time_utc_usec, uint32_t device_id, float azimuth_deg, float elevation_deg, float active_intensity, float q_factor, uint16_t source_index, uint16_t histogram_count, const float *mel_intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint64_t(buf, 8, time_utc_usec);
    _mav_put_uint32_t(buf, 16, timestamp_sample);
    _mav_put_uint32_t(buf, 20, device_id);
    _mav_put_float(buf, 24, azimuth_deg);
    _mav_put_float(buf, 28, elevation_deg);
    _mav_put_float(buf, 32, active_intensity);
    _mav_put_float(buf, 36, q_factor);
    _mav_put_uint16_t(buf, 104, source_index);
    _mav_put_uint16_t(buf, 106, histogram_count);
    _mav_put_float_array(buf, 40, mel_intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS, buf, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
#else
    mavlink_sensor_avs_t *packet = (mavlink_sensor_avs_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->time_utc_usec = time_utc_usec;
    packet->timestamp_sample = timestamp_sample;
    packet->device_id = device_id;
    packet->azimuth_deg = azimuth_deg;
    packet->elevation_deg = elevation_deg;
    packet->active_intensity = active_intensity;
    packet->q_factor = q_factor;
    packet->source_index = source_index;
    packet->histogram_count = histogram_count;
    mav_array_assign_float(packet->mel_intensity, mel_intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_AVS, (const char *)packet, MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN, MAVLINK_MSG_ID_SENSOR_AVS_LEN, MAVLINK_MSG_ID_SENSOR_AVS_CRC);
#endif
}
#endif

#endif

// MESSAGE SENSOR_AVS UNPACKING


/**
 * @brief Get field timestamp from sensor_avs message
 *
 * @return  time since system start (microseconds)
 */
static inline uint64_t mavlink_msg_sensor_avs_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field timestamp_sample from sensor_avs message
 *
 * @return  AVS sensor sample index since system SYNC
 */
static inline uint32_t mavlink_msg_sensor_avs_get_timestamp_sample(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field time_utc_usec from sensor_avs message
 *
 * @return  Timestamp (microseconds, UTC)
 */
static inline uint64_t mavlink_msg_sensor_avs_get_time_utc_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field device_id from sensor_avs message
 *
 * @return  unique device ID for the sensor that does not change between power cycles
 */
static inline uint32_t mavlink_msg_sensor_avs_get_device_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field azimuth_deg from sensor_avs message
 *
 * @return  azimuth in degrees
 */
static inline float mavlink_msg_sensor_avs_get_azimuth_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field elevation_deg from sensor_avs message
 *
 * @return  elevation in degrees
 */
static inline float mavlink_msg_sensor_avs_get_elevation_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field active_intensity from sensor_avs message
 *
 * @return  active intensity level re: 1 pW
 */
static inline float mavlink_msg_sensor_avs_get_active_intensity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field q_factor from sensor_avs message
 *
 * @return  Q-factor of the histogram peak for this detected source
 */
static inline float mavlink_msg_sensor_avs_get_q_factor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field source_index from sensor_avs message
 *
 * @return  index of detected source_index
 */
static inline uint16_t mavlink_msg_sensor_avs_get_source_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  104);
}

/**
 * @brief Get field histogram_count from sensor_avs message
 *
 * @return  number of hits for this azim/elev histogram bin
 */
static inline uint16_t mavlink_msg_sensor_avs_get_histogram_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  106);
}

/**
 * @brief Get field mel_intensity from sensor_avs message
 *
 * @return  MEL Intensity spectrum
 */
static inline uint16_t mavlink_msg_sensor_avs_get_mel_intensity(const mavlink_message_t* msg, float *mel_intensity)
{
    return _MAV_RETURN_float_array(msg, mel_intensity, 16,  40);
}

/**
 * @brief Decode a sensor_avs message into a struct
 *
 * @param msg The message to decode
 * @param sensor_avs C-struct to decode the message contents into
 */
static inline void mavlink_msg_sensor_avs_decode(const mavlink_message_t* msg, mavlink_sensor_avs_t* sensor_avs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sensor_avs->timestamp = mavlink_msg_sensor_avs_get_timestamp(msg);
    sensor_avs->time_utc_usec = mavlink_msg_sensor_avs_get_time_utc_usec(msg);
    sensor_avs->timestamp_sample = mavlink_msg_sensor_avs_get_timestamp_sample(msg);
    sensor_avs->device_id = mavlink_msg_sensor_avs_get_device_id(msg);
    sensor_avs->azimuth_deg = mavlink_msg_sensor_avs_get_azimuth_deg(msg);
    sensor_avs->elevation_deg = mavlink_msg_sensor_avs_get_elevation_deg(msg);
    sensor_avs->active_intensity = mavlink_msg_sensor_avs_get_active_intensity(msg);
    sensor_avs->q_factor = mavlink_msg_sensor_avs_get_q_factor(msg);
    mavlink_msg_sensor_avs_get_mel_intensity(msg, sensor_avs->mel_intensity);
    sensor_avs->source_index = mavlink_msg_sensor_avs_get_source_index(msg);
    sensor_avs->histogram_count = mavlink_msg_sensor_avs_get_histogram_count(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SENSOR_AVS_LEN? msg->len : MAVLINK_MSG_ID_SENSOR_AVS_LEN;
        memset(sensor_avs, 0, MAVLINK_MSG_ID_SENSOR_AVS_LEN);
    memcpy(sensor_avs, _MAV_PAYLOAD(msg), len);
#endif
}
