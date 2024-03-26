//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// IN
//********************************************************
#ifndef IN_H
#define IN_H
#pragma once


#include "../Common/common_types.h"

typedef enum 
{
    IN_STATE_IDLE = 0,
    IN_STATE_RECEIVING,
} IN_STATE_ENUM;


void InBase_Init(bool enable_flag);
void InBase_Configure(uint8_t new_config);
bool InBase_Update(tRcData* rc);


#endif // IN_H
