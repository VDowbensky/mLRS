//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Some Filters
//*******************************************************
#ifndef FILTERS_H
#define FILTERS_H

#include <stdint.h>

void LPFilterRate_Reset(void);
void LPFilterRate_Update(int32_t tnow_ms, int32_t x, int32_t T_ms);
int32_t LPFilterRate_Get(void);

extern int32_t Tfilt_ms;
extern int32_t xlast;
extern int32_t tlast_ms;
extern int32_t filt_internal;
extern uint8_t state;

#endif // FILTERS_H
