//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Mavlink Interface RX Side
//*******************************************************
#ifndef MAVLINK_INTERFACE_RX_H
#define MAVLINK_INTERFACE_RX_H

#include "../Common/mavlink/fmav_extension.h"
#include "../Common/libs/filters.h"
#ifdef USE_FEATURE_MAVLINKX
#include "../Common/thirdparty/mavlinkx.h"
#include "../Common/libs/fifo.h"
#endif


#define RADIO_LINK_SYSTEM_ID        51 // SiK uses 51, 68
#define GCS_SYSTEM_ID               255 // default of MissionPlanner, QGC
#define REBOOT_SHUTDOWN_MAGIC       1234321
#define MAVLINK_BUF_SIZE            300 // needs to be larger than max mavlink frame size = 280 bytes
#define MAVLINK_OPT_FAKE_PARAMFTP   2 // 0: off, 1: always, 2: determined from mode & baudrate

//public
void tRxMavlink_Init(void);
void tRxMavlink_Do(void);
void tRxMavlink_SendRcData(tRcData* rc_out, bool frame_missed, bool failsafe);
void tRxMavlink_FrameLost(void);

void tRxMavlink_putc(char c);
bool tRxMavlink_available(void);
uint8_t tRxMavlink_getc(void);
void tRxMavlink_flush(void);


#endif // MAVLINK_INTERFACE_RX_H
