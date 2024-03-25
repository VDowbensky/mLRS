//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX1276 Driver
//*******************************************************
#include "sx127x_driver.h"


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

const tSxLoraConfiguration Sx127xLoraConfiguration[] = {
    { .SpreadingFactor = SX1276_LORA_SF6,
      .Bandwidth = SX1276_LORA_BW_500,
      .CodingRate = SX1276_LORA_CR_4_5,
      .PreambleLength = 12,
      .HeaderType = SX1276_LORA_HEADER_DISABLE,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcEnabled = SX1276_LORA_CRC_DISABLE,
      .InvertIQ = SX1276_LORA_IQ_NORMAL,
      .TimeOverAir = 22300,
      .ReceiverSensitivity = -112,
    }
};

const tSxLoraConfiguration* lora_configuration;
tSxGlobalConfig* gconfig;
uint8_t sx_power;
int8_t actual_power_dbm;
uint32_t symbol_time_us;


#ifdef POWER_USE_DEFAULT_RFPOWER_CALC
void sx1276_rfpower_calc(const int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm, const uint8_t GAIN_DBM, const uint8_t SX1276_MAX_DBM)
{
    // Pout = 17 - (15 - OutputPower) if PaSelect = 1 (PA_BOOST pin)
    int16_t power_sx = (int16_t)power_dbm - GAIN_DBM - 2;

    if (power_sx < SX1276_OUTPUT_POWER_MIN) power_sx = SX1276_OUTPUT_POWER_MIN;
    if (power_sx > SX1276_OUTPUT_POWER_MAX) power_sx = SX1276_OUTPUT_POWER_MAX;
    if (power_sx > SX1276_MAX_DBM) power_sx = SX1276_MAX_DBM;
    *sx_power = power_sx;
    *actual_power_dbm = power_sx + GAIN_DBM + 2;
}
#endif

void Sx127x_Init(void)
{
    lora_configuration = NULL;
}

//-- high level API functions
bool Sx127x_isOk(void)
{
    uint8_t firmwareRev = GetFirmwareRev();
    return (firmwareRev == 0x12);
}

void Sx127x_SetLoraConfiguration(const tSxLoraConfiguration* config)
{
    Sx127x_SetModulationParams(config->SpreadingFactor,
                            config->Bandwidth,
                            config->CodingRate);

    Sx127x_SetPacketParams(config->PreambleLength,
                        config->HeaderType,
                        config->PayloadLength,
                        config->CrcEnabled,
                        config->InvertIQ);

    symbol_time_us = calc_symbol_time_us(config->SpreadingFactor, config->Bandwidth);
}

void Sx127x_SetLoraConfigurationByIndex(uint8_t index)
{
    if (index >= sizeof(Sx127xLoraConfiguration)/sizeof(Sx127xLoraConfiguration[0])) while (1) {} // must not happen
    lora_configuration = &(Sx127xLoraConfiguration[index]);
    Sx127x_etLoraConfiguration(lora_configuration);
}

void Sx127x_ResetToLoraConfiguration(void)
{
    SetLoraConfigurationByIndex(gconfig->LoraConfigIndex);
}

void Sx127x_SetRfPower_dbm(int8_t power_dbm)
{
    Sx127x_RfPowerCalc(power_dbm, &sx_power, &actual_power_dbm);
    // MaxPower is irrelevant, so set it to SX1276_MAX_POWER_15_DBM
    // there would be special setting for +20dBm mode, don't do it
    // 5 OcpOn, 4-0 OcpTrim
    Sx127x_ReadWriteRegister(SX1276_REG_Ocp, 0x3F, SX1276_OCP_ON | SX1276_OCP_TRIM_150_MA);
    Sx127x_SetPowerParams(SX1276_PA_SELECT_PA_BOOST, SX1276_MAX_POWER_15_DBM, sx_power, SX1276_PA_RAMP_40_US);
}

void Sx127x_Configure(tSxGlobalConfig* global_config)
{
    gconfig = global_config;
    Sx127x_SetSleep(); // must be in sleep to switch to LoRa mode
        Sx127x_WriteRegister(SX1276_REG_OpMode, SX1276_PACKET_TYPE_LORA |
                                         SX1276_ACCESS_SHARED_REG_LORA |
                                         SX1276_LOW_FREQUENCY_MODE_OFF |
                                         SX1276_MODE_SLEEP);
    Sx127x_SetStandby();
    //SetOperationMode(SX1276_PACKET_TYPE_LORA, SX1276_LOW_FREQUENCY_MODE_OFF);
    uint8_t band_width = Sx127xLoraConfiguration[gconfig->LoraConfigIndex].Bandwidth;
    Sx127x_OptimizeSensitivity(band_width);
    Sx127x_OptimizeReceiverResponse(band_width);
    Sx127x_SetLnaParams(SX1276_LNA_GAIN_DEFAULT, SX1276_LNA_BOOST_HF_ON);
    // 3 LowDataRateOptimize, 2 AgcAutoOn
    Sx127x_ReadWriteRegister(SX1276_REG_ModemConfig3, 0x0C, SX1276_LORA_LOW_DATA_RATE_OPTIMIZE_OFF | SX1276_LORA_AGC_AUTO_ON);
    // 5 OcpOn, 4-0 OcpTrim
    //ReadWriteRegister(SX1276_REG_Ocp, 0x3F, SX1276_OCP_ON | SX1276_OCP_TRIM_150_MA);
    //SetPowerParams(SX1276_PA_SELECT_PA_BOOST, SX1276_MAX_POWER_15_DBM, 0, SX1276_PA_RAMP_40_US);
    Sx127x_SetRfPower_dbm(gconfig->Power_dbm);
    Sx127x_SetLoraConfigurationByIndex(gconfig->LoraConfigIndex);
    // SetSyncWord(0x12);
    Sx127x_SetBufferBaseAddress(0, 0);
    Sx127x_SetDioIrqParams(SX1276_IRQ_TX_DONE | SX1276_IRQ_RX_DONE | SX1276_IRQ_RX_TIMEOUT, // this helps for RX!! //  SX1276_IRQ_ALL,
                        SX1276_DIO0_MAPPING_RX_TX_DONE,
                        SX1276_DIO1_MAPPING_RX_TIMEOUT);
    Sx127x_ClearIrqStatus(SX1276_IRQ_ALL);
}

//-- this are the API functions used in the loop
void Sx127x_ReadFrame(uint8_t* data, uint8_t len)
{
    uint8_t rxStartBufferPointer;
    uint8_t rxPayloadLength;
    Sx127x_GetRxBufferStatus(&rxPayloadLength, &rxStartBufferPointer);
    Sx127x_ReadBuffer(rxStartBufferPointer, data, len);
}

void Sx127x_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms) // SX1276 doesn't have a Tx timeout
{
    Sx127x_WriteBuffer(0, data, len);
    Sx127x_ClearIrqStatus(SX1276_IRQ_ALL);
    Sx127x_SetTx();
}

void Sx127x_SetToRx(uint16_t tmo_ms)
{
    Sx127x_WriteRegister(SX1276_REG_FifoAddrPtr, 0);
    Sx127x_ClearIrqStatus(SX1276_IRQ_ALL);
    if (tmo_ms == 0) 
	{ // 0 = no timeout
        Sx127x_SetRxContinuous();
    } else 
	{
        Sx127x_SetRxTimeout(((uint32_t)tmo_ms * 1000) / symbol_time_us);
        Sx127x_SetRxSingle();
    }
}

void Sx127x_SetToIdle(void)
{
    Sx127x_SetStandby();
    Sx127x_ClearIrqStatus(SX1276_IRQ_ALL);
}

void Sx127x_GetPacketStatus(int8_t* RssiSync, int8_t* Snr)
{
    int16_t rssi;
    Sx127x_GetPacketStatus(&rssi, Snr);
    if (rssi > -1) rssi = -1; // we do not support values larger than this
    if (rssi < -127) rssi = -127; // we do not support values lower than this
    *RssiSync = rssi;
}

void Sx127x_SetRfFrequency(uint32_t RfFrequency)
{
    Sx127x_AfcSetRfFrequency(RfFrequency);
}

void Sx127x_HandleAFC(void)
{
    Sx127x_AfcDo();
}

//-- RF power interface

//void RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) = 0;

//-- helper
void Sx127x_config_calc(void)
{
    int8_t power_dbm = gconfig->Power_dbm;
    Sx127x_RfPowerCalc(power_dbm, &sx_power, &actual_power_dbm);
    uint8_t index = gconfig->LoraConfigIndex;
    if (index >= sizeof(Sx127xLoraConfiguration)/sizeof(Sx127xLoraConfiguration[0])) while (1) {} // must not happen
    lora_configuration = &(Sx127xLoraConfiguration[index]);
    symbol_time_us = calc_symbol_time_us(lora_configuration->SpreadingFactor, lora_configuration->Bandwidth);
}

// cumbersome to calculate in general, so use hardcoded for a specific settings
uint32_t TimeOverAir_us(void)
{
    if (lora_configuration == NULL) config_calc(); // ensure it is set
    return lora_configuration->TimeOverAir;
}

int16_t Sx127x_ReceiverSensitivity_dbm(void)
{
    if (lora_configuration == NULL) config_calc(); // ensure it is set
    return lora_configuration->ReceiverSensitivity;
}

int8_t Sx127x_RfPower_dbm(void)
{
    if (lora_configuration == NULL) config_calc(); // ensure it is set
    return actual_power_dbm;
}

uint32_t Sx127x_calc_symbol_time_us(uint8_t SpreadingFactor, uint8_t Bandwidth)
{
    uint32_t sf = (SpreadingFactor >> 4); // slightly dirty as it uses explicit knowledge
    uint32_t bw = 7800;
    switch (Bandwidth) 
	{
        case SX1276_LORA_BW_7p8: bw = 7800; break;
        case SX1276_LORA_BW_10p4: bw = 10400; break;
        case SX1276_LORA_BW_15p6: bw = 15600; break;
        case SX1276_LORA_BW_20p8: bw = 20800; break;
        case SX1276_LORA_BW_31p25: bw = 31250; break;
        case SX1276_LORA_BW_41p7: bw = 41700; break;
        case SX1276_LORA_BW_62p5: bw = 62500; break;
        case SX1276_LORA_BW_125: bw = 125000; break;
        case SX1276_LORA_BW_250: bw = 250000; break;
        case SX1276_LORA_BW_500: bw = 500000; break;
    };
    return ((1 << sf) * 1000000) / bw;
}

//-------------------------------------------------------
// Driver for SX1
//-------------------------------------------------------

// SX1276 doesn't has BUSY
#ifndef SX_RESET
  #error SX must have a RESET pin!
#endif

//-- interface to SPI peripheral
void Sx127x1_SpiSelect(void) 
{
    delay_ns(30); // datasheet says tnhigh = 20 ns, NSS high time between SPI accesses
    spi_select();
    delay_ns(40); // datasheet says tnsetup = 30 ns, NSS setup time, From NSS falling edge to SCK rising  edge
}

void Sx127x1_SpiDeselect(void) 
{
    delay_ns(100); // datasheet says tnhold = 100 ns, NSS hold time From SCK falling edge to NSS rising edge, normal mode
    spi_deselect();
    delay_ns(100); // well...
}

void Sx127x1_SpiTransferByte(uint8_t* byteout, uint8_t* bytein) 
{
    *bytein = spi_transmitchar(*byteout);
}

//-- RF power interface

void Sx127x1_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) 
{
#if defined DEVICE_HAS_I2C_DAC || defined DEVICE_HAS_INTERNAL_DAC_TWOCHANNELS
    rfpower_calc(power_dbm, sx_power, actual_power_dbm, &dac);
#else
    sx1276_rfpower_calc(power_dbm, sx_power, actual_power_dbm, POWER_GAIN_DBM, POWER_SX1276_MAX_DBM);
#endif
}

//-- init API functions
void Sx127x1_reset(void)
{
    gpio_low(SX_RESET);
    delay_ms(5); // datasheet says > 100 us
    gpio_high(SX_RESET);
    delay_ms(50); // datasheet says 5 ms
}

void Sx127x1_Init(void)
{
    Sx127x_Init();
    spi_init();
    sx_init_gpio();
    sx_dio_exti_isr_clearflag();
    sx_dio_init_exti_isroff();
    // no idea how long the SX1276 takes to boot up, so give it some good time
    delay_ms(300);
    Sx127x1_reset(); // this is super crucial ! was so for SX1280, is it also for the SX1276 ??
    // this is not nice, figure out where to place
#if defined DEVICE_HAS_I2C_DAC || defined DEVICE_HAS_INTERNAL_DAC_TWOCHANNELS
    dac.Init();
#endif
    Sx127x1_SetStandby(); // should be in STDBY after reset
    delay_us(1000); // is this needed ????
}

//-- high level API functions

void Sx127x1_StartUp(tSxGlobalConfig* global_config)
{
//XX        // this is not nice, figure out where to place
//XX#ifdef DEVICE_HAS_I2C_DAC
//XX        dac.Init();
//XX#endif

//XX        SetStandby(); // should be in STDBY after reset
//XX        delay_us(1000); // is this needed ????
    Sx127x1_Configure(global_config);
    delay_us(125); // may not be needed
    sx_dio_enable_exti_isr();
}

//-- this are the API functions used in the loop

void Sx127x1_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms = 0)
{
    sx_amp_transmit();
    Sx127x_SendFrame(data, len, tmo_ms);
    delay_us(125); // may not be needed if busy available
}

void Sx127x1_SetToRx(uint16_t tmo_ms = 0)
{
    sx_amp_receive();
    Sx127x_SetToRx(tmo_ms);
    delay_us(125); // may not be needed if busy available
}

//-------------------------------------------------------
// Driver for SX2
//-------------------------------------------------------
#ifdef DEVICE_HAS_DIVERSITY
  #error Diversity not yet supported for SX127x!
#endif

