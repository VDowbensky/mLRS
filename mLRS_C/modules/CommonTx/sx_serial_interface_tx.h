//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX Serial Interface
//********************************************************
#ifndef SX_SERIAL_INTERFACE_TX_H
#define SX_SERIAL_INTERFACE_TX_H
#pragma once


class tTxSxSerial : public tSerialBase
{
  public:
    void Init(tSerialBase* _serialport, tSerialBase* _mbridge, tSerialBase* _serial2port);
    bool IsEnabled(void);

    bool available(void) override;
    char getc(void) override;
    void putc(char c) override;
    void flush(void) override;

  private:
    tSerialBase* ser;
};


void tTxSxSerial::Init(tSerialBase* _serialport, tSerialBase* _mbridge, tSerialBase* _serial2port)
{
    tSerialBase::Init();

    switch (Setup.Tx[Config.ConfigId].SerialDestination) {
    case SERIAL_DESTINATION_SERIAL:
        ser = _serialport;
        break;
    case SERIAL_DESTINATION_SERIAL2:
        ser = _serial2port;
        break;
    case SERIAL_DESTINATION_MBRDIGE:
        ser = _mbridge;
        break;
    default:
        while (1) {} // must not happen
    }
    if (!ser) while (1) {} // must not happen
}


bool tTxSxSerial::IsEnabled(void)
{
    return true;
}


bool tTxSxSerial::available(void)
{
    if (!connected_and_rx_setup_available()) return 0;

    if (SERIAL_LINK_MODE_IS_MAVLINK(Setup.Rx.SerialLinkMode)) {
        return mavlink.available(); // get from serial via mavlink parser
    }
    return ser->available(); // get from serial
}


char tTxSxSerial::getc(void)
{
    if (!connected_and_rx_setup_available()) return 0;

    if (SERIAL_LINK_MODE_IS_MAVLINK(Setup.Rx.SerialLinkMode)) {
        return mavlink.getc(); // get from serial via mavlink parser
    }
    return ser->getc(); // get from serial
}


void tTxSxSerial::putc(char c)
{
    if (!connected_and_rx_setup_available()) return;

    if (SERIAL_LINK_MODE_IS_MAVLINK(Setup.Rx.SerialLinkMode)) { // this has to go via the parser
        mavlink.putc(c);
        return;
    }
    ser->putc(c);
}


void tTxSxSerial::flush(void)
{
    mavlink.flush(); // we don't distinguish here, can't harm to always flush mavlink handler
    ser->flush();
}


#endif // SX_SERIAL_INTERFACE_TX_H
