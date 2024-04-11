//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Passthrough Protocol Header
//
// ArduPilot Passthrough Protocol
// https://docs.google.com/spreadsheets/d/1oFv5zSl10wyR0LOcCChDdy9peIRNkbaEBrsHDQ0ZdmE/edit
// https://github.com/ArduPilot/ardupilot/blob/master/libraries/AP_Frsky_Telem/AP_Frsky_SPort_Passthrough.h
// https://github.com/ArduPilot/ardupilot/blob/master/libraries/AP_Frsky_Telem/AP_Frsky_SPort_Passthrough.cpp
//*******************************************************
/*
  SYS_STATUS            #1    -> 0x5003 BATT_1                            SRx_EXT_STAT    not used, replaced by BATTERY_STATUS
  GPS_RAW_INT           #24   -> 0x5002 GPS STATUS                        SRx_EXT_STAT
  SCALED_IMU            #26   -> 0x5001 AP_STATUS                         -               not used, replaced by RAW_IMU
  RAW_IMU               #27   -> 0x5001 AP_STATUS                         SRx_RAW_SENS
  ATTITUDE              #30   -> 0x5006 ATTITUDE_RANGE                    SRx_EXTRA1
  GLOBAL_POSITION_INT   #33   -> 0x800 (2x), 0x5004 HOME                  SRx_POSITION
  MISSION_CURRENT       #42   -> 0x500D WAYPOINT_V2                       SRx_EXT_STAT
  NAV_CONTROLLER_OUTPUT #62   -> 0x5009 WAYPOINT_V1, 0x500D WAYPOINT V2   SRx_EXT_STAT
  VFR_HUD               #74   -> 0x5005 VEL_YAW, 0x50F2 VFR_HUD           SRx_EXTRA2
  TERRAIN_REPORT        #136  -> 0x500B TERRAIN                           -
  BATTERY_STATUS        #147  -> 0x5003 BATT_1, 0x5008 BATT_2             SRx_EXTRA3
  FENCE_STATUS          #162  -> 0x5001 AP_STATUS                         SRx_EXT_STAT
  // #173, #181, #226 are ArduPilot dialect specific
  RANGEFINDER           #173  -> 0x5006 ATTITUDE_RANGE                    SRx_EXTRA3
  BATTERY2              #181  -> 0x5008 BATT_2                            SRx_EXTRA3      not used, replaced by BATTERY_STATUS
  RPM                   #226  -> 0x500A RPM                               SRx_EXTRA3
  HOME_POSITION         #242  -> 0x5004 HOME                              -

  DISTANCE_SENSOR       #132                                              SRx_EXTRA3
  EKF_STATUS_REPORT     #193                                              SRx_EXTRA3
  WIND_COV              #231                                              -
  EXTENDED_SYS_STATE    #245                                              -

  // #168 is ArduPilot dialect specific
  WIND                  #168                                              SRx_EXTRA3

  GPS2_RAW              #124
  HIGH_LATENCY          #234
  HIGH_LATENCY2         #235

=> we want these streams:
                            HEARTBEAT               -> AP_STATUS_0x5001, PARAM_0x5007
  SRx_EXT_STAT (1/2 Hz) ->  SYS_STATUS              -> (VEL_YAW_0x5005)
                            GPS_RAW_INT             -> GPS_STATUS_0x5002 (GPS_LAT_0x800, GPS_LON_0x800)
                            MISSION_CURRENT         -> WAYPOINT_V2_0x500D
                            NAV_CONTROLLER_OUTPUT   -> WAYPOINT_V2_0x500D
                            FENCE_STATUS            -> (AP_STATUS_0x5001)
  SRx_EXTRA1   (4 Hz)   ->  ATTITUDE                -> ATTITUDE_RANGE_0x5006
  SRx_EXTRA2   (4 Hz)   ->  VFR_HUD                 -> VEL_YAW_0x5005, VEL_YAW_0x5005_AIR (AP_STATUS_0x5001)
  SRx_EXTRA3   (1/2 Hz) ->  RANGEFINDER             -> ATTITUDE_RANGE_0x5006
                            BATTERY_STATUS          -> BATT_1_0x5003, BATT_2_0x5008
                            TERRAIN_REPORT          -> TERRAIN_0x500B
                            RPM                     -> RPM_0x500A
                            WIND ?useful?
                            DISTANCE_SENSOR ?useful? yes, we want to digest it if we get it
  SRx_POSITION (2 Hz)   ->  GLOBAL_POSITION_INT     -> GPS_LAT_0x800, GPS_LON_0x800, HOME_0x5004
  SRx_RAW_SENS (0 Hz)   ->  RAW_IMU                 -> (AP_STATUS_0x5001)

  missing                   HOME_POSITION           -> HOME_0x5004
*/
/*
  MavToPass uses
  - SYS_STATUS to get BATT1 volt and curr, and BATTERY_STATUS to get BATT1 mAh
  - BATTERY2 to get BATT2 volt and curr, and BATTERY_STATUS to get BATT2 mAh
  we replace it with only using BATTERY_STATUS, see also MAVlink for OpenTx

  MavToPass uses
  - SCALED_IMU to get IMU temperature
  we replace it with RAW_IMU, as it is streamed
*/
#ifndef PASSTHROUGH_PROTOCOL_H
#define PASSTHROUGH_PROTOCOL_H

#include "thirdparty.h"

//-------------------------------------------------------
// Interface Implementation

// TODO:
// for passthrough messages which involve date from several mavlink messages, we need to avoid that invalid data is used

#define RAD2DEGF                    5.729577951E+01f
#define DEG2RADF                    1.745329252E-02f

void tPassThrough_Init(void);
bool tPassThrough_GetTelemetryFrameSingle(uint8_t packet_type, uint8_t* data, uint8_t* len);
bool tPassThrough_GetTelemetryFrameMulti(uint8_t* data, uint8_t* len);
// these read a mavlink message and convert data into passthrough data fields
void tPassThrough_handle_mavlink_msg_passthrough_array(fmav_frsky_passthrough_array_t* payload);
void tPassThrough_handle_mavlink_msg_passthrough_array_tunnel(fmav_tunnel_t* payload);
void tPassThrough_decode_passthrough_array(uint8_t count, uint8_t* buf);
bool tPassThrough_passthrough_array_is_receiving;
void tPassThrough_handle_mavlink_msg_heartbeat(fmav_heartbeat_t* payload);           // #0
void tPassThrough_handle_mavlink_msg_sys_status(fmav_sys_status_t* payload);         // #1
void tPassThrough_handle_mavlink_msg_gps_raw_int(fmav_gps_raw_int_t* payload);       // #24
void tPassThrough_handle_mavlink_msg_raw_imu(fmav_raw_imu_t* payload);               // #27
void tPassThrough_handle_mavlink_msg_attitude(fmav_attitude_t* payload);             // #30
void tPassThrough_handle_mavlink_msg_global_position_int(fmav_global_position_int_t* payload);     // #33
void tPassThrough_handle_mavlink_msg_mission_current(fmav_mission_current_t* payload);             // #42
void tPassThrough_handle_mavlink_msg_nav_controller_output(fmav_nav_controller_output_t* payload); // #62
void tPassThrough_handle_mavlink_msg_vfr_hud(fmav_vfr_hud_t* payload);               // #74
void tPassThrough_handle_mavlink_msg_terrain_report(fmav_terrain_report_t* payload); // #136
void tPassThrough_handle_mavlink_msg_battery_status(fmav_battery_status_t* payload); // #147
void tPassThrough_handle_mavlink_msg_fence_status(fmav_fence_status_t* payload);     // #162
void tPassThrough_handle_mavlink_msg_rangefinder(fmav_rangefinder_t* payload);       // #173, ArduPilot dialect specific
void tPassThrough_handle_mavlink_msg_rpm(fmav_rpm_t* payload);                       // #226, ArduPilot dialect specific
void tPassThrough_handle_mavlink_msg_home_position(fmav_home_position_t* payload);   // #242
void tPassThrough_handle_mavlink_msg_statustext(fmav_statustext_t* payload);         // #253
// methods to convert mavlink data to passthrough (OpenTX) format
bool tPassThrough_get_GpsLat_0x800(uint32_t* data);
bool tPassThrough_get_GpsLon_0x800(uint32_t* data);
bool tPassThrough_get_Text_0x5000(uint32_t* data);
bool tPassThrough_get_ApStatus_0x5001(uint32_t* data);
bool tPassThrough_get_GpsStatus_0x5002(uint32_t* data);
bool tPassThrough_get_Battery1_0x5003(uint32_t* data);
bool tPassThrough_get_Home_0x5004(uint32_t* data);
bool tPassThrough_get_VelocityYaw_0x5005(uint32_t* data);
bool tPassThrough_get_AttitudeRange_0x5006(uint32_t* data);
bool tPassThrough_get_Param_0x5007(uint32_t* data);
bool tPassThrough_get_Battery2_0x5008(uint32_t* data);
bool tPassThrough_get_Rpm_0x500A(uint32_t* data);
bool tPassThrough_get_Terrain_0x500B(uint32_t* data);
bool tPassThrough_get_Wind_0x500C(uint32_t* data);
bool tPassThrough_get_WayPointV2_0x500D(uint32_t* data);
bool tPassThrough_get_VfrHud_0x50F2(uint32_t* data);
bool tPassThrough_get_VelocityYaw_0x5005_Air(uint32_t* data);
bool tPassThrough_get_packet_data(uint8_t packet_type, uint32_t* data);


#endif // PASSTHROUGH_PROTOCOL_H


