//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// M Bridge Protocol
//*******************************************************
#include "mbridge_protocol.h"

uint8_t mbridge_cmd_payload_len(uint8_t cmd)
{
    switch (cmd) 
	{
		case MBRIDGE_CMD_TX_LINK_STATS: return MBRIDGE_CMD_TX_LINK_STATS_LEN;
		case MBRIDGE_CMD_REQUEST_INFO: return 0;
		case MBRIDGE_CMD_DEVICE_ITEM_TX: return MBRIDGE_CMD_DEVICE_ITEM_LEN;
		case MBRIDGE_CMD_DEVICE_ITEM_RX: return MBRIDGE_CMD_DEVICE_ITEM_LEN;
		case MBRIDGE_CMD_PARAM_REQUEST_LIST: return 0;
		case MBRIDGE_CMD_PARAM_ITEM: return MBRIDGE_CMD_PARAM_ITEM_LEN;
		case MBRIDGE_CMD_PARAM_ITEM2: return MBRIDGE_CMD_PARAM_ITEM_LEN;
		case MBRIDGE_CMD_PARAM_ITEM3: return MBRIDGE_CMD_PARAM_ITEM_LEN;
		case MBRIDGE_CMD_REQUEST_CMD: return MBRIDGE_CMD_REQUEST_CMD_LEN;
		case MBRIDGE_CMD_INFO: return MBRIDGE_CMD_INFO_LEN;
		case MBRIDGE_CMD_PARAM_SET: return MBRIDGE_CMD_PARAM_SET_LEN; break;
		case MBRIDGE_CMD_PARAM_STORE: return 0;
		case MBRIDGE_CMD_BIND_START: return 0;
		case MBRIDGE_CMD_BIND_STOP: return 0;
		case MBRIDGE_CMD_MODELID_SET: return MBRIDGE_CMD_MODELID_SET_LEN; break;
		case MBRIDGE_CMD_SYSTEM_BOOTLOADER: return 0;
    }
    return 0;
}
