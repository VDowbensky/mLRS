//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// While Transmit/Receive
//*******************************************************
#ifndef WHILE_H
#define WHILE_H
#pragma once


//-------------------------------------------------------
// While transmit/receive tasks
//-------------------------------------------------------

//virtual void handle_once(void) {};
//virtual void handle(void) {};

//virtual int32_t dtmax_us(void) { return 1; }


void WhileBase_Init(void);
void WhileBase_Trigger(void);
void WhileBase_Do(void);

#endif // WHILE_H
