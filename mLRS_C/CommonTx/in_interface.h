//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// IN Interface
//*******************************************************
#ifndef IN_INTERFACE_H
#define IN_INTERFACE_H
#pragma once


#include "../Common/hal/hal.h" // not needed but helps editor to get defines correct LOL
#include "in.h"


#ifdef USE_IN

//-------------------------------------------------------
// Interface Implementation

#if !(defined DEVICE_HAS_IN_ON_JRPIN5_RX || defined DEVICE_HAS_IN_ON_JRPIN5_TX)

#include "../modules/stm32ll-lib/src/stdstm32-uarte.h"

void tIn_Init(bool enable_flag);
#if defined DEVICE_HAS_IN || defined DEVICE_HAS_IN_INVERTED
bool tIn_config_sbus(bool enable_flag);
#if defined DEVICE_HAS_IN || defined DEVICE_HAS_IN_NORMAL
bool tIn_config_sbus_inverted(bool enable_flag);
bool available(void);
char getc(void);
#else // DEVICE_HAS_IN_ON_JRPIN5_RX or DEVICE_HAS_IN_ON_JRPIN5_TX

#include "jr_pin5_interface.h" // in case DEVICE_HAS_JRPIN5 was not defined

void tIn_Init(bool enable_flag);
bool tIn_config_sbus(bool enable_flag);
bool tIn_config_sbus_inverted(bool enable_flag);
bool available(void);
char getc(void);
void tIn_set_normal(void);
void tIn_set_inverted(void);

#endif

#endif // if (defined USE_IN)

#endif // IN_INTERFACE_H
