//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// test
//********************************************************
#ifndef BOARD_TEST_H
#define BOARD_TEST_H


#define PORTA_N  (sizeof(porta)/sizeof(porta[0]))
#define PORTB_N  (sizeof(portb)/sizeof(portb[0]))
#define PORTC_N  (sizeof(portc)/sizeof(portc[0]))


void init_test(void);
int main_test(void);

#endif // BOARD_TEST_H
