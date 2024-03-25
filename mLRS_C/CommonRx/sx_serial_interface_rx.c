//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX Serial Interface
//********************************************************
#include "sx_serial_interface_rx.h"

void tRxSxSerial_Init(void)
{
	tSerialBase_Init();
}

bool tRxSxSerial_available(void)
{
	if (SERIAL_LINK_MODE_IS_MAVLINK(Setup.Rx.SerialLinkMode)) return mavlink.available(); // get from serial via mavlink parser
	return serial.available(); // get from serial
}

char tRxSxSerial_getc(void)
{
	if (SERIAL_LINK_MODE_IS_MAVLINK(Setup.Rx.SerialLinkMode)) return mavlink.getc(); // get from serial via mavlink parser 
	return serial.getc(); // get from serial
}

void tRxSxSerial_flush(void)
{
	mavlink.flush(); // we don't distinguish here, can't harm to always flush mavlink handler
	serial.flush();
}

void tRxSxSerial_ putc(char c)
{
	if (SERIAL_LINK_MODE_IS_MAVLINK(Setup.Rx.SerialLinkMode)) mavlink.putc(c); // send to serial via mavlink parser
	else serial.putc(c); // send to serial
}
