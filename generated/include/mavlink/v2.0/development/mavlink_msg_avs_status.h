#pragma once
// MESSAGE AVS_STATUS PACKING

#define MAVLINK_MSG_ID_AVS_STATUS 2922


typedef struct __mavlink_avs_status_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch time).*/
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 uint32_t adcidx; /*<  ADC sample index of this event starting from AVS sync.*/
 float azim; /*< [deg] Estimated azimuth to the source.*/
 float elev; /*< [deg] Estimated elevation to the source.*/
 uint16_t histcnt; /*<  Histogram count at the maximum active intensity azimuth,elevation bin for this source.*/
 uint8_t melint[16]; /*< [W/m] Active intensity in each Mel band, 0.5 dB resolution*/
 uint8_t intensity; /*< [dB] Overall active intensity in the radial direction, 0.5 dB resolution.*/
 uint8_t qfac; /*<  Histogram Q-factor*/
 uint8_t srcidx; /*<  Detected source index, ordered from highest to lowest strength. minValue = 0, maxValue = 8, increment = 1.*/
 uint8_t bgint; /*<  Measurement of background intensity level, 0.5 dB resolution.*/
} mavlink_avs_status_t;

#define MAVLINK_MSG_ID_AVS_STATUS_LEN 46
#define MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN 46
#define MAVLINK_MSG_ID_2922_LEN 46
#define MAVLINK_MSG_ID_2922_MIN_LEN 46

#define MAVLINK_MSG_ID_AVS_STATUS_CRC 53
#define MAVLINK_MSG_ID_2922_CRC 53

#define MAVLINK_MSG_AVS_STATUS_FIELD_MELINT_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AVS_STATUS { \
    2922, \
    "AVS_STATUS", \
    11, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_avs_status_t, time_usec) }, \
         { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_avs_status_t, time_boot_ms) }, \
         { "adcidx", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_avs_status_t, adcidx) }, \
         { "azim", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_avs_status_t, azim) }, \
         { "elev", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_avs_status_t, elev) }, \
         { "histcnt", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_avs_status_t, histcnt) }, \
         { "melint", NULL, MAVLINK_TYPE_UINT8_T, 16, 26, offsetof(mavlink_avs_status_t, melint) }, \
         { "intensity", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_avs_status_t, intensity) }, \
         { "qfac", NULL, MAVLINK_TYPE_UINT8_T, 0, 43, offsetof(mavlink_avs_status_t, qfac) }, \
         { "srcidx", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_avs_status_t, srcidx) }, \
         { "bgint", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_avs_status_t, bgint) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AVS_STATUS { \
    "AVS_STATUS", \
    11, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_avs_status_t, time_usec) }, \
         { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_avs_status_t, time_boot_ms) }, \
         { "adcidx", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_avs_status_t, adcidx) }, \
         { "azim", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_avs_status_t, azim) }, \
         { "elev", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_avs_status_t, elev) }, \
         { "histcnt", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_avs_status_t, histcnt) }, \
         { "melint", NULL, MAVLINK_TYPE_UINT8_T, 16, 26, offsetof(mavlink_avs_status_t, melint) }, \
         { "intensity", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_avs_status_t, intensity) }, \
         { "qfac", NULL, MAVLINK_TYPE_UINT8_T, 0, 43, offsetof(mavlink_avs_status_t, qfac) }, \
         { "srcidx", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_avs_status_t, srcidx) }, \
         { "bgint", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_avs_status_t, bgint) }, \
         } \
}
#endif

/**
 * @brief Pack a avs_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param adcidx  ADC sample index of this event starting from AVS sync.
 * @param azim [deg] Estimated azimuth to the source.
 * @param elev [deg] Estimated elevation to the source.
 * @param histcnt  Histogram count at the maximum active intensity azimuth,elevation bin for this source.
 * @param melint [W/m] Active intensity in each Mel band, 0.5 dB resolution
 * @param intensity [dB] Overall active intensity in the radial direction, 0.5 dB resolution.
 * @param qfac  Histogram Q-factor
 * @param srcidx  Detected source index, ordered from highest to lowest strength. minValue = 0, maxValue = 8, increment = 1.
 * @param bgint  Measurement of background intensity level, 0.5 dB resolution.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_avs_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t time_boot_ms, uint32_t adcidx, float azim, float elev, uint16_t histcnt, const uint8_t *melint, uint8_t intensity, uint8_t qfac, uint8_t srcidx, uint8_t bgint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, adcidx);
    _mav_put_float(buf, 16, azim);
    _mav_put_float(buf, 20, elev);
    _mav_put_uint16_t(buf, 24, histcnt);
    _mav_put_uint8_t(buf, 42, intensity);
    _mav_put_uint8_t(buf, 43, qfac);
    _mav_put_uint8_t(buf, 44, srcidx);
    _mav_put_uint8_t(buf, 45, bgint);
    _mav_put_uint8_t_array(buf, 26, melint, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#else
    mavlink_avs_status_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.adcidx = adcidx;
    packet.azim = azim;
    packet.elev = elev;
    packet.histcnt = histcnt;
    packet.intensity = intensity;
    packet.qfac = qfac;
    packet.srcidx = srcidx;
    packet.bgint = bgint;
    mav_array_assign_uint8_t(packet.melint, melint, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AVS_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
}

/**
 * @brief Pack a avs_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param adcidx  ADC sample index of this event starting from AVS sync.
 * @param azim [deg] Estimated azimuth to the source.
 * @param elev [deg] Estimated elevation to the source.
 * @param histcnt  Histogram count at the maximum active intensity azimuth,elevation bin for this source.
 * @param melint [W/m] Active intensity in each Mel band, 0.5 dB resolution
 * @param intensity [dB] Overall active intensity in the radial direction, 0.5 dB resolution.
 * @param qfac  Histogram Q-factor
 * @param srcidx  Detected source index, ordered from highest to lowest strength. minValue = 0, maxValue = 8, increment = 1.
 * @param bgint  Measurement of background intensity level, 0.5 dB resolution.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_avs_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t time_boot_ms, uint32_t adcidx, float azim, float elev, uint16_t histcnt, const uint8_t *melint, uint8_t intensity, uint8_t qfac, uint8_t srcidx, uint8_t bgint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, adcidx);
    _mav_put_float(buf, 16, azim);
    _mav_put_float(buf, 20, elev);
    _mav_put_uint16_t(buf, 24, histcnt);
    _mav_put_uint8_t(buf, 42, intensity);
    _mav_put_uint8_t(buf, 43, qfac);
    _mav_put_uint8_t(buf, 44, srcidx);
    _mav_put_uint8_t(buf, 45, bgint);
    _mav_put_uint8_t_array(buf, 26, melint, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#else
    mavlink_avs_status_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.adcidx = adcidx;
    packet.azim = azim;
    packet.elev = elev;
    packet.histcnt = histcnt;
    packet.intensity = intensity;
    packet.qfac = qfac;
    packet.srcidx = srcidx;
    packet.bgint = bgint;
    mav_array_memcpy(packet.melint, melint, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AVS_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#endif
}

/**
 * @brief Pack a avs_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param adcidx  ADC sample index of this event starting from AVS sync.
 * @param azim [deg] Estimated azimuth to the source.
 * @param elev [deg] Estimated elevation to the source.
 * @param histcnt  Histogram count at the maximum active intensity azimuth,elevation bin for this source.
 * @param melint [W/m] Active intensity in each Mel band, 0.5 dB resolution
 * @param intensity [dB] Overall active intensity in the radial direction, 0.5 dB resolution.
 * @param qfac  Histogram Q-factor
 * @param srcidx  Detected source index, ordered from highest to lowest strength. minValue = 0, maxValue = 8, increment = 1.
 * @param bgint  Measurement of background intensity level, 0.5 dB resolution.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_avs_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t time_boot_ms,uint32_t adcidx,float azim,float elev,uint16_t histcnt,const uint8_t *melint,uint8_t intensity,uint8_t qfac,uint8_t srcidx,uint8_t bgint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, adcidx);
    _mav_put_float(buf, 16, azim);
    _mav_put_float(buf, 20, elev);
    _mav_put_uint16_t(buf, 24, histcnt);
    _mav_put_uint8_t(buf, 42, intensity);
    _mav_put_uint8_t(buf, 43, qfac);
    _mav_put_uint8_t(buf, 44, srcidx);
    _mav_put_uint8_t(buf, 45, bgint);
    _mav_put_uint8_t_array(buf, 26, melint, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#else
    mavlink_avs_status_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.adcidx = adcidx;
    packet.azim = azim;
    packet.elev = elev;
    packet.histcnt = histcnt;
    packet.intensity = intensity;
    packet.qfac = qfac;
    packet.srcidx = srcidx;
    packet.bgint = bgint;
    mav_array_assign_uint8_t(packet.melint, melint, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AVS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AVS_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
}

/**
 * @brief Encode a avs_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param avs_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_avs_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_avs_status_t* avs_status)
{
    return mavlink_msg_avs_status_pack(system_id, component_id, msg, avs_status->time_usec, avs_status->time_boot_ms, avs_status->adcidx, avs_status->azim, avs_status->elev, avs_status->histcnt, avs_status->melint, avs_status->intensity, avs_status->qfac, avs_status->srcidx, avs_status->bgint);
}

/**
 * @brief Encode a avs_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param avs_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_avs_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_avs_status_t* avs_status)
{
    return mavlink_msg_avs_status_pack_chan(system_id, component_id, chan, msg, avs_status->time_usec, avs_status->time_boot_ms, avs_status->adcidx, avs_status->azim, avs_status->elev, avs_status->histcnt, avs_status->melint, avs_status->intensity, avs_status->qfac, avs_status->srcidx, avs_status->bgint);
}

/**
 * @brief Encode a avs_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param avs_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_avs_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_avs_status_t* avs_status)
{
    return mavlink_msg_avs_status_pack_status(system_id, component_id, _status, msg,  avs_status->time_usec, avs_status->time_boot_ms, avs_status->adcidx, avs_status->azim, avs_status->elev, avs_status->histcnt, avs_status->melint, avs_status->intensity, avs_status->qfac, avs_status->srcidx, avs_status->bgint);
}

/**
 * @brief Send a avs_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch time).
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param adcidx  ADC sample index of this event starting from AVS sync.
 * @param azim [deg] Estimated azimuth to the source.
 * @param elev [deg] Estimated elevation to the source.
 * @param histcnt  Histogram count at the maximum active intensity azimuth,elevation bin for this source.
 * @param melint [W/m] Active intensity in each Mel band, 0.5 dB resolution
 * @param intensity [dB] Overall active intensity in the radial direction, 0.5 dB resolution.
 * @param qfac  Histogram Q-factor
 * @param srcidx  Detected source index, ordered from highest to lowest strength. minValue = 0, maxValue = 8, increment = 1.
 * @param bgint  Measurement of background intensity level, 0.5 dB resolution.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_avs_status_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t time_boot_ms, uint32_t adcidx, float azim, float elev, uint16_t histcnt, const uint8_t *melint, uint8_t intensity, uint8_t qfac, uint8_t srcidx, uint8_t bgint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AVS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, adcidx);
    _mav_put_float(buf, 16, azim);
    _mav_put_float(buf, 20, elev);
    _mav_put_uint16_t(buf, 24, histcnt);
    _mav_put_uint8_t(buf, 42, intensity);
    _mav_put_uint8_t(buf, 43, qfac);
    _mav_put_uint8_t(buf, 44, srcidx);
    _mav_put_uint8_t(buf, 45, bgint);
    _mav_put_uint8_t_array(buf, 26, melint, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_STATUS, buf, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
#else
    mavlink_avs_status_t packet;
    packet.time_usec = time_usec;
    packet.time_boot_ms = time_boot_ms;
    packet.adcidx = adcidx;
    packet.azim = azim;
    packet.elev = elev;
    packet.histcnt = histcnt;
    packet.intensity = intensity;
    packet.qfac = qfac;
    packet.srcidx = srcidx;
    packet.bgint = bgint;
    mav_array_assign_uint8_t(packet.melint, melint, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_STATUS, (const char *)&packet, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
#endif
}

/**
 * @brief Send a avs_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_avs_status_send_struct(mavlink_channel_t chan, const mavlink_avs_status_t* avs_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_avs_status_send(chan, avs_status->time_usec, avs_status->time_boot_ms, avs_status->adcidx, avs_status->azim, avs_status->elev, avs_status->histcnt, avs_status->melint, avs_status->intensity, avs_status->qfac, avs_status->srcidx, avs_status->bgint);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_STATUS, (const char *)avs_status, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_AVS_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_avs_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t time_boot_ms, uint32_t adcidx, float azim, float elev, uint16_t histcnt, const uint8_t *melint, uint8_t intensity, uint8_t qfac, uint8_t srcidx, uint8_t bgint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, time_boot_ms);
    _mav_put_uint32_t(buf, 12, adcidx);
    _mav_put_float(buf, 16, azim);
    _mav_put_float(buf, 20, elev);
    _mav_put_uint16_t(buf, 24, histcnt);
    _mav_put_uint8_t(buf, 42, intensity);
    _mav_put_uint8_t(buf, 43, qfac);
    _mav_put_uint8_t(buf, 44, srcidx);
    _mav_put_uint8_t(buf, 45, bgint);
    _mav_put_uint8_t_array(buf, 26, melint, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_STATUS, buf, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
#else
    mavlink_avs_status_t *packet = (mavlink_avs_status_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->time_boot_ms = time_boot_ms;
    packet->adcidx = adcidx;
    packet->azim = azim;
    packet->elev = elev;
    packet->histcnt = histcnt;
    packet->intensity = intensity;
    packet->qfac = qfac;
    packet->srcidx = srcidx;
    packet->bgint = bgint;
    mav_array_assign_uint8_t(packet->melint, melint, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AVS_STATUS, (const char *)packet, MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN, MAVLINK_MSG_ID_AVS_STATUS_LEN, MAVLINK_MSG_ID_AVS_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE AVS_STATUS UNPACKING


/**
 * @brief Get field time_usec from avs_status message
 *
 * @return [us] Timestamp (UNIX epoch time).
 */
static inline uint64_t mavlink_msg_avs_status_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field time_boot_ms from avs_status message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_avs_status_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field adcidx from avs_status message
 *
 * @return  ADC sample index of this event starting from AVS sync.
 */
static inline uint32_t mavlink_msg_avs_status_get_adcidx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field azim from avs_status message
 *
 * @return [deg] Estimated azimuth to the source.
 */
static inline float mavlink_msg_avs_status_get_azim(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field elev from avs_status message
 *
 * @return [deg] Estimated elevation to the source.
 */
static inline float mavlink_msg_avs_status_get_elev(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field histcnt from avs_status message
 *
 * @return  Histogram count at the maximum active intensity azimuth,elevation bin for this source.
 */
static inline uint16_t mavlink_msg_avs_status_get_histcnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field melint from avs_status message
 *
 * @return [W/m] Active intensity in each Mel band, 0.5 dB resolution
 */
static inline uint16_t mavlink_msg_avs_status_get_melint(const mavlink_message_t* msg, uint8_t *melint)
{
    return _MAV_RETURN_uint8_t_array(msg, melint, 16,  26);
}

/**
 * @brief Get field intensity from avs_status message
 *
 * @return [dB] Overall active intensity in the radial direction, 0.5 dB resolution.
 */
static inline uint8_t mavlink_msg_avs_status_get_intensity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  42);
}

/**
 * @brief Get field qfac from avs_status message
 *
 * @return  Histogram Q-factor
 */
static inline uint8_t mavlink_msg_avs_status_get_qfac(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  43);
}

/**
 * @brief Get field srcidx from avs_status message
 *
 * @return  Detected source index, ordered from highest to lowest strength. minValue = 0, maxValue = 8, increment = 1.
 */
static inline uint8_t mavlink_msg_avs_status_get_srcidx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  44);
}

/**
 * @brief Get field bgint from avs_status message
 *
 * @return  Measurement of background intensity level, 0.5 dB resolution.
 */
static inline uint8_t mavlink_msg_avs_status_get_bgint(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Decode a avs_status message into a struct
 *
 * @param msg The message to decode
 * @param avs_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_avs_status_decode(const mavlink_message_t* msg, mavlink_avs_status_t* avs_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    avs_status->time_usec = mavlink_msg_avs_status_get_time_usec(msg);
    avs_status->time_boot_ms = mavlink_msg_avs_status_get_time_boot_ms(msg);
    avs_status->adcidx = mavlink_msg_avs_status_get_adcidx(msg);
    avs_status->azim = mavlink_msg_avs_status_get_azim(msg);
    avs_status->elev = mavlink_msg_avs_status_get_elev(msg);
    avs_status->histcnt = mavlink_msg_avs_status_get_histcnt(msg);
    mavlink_msg_avs_status_get_melint(msg, avs_status->melint);
    avs_status->intensity = mavlink_msg_avs_status_get_intensity(msg);
    avs_status->qfac = mavlink_msg_avs_status_get_qfac(msg);
    avs_status->srcidx = mavlink_msg_avs_status_get_srcidx(msg);
    avs_status->bgint = mavlink_msg_avs_status_get_bgint(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AVS_STATUS_LEN? msg->len : MAVLINK_MSG_ID_AVS_STATUS_LEN;
        memset(avs_status, 0, MAVLINK_MSG_ID_AVS_STATUS_LEN);
    memcpy(avs_status, _MAV_PAYLOAD(msg), len);
#endif
}
