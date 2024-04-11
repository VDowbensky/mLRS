//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX12XX driver shim
//*******************************************************
#ifndef SX12XX_DRIVER_H
#define SX12XX_DRIVER_H

#include "hal.h"

#if defined DEVICE_HAS_SX126x || defined DEVICE_HAS_DUAL_SX126x_SX126x
#include "sx126x_driver.h"
#elif defined DEVICE_HAS_SX127x
#include "sx127x_driver.h"
#elif defined DEVICE_HAS_DUAL_SX126x_SX128x
#include "sx126x_driver.h"
#include "sx128x_driver.h"
#else
#include "sx128x_driver.h"
#endif

typedef struct
{
    uint8_t SpreadingFactor;
    uint8_t Bandwidth;
    uint8_t CodingRate;
    uint8_t PreambleLength;
    uint8_t HeaderType;
    uint8_t PayloadLength;
    uint8_t CrcEnabled;
    uint8_t InvertIQ;
    uint32_t TimeOverAir; // in us
    int16_t ReceiverSensitivity;
} tSxLoraConfiguration;

void SxDriverDummy_Init(void);
bool SxDriverDummy_isOk(void);
void SxDriverDummy_StartUp(tSxGlobalConfig* global_config);
void SxDriverDummy_SetPacketType(uint8_t PacketType);
void SxDriverDummy_SetRfFrequency(uint32_t RfFrequency);
void SxDriverDummy_GetPacketStatus(int8_t* RssiSync, int8_t* Snr);
void SxDriverDummy_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms);
void SxDriverDummy_ReadFrame(uint8_t* data, uint8_t len);
void SxDriverDummy_SetToRx(uint16_t tmo_ms);
void SxDriverDummy_SetToIdle(void);
void SxDriverDummy_ResetToLoraConfiguration();
void SxDriverDummy_SetRfPower_dbm(int8_t power_dbm);
void SxDriverDummy_ClearIrqStatus(uint16_t IrqMask);
int16_t SxDriverDummy_ReceiverSensitivity_dbm(void);
int8_t SxDriverDummy_RfPower_dbm(void);
void SxDriverDummy_HandleAFC(void);

#ifdef DEVICE_HAS_I2C_DAC
void tI2cDac_Init(void);
bool tI2cDac_put_buf_blocking(uint8_t device_adr, uint8_t* buf, uint16_t len);
//tI2cDac dac;
#endif

#ifdef DEVICE_HAS_INTERNAL_DAC_TWOCHANNELS
void tInternalDac_Init(void);
void tInternalDacput_channel1(uint16_t value);
void put_channel2(uint16_t value) ;
//tInternalDac dac;
#endif


#endif // SX12XX_DRIVER_H
