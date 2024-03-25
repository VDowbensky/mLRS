//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Rx Clock
//********************************************************
#ifndef RXCLOCK_H
#define RXCLOCK_H

// we use a 10us time base, so that overrun is 655 ms
// 65 ms would only be 3 packets
// I have tested it with 1us time base, and it also works fine, but hey
// Note that TIM2 may be 16 bit or 32 bit depending on which STM32 controller is used


#ifndef CLOCK_TIMx
#error CLOCK_TIMx not defined !
#endif

#define CLOCK_SHIFT_10US          100 // 75 // 100 // 1 ms

volatile bool doPostReceive;
uint16_t CLOCK_PERIOD_10US; // does not change while isr is enabled, so no need for volatile

void RxClockBase_Init(uint16_t period_ms);
void RxClockBase_SetPeriod(uint16_t period_ms);
void RxClockBase_Reset(void);
void RxClockBase_init_isr_off(void);
void RxClockBase_enable_isr(void);
uint16_t RxClockBase_tim_10us(void);
void CLOCK_IRQHandler(void);

#endif // RXCLOCK_H
