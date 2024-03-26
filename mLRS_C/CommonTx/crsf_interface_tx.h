//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// CRSF Interface TX Side
//*******************************************************
#ifndef CRSF_INTERFACE_TX_H
#define CRSF_INTERFACE_TX_H

#if (defined DEVICE_HAS_JRPIN5)

#include "math.h"
#include "../Common/thirdparty/thirdparty.h"
#include "../Common/protocols/crsf_protocol.h"
#include "../Common/protocols/passthrough_protocol.h"
#include "../Common/protocols/ardupilot_protocol.h"
#include "jr_pin5_interface.h"


// a frame is sent every 4 ms, frame length is max 64 bytes
// a byte is 25 us
// gaps between frames are 1 ms or so
#define CRSF_PARSE_NEXTCHAR_TMO_US  500

#define CRSF_REFRESH_TIME_MS  2500 // what is actually a proper value ??


#define CRSF_REV_U16(x)  __REV16(x)
#define CRSF_REV_I16(x)  __REVSH(x)
#define CRSF_REV_U32(x)  __REV(x)

extern uint16_t micros(void);
extern volatile uint32_t millis32(void);
extern tTxStats txstats;


//-------------------------------------------------------
// Interface Implementation

typedef enum {
    TXCRSF_SEND_LINK_STATISTICS = 0,
    TXCRSF_SEND_LINK_STATISTICS_TX,
    TXCRSF_SEND_LINK_STATISTICS_RX,
    TXCRSF_SEND_TELEMETRY_FRAME, // native or passthrough telemetry frame
} TXCRSF_SEND_ENUM;


typedef enum {
    TXCRSF_CMD_MODELID_SET = 0,
    TXCRSF_CMD_MBRIDGE_IN,
} TXCRSF_CMD_ENUM;

void tTxCrsf_Init(bool enable_flag);
bool tTxCrsf_ChannelsUpdated(tRcData* rc);
bool tTxCrsf_TelemetryUpdate(uint8_t* task, uint16_t frame_rate_ms);

bool tTxCrsf_CommandReceived(uint8_t* cmd);
uint8_t* tTxCrsf_GetCmdDataPtr(void);
uint8_t* tTxCrsf_GetPayloadPtr(void);
uint8_t tTxCrsf_GetPayloadLen(void);
uint8_t tTxCrsf_GetCmdModelId(void);

void tTxCrsf_SendLinkStatistics(tCrsfLinkStatistics* payload); // in OpenTx this triggers telemetryStreaming
void tTxCrsf_SendLinkStatisticsTx(tCrsfLinkStatisticsTx* payload);
void tTxCrsf_SendLinkStatisticsRx(tCrsfLinkStatisticsRx* payload);
void tTxCrsf_SendFrame(const uint8_t frame_id, void* payload, const uint8_t payload_len);

void tTxCrsf_TelemetryHandleMavlinkMsg(fmav_message_t* msg);
void tTxCrsf_SendTelemetryFrame(void);

void tTxCrsf_SendMBridgeFrame(void* payload, const uint8_t payload_len);
// helper
uint8_t tTxCrsf_crc8(const uint8_t* buf);
void tTxCrsf_fill_rcdata(tRcData* rc);
// for in-isr processing, used in half-duplex mode
void tTxCrsf_parse_nextchar(uint8_t c);
bool tTxCrsf_transmit_start(void); // returns true if transmission should be started

// mavlink handlers

void handle_mavlink_msg_heartbeat(fmav_heartbeat_t* payload);
void handle_mavlink_msg_battery_status(fmav_battery_status_t* payload);
void handle_mavlink_msg_attitude(fmav_attitude_t* payload);
void handle_mavlink_msg_gps_raw_int(fmav_gps_raw_int_t* payload);
void handle_mavlink_msg_gps2_raw(fmav_gps2_raw_t* payload);
void handle_mavlink_msg_global_position_int(fmav_global_position_int_t* payload);
void handle_mavlink_msg_vfr_hud(fmav_vfr_hud_t* payload);


//-------------------------------------------------------
// Crsf half-duplex interface, used for radio <-> mLRS tx module

// to avoid error: ISO C++ forbids taking the address of a bound member function to form a pointer to member function
void crsf_uart_rx_callback(uint8_t c);
void crsf_uart_tc_callback(void);

//-------------------------------------------------------
// CRSF Telemetry Mavlink Handling
// we have to kinds to consider:
// - native CRSF telemetry frames:
//   these are filled from MAVLink messages by the tTxCrsf class
// - passthrough packets which are packed into CRSF passthrough telemetry frames:
//   these are filled from MAVLink messages through the tPassThrough class

void tTxCrsf_handle_mavlink_msg_heartbeat(fmav_heartbeat_t* payload);
int32_t mav_battery_voltage(fmav_battery_status_t* payload);
void tTxCrsf_handle_mavlink_msg_battery_status(fmav_battery_status_t* payload);
void tTxCrsf_handle_mavlink_msg_attitude(fmav_attitude_t* payload);
void tTxCrsf_handle_mavlink_msg_gps_raw_int(fmav_gps_raw_int_t* payload);
void tTxCrsf_handle_mavlink_msg_gps2_raw(fmav_gps2_raw_t* payload);
void tTxCrsf_handle_mavlink_msg_global_position_int(fmav_global_position_int_t* payload);
void tTxCrsf_handle_mavlink_msg_vfr_hud(fmav_vfr_hud_t* payload);
//-------------------------------------------------------
// convenience helper
uint8_t crsf_cvt_rssi_percent(int8_t rssi);
void crsf_send_LinkStatistics(void);
void crsf_send_LinkStatisticsTx(void);
void crsf_send_LinkStatisticsRx(void);

#endif // if (defined DEVICE_HAS_JRPIN5)

#endif // CRSF_INTERFACE_TX_H
