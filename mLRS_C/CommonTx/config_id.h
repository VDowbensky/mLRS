//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// ConfiId
//********************************************************
#ifndef CONFIGID_H
#define CONFIGID_H

#include <inttypes.h>


//-------------------------------------------------------
// Generic ConfigId Class
//-------------------------------------------------------

void tConfigId_Init(void);
void tConfigId_Change(uint8_t config_id);
bool tConfigId_Do(void);

#endif // CONFIGID_H
