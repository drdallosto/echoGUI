#pragma once
// MESSAGE AVS_MFC PACKING

#define MAVLINK_MSG_ID_AVS_MFC 294


typedef struct __mavlink_avs_mfc_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch time).*/
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 uint32_t sample_index; /*<  ADC sample index of this event starting from AVS sync.*/
 float intensity[16]; /*< [W/m] Active intensity in each Mel band*/
 uint8_t node_id; /*<  Node ID.*/
} mavlink_avs_mfc_t;

#define MAVLINK_MSG_ID_AVS_MFC_LEN 81
#define MAVLINK_MSG_ID_AVS_MFC_MIN_LEN 81
#define MAVLINK_MSG_ID_294_LEN 81
#define MAVLINK_MSG_ID_294_MIN_LEN 81

#define MAVLINK_MSG_ID_AVS_MFC_CRC 213
#define MAVLINK_MSG_ID_294_CRC 213

#define MAVLINK_MSG_AVS_MFC_FIELD_INTENSITY_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AVS_MFC { \
    294, \
    "AVS_MFC", \
    5, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_avs_mfc_t, time_boot_ms) }, \
         { "sample_index", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_avs_mfc_t, sample_index) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_avs_mfc_t, time_usec) }, \
         { "node_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 80, offsetof(mavlink_avs_mfc_t, node_id) }, \
         { "intensity", NULL, MAVLINK_TYPE_FLOAT, 16, 16, offsetof(mavlink_avs_mfc_t, intensity) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AVS_MFC { \
    "AVS_MFC", \
    5, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_avs_mfc_t, time_boot_ms) }, \
         { "sample_index", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_avs_mfc_t, sample_index) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_avs_mfc_t, time_usec) }, \
         { "node_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 80, offsetof(mavlink_avs_mfc_t, node_id) }, \
         { "intensity", NULL, MAVLINK_TYPE_FLOAT, 16, 16, offsetof(mavlink_avs_mfc_t, intensity) }, \
         } \
}
#endif

/**
 * @brief Pack a avs_mfc message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param sample_index  ADC sample index of this event starting from AVS sync.
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param node_id  Node ID.
 * @param intensity [W/m] Active intensity in each Mel band
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_avs_mfc_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, uint32_t sample_index, uint64_t time_usec, uint8_t node_id, const float *intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_MFC_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, sample_index);
    _mav_put_uint8_t(buf, 80, node_id);
    _mav_put_float_array(buf, 16, intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AVS_MFC_LEN);
#else
    mavlink_avs_mfc_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.sample_index = sample_index;
    packet.node_id = node_id;
    mav_array_assign_float(packet.intensity, intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AVS_MFC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AVS_MFC;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
}

/**
 * @brief Pack a avs_mfc message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param sample_index  ADC sample index of this event starting from AVS sync.
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param node_id  Node ID.
 * @param intensity [W/m] Active intensity in each Mel band
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_avs_mfc_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t time_boot_ms, uint32_t sample_index, uint64_t time_usec, uint8_t node_id, const float *intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_MFC_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, sample_index);
    _mav_put_uint8_t(buf, 80, node_id);
    _mav_put_float_array(buf, 16, intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AVS_MFC_LEN);
#else
    mavlink_avs_mfc_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.sample_index = sample_index;
    packet.node_id = node_id;
    mav_array_memcpy(packet.intensity, intensity, sizeof(float)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AVS_MFC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AVS_MFC;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN);
#endif
}

/**
 * @brief Pack a avs_mfc message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param sample_index  ADC sample index of this event starting from AVS sync.
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param node_id  Node ID.
 * @param intensity [W/m] Active intensity in each Mel band
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_avs_mfc_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,uint32_t sample_index,uint64_t time_usec,uint8_t node_id,const float *intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_MFC_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, sample_index);
    _mav_put_uint8_t(buf, 80, node_id);
    _mav_put_float_array(buf, 16, intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AVS_MFC_LEN);
#else
    mavlink_avs_mfc_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.sample_index = sample_index;
    packet.node_id = node_id;
    mav_array_assign_float(packet.intensity, intensity, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AVS_MFC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AVS_MFC;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
}

/**
 * @brief Encode a avs_mfc struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param avs_mfc C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_avs_mfc_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_avs_mfc_t* avs_mfc)
{
    return mavlink_msg_avs_mfc_pack(system_id, component_id, msg, avs_mfc->time_boot_ms, avs_mfc->sample_index, avs_mfc->time_usec, avs_mfc->node_id, avs_mfc->intensity);
}

/**
 * @brief Encode a avs_mfc struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param avs_mfc C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_avs_mfc_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_avs_mfc_t* avs_mfc)
{
    return mavlink_msg_avs_mfc_pack_chan(system_id, component_id, chan, msg, avs_mfc->time_boot_ms, avs_mfc->sample_index, avs_mfc->time_usec, avs_mfc->node_id, avs_mfc->intensity);
}

/**
 * @brief Encode a avs_mfc struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param avs_mfc C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_avs_mfc_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_avs_mfc_t* avs_mfc)
{
    return mavlink_msg_avs_mfc_pack_status(system_id, component_id, _status, msg,  avs_mfc->time_boot_ms, avs_mfc->sample_index, avs_mfc->time_usec, avs_mfc->node_id, avs_mfc->intensity);
}

/**
 * @brief Send a avs_mfc message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param sample_index  ADC sample index of this event starting from AVS sync.
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param node_id  Node ID.
 * @param intensity [W/m] Active intensity in each Mel band
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_avs_mfc_send(mavlink_channel_t chan, uint32_t time_boot_ms, uint32_t sample_index, uint64_t time_usec, uint8_t node_id, const float *intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_MFC_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, sample_index);
    _mav_put_uint8_t(buf, 80, node_id);
    _mav_put_float_array(buf, 16, intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_MFC, buf, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
#else
    mavlink_avs_mfc_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.sample_index = sample_index;
    packet.node_id = node_id;
    mav_array_assign_float(packet.intensity, intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_MFC, (const char *)&packet, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
#endif
}

/**
 * @brief Send a avs_mfc message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_avs_mfc_send_struct(mavlink_channel_t chan, const mavlink_avs_mfc_t* avs_mfc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_avs_mfc_send(chan, avs_mfc->time_boot_ms, avs_mfc->sample_index, avs_mfc->time_usec, avs_mfc->node_id, avs_mfc->intensity);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_MFC, (const char *)avs_mfc, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
#endif
}

#if MAVLINK_MSG_ID_AVS_MFC_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_avs_mfc_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, uint32_t sample_index, uint64_t time_usec, uint8_t node_id, const float *intensity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, sample_index);
    _mav_put_uint8_t(buf, 80, node_id);
    _mav_put_float_array(buf, 16, intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_MFC, buf, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
#else
    mavlink_avs_mfc_t *packet = (mavlink_avs_mfc_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->time_boot_ms = time_boot_ms;
    packet->sample_index = sample_index;
    packet->node_id = node_id;
    mav_array_assign_float(packet->intensity, intensity, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_MFC, (const char *)packet, MAVLINK_MSG_ID_AVS_MFC_MIN_LEN, MAVLINK_MSG_ID_AVS_MFC_LEN, MAVLINK_MSG_ID_AVS_MFC_CRC);
#endif
}
#endif

#endif

// MESSAGE AVS_MFC UNPACKING


/**
 * @brief Get field time_boot_ms from avs_mfc message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_avs_mfc_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field sample_index from avs_mfc message
 *
 * @return  ADC sample index of this event starting from AVS sync.
 */
static inline uint32_t mavlink_msg_avs_mfc_get_sample_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field time_usec from avs_mfc message
 *
 * @return [us] Timestamp (UNIX epoch time).
 */
static inline uint64_t mavlink_msg_avs_mfc_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field node_id from avs_mfc message
 *
 * @return  Node ID.
 */
static inline uint8_t mavlink_msg_avs_mfc_get_node_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  80);
}

/**
 * @brief Get field intensity from avs_mfc message
 *
 * @return [W/m] Active intensity in each Mel band
 */
static inline uint16_t mavlink_msg_avs_mfc_get_intensity(const mavlink_message_t* msg, float *intensity)
{
    return _MAV_RETURN_float_array(msg, intensity, 16,  16);
}

/**
 * @brief Decode a avs_mfc message into a struct
 *
 * @param msg The message to decode
 * @param avs_mfc C-struct to decode the message contents into
 */
static inline void mavlink_msg_avs_mfc_decode(const mavlink_message_t* msg, mavlink_avs_mfc_t* avs_mfc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    avs_mfc->time_usec = mavlink_msg_avs_mfc_get_time_usec(msg);
    avs_mfc->time_boot_ms = mavlink_msg_avs_mfc_get_time_boot_ms(msg);
    avs_mfc->sample_index = mavlink_msg_avs_mfc_get_sample_index(msg);
    mavlink_msg_avs_mfc_get_intensity(msg, avs_mfc->intensity);
    avs_mfc->node_id = mavlink_msg_avs_mfc_get_node_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AVS_MFC_LEN? msg->len : MAVLINK_MSG_ID_AVS_MFC_LEN;
        memset(avs_mfc, 0, MAVLINK_MSG_ID_AVS_MFC_LEN);
    memcpy(avs_mfc, _MAV_PAYLOAD(msg), len);
#endif
}
