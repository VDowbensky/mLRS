//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// rx hal splicer
//*******************************************************

#pragma once

#include "hal.h"


//-------------------------------------------------------
// Empty Prototypes
//-------------------------------------------------------
// should be in the device hal files, but is just so much more convenient to have them here

#ifndef DEVICE_HAS_SYSTEMBOOT
void systembootloader_init(void) 
{
	
}
#endif

#ifndef USE_ESP_WIFI_BRIDGE
void esp_init(void) 
{
	
}
#endif

#if !defined DEVICE_HAS_FIVEWAY && !defined USE_DISPLAY
void fiveway_init(void) 
{
	
}
#endif
