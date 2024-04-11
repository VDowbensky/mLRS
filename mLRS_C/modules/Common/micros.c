//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Micros
//********************************************************
#include "micros.h"

// free running timer with 1us time base

//-------------------------------------------------------
// Micros functions
//-------------------------------------------------------

void micros_init(void)
{
    tim_init_1us_freerunning(MICROS_TIMx);
}


uint16_t micros(void)
{
    return MICROS_TIMx->CNT;
}

