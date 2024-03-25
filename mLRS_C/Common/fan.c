//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Cooling Fan
//********************************************************
#include "fan.h"


#include <stdlib.h>
#include <ctype.h>


#ifdef USE_FAN

bool fan_initialized;
int8_t fan_power_dbm_curr;


void tFan_Init(void)
{
    fan_init();
    fan_initialized = false;
    fan_power_dbm_curr = POWER_MIN;
}


void tFan_SetPower(int8_t power_dbm)
{
#ifdef DEVICE_HAS_FAN_ONOFF
    if (fan_power_dbm_curr != power_dbm || !fan_initialized) 
	{
        fan_initialized = true;
        fan_set_power(power_dbm);
        fan_power_dbm_curr = power_dbm;
    }
#endif
}


//-------------------------------------------------------
// Low-level beep implementation
//-------------------------------------------------------

#endif // DEVICE_HAS_FAN




