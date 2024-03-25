//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Micros
//********************************************************
#ifndef MICROS_H
#define MICROS_H

// free running timer with 1us time base


#ifndef MICROS_TIMx
#error MICROS_TIMx not defined !
#endif


//-------------------------------------------------------
// Micros functions
//-------------------------------------------------------
void micros_init(void);
uint16_t micros(void);

#endif // MICROS_H
