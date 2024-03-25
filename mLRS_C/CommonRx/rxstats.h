//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Statistics for Receiver
//********************************************************
#ifndef RXSTATS_H


void tRxStats_Init(uint8_t _period);
void tRxStats_Update1Hz(void); // called at 1 Hz
void tRxStats_Next(void); // called at each cycle
void tRxStats_Clear(void); // called then not connected
void tRxStats_doFrameReceived(void);
void tRxStats_doValidCrc1FrameReceived(void);
void tRxStats_doValidFrameReceived(void);

#endif // RXSTATS_H
