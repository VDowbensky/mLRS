//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// FIFO
//********************************************************

#include "fifo.h"

static uint16_t writepos; // pos at which the next byte will be stored
static uint16_t readpos; // pos at which the oldest byte is fetched
static uint16_t SIZEMASK;
static uint8_t 	buf[FIFO_SIZE];


void FifoBase_Init(void)
{
    writepos = readpos = 0;
    SIZEMASK = FIFO_SIZE - 1;
}

bool FifoBase_Put(uint8_t c)
{
    uint16_t next = (writepos + 1) & (SIZEMASK);
    if (next != readpos) 
	{ // fifo not full
        buf[writepos] = c;
        writepos = next;
        return true;
    }
    return false;
}

void FifoBase_PutBuf(void* buf, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) Put(((T*)buf)[i]);
}

uint16_t FifoBase_Available(void)
{
    int16_t d = (int16_t)writepos - (int16_t)readpos;
    if (d < 0) return d + (SIZEMASK + 1);
    return d;
}

bool FifoBase_HasSpace(uint16_t space)
{
    return (Available() < (FIFO_SIZE - space));
}

void FifoBase_T Get(void)
{
    if (writepos != readpos) 
	{ // fifo not empty
        c = buf[readpos];
        readpos = (readpos + 1) & (SIZEMASK);
        return c;
    }
    return 0;
}

void FifoBase_Flush(void)
{
    writepos = readpos = 0;
}


