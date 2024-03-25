//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// frames
//*******************************************************
#ifndef FRAMES_H
#define FRAMES_H
#pragma once


#include "frame_types.h"


extern SX_DRIVER sx;
extern SX2_DRIVER sx2;


//-------------------------------------------------------
// Tx, Rx Frames
//-------------------------------------------------------

typedef enum {
    CHECK_OK = 0,
    CHECK_ERROR_SYNCWORD, // 1
    CHECK_ERROR_HEADER,   // 2
    CHECK_ERROR_CRC1,     // 3
    CHECK_ERROR_CRC,      // 4
} CHECK_ENUM;


void _pack_txframe_w_type(tTxFrame* frame, uint8_t type, tFrameStats* frame_stats, tRcData* rc, uint8_t* payload, uint8_t payload_len);
void pack_txframe(tTxFrame* frame, tFrameStats* frame_stats, tRcData* rc, uint8_t* payload, uint8_t payload_len);
// returns 0 if OK !!
uint8_t check_txframe(tTxFrame* frame);
void rcdata_rc1_from_txframe(tRcData* rc, tTxFrame* frame);
void rcdata_from_txframe(tRcData* rc, tTxFrame* frame);
void _pack_rxframe_w_type(tRxFrame* frame, uint8_t type, tFrameStats* frame_stats, uint8_t* payload, uint8_t payload_len);
void pack_rxframe(tRxFrame* frame, tFrameStats* frame_stats, uint8_t* payload, uint8_t payload_len);
// returns 0 if OK !!
uint8_t check_rxframe(tRxFrame* frame);
//-------------------------------------------------------
// Tx/Rx Cmd Frames
//-------------------------------------------------------
void cmdframerxparameters_rxparams_from_rxsetup(tCmdFrameRxParameters* rx_params);
void cmdframerxparameters_rxparams_to_rxsetup(tCmdFrameRxParameters* rx_params);
#ifdef DEVICE_IS_TRANSMITTER
// Tx: send cmd to Rx
void pack_txcmdframe_cmd(tTxFrame* frame, tFrameStats* frame_stats, tRcData* rc, uint8_t cmd);
// Tx: handle FRAME_CMD_RX_SETUPDATA from Rx
void unpack_rxcmdframe_rxsetupdata(tRxFrame* frame);
// Tx: send new receiver parameters with FRAME_CMD_SET_RX_PARAMS to Rx
// we take the values from Tx' Setup.Rx structure
void pack_txcmdframe_setrxparams(tTxFrame* frame, tFrameStats* frame_stats, tRcData* rc);
#endif

#ifdef DEVICE_IS_RECEIVER
// Rx: send cmd to Tx
void pack_rxcmdframe_cmd(tRxFrame* frame, tFrameStats* frame_stats, uint8_t cmd);
// Rx: send FRAME_CMD_RX_SETUPDATA to Tx
void pack_rxcmdframe_rxsetupdata(tRxFrame* frame, tFrameStats* frame_stats);
// Rx: handle FRAME_CMD_SET_RX_PARAMS
// new parameter values are stored in Rx' Setup.Rx fields
void unpack_txcmdframe_setrxparams(tTxFrame* frame);
#endif


#endif // FRAMES_H
