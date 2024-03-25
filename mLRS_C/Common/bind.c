//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Bind
//*******************************************************
#ifndef BIND_H
#define BIND_H

#include "bind.h"

uint32_t auto_bind_tmo_ms;
bool is_in_binding; // is in sync with link loop
bool binding_requested;
bool binding_stop_requested;
uint32_t button_tlast_ms;
uint8_t task;
bool is_connected;
uint64_t TxSignature; // 8 bytes, signature of Tx module
uint64_t RxSignature; // 8 bytes, signature of Rx module
bool is_pressed;
int8_t pressed_cnt;


bool BindBase_IsInBind(void) 
{ 
	return is_in_binding; 
}
	
void BindBase_StartBind(void) 
{ 
	binding_requested = true; 
}
	
void BindBase_StopBind(void) 
{ 
	binding_stop_requested = true; 
}

void BindBase_Init(void)
{
    is_in_binding = false;
    binding_requested = false;
    binding_stop_requested = false;
    task = BIND_TASK_NONE;
    is_connected = false;

    button_tlast_ms = millis32();
    is_pressed = false;
    pressed_cnt = 0;

    memcpy(&TxSignature, BIND_SIGNATURE_TX_STR, 8);
    memcpy(&RxSignature, BIND_SIGNATURE_RX_STR, 8);

    auto_bind_tmo_ms = 1000 * RX_BIND_MODE_AFTER_POWERUP_TIME_SEC;
}


void BindBase_ConfigForBind(void)
{
    // switch to 19 Mode, select lowest possible power
    configure_mode(MODE_19HZ);

    sx.SetToIdle();
    sx2.SetToIdle();
    sx.SetRfPower_dbm(rfpower_list[0].dbm);
    sx2.SetRfPower_dbm(rfpower_list[0].dbm);
    sx.ResetToLoraConfiguration();
    sx2.ResetToLoraConfiguration();
    sx.SetToIdle();
    sx2.SetToIdle();
}

// called in each doPreTransmit or doPostReceive cycle
void BindBase_Do(void)
{
    uint32_t tnow = millis32();

    // a not so efficient but simple debounce
    if (!is_pressed) 
	{
        if (button_pressed()) pressed_cnt++;
		else pressed_cnt = 0;
        if (pressed_cnt >= 4) is_pressed = true;
    } 
	else 
	{
        if (!button_pressed()) pressed_cnt--;
		else pressed_cnt = 4;
        if (pressed_cnt <= 0) is_pressed = false;
    }

    if (is_pressed) 
	{
        if (tnow - button_tlast_ms > BIND_BUTTON_TMO_MS) binding_requested = true;
    } 
	else button_tlast_ms = tnow;

#ifdef DEVICE_IS_TRANSMITTER
    if (is_in_binding) 
	{
        if (is_connected && !connected()) task = BIND_TASK_TX_RESTART_CONTROLLER; // we just lost connection
        is_connected = connected();
        if (binding_stop_requested) task = BIND_TASK_TX_RESTART_CONTROLLER;
    }
#endif

    if (!is_in_binding && binding_requested) 
	{
        is_in_binding = true;
        task = BIND_TASK_CHANGED_TO_BIND;
    }
}


// called directly after bind.Do()
uint8_t BindBase_Task(void)
{
    switch (task) 
	{
		case BIND_TASK_TX_RESTART_CONTROLLER:
		case BIND_TASK_RX_STORE_PARAMS:
        // postpone until button is released, prevents jumping to RESTART while button is till pressed by user
        if (is_pressed) return BIND_TASK_NONE;
        break;
    }
    uint8_t ret = task;
    task = BIND_TASK_NONE;
    return ret;
}


void BindBase_AutoBind(void) // only for receiver, call every ms
{
#if defined DEVICE_IS_RECEIVER && defined RX_BIND_MODE_AFTER_POWERUP
    if (!auto_bind_tmo_ms) return;
    auto_bind_tmo_ms--;

    if (auto_bind_tmo_ms == 0) binding_requested = true;
#endif
}


tTxBindFrame txBindFrame;
tRxBindFrame rxBindFrame;


#ifdef DEVICE_IS_TRANSMITTER
void BindBase_handle_receive(uint8_t antenna, uint8_t rx_status)
{
    if (rx_status == RX_STATUS_INVALID) return;
    // do stuff
}


void BindBase_do_transmit(uint8_t antenna)
{
    memset(&txBindFrame, 0, sizeof(txBindFrame));
    txBindFrame.bind_signature = TxSignature;
    txBindFrame.connected = connected();
    strbufstrcpy(txBindFrame.BindPhrase_6, Setup.Common[Config.ConfigId].BindPhrase, 6);
    // TODO txBindFrame.FrequencyBand = Setup.Common[Config.ConfigId].FrequencyBand;
    txBindFrame.Mode = Setup.Common[Config.ConfigId].Mode;
    txBindFrame.Ortho = Setup.Common[Config.ConfigId].Ortho;
    txBindFrame.crc = fmav_crc_calculate((uint8_t*)&txBindFrame, FRAME_TX_RX_LEN - 2);
    sxSendFrame(antenna, &txBindFrame, FRAME_TX_RX_LEN, SEND_FRAME_TMO_MS);
}

uint8_t BindBase_do_receive(uint8_t antenna, bool do_clock_reset)
{
    sxReadFrame(antenna, &rxBindFrame, &rxBindFrame, FRAME_TX_RX_LEN);
    bool ok = (rxBindFrame.bind_signature == RxSignature);
    if (ok) 
	{
        uint16_t crc = fmav_crc_calculate((uint8_t*)&rxBindFrame, FRAME_TX_RX_LEN - 2);
        ok = (crc == rxBindFrame.crc);
    }
    sxGetPacketStatus(antenna, &stats);
    if (ok) return RX_STATUS_VALID;
    return RX_STATUS_INVALID;
}

#endif

#ifdef DEVICE_IS_RECEIVER
void BindBase_handle_receive(uint8_t antenna, uint8_t rx_status)
{
    if (rx_status == RX_STATUS_INVALID) return;
    strstrbufcpy(Setup.Common[0].BindPhrase, txBindFrame.BindPhrase_6, 6);
    // TODO Setup.Common[0].FrequencyBand = txBindFrame.FrequencyBand;
    Setup.Common[0].Mode = txBindFrame.Mode;
    Setup.Common[0].Ortho = txBindFrame.Ortho;
    if (txBindFrame.connected) task = BIND_TASK_RX_STORE_PARAMS;
}

void BindBase_do_transmit(uint8_t antenna)
{
    memset(&rxBindFrame, 0, sizeof(rxBindFrame));
    rxBindFrame.bind_signature = RxSignature;
    rxBindFrame.connected = connected();
    rxBindFrame.firmware_version = VERSION;
    strbufstrcpy(rxBindFrame.device_name_20, DEVICE_NAME, 20);
    rxBindFrame.crc = fmav_crc_calculate((uint8_t*)&rxBindFrame, FRAME_TX_RX_LEN - 2);
    sxSendFrame(antenna, &rxBindFrame, FRAME_TX_RX_LEN, SEND_FRAME_TMO_MS);
}

uint8_t BindBase_do_receive(uint8_t antenna, bool do_clock_reset)
{
    sxReadFrame(antenna, &txBindFrame, &txBindFrame, FRAME_TX_RX_LEN);
    bool ok = (txBindFrame.bind_signature == TxSignature);
    if (ok) 
	{
        uint16_t crc = fmav_crc_calculate((uint8_t*)&txBindFrame, FRAME_TX_RX_LEN - 2);
        ok = (crc == txBindFrame.crc);
    }
    if (ok && do_clock_reset) clock_reset();
    sxGetPacketStatus(antenna, &stats);
    if (ok) return RX_STATUS_VALID;
    return RX_STATUS_INVALID;
}

#endif
