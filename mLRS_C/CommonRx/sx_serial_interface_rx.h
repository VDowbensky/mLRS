//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX Serial Interface
//********************************************************
#ifndef SX_SERIAL_INTERFACE_RX_H
#define SX_SERIAL_INTERFACE_TX_H

void tRxSxSerial_Init(void);
bool tRxSxSerial_available(void);
char tRxSxSerial_getc(void);
void tRxSxSerial_flush(void);
void tRxSxSerial_ putc(char c);

#endif // SX_SERIAL_INTERFACE_RX_H
