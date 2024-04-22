//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// While Transmit/Receive
//*******************************************************

#include <stdint.h>
#include "while.h"


extern uint16_t micros16(void);


void WhileBase::Init(void)
{
    do_cnt = 0;
    tstart_us = 0;
    tremaining_us = 0;
}


void WhileBase::Trigger(void)
{
    do_cnt = 10; // postpone action by few loops
    tstart_us = micros16();
    tremaining_us = dtmax_us(); // this starts it
}


void WhileBase::Do(void)
{
    if (tremaining_us <= 0) return;

    if (do_cnt) { // count down
        do_cnt--;
        if (!do_cnt) { handle_once(); }
        return;
    }

    tremaining_us = dtmax_us() - (int32_t)(micros16() - tstart_us);
    if (tremaining_us <= 0) return;

    handle();
}

