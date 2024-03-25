//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Powerup Counter
//********************************************************
#ifndef POWERUP_CNT_H
#define POWERUP_CNT_H

// !!!!!!!!!!!
// ARGHHHH  we only can write twice to the same address after erased to FF, 1st to write arbitrary data, 2nd to write 00
// !!!!!!!!!!!
// So we use a full flash page, and count using the states FF, AA, 00

// ATTENTION: we must do that before RESTART!!! so that it are really only powerups!!


#include <inttypes.h>
#include "../Common/setup_types.h"


extern volatile uint32_t millis32(void);


//-------------------------------------------------------
// Generic PowerupCounter Class
//-------------------------------------------------------

#if !defined EE_USE_WORD && !defined EE_USE_DOUBLEWORD
#error Either EE_USE_WORD or EE_USE_DOUBLEWORD must be defined !
#endif
#ifndef EE_PAGE_SIZE
#error POWERUPCNT needs EE_PAGE_SIZE !
#endif
#if (EE_PAGE_SIZE < 0x0800) && (defined EE_USE_DOUBLEWORD)
#error EE_PAGE_SIZE is too small !
#endif

#define POWERUPCNT_EE_PAGE            (EE_START_PAGE + 2) // setup/eeprom uses two pages!
#define POWERUPCNT_EE_PAGE_ADDRESS    ((uint32_t)(0x08000000 + (POWERUPCNT_EE_PAGE * EE_PAGE_SIZE)))

#if defined EE_USE_WORD
  #define POWERUPCNT_FF               0xFFFFFFFF
  #define POWERUPCNT_AA               0xAAAAAAAA
  typedef uint32_t tPOWERUPCNT_UINT;
#else
  #define POWERUPCNT_FF               0xFFFFFFFFFFFFFFFF
  #define POWERUPCNT_AA               0xAAAAAAAAAAAAAAAA
  typedef uint64_t tPOWERUPCNT_UINT;
#endif


#define POWERUPCNT_TMO_MS             2000


#define POWERUPCNT_SIGNATURE_A        0x12345678FEDCBA90
#define POWERUPCNT_SIGNATURE_B        0x90BADCFE78563412


static uint64_t powerup_counter_signature = POWERUPCNT_SIGNATURE_A;


typedef enum {
    POWERUPCNT_TASK_NONE = 0,
    POWERUPCNT_TASK_BIND,
} POWERUPCNT_TASK_ENUM;

void PowerupCounterBase_Init(void);
void PowerupCounterBase_Do(void);
uint8_t PowerupCounterBase_Task(void);
//-------------------------------------------------------
// EE helper
//-------------------------------------------------------
#if defined EE_USE_WORD
EE_STATUS_ENUM ee_program_u32(uint32_t adr, uint32_t* data, uint8_t datalen);
void PowerupCounterBase_ee_program_val(uint32_t adr, uint32_t* data, uint8_t datalen);
#else
EE_STATUS_ENUM ee_program_u64(uint32_t adr, uint64_t* data, uint8_t datalen);
void PowerupCounterBase_ee_program_val(uint32_t adr, uint64_t* data, uint8_t datalen);
#endif // POWERUP_CNT
