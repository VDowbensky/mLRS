//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// OUT
//********************************************************
#ifndef OUT_H
#define OUT_H

#include <inttypes.h>
#include "../Common/common_types.h"
#include "../Common/frame_types.h"
#include "../Common/setup_types.h"
#include "../Common/channel_order.h"

//-------------------------------------------------------
// Generic Out Class
/
typedef struct
{
    int8_t receiver_rssi1;
    int8_t receiver_rssi2;
    uint8_t receiver_LQ;
    int8_t receiver_snr;
    uint8_t receiver_antenna;
    uint8_t receiver_transmit_antenna;
    int8_t receiver_power_dbm;
    int8_t transmitter_rssi;
    uint8_t transmitter_LQ;
    int8_t transmitter_snr;
    uint8_t transmitter_antenna;
    uint8_t transmitter_transmit_antenna;
    uint8_t mode;
    uint8_t antenna_config;
} tOutLinkStats;


void OutBase_Init(tRxSetup* _setup);
void OutBase_Configure(uint8_t new_config);
void OutBase_Do(void);
void OutBase_SendRcData(tRcData* rc, bool frame_lost, bool failsafe, int8_t rssi, uint8_t lq);
void OutBase_SendLinkStatistics(tOutLinkStats* lstats);
void OutBase_SendLinkStatisticsDisconnected(void);
void OutBase_SetChannelOrder(uint8_t new_channel_order);
OutBase_tRcData* GetRcDataPtr(void);

#endif // OUT_H
