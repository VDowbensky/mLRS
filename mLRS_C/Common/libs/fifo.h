//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// FIFO
//********************************************************
#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>

void FifoBase_Init(void);
bool FifoBase_Put(uint8_t c);
void FifoBase_PutBuf(void* buf, uint16_t len);
uint16_t FifoBase_Available(void);
bool FifoBase_HasSpace(uint16_t space);
void FifoBase_T Get(void);
void FifoBase_Flush(void);

#endif // FIFO_H
