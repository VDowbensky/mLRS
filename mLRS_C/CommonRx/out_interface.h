//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// OUT Interface
//********************************************************
#ifndef OUT_INTERFACE_H
#define OUT_INTERFACE_H

#include "../Common/hal/hal.h" // not needed but helps editor to get defines correct LOL
#include "out.h"

extern tRxStats rxstats;

void tOut_Init(void);	
void tOut_SendLinkStatistics(void);

#ifdef USE_OUT
//-------------------------------------------------------
// Interface Implementation

#include "../modules/stm32ll-lib/src/stdstm32-uart.h"

#if defined DEVICE_HAS_OUT || defined DEVICE_HAS_OUT_NORMAL
bool tOut_config_crsf(bool enable_flag);
bool tOut_config_sbus_inverted(bool enable_flag);
#endif
#if defined DEVICE_HAS_OUT || defined DEVICE_HAS_OUT_INVERTED
bool tOut_config_sbus(bool enable_flag);
#endif
void putc(char c);
void tOut_SendLinkStatistics(void);

#endif // #ifdef USE_OUT

#endif // OUT_INTERFACE_H
