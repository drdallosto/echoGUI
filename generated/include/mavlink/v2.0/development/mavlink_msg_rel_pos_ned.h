#pragma once
// MESSAGE REL_POS_NED PACKING

#define MAVLINK_MSG_ID_REL_POS_NED 293


typedef struct __mavlink_rel_pos_ned_t {
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 float north; /*< [m] Relative North coordinate.*/
 float east; /*< [m] Relative East coordinate.*/
 float down; /*< [m] Relative Down coordinate.*/
 float acc_n; /*< [m] Relative North coordinate accuracy.*/
 float acc_e; /*< [m] Relative East coordinate accuracy.*/
 float acc_d; /*< [m] Relative Down coordinate accuracy.*/
 float head; /*< [deg] Estimated moving baseline heading.*/
 float acc_h; /*< [deg] Estimated heading accuracy.*/
 float len; /*< [m] Estimated baseline length.*/
 float acc_l; /*< [m] Estimated baseline accuracy.*/
 uint8_t node_id; /*<  Node ID.*/
 uint8_t fixed; /*<  Fix quality.*/
} mavlink_rel_pos_ned_t;

#define MAVLINK_MSG_ID_REL_POS_NED_LEN 46
#define MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN 46
#define MAVLINK_MSG_ID_293_LEN 46
#define MAVLINK_MSG_ID_293_MIN_LEN 46

#define MAVLINK_MSG_ID_REL_POS_NED_CRC 236
#define MAVLINK_MSG_ID_293_CRC 236



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_REL_POS_NED { \
    293, \
    "REL_POS_NED", \
    13, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_rel_pos_ned_t, time_boot_ms) }, \
         { "north", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_rel_pos_ned_t, north) }, \
         { "east", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rel_pos_ned_t, east) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rel_pos_ned_t, down) }, \
         { "acc_n", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rel_pos_ned_t, acc_n) }, \
         { "acc_e", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rel_pos_ned_t, acc_e) }, \
         { "acc_d", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_rel_pos_ned_t, acc_d) }, \
         { "head", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_rel_pos_ned_t, head) }, \
         { "acc_h", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_rel_pos_ned_t, acc_h) }, \
         { "len", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_rel_pos_ned_t, len) }, \
         { "acc_l", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_rel_pos_ned_t, acc_l) }, \
         { "node_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_rel_pos_ned_t, node_id) }, \
         { "fixed", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_rel_pos_ned_t, fixed) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_REL_POS_NED { \
    "REL_POS_NED", \
    13, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_rel_pos_ned_t, time_boot_ms) }, \
         { "north", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_rel_pos_ned_t, north) }, \
         { "east", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rel_pos_ned_t, east) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rel_pos_ned_t, down) }, \
         { "acc_n", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rel_pos_ned_t, acc_n) }, \
         { "acc_e", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rel_pos_ned_t, acc_e) }, \
         { "acc_d", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_rel_pos_ned_t, acc_d) }, \
         { "head", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_rel_pos_ned_t, head) }, \
         { "acc_h", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_rel_pos_ned_t, acc_h) }, \
         { "len", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_rel_pos_ned_t, len) }, \
         { "acc_l", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_rel_pos_ned_t, acc_l) }, \
         { "node_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_rel_pos_ned_t, node_id) }, \
         { "fixed", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_rel_pos_ned_t, fixed) }, \
         } \
}
#endif

/**
 * @brief Pack a rel_pos_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param north [m] Relative North coordinate.
 * @param east [m] Relative East coordinate.
 * @param down [m] Relative Down coordinate.
 * @param acc_n [m] Relative North coordinate accuracy.
 * @param acc_e [m] Relative East coordinate accuracy.
 * @param acc_d [m] Relative Down coordinate accuracy.
 * @param head [deg] Estimated moving baseline heading.
 * @param acc_h [deg] Estimated heading accuracy.
 * @param len [m] Estimated baseline length.
 * @param acc_l [m] Estimated baseline accuracy.
 * @param node_id  Node ID.
 * @param fixed  Fix quality.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rel_pos_ned_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, float north, float east, float down, float acc_n, float acc_e, float acc_d, float head, float acc_h, float len, float acc_l, uint8_t node_id, uint8_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REL_POS_NED_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, north);
    _mav_put_float(buf, 8, east);
    _mav_put_float(buf, 12, down);
    _mav_put_float(buf, 16, acc_n);
    _mav_put_float(buf, 20, acc_e);
    _mav_put_float(buf, 24, acc_d);
    _mav_put_float(buf, 28, head);
    _mav_put_float(buf, 32, acc_h);
    _mav_put_float(buf, 36, len);
    _mav_put_float(buf, 40, acc_l);
    _mav_put_uint8_t(buf, 44, node_id);
    _mav_put_uint8_t(buf, 45, fixed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#else
    mavlink_rel_pos_ned_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.head = head;
    packet.acc_h = acc_h;
    packet.len = len;
    packet.acc_l = acc_l;
    packet.node_id = node_id;
    packet.fixed = fixed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_REL_POS_NED;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
}

/**
 * @brief Pack a rel_pos_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param north [m] Relative North coordinate.
 * @param east [m] Relative East coordinate.
 * @param down [m] Relative Down coordinate.
 * @param acc_n [m] Relative North coordinate accuracy.
 * @param acc_e [m] Relative East coordinate accuracy.
 * @param acc_d [m] Relative Down coordinate accuracy.
 * @param head [deg] Estimated moving baseline heading.
 * @param acc_h [deg] Estimated heading accuracy.
 * @param len [m] Estimated baseline length.
 * @param acc_l [m] Estimated baseline accuracy.
 * @param node_id  Node ID.
 * @param fixed  Fix quality.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rel_pos_ned_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t time_boot_ms, float north, float east, float down, float acc_n, float acc_e, float acc_d, float head, float acc_h, float len, float acc_l, uint8_t node_id, uint8_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REL_POS_NED_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, north);
    _mav_put_float(buf, 8, east);
    _mav_put_float(buf, 12, down);
    _mav_put_float(buf, 16, acc_n);
    _mav_put_float(buf, 20, acc_e);
    _mav_put_float(buf, 24, acc_d);
    _mav_put_float(buf, 28, head);
    _mav_put_float(buf, 32, acc_h);
    _mav_put_float(buf, 36, len);
    _mav_put_float(buf, 40, acc_l);
    _mav_put_uint8_t(buf, 44, node_id);
    _mav_put_uint8_t(buf, 45, fixed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#else
    mavlink_rel_pos_ned_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.head = head;
    packet.acc_h = acc_h;
    packet.len = len;
    packet.acc_l = acc_l;
    packet.node_id = node_id;
    packet.fixed = fixed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_REL_POS_NED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#endif
}

/**
 * @brief Pack a rel_pos_ned message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param north [m] Relative North coordinate.
 * @param east [m] Relative East coordinate.
 * @param down [m] Relative Down coordinate.
 * @param acc_n [m] Relative North coordinate accuracy.
 * @param acc_e [m] Relative East coordinate accuracy.
 * @param acc_d [m] Relative Down coordinate accuracy.
 * @param head [deg] Estimated moving baseline heading.
 * @param acc_h [deg] Estimated heading accuracy.
 * @param len [m] Estimated baseline length.
 * @param acc_l [m] Estimated baseline accuracy.
 * @param node_id  Node ID.
 * @param fixed  Fix quality.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rel_pos_ned_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,float north,float east,float down,float acc_n,float acc_e,float acc_d,float head,float acc_h,float len,float acc_l,uint8_t node_id,uint8_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REL_POS_NED_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, north);
    _mav_put_float(buf, 8, east);
    _mav_put_float(buf, 12, down);
    _mav_put_float(buf, 16, acc_n);
    _mav_put_float(buf, 20, acc_e);
    _mav_put_float(buf, 24, acc_d);
    _mav_put_float(buf, 28, head);
    _mav_put_float(buf, 32, acc_h);
    _mav_put_float(buf, 36, len);
    _mav_put_float(buf, 40, acc_l);
    _mav_put_uint8_t(buf, 44, node_id);
    _mav_put_uint8_t(buf, 45, fixed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#else
    mavlink_rel_pos_ned_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.head = head;
    packet.acc_h = acc_h;
    packet.len = len;
    packet.acc_l = acc_l;
    packet.node_id = node_id;
    packet.fixed = fixed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_REL_POS_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_REL_POS_NED;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
}

/**
 * @brief Encode a rel_pos_ned struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rel_pos_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rel_pos_ned_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rel_pos_ned_t* rel_pos_ned)
{
    return mavlink_msg_rel_pos_ned_pack(system_id, component_id, msg, rel_pos_ned->time_boot_ms, rel_pos_ned->north, rel_pos_ned->east, rel_pos_ned->down, rel_pos_ned->acc_n, rel_pos_ned->acc_e, rel_pos_ned->acc_d, rel_pos_ned->head, rel_pos_ned->acc_h, rel_pos_ned->len, rel_pos_ned->acc_l, rel_pos_ned->node_id, rel_pos_ned->fixed);
}

/**
 * @brief Encode a rel_pos_ned struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rel_pos_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rel_pos_ned_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rel_pos_ned_t* rel_pos_ned)
{
    return mavlink_msg_rel_pos_ned_pack_chan(system_id, component_id, chan, msg, rel_pos_ned->time_boot_ms, rel_pos_ned->north, rel_pos_ned->east, rel_pos_ned->down, rel_pos_ned->acc_n, rel_pos_ned->acc_e, rel_pos_ned->acc_d, rel_pos_ned->head, rel_pos_ned->acc_h, rel_pos_ned->len, rel_pos_ned->acc_l, rel_pos_ned->node_id, rel_pos_ned->fixed);
}

/**
 * @brief Encode a rel_pos_ned struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param rel_pos_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rel_pos_ned_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_rel_pos_ned_t* rel_pos_ned)
{
    return mavlink_msg_rel_pos_ned_pack_status(system_id, component_id, _status, msg,  rel_pos_ned->time_boot_ms, rel_pos_ned->north, rel_pos_ned->east, rel_pos_ned->down, rel_pos_ned->acc_n, rel_pos_ned->acc_e, rel_pos_ned->acc_d, rel_pos_ned->head, rel_pos_ned->acc_h, rel_pos_ned->len, rel_pos_ned->acc_l, rel_pos_ned->node_id, rel_pos_ned->fixed);
}

/**
 * @brief Send a rel_pos_ned message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param north [m] Relative North coordinate.
 * @param east [m] Relative East coordinate.
 * @param down [m] Relative Down coordinate.
 * @param acc_n [m] Relative North coordinate accuracy.
 * @param acc_e [m] Relative East coordinate accuracy.
 * @param acc_d [m] Relative Down coordinate accuracy.
 * @param head [deg] Estimated moving baseline heading.
 * @param acc_h [deg] Estimated heading accuracy.
 * @param len [m] Estimated baseline length.
 * @param acc_l [m] Estimated baseline accuracy.
 * @param node_id  Node ID.
 * @param fixed  Fix quality.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rel_pos_ned_send(mavlink_channel_t chan, uint32_t time_boot_ms, float north, float east, float down, float acc_n, float acc_e, float acc_d, float head, float acc_h, float len, float acc_l, uint8_t node_id, uint8_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REL_POS_NED_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, north);
    _mav_put_float(buf, 8, east);
    _mav_put_float(buf, 12, down);
    _mav_put_float(buf, 16, acc_n);
    _mav_put_float(buf, 20, acc_e);
    _mav_put_float(buf, 24, acc_d);
    _mav_put_float(buf, 28, head);
    _mav_put_float(buf, 32, acc_h);
    _mav_put_float(buf, 36, len);
    _mav_put_float(buf, 40, acc_l);
    _mav_put_uint8_t(buf, 44, node_id);
    _mav_put_uint8_t(buf, 45, fixed);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REL_POS_NED, buf, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
#else
    mavlink_rel_pos_ned_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.north = north;
    packet.east = east;
    packet.down = down;
    packet.acc_n = acc_n;
    packet.acc_e = acc_e;
    packet.acc_d = acc_d;
    packet.head = head;
    packet.acc_h = acc_h;
    packet.len = len;
    packet.acc_l = acc_l;
    packet.node_id = node_id;
    packet.fixed = fixed;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REL_POS_NED, (const char *)&packet, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
#endif
}

/**
 * @brief Send a rel_pos_ned message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rel_pos_ned_send_struct(mavlink_channel_t chan, const mavlink_rel_pos_ned_t* rel_pos_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rel_pos_ned_send(chan, rel_pos_ned->time_boot_ms, rel_pos_ned->north, rel_pos_ned->east, rel_pos_ned->down, rel_pos_ned->acc_n, rel_pos_ned->acc_e, rel_pos_ned->acc_d, rel_pos_ned->head, rel_pos_ned->acc_h, rel_pos_ned->len, rel_pos_ned->acc_l, rel_pos_ned->node_id, rel_pos_ned->fixed);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REL_POS_NED, (const char *)rel_pos_ned, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
#endif
}

#if MAVLINK_MSG_ID_REL_POS_NED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rel_pos_ned_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, float north, float east, float down, float acc_n, float acc_e, float acc_d, float head, float acc_h, float len, float acc_l, uint8_t node_id, uint8_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, north);
    _mav_put_float(buf, 8, east);
    _mav_put_float(buf, 12, down);
    _mav_put_float(buf, 16, acc_n);
    _mav_put_float(buf, 20, acc_e);
    _mav_put_float(buf, 24, acc_d);
    _mav_put_float(buf, 28, head);
    _mav_put_float(buf, 32, acc_h);
    _mav_put_float(buf, 36, len);
    _mav_put_float(buf, 40, acc_l);
    _mav_put_uint8_t(buf, 44, node_id);
    _mav_put_uint8_t(buf, 45, fixed);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REL_POS_NED, buf, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
#else
    mavlink_rel_pos_ned_t *packet = (mavlink_rel_pos_ned_t *)msgbuf;
    packet->time_boot_ms = time_boot_ms;
    packet->north = north;
    packet->east = east;
    packet->down = down;
    packet->acc_n = acc_n;
    packet->acc_e = acc_e;
    packet->acc_d = acc_d;
    packet->head = head;
    packet->acc_h = acc_h;
    packet->len = len;
    packet->acc_l = acc_l;
    packet->node_id = node_id;
    packet->fixed = fixed;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REL_POS_NED, (const char *)packet, MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN, MAVLINK_MSG_ID_REL_POS_NED_LEN, MAVLINK_MSG_ID_REL_POS_NED_CRC);
#endif
}
#endif

#endif

// MESSAGE REL_POS_NED UNPACKING


/**
 * @brief Get field time_boot_ms from rel_pos_ned message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_rel_pos_ned_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field north from rel_pos_ned message
 *
 * @return [m] Relative North coordinate.
 */
static inline float mavlink_msg_rel_pos_ned_get_north(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field east from rel_pos_ned message
 *
 * @return [m] Relative East coordinate.
 */
static inline float mavlink_msg_rel_pos_ned_get_east(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field down from rel_pos_ned message
 *
 * @return [m] Relative Down coordinate.
 */
static inline float mavlink_msg_rel_pos_ned_get_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field acc_n from rel_pos_ned message
 *
 * @return [m] Relative North coordinate accuracy.
 */
static inline float mavlink_msg_rel_pos_ned_get_acc_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field acc_e from rel_pos_ned message
 *
 * @return [m] Relative East coordinate accuracy.
 */
static inline float mavlink_msg_rel_pos_ned_get_acc_e(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field acc_d from rel_pos_ned message
 *
 * @return [m] Relative Down coordinate accuracy.
 */
static inline float mavlink_msg_rel_pos_ned_get_acc_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field head from rel_pos_ned message
 *
 * @return [deg] Estimated moving baseline heading.
 */
static inline float mavlink_msg_rel_pos_ned_get_head(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field acc_h from rel_pos_ned message
 *
 * @return [deg] Estimated heading accuracy.
 */
static inline float mavlink_msg_rel_pos_ned_get_acc_h(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field len from rel_pos_ned message
 *
 * @return [m] Estimated baseline length.
 */
static inline float mavlink_msg_rel_pos_ned_get_len(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field acc_l from rel_pos_ned message
 *
 * @return [m] Estimated baseline accuracy.
 */
static inline float mavlink_msg_rel_pos_ned_get_acc_l(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field node_id from rel_pos_ned message
 *
 * @return  Node ID.
 */
static inline uint8_t mavlink_msg_rel_pos_ned_get_node_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  44);
}

/**
 * @brief Get field fixed from rel_pos_ned message
 *
 * @return  Fix quality.
 */
static inline uint8_t mavlink_msg_rel_pos_ned_get_fixed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Decode a rel_pos_ned message into a struct
 *
 * @param msg The message to decode
 * @param rel_pos_ned C-struct to decode the message contents into
 */
static inline void mavlink_msg_rel_pos_ned_decode(const mavlink_message_t* msg, mavlink_rel_pos_ned_t* rel_pos_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rel_pos_ned->time_boot_ms = mavlink_msg_rel_pos_ned_get_time_boot_ms(msg);
    rel_pos_ned->north = mavlink_msg_rel_pos_ned_get_north(msg);
    rel_pos_ned->east = mavlink_msg_rel_pos_ned_get_east(msg);
    rel_pos_ned->down = mavlink_msg_rel_pos_ned_get_down(msg);
    rel_pos_ned->acc_n = mavlink_msg_rel_pos_ned_get_acc_n(msg);
    rel_pos_ned->acc_e = mavlink_msg_rel_pos_ned_get_acc_e(msg);
    rel_pos_ned->acc_d = mavlink_msg_rel_pos_ned_get_acc_d(msg);
    rel_pos_ned->head = mavlink_msg_rel_pos_ned_get_head(msg);
    rel_pos_ned->acc_h = mavlink_msg_rel_pos_ned_get_acc_h(msg);
    rel_pos_ned->len = mavlink_msg_rel_pos_ned_get_len(msg);
    rel_pos_ned->acc_l = mavlink_msg_rel_pos_ned_get_acc_l(msg);
    rel_pos_ned->node_id = mavlink_msg_rel_pos_ned_get_node_id(msg);
    rel_pos_ned->fixed = mavlink_msg_rel_pos_ned_get_fixed(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_REL_POS_NED_LEN? msg->len : MAVLINK_MSG_ID_REL_POS_NED_LEN;
        memset(rel_pos_ned, 0, MAVLINK_MSG_ID_REL_POS_NED_LEN);
    memcpy(rel_pos_ned, _MAV_PAYLOAD(msg), len);
#endif
}
