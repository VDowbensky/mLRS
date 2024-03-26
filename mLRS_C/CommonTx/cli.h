//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// CLI Interface Header
//********************************************************
#ifndef TX_CLI_H
#define TX_CLI_H

#include <stdlib.h>
#include <ctype.h>
#include "setup_tx.h"


extern volatile uint32_t millis32(void);
extern tTxStats txstats;
extern tConfigId config_id;


//-------------------------------------------------------
// param helper routines
//-------------------------------------------------------

typedef enum 
{
    PARAM_FORMAT_DEFAULT = 0,
    PARAM_FORMAT_CLI,
    PARAM_FORMAT_DISPLAY,
} PARAM_FORMAT_ENUM;

typedef enum 
{
    CLI_TASK_NONE = 0,
    CLI_TASK_RX_PARAM_SET,
    CLI_TASK_PARAM_STORE,
    CLI_TASK_BIND,
    CLI_TASK_PARAM_RELOAD,
    CLI_TASK_BOOT,
    CLI_TASK_FLASH_ESP,
    CLI_TASK_ESP_PASSTHROUGH,
    CLI_TASK_ESP_CLI,
    CLI_TASK_CHANGE_CONFIG_ID,
} CLI_TASK_ENUM;

typedef enum 
{
	CLI_STATE_NORMAL = 0,
	CLI_STATE_STATS,
} CLI_STATE_ENUM;

//public:
void tTxCli_Init(tSerialBase* _comport);
void tTxCli_Set(uint8_t new_line_end);
void tTxCli_Do(void);
uint8_t tTxCli_Task(void);
int32_t tTxCli_GetTaskValue(void);

#endif // TX_CLI_H



