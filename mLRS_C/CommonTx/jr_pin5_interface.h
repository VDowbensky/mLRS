//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// JR Pin5 Interface Header
//********************************************************
//
// Documentation
//
// 1. Methods which require external hardware, like xor and buffer chips
//   these are essentially used for F103 chips
//
//   #define JRPIN5_TX_XOR  : a xor is in the Tx line to invert the Tx signal
//
//   #define JRPIN5_RX_XOR  : a xor is in the Rx line to invert the Rx signal
//
//   #define JRPIN5_TX_OE   : Tx & Rx inverter with Tx buffer method
//
// 2. Methods which use the swap and invert capability of more modern UART peripherals
//   but need an external Schottky diode
//
//   #define JRPIN5_RX_TX_INVERT_INTERNAL
//     internal peripheral inverter method, needs a diode from Tx to Rx
//     the jrpin5 signal is on the Rx pin
//
//   #define JRPIN5_RX_TX_INVERT_SWAP_INTERNAL
//     internal peripheral inverter method with Tx<->Rx swap, needs a diode from Rx to Tx
//     the jrpin5 signal is on the Tx pin
//
// 3. Methods which use the swap and invert capability of more modern UART peripherals
//   but avoid the need of an external Schottky diode
//   they essentially supersede the other options
//
//   #define JRPIN5_FULL_INTERNAL_ON_TX     : jrpin5 signal is on the Tx pin
//
//   #define JRPIN5_FULL_INTERNAL_ON_RX     : jrpin5 signal is on the Rx pin
//
//   #define JRPIN5_FULL_INTERNAL_ON_RX_TX  : in cases there Rx & Tx pins are electrically connected
//
#ifndef JRPIN5_INTERFACE_H
#define JRPIN5_INTERFACE_H
#pragma once


#include "../Common/hal/hal.h" // not needed but helps editor to get defines correct LOL

// parser
typedef enum 
{
	STATE_IDLE = 0,
	// mBridge receive states
	STATE_RECEIVE_MBRIDGE_STX2,
	STATE_RECEIVE_MBRIDGE_LEN,
	STATE_RECEIVE_MBRIDGE_SERIALPACKET,
	STATE_RECEIVE_MBRIDGE_CHANNELPACKET,
	STATE_RECEIVE_MBRIDGE_COMMANDPACKET,
	// crsf receive states
	STATE_RECEIVE_CRSF_LEN,
	STATE_RECEIVE_CRSF_PAYLOAD,
	STATE_RECEIVE_CRSF_CRC,
	// transmit states, used by all
	STATE_TRANSMIT_START,
	STATE_TRANSMITING,
} STATE_ENUM;


extern volatile uint32_t millis32(void);


//-------------------------------------------------------
// Interface Implementation
// the uart used for JR pin5 must be UART_UARTx

void uart_rx_callback_dummy(uint8_t c) {}
void uart_tc_callback_dummy(void) {}

void (*uart_rx_callback_ptr)(uint8_t) = &uart_rx_callback_dummy;
void (*uart_tc_callback_ptr)(void) = &uart_tc_callback_dummy;

#define UART_RX_CALLBACK_FULL(c)    (*uart_rx_callback_ptr)(c)
#define UART_TC_CALLBACK()          (*uart_tc_callback_ptr)()

#include "../modules/stm32ll-lib/src/stdstm32-uart.h"

void tPin5BridgeBase_Init(void);
void pin5_tx_start(void) ;
void tPin5BridgeBaseTelemetryStart(void);
// actual isr functions
void uart_rx_callback(uint8_t c);
void uart_tc_callback(void);
// for in-isr processing
void pin5_tx_enable(bool enable_flag);
void CheckAndRescue(void);
// not available in stdstm32-uart.h, used for half-duplex mode
void uart_tx_putc_totxbuf(char c);
// not available in stdstm32-uart.h, used for half-duplex mode
void uart_tx_start(void);
// not available in stdstm32-uart.h, used for full-duplex mode
void uart_rx_putc_torxbuf(uint8_t c);
void tPin5BridgeBase_CheckAndRescue(void);
void tPin5BridgeBase_TelemetryStart(void);
void tPin5BridgeBase_pin5_tx_enable(bool enable_flag);
// we do not add a delay here before we transmit
// the logic analyzer shows this gives a 30-35 us gap nevertheless, which is perfect
void tPin5BridgeBase_uart_rx_callback(uint8_t c);
void tPin5BridgeBase_uart_tc_callback(void);

#endif // JRPIN5_INTERFACE_H
