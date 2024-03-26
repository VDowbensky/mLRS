//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// EPS Wifi Bridge Interface Header
//********************************************************
#ifndef TX_ESP_H
#define TX_ESP_H
#pragma once


#include <stdlib.h>
#include <ctype.h>


//-------------------------------------------------------
// ESP Helper
//-------------------------------------------------------

#define ESP_PASSTHROUGH_TMO_MS  3000

typedef enum 
{
    ESP_TASK_NONE = 0,
    ESP_TASK_RESTART_CONTROLLER,
} ESP_TASK_ENUM;

void esp_enable(uint8_t serial_destination);

#ifdef USE_ESP_WIFI_BRIDGE

extern volatile uint32_t millis32(void);
extern tTxDisp disp;
//public:
void tTxEspWifiBridge_Init(tSerialBase* _comport, tSerialBase* _serialport);
void tTxEspWifiBridge_Do(void);
uint8_t tTxEspWifiBridge_Task(void);

void tTxEspWifiBridge_EnterFlash(void);
void tTxEspWifiBridge_EnterCli(void);
void tTxEspWifiBridge_EnterPassthrough(void);

#endif // USE_ESP_WIFI_BRIDGE

#endif // TX_ESP_H



