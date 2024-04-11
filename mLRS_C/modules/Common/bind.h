//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Bind
//*******************************************************
#ifndef BIND_H
#define BIND_H
#pragma once


#include <stdint.h>
#include "common_conf.h"


extern volatile uint32_t millis32(void);
static inline bool connected(void);
extern void clock_reset(void);

extern SX_DRIVER sx;
extern SX2_DRIVER sx2;

extern void sxReadFrame(uint8_t antenna, void* data, void* data2, uint8_t len);
extern void sxSendFrame(uint8_t antenna, void* data, uint8_t len, uint16_t tmo_ms);
extern void sxGetPacketStatus(uint8_t antenna, Stats* stats);

extern Stats stats;


//-------------------------------------------------------
// Bind Class
//-------------------------------------------------------

#define BIND_SIGNATURE_TX_STR  "mLRS\x01\x02\x03\x04"
#define BIND_SIGNATURE_RX_STR  "mLRS\x04\x03\x02\x01"
#define BIND_BUTTON_TMO_MS     4000


typedef enum {
    BIND_TASK_NONE = 0,
    BIND_TASK_CHANGED_TO_BIND,
    BIND_TASK_RX_STORE_PARAMS,
    BIND_TASK_TX_RESTART_CONTROLLER,
} BIND_TASK_ENUM;



bool BindBase_IsInBind(void);
void BindBase_StartBind(void);
void BindBase_StopBind(void);
void BindBase_Init(void);
void BindBase_ConfigForBind(void);
// called in each doPreTransmit or doPostReceive cycle
void BindBase_Do(void);
// called directly after bind.Do()
uint8_t BindBase_Task(void);
void BindBase_AutoBind(void);

void BindBase_handle_receive(uint8_t antenna, uint8_t rx_status);
void BindBase_do_transmit(uint8_t antenna);
uint8_t BindBase_do_receive(uint8_t antenna, bool do_clock_reset);

extern tTxBindFrame txBindFrame;
extern tRxBindFrame rxBindFrame;

#endif // BIND_H
