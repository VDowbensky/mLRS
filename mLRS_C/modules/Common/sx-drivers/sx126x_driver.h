//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX126X Driver
//*******************************************************
// contributed by jinchuuriki
//*******************************************************
#ifndef SX126X_DRIVER_H
#define SX126X_DRIVER_H

//-------------------------------------------------------
// SX Driver
//-------------------------------------------------------

typedef struct
{
    uint32_t br_bps;
    uint8_t PulseShape;
    uint8_t Bandwidth;
    uint32_t Fdev_hz;
    uint16_t PreambleLength;
    uint8_t PreambleDetectorLength;
    uint8_t SyncWordLength;
    uint8_t AddrComp;
    uint8_t PacketType;
    uint8_t PayloadLength;
    uint8_t CRCType;
    uint8_t Whitening;
    uint32_t TimeOverAir; // in us
    int16_t ReceiverSensitivity;
} tSxGfskConfiguration;

typedef enum 
{
    SX12xx_OSCILLATOR_CONFIG_TXCO_1P6_V = SX126X_DIO3_OUTPUT_1_6,
    SX12xx_OSCILLATOR_CONFIG_TXCO_1P7_V = SX126X_DIO3_OUTPUT_1_7,
    SX12xx_OSCILLATOR_CONFIG_TXCO_1P8_V = SX126X_DIO3_OUTPUT_1_8,
    SX12xx_OSCILLATOR_CONFIG_TXCO_2P2_V = SX126X_DIO3_OUTPUT_2_2,
    SX12xx_OSCILLATOR_CONFIG_TXCO_2P4_V = SX126X_DIO3_OUTPUT_2_4,
    SX12xx_OSCILLATOR_CONFIG_TXCO_2P7_V = SX126X_DIO3_OUTPUT_2_7,
    SX12xx_OSCILLATOR_CONFIG_TXCO_3P0_V = SX126X_DIO3_OUTPUT_3_0,
    SX12xx_OSCILLATOR_CONFIG_TXCO_3P3_V = SX126X_DIO3_OUTPUT_3_3,
    SX12xx_OSCILLATOR_CONFIG_CRYSTAL = UINT8_MAX,
} SX12xx_OSCILLATOR_CONFIG_ENUM;


#ifdef POWER_USE_DEFAULT_RFPOWER_CALC
void Sx126x_rfpower_calc(const int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm, const uint8_t GAIN_DBM, const uint8_t SX126X_MAX_DBM);
#endif

void Sx126x_Init(void);
//-- high level API functions
bool Sx126x_isOk(void);
void Sx126x_SetLoraConfiguration(const tSxLoraConfiguration* config);
void Sx126x_SetLoraConfigurationByIndex(uint8_t index);
void Sx126x_ResetToLoraConfiguration(void);
void Sx126x_SetGfskConfiguration(const tSxGfskConfiguration* config, uint16_t sync_word);
void Sx126x_SetGfskConfigurationByIndex(uint8_t index, uint16_t sync_word);
void Sx126x_SetRfPower_dbm(int8_t power_dbm);
void Sx126x_Configure(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx126x_ReadFrame(uint8_t* data, uint8_t len);
void Sx126x_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx126x_SetToRx(uint16_t tmo_ms);
void Sx126x_SetToIdle(void);
void Sx126x_GetPacketStatus(int8_t* RssiSync, int8_t* Snr);
void Sx126x_HandleAFC(void);

//-- RF power interface
//void Sx126x_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) = 0;

//-- helper
void Sx126x_config_calc(void);
// cumbersome to calculate in general, so use hardcoded for a specific settings
uint32_t Sx126x_TimeOverAir_us(void);
int16_t Sx126x_ReceiverSensitivity_dbm(void);
int8_t Sx126x_RfPower_dbm(void);

//-------------------------------------------------------
// Driver for SX1
//-------------------------------------------------------

#ifndef SX_BUSY
  #error SX must have a BUSY pin!
#endif
#if !defined SX_RESET && !defined SX_HAS_NO_RESET
  #error SX must have a RESET pin!
#endif

void Sx126x1_WaitOnBusy(void);
void Sx126x1_SpiSelect(void);
void Sx126x1_SpiDeselect(void);
void Sx126x1_SpiTransferByte(uint8_t* byteout, uint8_t* bytein);
//-- RF power interface
void Sx126x1_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm);
//-- init API functions
void Sx126x1_reset(void);
void Sx126x1_Init(void);
//-- high level API functions
void Sx126x1_StartUp(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx126x1_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx126x1_SetToRx(uint16_t tmo_ms);

//-------------------------------------------------------
// Driver for SX2
//-------------------------------------------------------
#if defined DEVICE_HAS_DIVERSITY || defined DEVICE_HAS_DUAL_SX126x_SX126x

#ifndef SX2_BUSY
  #error SX2 must have a BUSY pin!
#endif
#ifndef SX2_RESET
  #error SX2 must have a RESET pin!
#endif

void Sx126x2_WaitOnBusy(void);
void Sx126x2_SpiSelect(void);
void Sx126x2_SpiDeselect(void);
void Sx126x2_SpiTransferByte(uint8_t* byteout, uint8_t* bytein);
//-- RF power interface
void Sx126x2_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm);
//-- init API functions
void Sx126x2_reset(void);
void Sx126x2_Init(void);
//-- high level API functions
void Sx126x2_StartUp(tSxGlobalConfig* global_config);
//-- this are the API functions used in the loop
void Sx126x2_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void Sx126x2_SetToRx(uint16_t tmo_ms);
#endif

#endif // SX126X_DRIVER_H
