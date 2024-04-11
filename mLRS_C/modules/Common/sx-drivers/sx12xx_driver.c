//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX12XX driver shim
//*******************************************************
#include "sx12xx_driver.h"

#ifdef DEVICE_HAS_I2C_DAC
void tI2cDac_Init(void)
{
    i2c_init();
    i2c_setdeviceadr(SX_PA_DAC_I2C_DEVICE_ADR);
    HAL_StatusTypeDef res = i2c_device_ready();
    initialized = (res == HAL_OK);
}

bool tI2cDac_put_buf_blocking(uint8_t device_adr, uint8_t* buf, uint16_t len)
{
    if (!initialized) return false;
    i2c_setdeviceadr(device_adr);
    HAL_StatusTypeDef res = i2c_put_buf_blocked(buf, len);
    return (res == HAL_OK);
}
//tI2cDac dac;
#endif

#ifdef DEVICE_HAS_INTERNAL_DAC_TWOCHANNELS
void tInternalDac_Init(void)
{
    dac_init(SX_PA_DAC);
    dac_config_channel(SX_PA_DAC, SX_PA_DAC_CHANNEL1, SX_PA_DAC_IO1);
    dac_config_channel(SX_PA_DAC, SX_PA_DAC_CHANNEL2, SX_PA_DAC_IO2);
}

void tInternalDacput_channel1(uint16_t value)
{
    dac_write_channel(SX_PA_DAC, SX_PA_DAC_CHANNEL1, value);
}

void put_channel2(uint16_t value) 
{
    dac_write_channel(SX_PA_DAC, SX_PA_DAC_CHANNEL2, value);
}
//tInternalDac dac;
#endif

void SxDriverDummy_Init(void) 
{
	
}

bool SxDriverDummy_isOk(void) 
{ 
	return true; 
}

void SxDriverDummy_StartUp(tSxGlobalConfig* global_config) 
{
	
}

void SxDriverDummy_SetPacketType(uint8_t PacketType) 
{
	
}

void SxDriverDummy_SetRfFrequency(uint32_t RfFrequency) 
{
	
}

void SxDriverDummy_GetPacketStatus(int8_t* RssiSync, int8_t* Snr) 
{
	
}

void SxDriverDummy_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms) 
{
	
}

void SxDriverDummy_ReadFrame(uint8_t* data, uint8_t len) 
{
	
}

void SxDriverDummy_SetToRx(uint16_t tmo_ms) 
{
	
}

void SxDriverDummy_SetToIdle(void) 
{
	
}

void SxDriverDummy_ResetToLoraConfiguration() 
{
	
}

void SxDriverDummy_SetRfPower_dbm(int8_t power_dbm) 
{
	
}

void SxDriverDummy_ClearIrqStatus(uint16_t IrqMask) 
{
	
}

int16_t SxDriverDummy_ReceiverSensitivity_dbm(void) 
{ 
	return 0; 
}

int8_t SxDriverDummy_RfPower_dbm(void) 
{ 
	return INT8_MIN; 
}

void SxDriverDummy_HandleAFC(void) 
{
	
}
