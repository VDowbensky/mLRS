//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// mLRS RX
/********************************************************

v0.0.00:
*/

#ifndef _MLRS_RX_H_
#define _MLRS_RX_H_

#define DBG_MAIN(x)
#define DBG_MAIN_SLIM(x)
#define DEBUG_ENABLED
#define FAIL_ENABLED


// we set the priorities here to have an overview, SysTick is at 15
#define CLOCK_IRQ_PRIORITY          10
#define UARTB_IRQ_PRIORITY          11 // serial
#define UART_IRQ_PRIORITY           12 // out pin
#define UARTC_IRQ_PRIORITY          11 // debug
#define SX_DIO_EXTI_IRQ_PRIORITY    13
#define SX2_DIO_EXTI_IRQ_PRIORITY   13
#define SWUART_TIM_IRQ_PRIORITY      9 // debug on swuart
#define BUZZER_TIM_IRQ_PRIORITY     14

#include "../Common/common_conf.h"
#include "../Common/common_types.h"
#include "../Common/hal/glue.h"
#include "../modules/stm32ll-lib/src/stdstm32.h"
#include "../modules/stm32ll-lib/src/stdstm32-peripherals.h"
#include "../modules/stm32ll-lib/src/stdstm32-mcu.h"
#include "../modules/stm32ll-lib/src/stdstm32-dac.h"
#include "../modules/stm32ll-lib/src/stdstm32-stack.h"
#ifdef STM32WL
#include "../modules/stm32ll-lib/src/stdstm32-subghz.h"
#endif
#include "../Common/hal/hal.h"
#include "../Common/sx-drivers/sx12xx.h"
#include "../modules/stm32ll-lib/src/stdstm32-delay.h" // these are dependent on hal
#include "../modules/stm32ll-lib/src/stdstm32-eeprom.h"
#include "../modules/stm32ll-lib/src/stdstm32-spi.h"
#ifdef USE_SX2
#include "../modules/stm32ll-lib/src/stdstm32-spib.h"
#endif
#ifdef USE_SERIAL
#include "../modules/stm32ll-lib/src/stdstm32-uartb.h"
#endif
#ifdef USE_DEBUG
#ifdef DEVICE_HAS_DEBUG_SWUART
#include "../modules/stm32ll-lib/src/stdstm32-uart-sw.h"
#else
#include "../modules/stm32ll-lib/src/stdstm32-uartc.h"
#endif
#endif
#ifdef USE_I2C
#include "../modules/stm32ll-lib/src/stdstm32-i2c.h"
#endif
#include "../Common/mavlink/fmav.h"
#include "../Common/setup.h"
#include "../Common/common.h"
#include "../Common/micros.h"
#include "../Common/diversity.h"
//#include "../Common/test.h" // un-comment if you want to compile for board test

#include "rxclock.h"
#include "rxstats.h"
#include "out_interface.h" // this includes uart.h, out.h, declares tOut out
#include "powerup.h"

//-------------------------------------------------------
// Mavlink
//-------------------------------------------------------
#include "mavlink_interface_rx.h"
#include "sx_serial_interface_rx.h"

RxClockBase rxclock;
PowerupCounterBase powerup;
tRxStats rxstats;
tRDiversity rdiversity;
tTDiversity tdiversity;

// is required in bind.h
void clock_reset(void);
//-------------------------------------------------------
// Init
//-------------------------------------------------------
void init_hw(void);
//-------------------------------------------------------
// SX12xx
//-------------------------------------------------------
void SX_DIO_EXTI_IRQHandler(void);
#ifdef USE_SX2
void SX2_DIO_EXTI_IRQHandler(void);
#endif

void link_task_init(void);
void link_task_set(uint8_t task);
void link_task_reset(void);
void process_received_txcmdframe(tTxFrame* frame);
void pack_rxcmdframe(tRxFrame* frame, tFrameStats* frame_stats);
//-- normal Tx, Rx frames handling
void prepare_transmit_frame(uint8_t antenna, uint8_t ack);
void process_received_frame(bool do_payload, tTxFrame* frame);
//-- receive/transmit handling api
void handle_receive(uint8_t antenna);
void handle_receive_none(void);
void do_transmit(uint8_t antenna);
uint8_t do_receive(uint8_t antenna, bool do_clock_reset);
//##############################################################################################################
//*******************************************************
// MAIN routine
//*******************************************************
int main_main(void);

#endif
