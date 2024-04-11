//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX1276 Driver
//*******************************************************
#ifndef SX1276_DRIVER_H
#define SX1276_DRIVER_H

/* on syncword
https://forum.arduino.cc/t/what-is-sync-word-lora/629624/5:
The default private syncwords are 0x12 for SX127x devices and 0x1424 for SX126x devices.
The syncwords used for public networks such as LoRaWAN\TTN are 0x34 for SX127x devices and 0x3444 for SX126x devices.
https://www.thethingsnetwork.org/forum/t/should-private-lorawan-networks-use-a-different-sync-word/34496/5
https://www.thethingsnetwork.org/forum/t/should-private-lorawan-networks-use-a-different-sync-word/34496/15
*/


//-------------------------------------------------------
// SX Driver
//-------------------------------------------------------

// map the irq bits
typedef enum 
{
    SX_IRQ_TX_DONE = SX1276_IRQ_TX_DONE,
    SX_IRQ_RX_DONE = SX1276_IRQ_RX_DONE,
    SX_IRQ_TIMEOUT = SX1276_IRQ_RX_TIMEOUT,
    SX_IRQ_ALL     = SX1276_IRQ_ALL,
} SX_IRQ_ENUM;


#ifdef POWER_USE_DEFAULT_RFPOWER_CALC
void sx1276_rfpower_calc(const int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm, const uint8_t GAIN_DBM, const uint8_t SX1276_MAX_DBM);
#endif

void Sx127x_Init(void);

//-- high level API functions
bool Sx127x_isOk(void);
void Sx127x_SetLoraConfiguration(const tSxLoraConfiguration* config);
void Sx127x_SetLoraConfigurationByIndex(uint8_t index);
void Sx127x_ResetToLoraConfiguration(void);
void Sx127x_SetRfPower_dbm(int8_t power_dbm);
void Sx127x_Configure(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx127x_ReadFrame(uint8_t* data, uint8_t len);
void Sx127x_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx127x_SetToRx(uint16_t tmo_ms);
void Sx127x_SetToIdle(void);
void Sx127x_GetPacketStatus(int8_t* RssiSync, int8_t* Snr);
void Sx127x_SetRfFrequency(uint32_t RfFrequency);
void Sx127x_HandleAFC(void);
//-- RF power interface
//void RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) = 0;
//-- helper
void Sx127x_config_calc(void);
// cumbersome to calculate in general, so use hardcoded for a specific settings
uint32_t TimeOverAir_us(void);
int16_t Sx127x_ReceiverSensitivity_dbm(void);
int8_t Sx127x_RfPower_dbm(void);
uint32_t Sx127x_calc_symbol_time_us(uint8_t SpreadingFactor, uint8_t Bandwidth);
//-------------------------------------------------------
// Driver for SX1
//-------------------------------------------------------

// SX1276 doesn't has BUSY
#ifndef SX_RESET
  #error SX must have a RESET pin!
#endif
//-- interface to SPI peripheral
void Sx127x1_SpiSelect(void);
void Sx127x1_SpiDeselect(void);
void Sx127x1_SpiTransferByte(uint8_t* byteout, uint8_t* bytein);
//-- RF power interface
void Sx127x1_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm);
//-- init API functions
void Sx127x1_reset(void);
void Sx127x1_Init(void);
//-- high level API functions
void Sx127x1_StartUp(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx127x1_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx127x1_SetToRx(uint16_t tmo_ms);

//-------------------------------------------------------
// Driver for SX2
//-------------------------------------------------------
#ifdef DEVICE_HAS_DIVERSITY
  #error Diversity not yet supported for SX127x!
#endif


#endif // SX1276_DRIVER_H
