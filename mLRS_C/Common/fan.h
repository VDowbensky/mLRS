//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Cooling Fan
//********************************************************
#ifndef FAN_H
#define FAN_H

#include <stdlib.h>
#include <ctype.h>


#ifdef USE_FAN
void tFan_Init(void);
void tFan_SetPower(int8_t power_dbm);

//-------------------------------------------------------
// Low-level beep implementation
//-------------------------------------------------------

#endif // USE_FAN

#endif // FAN_H



