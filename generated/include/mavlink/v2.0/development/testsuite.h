/** @file
 *    @brief MAVLink comm protocol testsuite generated from development.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef DEVELOPMENT_TESTSUITE_H
#define DEVELOPMENT_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_development(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_development(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_airspeed(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AIRSPEED >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_airspeed_t packet_in = {
        17.0,45.0,17651,163,230
    };
    mavlink_airspeed_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.airspeed = packet_in.airspeed;
        packet1.raw_press = packet_in.raw_press;
        packet1.temperature = packet_in.temperature;
        packet1.id = packet_in.id;
        packet1.flags = packet_in.flags;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AIRSPEED_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AIRSPEED_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeed_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_airspeed_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeed_pack(system_id, component_id, &msg , packet1.id , packet1.airspeed , packet1.temperature , packet1.raw_press , packet1.flags );
    mavlink_msg_airspeed_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeed_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id , packet1.airspeed , packet1.temperature , packet1.raw_press , packet1.flags );
    mavlink_msg_airspeed_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_airspeed_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeed_send(MAVLINK_COMM_1 , packet1.id , packet1.airspeed , packet1.temperature , packet1.raw_press , packet1.flags );
    mavlink_msg_airspeed_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AIRSPEED") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AIRSPEED) != NULL);
#endif
}

static void mavlink_test_set_velocity_limits(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SET_VELOCITY_LIMITS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_set_velocity_limits_t packet_in = {
        17.0,45.0,73.0,41,108
    };
    mavlink_set_velocity_limits_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.horizontal_speed_limit = packet_in.horizontal_speed_limit;
        packet1.vertical_speed_limit = packet_in.vertical_speed_limit;
        packet1.yaw_rate_limit = packet_in.yaw_rate_limit;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SET_VELOCITY_LIMITS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SET_VELOCITY_LIMITS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_velocity_limits_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_set_velocity_limits_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_velocity_limits_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.horizontal_speed_limit , packet1.vertical_speed_limit , packet1.yaw_rate_limit );
    mavlink_msg_set_velocity_limits_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_velocity_limits_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.horizontal_speed_limit , packet1.vertical_speed_limit , packet1.yaw_rate_limit );
    mavlink_msg_set_velocity_limits_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_set_velocity_limits_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_velocity_limits_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.horizontal_speed_limit , packet1.vertical_speed_limit , packet1.yaw_rate_limit );
    mavlink_msg_set_velocity_limits_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SET_VELOCITY_LIMITS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SET_VELOCITY_LIMITS) != NULL);
#endif
}

static void mavlink_test_velocity_limits(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_VELOCITY_LIMITS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_velocity_limits_t packet_in = {
        17.0,45.0,73.0
    };
    mavlink_velocity_limits_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.horizontal_speed_limit = packet_in.horizontal_speed_limit;
        packet1.vertical_speed_limit = packet_in.vertical_speed_limit;
        packet1.yaw_rate_limit = packet_in.yaw_rate_limit;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_VELOCITY_LIMITS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_VELOCITY_LIMITS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_velocity_limits_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_velocity_limits_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_velocity_limits_pack(system_id, component_id, &msg , packet1.horizontal_speed_limit , packet1.vertical_speed_limit , packet1.yaw_rate_limit );
    mavlink_msg_velocity_limits_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_velocity_limits_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.horizontal_speed_limit , packet1.vertical_speed_limit , packet1.yaw_rate_limit );
    mavlink_msg_velocity_limits_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_velocity_limits_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_velocity_limits_send(MAVLINK_COMM_1 , packet1.horizontal_speed_limit , packet1.vertical_speed_limit , packet1.yaw_rate_limit );
    mavlink_msg_velocity_limits_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("VELOCITY_LIMITS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_VELOCITY_LIMITS) != NULL);
#endif
}

static void mavlink_test_figure_eight_execution_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FIGURE_EIGHT_EXECUTION_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_figure_eight_execution_status_t packet_in = {
        93372036854775807ULL,73.0,101.0,129.0,963498504,963498712,213.0,101
    };
    mavlink_figure_eight_execution_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.major_radius = packet_in.major_radius;
        packet1.minor_radius = packet_in.minor_radius;
        packet1.orientation = packet_in.orientation;
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.z = packet_in.z;
        packet1.frame = packet_in.frame;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FIGURE_EIGHT_EXECUTION_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FIGURE_EIGHT_EXECUTION_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_figure_eight_execution_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_figure_eight_execution_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_figure_eight_execution_status_pack(system_id, component_id, &msg , packet1.time_usec , packet1.major_radius , packet1.minor_radius , packet1.orientation , packet1.frame , packet1.x , packet1.y , packet1.z );
    mavlink_msg_figure_eight_execution_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_figure_eight_execution_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.major_radius , packet1.minor_radius , packet1.orientation , packet1.frame , packet1.x , packet1.y , packet1.z );
    mavlink_msg_figure_eight_execution_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_figure_eight_execution_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_figure_eight_execution_status_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.major_radius , packet1.minor_radius , packet1.orientation , packet1.frame , packet1.x , packet1.y , packet1.z );
    mavlink_msg_figure_eight_execution_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FIGURE_EIGHT_EXECUTION_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FIGURE_EIGHT_EXECUTION_STATUS) != NULL);
#endif
}

static void mavlink_test_battery_status_v2(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_BATTERY_STATUS_V2 >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_battery_status_v2_t packet_in = {
        17.0,45.0,73.0,101.0,963498296,18275,199,10
    };
    mavlink_battery_status_v2_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.voltage = packet_in.voltage;
        packet1.current = packet_in.current;
        packet1.capacity_consumed = packet_in.capacity_consumed;
        packet1.capacity_remaining = packet_in.capacity_remaining;
        packet1.status_flags = packet_in.status_flags;
        packet1.temperature = packet_in.temperature;
        packet1.id = packet_in.id;
        packet1.percent_remaining = packet_in.percent_remaining;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_BATTERY_STATUS_V2_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_BATTERY_STATUS_V2_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battery_status_v2_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_battery_status_v2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battery_status_v2_pack(system_id, component_id, &msg , packet1.id , packet1.temperature , packet1.voltage , packet1.current , packet1.capacity_consumed , packet1.capacity_remaining , packet1.percent_remaining , packet1.status_flags );
    mavlink_msg_battery_status_v2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battery_status_v2_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id , packet1.temperature , packet1.voltage , packet1.current , packet1.capacity_consumed , packet1.capacity_remaining , packet1.percent_remaining , packet1.status_flags );
    mavlink_msg_battery_status_v2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_battery_status_v2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battery_status_v2_send(MAVLINK_COMM_1 , packet1.id , packet1.temperature , packet1.voltage , packet1.current , packet1.capacity_consumed , packet1.capacity_remaining , packet1.percent_remaining , packet1.status_flags );
    mavlink_msg_battery_status_v2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("BATTERY_STATUS_V2") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_BATTERY_STATUS_V2) != NULL);
#endif
}

static void mavlink_test_group_start(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GROUP_START >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_group_start_t packet_in = {
        93372036854775807ULL,963497880,963498088
    };
    mavlink_group_start_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.group_id = packet_in.group_id;
        packet1.mission_checksum = packet_in.mission_checksum;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GROUP_START_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GROUP_START_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_start_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_group_start_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_start_pack(system_id, component_id, &msg , packet1.group_id , packet1.mission_checksum , packet1.time_usec );
    mavlink_msg_group_start_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_start_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.group_id , packet1.mission_checksum , packet1.time_usec );
    mavlink_msg_group_start_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_group_start_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_start_send(MAVLINK_COMM_1 , packet1.group_id , packet1.mission_checksum , packet1.time_usec );
    mavlink_msg_group_start_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GROUP_START") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GROUP_START) != NULL);
#endif
}

static void mavlink_test_group_end(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GROUP_END >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_group_end_t packet_in = {
        93372036854775807ULL,963497880,963498088
    };
    mavlink_group_end_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.group_id = packet_in.group_id;
        packet1.mission_checksum = packet_in.mission_checksum;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GROUP_END_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GROUP_END_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_end_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_group_end_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_end_pack(system_id, component_id, &msg , packet1.group_id , packet1.mission_checksum , packet1.time_usec );
    mavlink_msg_group_end_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_end_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.group_id , packet1.mission_checksum , packet1.time_usec );
    mavlink_msg_group_end_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_group_end_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_group_end_send(MAVLINK_COMM_1 , packet1.group_id , packet1.mission_checksum , packet1.time_usec );
    mavlink_msg_group_end_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GROUP_END") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GROUP_END) != NULL);
#endif
}

static void mavlink_test_radio_rc_channels(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RADIO_RC_CHANNELS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_radio_rc_channels_t packet_in = {
        963497464,17443,151,218,29,{ 17703, 17704, 17705, 17706, 17707, 17708, 17709, 17710, 17711, 17712, 17713, 17714, 17715, 17716, 17717, 17718, 17719, 17720, 17721, 17722, 17723, 17724, 17725, 17726, 17727, 17728, 17729, 17730, 17731, 17732, 17733, 17734 }
    };
    mavlink_radio_rc_channels_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_last_update_ms = packet_in.time_last_update_ms;
        packet1.flags = packet_in.flags;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.count = packet_in.count;
        
        mav_array_memcpy(packet1.channels, packet_in.channels, sizeof(int16_t)*32);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RADIO_RC_CHANNELS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RADIO_RC_CHANNELS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_rc_channels_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_radio_rc_channels_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_rc_channels_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.time_last_update_ms , packet1.flags , packet1.count , packet1.channels );
    mavlink_msg_radio_rc_channels_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_rc_channels_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.time_last_update_ms , packet1.flags , packet1.count , packet1.channels );
    mavlink_msg_radio_rc_channels_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_radio_rc_channels_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_rc_channels_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.time_last_update_ms , packet1.flags , packet1.count , packet1.channels );
    mavlink_msg_radio_rc_channels_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RADIO_RC_CHANNELS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RADIO_RC_CHANNELS) != NULL);
#endif
}

static void mavlink_test_available_modes(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AVAILABLE_MODES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_available_modes_t packet_in = {
        963497464,963497672,29,96,163,"LMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRS"
    };
    mavlink_available_modes_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.custom_mode = packet_in.custom_mode;
        packet1.properties = packet_in.properties;
        packet1.number_modes = packet_in.number_modes;
        packet1.mode_index = packet_in.mode_index;
        packet1.standard_mode = packet_in.standard_mode;
        
        mav_array_memcpy(packet1.mode_name, packet_in.mode_name, sizeof(char)*35);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AVAILABLE_MODES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AVAILABLE_MODES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_available_modes_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_pack(system_id, component_id, &msg , packet1.number_modes , packet1.mode_index , packet1.standard_mode , packet1.custom_mode , packet1.properties , packet1.mode_name );
    mavlink_msg_available_modes_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.number_modes , packet1.mode_index , packet1.standard_mode , packet1.custom_mode , packet1.properties , packet1.mode_name );
    mavlink_msg_available_modes_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_available_modes_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_send(MAVLINK_COMM_1 , packet1.number_modes , packet1.mode_index , packet1.standard_mode , packet1.custom_mode , packet1.properties , packet1.mode_name );
    mavlink_msg_available_modes_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AVAILABLE_MODES") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AVAILABLE_MODES) != NULL);
#endif
}

static void mavlink_test_current_mode(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CURRENT_MODE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_current_mode_t packet_in = {
        963497464,963497672,29
    };
    mavlink_current_mode_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.custom_mode = packet_in.custom_mode;
        packet1.intended_custom_mode = packet_in.intended_custom_mode;
        packet1.standard_mode = packet_in.standard_mode;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CURRENT_MODE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CURRENT_MODE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_current_mode_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_current_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_current_mode_pack(system_id, component_id, &msg , packet1.standard_mode , packet1.custom_mode , packet1.intended_custom_mode );
    mavlink_msg_current_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_current_mode_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.standard_mode , packet1.custom_mode , packet1.intended_custom_mode );
    mavlink_msg_current_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_current_mode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_current_mode_send(MAVLINK_COMM_1 , packet1.standard_mode , packet1.custom_mode , packet1.intended_custom_mode );
    mavlink_msg_current_mode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CURRENT_MODE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CURRENT_MODE) != NULL);
#endif
}

static void mavlink_test_available_modes_monitor(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AVAILABLE_MODES_MONITOR >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_available_modes_monitor_t packet_in = {
        5
    };
    mavlink_available_modes_monitor_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.seq = packet_in.seq;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AVAILABLE_MODES_MONITOR_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AVAILABLE_MODES_MONITOR_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_monitor_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_available_modes_monitor_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_monitor_pack(system_id, component_id, &msg , packet1.seq );
    mavlink_msg_available_modes_monitor_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_monitor_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.seq );
    mavlink_msg_available_modes_monitor_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_available_modes_monitor_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_available_modes_monitor_send(MAVLINK_COMM_1 , packet1.seq );
    mavlink_msg_available_modes_monitor_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AVAILABLE_MODES_MONITOR") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AVAILABLE_MODES_MONITOR) != NULL);
#endif
}

static void mavlink_test_gnss_integrity(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GNSS_INTEGRITY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_gnss_integrity_t packet_in = {
        963497464,17443,17547,29,96,163,230,41,108,175,242,53
    };
    mavlink_gnss_integrity_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.system_errors = packet_in.system_errors;
        packet1.raim_hfom = packet_in.raim_hfom;
        packet1.raim_vfom = packet_in.raim_vfom;
        packet1.id = packet_in.id;
        packet1.authentication_state = packet_in.authentication_state;
        packet1.jamming_state = packet_in.jamming_state;
        packet1.spoofing_state = packet_in.spoofing_state;
        packet1.raim_state = packet_in.raim_state;
        packet1.corrections_quality = packet_in.corrections_quality;
        packet1.system_status_summary = packet_in.system_status_summary;
        packet1.gnss_signal_quality = packet_in.gnss_signal_quality;
        packet1.post_processing_quality = packet_in.post_processing_quality;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GNSS_INTEGRITY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GNSS_INTEGRITY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gnss_integrity_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_gnss_integrity_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gnss_integrity_pack(system_id, component_id, &msg , packet1.id , packet1.system_errors , packet1.authentication_state , packet1.jamming_state , packet1.spoofing_state , packet1.raim_state , packet1.raim_hfom , packet1.raim_vfom , packet1.corrections_quality , packet1.system_status_summary , packet1.gnss_signal_quality , packet1.post_processing_quality );
    mavlink_msg_gnss_integrity_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gnss_integrity_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id , packet1.system_errors , packet1.authentication_state , packet1.jamming_state , packet1.spoofing_state , packet1.raim_state , packet1.raim_hfom , packet1.raim_vfom , packet1.corrections_quality , packet1.system_status_summary , packet1.gnss_signal_quality , packet1.post_processing_quality );
    mavlink_msg_gnss_integrity_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_gnss_integrity_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gnss_integrity_send(MAVLINK_COMM_1 , packet1.id , packet1.system_errors , packet1.authentication_state , packet1.jamming_state , packet1.spoofing_state , packet1.raim_state , packet1.raim_hfom , packet1.raim_vfom , packet1.corrections_quality , packet1.system_status_summary , packet1.gnss_signal_quality , packet1.post_processing_quality );
    mavlink_msg_gnss_integrity_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GNSS_INTEGRITY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GNSS_INTEGRITY) != NULL);
#endif
}

static void mavlink_test_target_absolute(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_ABSOLUTE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_absolute_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,{ 157.0, 158.0, 159.0 },{ 241.0, 242.0, 243.0 },{ 325.0, 326.0, 327.0, 328.0 },{ 437.0, 438.0, 439.0 },{ 521.0, 522.0 },{ 577.0, 578.0, 579.0 },{ 661.0, 662.0, 663.0 },61,128
    };
    mavlink_target_absolute_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.id = packet_in.id;
        packet1.sensor_capabilities = packet_in.sensor_capabilities;
        
        mav_array_memcpy(packet1.vel, packet_in.vel, sizeof(float)*3);
        mav_array_memcpy(packet1.acc, packet_in.acc, sizeof(float)*3);
        mav_array_memcpy(packet1.q_target, packet_in.q_target, sizeof(float)*4);
        mav_array_memcpy(packet1.rates, packet_in.rates, sizeof(float)*3);
        mav_array_memcpy(packet1.position_std, packet_in.position_std, sizeof(float)*2);
        mav_array_memcpy(packet1.vel_std, packet_in.vel_std, sizeof(float)*3);
        mav_array_memcpy(packet1.acc_std, packet_in.acc_std, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_ABSOLUTE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_ABSOLUTE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_absolute_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_absolute_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_absolute_pack(system_id, component_id, &msg , packet1.timestamp , packet1.id , packet1.sensor_capabilities , packet1.lat , packet1.lon , packet1.alt , packet1.vel , packet1.acc , packet1.q_target , packet1.rates , packet1.position_std , packet1.vel_std , packet1.acc_std );
    mavlink_msg_target_absolute_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_absolute_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.id , packet1.sensor_capabilities , packet1.lat , packet1.lon , packet1.alt , packet1.vel , packet1.acc , packet1.q_target , packet1.rates , packet1.position_std , packet1.vel_std , packet1.acc_std );
    mavlink_msg_target_absolute_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_absolute_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_absolute_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.id , packet1.sensor_capabilities , packet1.lat , packet1.lon , packet1.alt , packet1.vel , packet1.acc , packet1.q_target , packet1.rates , packet1.position_std , packet1.vel_std , packet1.acc_std );
    mavlink_msg_target_absolute_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_ABSOLUTE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_ABSOLUTE) != NULL);
#endif
}

static void mavlink_test_target_relative(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_RELATIVE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_relative_t packet_in = {
        93372036854775807ULL,73.0,101.0,129.0,{ 157.0, 158.0, 159.0 },241.0,{ 269.0, 270.0, 271.0, 272.0 },{ 381.0, 382.0, 383.0, 384.0 },209,20,87
    };
    mavlink_target_relative_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.z = packet_in.z;
        packet1.yaw_std = packet_in.yaw_std;
        packet1.id = packet_in.id;
        packet1.frame = packet_in.frame;
        packet1.type = packet_in.type;
        
        mav_array_memcpy(packet1.pos_std, packet_in.pos_std, sizeof(float)*3);
        mav_array_memcpy(packet1.q_target, packet_in.q_target, sizeof(float)*4);
        mav_array_memcpy(packet1.q_sensor, packet_in.q_sensor, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_RELATIVE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_RELATIVE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_relative_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_relative_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_relative_pack(system_id, component_id, &msg , packet1.timestamp , packet1.id , packet1.frame , packet1.x , packet1.y , packet1.z , packet1.pos_std , packet1.yaw_std , packet1.q_target , packet1.q_sensor , packet1.type );
    mavlink_msg_target_relative_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_relative_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.id , packet1.frame , packet1.x , packet1.y , packet1.z , packet1.pos_std , packet1.yaw_std , packet1.q_target , packet1.q_sensor , packet1.type );
    mavlink_msg_target_relative_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_relative_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_relative_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.id , packet1.frame , packet1.x , packet1.y , packet1.z , packet1.pos_std , packet1.yaw_std , packet1.q_target , packet1.q_sensor , packet1.type );
    mavlink_msg_target_relative_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_RELATIVE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_RELATIVE) != NULL);
#endif
}

static void mavlink_test_control_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CONTROL_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_control_status_t packet_in = {
        5,72
    };
    mavlink_control_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.sysid_in_control = packet_in.sysid_in_control;
        packet1.flags = packet_in.flags;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CONTROL_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CONTROL_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_control_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_control_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_control_status_pack(system_id, component_id, &msg , packet1.sysid_in_control , packet1.flags );
    mavlink_msg_control_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_control_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.sysid_in_control , packet1.flags );
    mavlink_msg_control_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_control_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_control_status_send(MAVLINK_COMM_1 , packet1.sysid_in_control , packet1.flags );
    mavlink_msg_control_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CONTROL_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CONTROL_STATUS) != NULL);
#endif
}

static void mavlink_test_avs_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AVS_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_avs_status_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,18483,{ 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226 },3,70,137,204
    };
    mavlink_avs_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.adcidx = packet_in.adcidx;
        packet1.azim = packet_in.azim;
        packet1.elev = packet_in.elev;
        packet1.histcnt = packet_in.histcnt;
        packet1.intensity = packet_in.intensity;
        packet1.qfac = packet_in.qfac;
        packet1.srcidx = packet_in.srcidx;
        packet1.bgint = packet_in.bgint;
        
        mav_array_memcpy(packet1.melint, packet_in.melint, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AVS_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_avs_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_status_pack(system_id, component_id, &msg , packet1.time_usec , packet1.time_boot_ms , packet1.adcidx , packet1.azim , packet1.elev , packet1.histcnt , packet1.melint , packet1.intensity , packet1.qfac , packet1.srcidx , packet1.bgint );
    mavlink_msg_avs_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.time_boot_ms , packet1.adcidx , packet1.azim , packet1.elev , packet1.histcnt , packet1.melint , packet1.intensity , packet1.qfac , packet1.srcidx , packet1.bgint );
    mavlink_msg_avs_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_avs_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_status_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.time_boot_ms , packet1.adcidx , packet1.azim , packet1.elev , packet1.histcnt , packet1.melint , packet1.intensity , packet1.qfac , packet1.srcidx , packet1.bgint );
    mavlink_msg_avs_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AVS_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AVS_STATUS) != NULL);
#endif
}

static void mavlink_test_sensor_avs(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SENSOR_AVS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_sensor_avs_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,213.0,241.0,269.0,{ 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0, 304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0 },22643,22747
    };
    mavlink_sensor_avs_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.time_utc_usec = packet_in.time_utc_usec;
        packet1.timestamp_sample = packet_in.timestamp_sample;
        packet1.device_id = packet_in.device_id;
        packet1.azimuth_deg = packet_in.azimuth_deg;
        packet1.elevation_deg = packet_in.elevation_deg;
        packet1.active_intensity = packet_in.active_intensity;
        packet1.q_factor = packet_in.q_factor;
        packet1.source_index = packet_in.source_index;
        packet1.histogram_count = packet_in.histogram_count;
        
        mav_array_memcpy(packet1.mel_intensity, packet_in.mel_intensity, sizeof(float)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SENSOR_AVS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_sensor_avs_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_pack(system_id, component_id, &msg , packet1.timestamp , packet1.timestamp_sample , packet1.time_utc_usec , packet1.device_id , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.source_index , packet1.histogram_count , packet1.mel_intensity );
    mavlink_msg_sensor_avs_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.timestamp_sample , packet1.time_utc_usec , packet1.device_id , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.source_index , packet1.histogram_count , packet1.mel_intensity );
    mavlink_msg_sensor_avs_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_sensor_avs_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.timestamp_sample , packet1.time_utc_usec , packet1.device_id , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.source_index , packet1.histogram_count , packet1.mel_intensity );
    mavlink_msg_sensor_avs_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SENSOR_AVS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SENSOR_AVS) != NULL);
#endif
}

static void mavlink_test_rel_pos_ned(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_REL_POS_NED >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rel_pos_ned_t packet_in = {
        963497464,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,137,204
    };
    mavlink_rel_pos_ned_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.north = packet_in.north;
        packet1.east = packet_in.east;
        packet1.down = packet_in.down;
        packet1.acc_n = packet_in.acc_n;
        packet1.acc_e = packet_in.acc_e;
        packet1.acc_d = packet_in.acc_d;
        packet1.head = packet_in.head;
        packet1.acc_h = packet_in.acc_h;
        packet1.len = packet_in.len;
        packet1.acc_l = packet_in.acc_l;
        packet1.node_id = packet_in.node_id;
        packet1.fixed = packet_in.fixed;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_REL_POS_NED_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rel_pos_ned_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rel_pos_ned_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rel_pos_ned_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.north , packet1.east , packet1.down , packet1.acc_n , packet1.acc_e , packet1.acc_d , packet1.head , packet1.acc_h , packet1.len , packet1.acc_l , packet1.node_id , packet1.fixed );
    mavlink_msg_rel_pos_ned_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rel_pos_ned_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.north , packet1.east , packet1.down , packet1.acc_n , packet1.acc_e , packet1.acc_d , packet1.head , packet1.acc_h , packet1.len , packet1.acc_l , packet1.node_id , packet1.fixed );
    mavlink_msg_rel_pos_ned_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rel_pos_ned_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rel_pos_ned_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.north , packet1.east , packet1.down , packet1.acc_n , packet1.acc_e , packet1.acc_d , packet1.head , packet1.acc_h , packet1.len , packet1.acc_l , packet1.node_id , packet1.fixed );
    mavlink_msg_rel_pos_ned_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("REL_POS_NED") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_REL_POS_NED) != NULL);
#endif
}

static void mavlink_test_avs_mfc(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AVS_MFC >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_avs_mfc_t packet_in = {
        93372036854775807ULL,963497880,963498088,{ 129.0, 130.0, 131.0, 132.0, 133.0, 134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0, 144.0 },245
    };
    mavlink_avs_mfc_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.sample_index = packet_in.sample_index;
        packet1.node_id = packet_in.node_id;
        
        mav_array_memcpy(packet1.intensity, packet_in.intensity, sizeof(float)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AVS_MFC_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AVS_MFC_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_mfc_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_avs_mfc_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_mfc_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.sample_index , packet1.time_usec , packet1.node_id , packet1.intensity );
    mavlink_msg_avs_mfc_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_mfc_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.sample_index , packet1.time_usec , packet1.node_id , packet1.intensity );
    mavlink_msg_avs_mfc_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_avs_mfc_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_avs_mfc_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.sample_index , packet1.time_usec , packet1.node_id , packet1.intensity );
    mavlink_msg_avs_mfc_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AVS_MFC") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AVS_MFC) != NULL);
#endif
}

static void mavlink_test_sensor_avs_lite(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SENSOR_AVS_LITE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_sensor_avs_lite_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,213.0,241.0,269.0,19315
    };
    mavlink_sensor_avs_lite_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_utc_usec = packet_in.time_utc_usec;
        packet1.timestamp = packet_in.timestamp;
        packet1.device_id = packet_in.device_id;
        packet1.timestamp_sample = packet_in.timestamp_sample;
        packet1.azimuth_deg = packet_in.azimuth_deg;
        packet1.elevation_deg = packet_in.elevation_deg;
        packet1.active_intensity = packet_in.active_intensity;
        packet1.q_factor = packet_in.q_factor;
        packet1.histogram_count = packet_in.histogram_count;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SENSOR_AVS_LITE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SENSOR_AVS_LITE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_sensor_avs_lite_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_pack(system_id, component_id, &msg , packet1.device_id , packet1.time_utc_usec , packet1.timestamp , packet1.timestamp_sample , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.histogram_count );
    mavlink_msg_sensor_avs_lite_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.device_id , packet1.time_utc_usec , packet1.timestamp , packet1.timestamp_sample , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.histogram_count );
    mavlink_msg_sensor_avs_lite_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_sensor_avs_lite_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_send(MAVLINK_COMM_1 , packet1.device_id , packet1.time_utc_usec , packet1.timestamp , packet1.timestamp_sample , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.histogram_count );
    mavlink_msg_sensor_avs_lite_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SENSOR_AVS_LITE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SENSOR_AVS_LITE) != NULL);
#endif
}

static void mavlink_test_sensor_avs_lite_ext(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_sensor_avs_lite_ext_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,20563
    };
    mavlink_sensor_avs_lite_ext_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_utc_usec = packet_in.time_utc_usec;
        packet1.timestamp = packet_in.timestamp;
        packet1.device_id = packet_in.device_id;
        packet1.timestamp_sample = packet_in.timestamp_sample;
        packet1.azimuth_deg = packet_in.azimuth_deg;
        packet1.elevation_deg = packet_in.elevation_deg;
        packet1.active_intensity = packet_in.active_intensity;
        packet1.q_factor = packet_in.q_factor;
        packet1.north = packet_in.north;
        packet1.east = packet_in.east;
        packet1.down = packet_in.down;
        packet1.yaw = packet_in.yaw;
        packet1.pitch = packet_in.pitch;
        packet1.roll = packet_in.roll;
        packet1.histogram_count = packet_in.histogram_count;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_ext_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_sensor_avs_lite_ext_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_ext_pack(system_id, component_id, &msg , packet1.device_id , packet1.time_utc_usec , packet1.timestamp , packet1.timestamp_sample , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.histogram_count , packet1.north , packet1.east , packet1.down , packet1.yaw , packet1.pitch , packet1.roll );
    mavlink_msg_sensor_avs_lite_ext_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_ext_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.device_id , packet1.time_utc_usec , packet1.timestamp , packet1.timestamp_sample , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.histogram_count , packet1.north , packet1.east , packet1.down , packet1.yaw , packet1.pitch , packet1.roll );
    mavlink_msg_sensor_avs_lite_ext_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_sensor_avs_lite_ext_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_avs_lite_ext_send(MAVLINK_COMM_1 , packet1.device_id , packet1.time_utc_usec , packet1.timestamp , packet1.timestamp_sample , packet1.azimuth_deg , packet1.elevation_deg , packet1.active_intensity , packet1.q_factor , packet1.histogram_count , packet1.north , packet1.east , packet1.down , packet1.yaw , packet1.pitch , packet1.roll );
    mavlink_msg_sensor_avs_lite_ext_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SENSOR_AVS_LITE_EXT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SENSOR_AVS_LITE_EXT) != NULL);
#endif
}

static void mavlink_test_development(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_airspeed(system_id, component_id, last_msg);
    mavlink_test_set_velocity_limits(system_id, component_id, last_msg);
    mavlink_test_velocity_limits(system_id, component_id, last_msg);
    mavlink_test_figure_eight_execution_status(system_id, component_id, last_msg);
    mavlink_test_battery_status_v2(system_id, component_id, last_msg);
    mavlink_test_group_start(system_id, component_id, last_msg);
    mavlink_test_group_end(system_id, component_id, last_msg);
    mavlink_test_radio_rc_channels(system_id, component_id, last_msg);
    mavlink_test_available_modes(system_id, component_id, last_msg);
    mavlink_test_current_mode(system_id, component_id, last_msg);
    mavlink_test_available_modes_monitor(system_id, component_id, last_msg);
    mavlink_test_gnss_integrity(system_id, component_id, last_msg);
    mavlink_test_target_absolute(system_id, component_id, last_msg);
    mavlink_test_target_relative(system_id, component_id, last_msg);
    mavlink_test_control_status(system_id, component_id, last_msg);
    mavlink_test_avs_status(system_id, component_id, last_msg);
    mavlink_test_sensor_avs(system_id, component_id, last_msg);
    mavlink_test_rel_pos_ned(system_id, component_id, last_msg);
    mavlink_test_avs_mfc(system_id, component_id, last_msg);
    mavlink_test_sensor_avs_lite(system_id, component_id, last_msg);
    mavlink_test_sensor_avs_lite_ext(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // DEVELOPMENT_TESTSUITE_H
