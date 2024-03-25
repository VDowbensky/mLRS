//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// fail
//*******************************************************
#ifndef FAIL_H
#define FAIL_H
#pragma once


#include <stdint.h>
#include "common_types.h"


typedef enum 
{
    FAIL_LED_PATTERN_GR_OFF_RD_BLINK = 1,
    FAIL_LED_PATTERN_RD_OFF_GR_BLINK = 2,
    FAIL_LED_PATTERN_GR_ON_RD_BLINK = 3,
    FAIL_LED_PATTERN_RD_ON_GR_BLINK = 4,
    FAIL_LED_PATTERN_BLINK_COMMON = 5,
    FAIL_LED_PATTERN_BLINK_ALTERNATE = 6,

    FAIL_LED_PATTERN_RD_BLINK_GR_BLINK1 = 10,
    FAIL_LED_PATTERN_RD_BLINK_GR_BLINK2,
    FAIL_LED_PATTERN_RD_BLINK_GR_BLINK3,
    FAIL_LED_PATTERN_RD_BLINK_GR_BLINK4,
    FAIL_LED_PATTERN_RD_BLINK_GR_BLINK5,
} FAIL_LED_PATTERN_ENUM;


uint16_t fail_dbg_cnt;

void fail_do_dbg(tSerialBase* dbg, const char* msg);
void fail(tSerialBase* dbg, uint8_t led_pattern, const char* msg);

#endif // FAIL_H
