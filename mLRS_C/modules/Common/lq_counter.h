//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// LQ
//*******************************************************
#ifndef LQ_COUNTER_H
#define LQ_COUNTER_H


//-------------------------------------------------------
// 1 Hz count statistics
//-------------------------------------------------------
// that's one way to get stats
void StatsCount_Init(void);
// targeted at LQ
void StatsLQ_Update1Hz(void);
void StatsLQ_Inc(void);
uint8_t StatsLQ_GetLQ(void);
void StatsBytes_Update1Hz(void);
void StatsBytes_Add(uint16_t num);
uint32_t StatsBytes_GetBytesPerSec(void); // this make a presumption about its usage :)
//-------------------------------------------------------
// moving window statistics
//-------------------------------------------------------
// that's another way to get stats
void LqCounterBase_Init(uint8_t _period);
void LqCounterBase_SetPeriod(uint8_t new_period);
void LqCounterBase_Reset(void);
void LqCounterBase_Set(void);
void LqCounterBase_Next(void);
uint8_t LqCounterBase_GetRaw(void);
uint8_t LqCounterBase_GetNormalized(void);
uint8_t LqCounterBase_calc_raw(void);
#endif // LQ_COUNTER_H
