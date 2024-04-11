//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX128x Driver
//*******************************************************
#ifndef SX128X_DRIVER_H
#define SX128X_DRIVER_H
#pragma once


//-------------------------------------------------------
// SX Driver
//-------------------------------------------------------

typedef struct
{
    uint8_t Bandwidth;
    uint8_t CodingRate;
    uint8_t Bt;
    uint8_t AGCPreambleLength;
    uint8_t SyncWordLength;
    uint8_t SyncWordMatch;
    uint8_t PacketType;
    uint8_t PayloadLength;
    uint8_t CrcLength;
    uint16_t CrcSeed;
    uint32_t TimeOverAir; // in us
    int16_t ReceiverSensitivity;
} tSxFlrcConfiguration;

// map the irq bits
typedef enum {
    SX_IRQ_TX_DONE = SX1280_IRQ_TX_DONE,
    SX_IRQ_RX_DONE = SX1280_IRQ_RX_DONE,
    SX_IRQ_TIMEOUT = SX1280_IRQ_RX_TX_TIMEOUT,
    SX_IRQ_ALL     = SX1280_IRQ_ALL,
} SX_IRQ_ENUM;

// map the irq bits
typedef enum {
    SX2_IRQ_TX_DONE = SX1280_IRQ_TX_DONE,
    SX2_IRQ_RX_DONE = SX1280_IRQ_RX_DONE,
    SX2_IRQ_TIMEOUT = SX1280_IRQ_RX_TX_TIMEOUT,
    SX2_IRQ_ALL     = SX1280_IRQ_ALL,
} SX2_IRQ_ENUM;

#ifdef POWER_USE_DEFAULT_RFPOWER_CALC
void sx1280_rfpower_calc(const int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm, const uint8_t GAIN_DBM, const uint8_t SX1280_MAX_DBM);
#endif
void Sx128x_Init(void)
//-- high level API functions
bool Sx128x_isOk(void);
void Sx128x_SetLoraConfiguration(const tSxLoraConfiguration* config);
void Sx128x_SetLoraConfigurationByIndex(uint8_t index);
void Sx128x_ResetToLoraConfiguration(void);
void Sx128x_SetFlrcConfiguration(const tSxFlrcConfiguration* config, uint32_t sync_word);
void Sx128x_SetFlrcConfigurationByIndex(uint8_t index, uint32_t sync_word);
void Sx128x_SetRfPower_dbm(int8_t power_dbm);
void Sx128x_Configure(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx128x_ReadFrame(uint8_t* data, uint8_t len);
void Sx128x_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx128x_SetToRx(uint16_t tmo_ms);
void Sx128x_SetToIdle(void);
void Sx128x_GetPacketStatus(int8_t* RssiSync, int8_t* Snr);
void Sx128x_HandleAFC(void);
//-- RF power interface
//void RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) = 0;
//-- helper
void Sx128x_config_calc(void);
// cumbersome to calculate in general, so use hardcoded for a specific settings
uint32_t Sx128x_TimeOverAir_us(void);
int16_t Sx128x_ReceiverSensitivity_dbm(void);
int8_t Sx128x_RfPower_dbm(void);
//-------------------------------------------------------
// Driver for SX1
//-------------------------------------------------------
#if !defined DEVICE_HAS_DUAL_SX126x_SX128x

#ifndef SX_BUSY
  #error SX must have a BUSY pin!
#endif
#ifndef SX_RESET
  #error SX must have a RESET pin!
#endif

//-- interface to SPI peripheral
void Sx128x1_WaitOnBusy(void);
void Sx128x1_SpiSelect(void);
void Sx128x1_SpiDeselect(void);
void Sx128x1_SpiTransferByte(uint8_t* byteout, uint8_t* bytein);
//-- RF power interface
void Sx128x1_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm);
//-- init API functions
void Sx128x1_reset(void);
void Sx128x1_Init(void);
//-- high level API functions
void Sx128x1_StartUp(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx128x1_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx128x1_SetToRx(uint16_t tmo_ms);
#endif

//-------------------------------------------------------
// Driver for SX2
//-------------------------------------------------------
#if defined DEVICE_HAS_DIVERSITY || defined DEVICE_HAS_DUAL_SX126x_SX128x

#ifndef SX2_BUSY
  #error SX2 must have a BUSY pin!
#endif
#ifndef SX2_RESET
  #error SX2 must have a RESET pin!
#endif

void Sx128x2_WaitOnBusy(void);
void Sx128x2SpiSelect(void);
void Sx128x2SpiDeselect(void);
void Sx128x2SpiTransferByte(uint8_t* byteout, uint8_t* bytein);
//-- RF power interface
void Sx128x2RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm);
//-- init API functions
void Sx128x2reset(void);
void Sx128x2Init(void);
//-- high level API functions
void Sx128x2StartUp(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx128x2SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx128x2SetToRx(uint16_t tmo_ms);
#endif

#endif // SX128X_DRIVER_H
