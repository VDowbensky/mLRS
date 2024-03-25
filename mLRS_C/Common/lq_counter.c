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
#pragma once


//-------------------------------------------------------
// 1 Hz count statistics
//-------------------------------------------------------
// that's one way to get stats

uint8_t LqCounterBase_calc_raw(void);

uint8_t LqCounterBase_period;
uint64_t LqCounterBase_periodbit;
uint64_t LqCounterBase_shiftreg;
uint64_t LqCounterBase_curbit;
uint8_t LqCounterBase_LQraw_last;

uint32_t StatsCount_count;
uint32_t StatsCount_count_last;
uint32_t StatsCount_counts_per_sec;
uint8_t StatsCount_LQ;

void StatsCount_Init(void)
{
    count = count_last = counts_per_sec = 0;
    LQ = 0;
}

// targeted at LQ
void StatsLQ_Update1Hz(void)
{
    // the period is Config.frame_rate_ms * Config.frame_rate_hz, and may not be exactly 1000
    counts_per_sec = count - count_last;
    LQ = (counts_per_sec * 100) / Config.frame_rate_hz;
    count_last = count;
}

void StatsLQ_Inc(void)
{
    count++;
}

uint8_t StatsLQ_GetLQ(void)
{
    return LQ;
}

void StatsBytes_Update1Hz(void) 
{
    counts_per_sec = count - count_last; // are not exactly the bytes per sec, but the difference is 0.8% at most
    count_last = count;
}

void StatsBytes_Add(uint16_t num)
{
    StatsBytes_count += num;
}

uint32_t StatsBytes_GetBytesPerSec(void) // this make a presumption about its usage :)
{
    return StatsBytes_counts_per_sec;
}

//-------------------------------------------------------
// moving window statistics
//-------------------------------------------------------
// that's another way to get stats

void LqCounterBase_Init(uint8_t _period)
{
    LqCounterBase_SetPeriod(_period);
    LqCounterBase_Reset();
}

void LqCounterBase_SetPeriod(uint8_t new_period)
{
	LqCounterBase_period = new_period;
    LqCounterBase_periodbit = (uint64_t)1 << (period - 1);
}

void LqCounterBase_Reset(void)
{
    LqCounterBase_shiftreg = 0xFFFFFFFFFFFFFFFF; // this makes it that it starts with 100%
    LqCounterBase_curbit = periodbit; // so that calling Next() makes it to start at bit 1
    LqCounterBase_LQraw_last = period;
}

void LqCounterBase_Set(void)
{
    LqCounterBase_shiftreg |= curbit;
}

void LqCounterBase_Next(void)
{
    LqCounterBase_LQraw_last = calc_raw(); // buffer it, required since Next() and Set() do not coincide
    LqCounterBase_curbit <<= 1;
    if (curbit > periodbit) curbit = 1;
    LqCounterBase_shiftreg &=~ curbit;
}

uint8_t LqCounterBase_GetRaw(void)
{
    return LQraw_last;
}

uint8_t LqCounterBase_GetNormalized(void)
{
    return (LQraw_last * 100 + period/2) / period;
}

uint8_t LqCounterBase_calc_raw(void)
{
    uint16_t LQraw = 0;
    uint64_t bit = 1;
    while (bit <= periodbit) 
	{
		if (shiftreg & bit) LQraw++;
        bit <<= 1;
    }
    return LQraw;
}
