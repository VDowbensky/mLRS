//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX128x Driver
//*******************************************************
#include "sx128x_driver.h"

//-------------------------------------------------------
// SX Driver
//-------------------------------------------------------

const tSxLoraConfiguration Sx128xLoraConfiguration[] = 
{
    { .SpreadingFactor = SX1280_LORA_SF5,
      .Bandwidth = SX1280_LORA_BW_800,
      .CodingRate = SX1280_LORA_CR_LI_4_5,
      .PreambleLength = 12,
      .HeaderType = SX1280_LORA_HEADER_DISABLE,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcEnabled = SX1280_LORA_CRC_DISABLE,
      .InvertIQ = SX1280_LORA_IQ_NORMAL,
      .TimeOverAir = 7892,
      .ReceiverSensitivity = -105,
    },
    { .SpreadingFactor = SX1280_LORA_SF6,
      .Bandwidth = SX1280_LORA_BW_800,
      .CodingRate = SX1280_LORA_CR_LI_4_5,
      .PreambleLength = 12,
      .HeaderType = SX1280_LORA_HEADER_DISABLE,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcEnabled = SX1280_LORA_CRC_DISABLE,
      .InvertIQ = SX1280_LORA_IQ_NORMAL,
      .TimeOverAir = 13418,
      .ReceiverSensitivity = -108,
    },
    { .SpreadingFactor = SX1280_LORA_SF7,
      .Bandwidth = SX1280_LORA_BW_800,
      .CodingRate = SX1280_LORA_CR_LI_4_5,
      .PreambleLength = 12,
      .HeaderType = SX1280_LORA_HEADER_DISABLE,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcEnabled = SX1280_LORA_CRC_DISABLE,
      .InvertIQ = SX1280_LORA_IQ_NORMAL,
      .TimeOverAir = 23527,
      .ReceiverSensitivity = -112,
    }
};

const tSxLoraConfiguration* lora_configuration;
const tSxFlrcConfiguration* flrc_configuration;
tSxGlobalConfig* gconfig;
uint8_t sx_power;
int8_t actual_power_dbm;


const tSxFlrcConfiguration Sx128xFlrcConfiguration[] = 
{
    { .Bandwidth = SX1280_FLRC_BR_0_650_BW_0_6,
      .CodingRate = SX1280_FLRC_CR_1_2,
      .Bt = SX1280_FLRC_BT_1,
      .AGCPreambleLength = SX1280_FLRC_PREAMBLE_LENGTH_32_BITS,
      .SyncWordLength = SX1280_FLRC_SYNCWORD_LEN_P32S,
      .SyncWordMatch = SX1280_FLRC_SYNCWORD_MATCH_1,
      .PacketType = SX1280_FLRC_PACKET_TYPE_FIXED_LENGTH,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcLength = SX1280_FLRC_CRC_DISABLE,
      .CrcSeed = 27368, // CrcSeed is 'j', 'p'. Not used.
      .TimeOverAir = 2383,
      .ReceiverSensitivity = -104,
    }
};


#ifdef POWER_USE_DEFAULT_RFPOWER_CALC
void sx1280_rfpower_calc(const int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm, const uint8_t GAIN_DBM, const uint8_t SX1280_MAX_DBM)
{
    int16_t power_sx = (int16_t)power_dbm - GAIN_DBM + 18;

    if (power_sx < SX1280_POWER_MIN) power_sx = SX1280_POWER_MIN;
    if (power_sx > SX1280_POWER_MAX) power_sx = SX1280_POWER_MAX;
    if (power_sx > SX1280_MAX_DBM) power_sx = SX1280_MAX_DBM;

    *sx_power = power_sx;
    *actual_power_dbm = power_sx + GAIN_DBM - 18;
}
#endif


void Sx128x_Init(void)
{
    lora_configuration = NULL;
    flrc_configuration = NULL;
}

//-- high level API functions
bool Sx128x_isOk(void)
{
    uint16_t firmwareRev = GetFirmwareRev();
    return ((firmwareRev != 0) && (firmwareRev != 65535));
}

void Sx128x_SetLoraConfiguration(const tSxLoraConfiguration* config)
{
    SetModulationParams(config->SpreadingFactor,
                        config->Bandwidth,
                        config->CodingRate);
    SetPacketParams(config->PreambleLength,
                    config->HeaderType,
                    config->PayloadLength,
                    config->CrcEnabled,
                    config->InvertIQ);
}

void Sx128x_SetLoraConfigurationByIndex(uint8_t index)
{
    if (index >= sizeof(Sx128xLoraConfiguration)/sizeof(Sx128xLoraConfiguration[0])) while (1) {} // must not happen
    lora_configuration = &(Sx128xLoraConfiguration[index]);
    Sx128x_SetLoraConfiguration(lora_configuration);
}

void Sx128x_ResetToLoraConfiguration(void)
{
    Sx128x_SetStandby(SX1280_STDBY_CONFIG_STDBY_RC);
    delay_us(1000); // seems ok without, but do it
    Sx128x_SetPacketType(SX1280_PACKET_TYPE_LORA);
    Sx128x_SetLoraConfigurationByIndex(gconfig->LoraConfigIndex);
}

void Sx128x_SetFlrcConfiguration(const tSxFlrcConfiguration* config, uint32_t sync_word)
{
    Sx128x_SetModulationParamsFLRC(config->Bandwidth,
                            config->CodingRate,
                            config->Bt);

    Sx128x_SetPacketParamsFLRC(config->AGCPreambleLength,
                        config->SyncWordLength,
                        config->SyncWordMatch,
                        config->PacketType,
                        config->PayloadLength,
                        config->CrcLength,
                        config->CrcSeed);

    Sx128x_SetSyncWordFLRC(sync_word, config->CodingRate);
}

void Sx128x_SetFlrcConfigurationByIndex(uint8_t index, uint32_t sync_word)
{
    if (index >= sizeof(Sx128xFlrcConfiguration)/sizeof(Sx128xFlrcConfiguration[0])) while (1) {} // must not happen
    flrc_configuration = &(Sx128xFlrcConfiguration[index]);
    Sx128x_SetFlrcConfiguration(flrc_configuration, sync_word);
}

void Sx128x_SetRfPower_dbm(int8_t power_dbm)
{
    RfPowerCalc(power_dbm, &sx_power, &actual_power_dbm);
    SetTxParams(sx_power, SX1280_RAMPTIME_04_US);
}

void Sx128x_Configure(tSxGlobalConfig* global_config)
{
    gconfig = global_config;
    if (gconfig->modeIsLora()) 
	{
        Sx128x_SetPacketType(SX1280_PACKET_TYPE_LORA);
        Sx128x_SetAutoFs(true);
        Sx128x_SetLnaGainMode(SX1280_LNAGAIN_MODE_HIGH_SENSITIVITY);
        Sx128x_SetRfPower_dbm(gconfig->Power_dbm);
        Sx128x_SetLoraConfigurationByIndex(gconfig->LoraConfigIndex);
#ifdef LORA_SYNCWORD
        Sx128x_SetSyncWord(LORA_SYNCWORD);
#endif
        } 
		else
		{
            Sx128x_SetPacketType(SX1280_PACKET_TYPE_FLRC);
            Sx128x_SetAutoFs(true);
            Sx128x_SetLnaGainMode(SX1280_LNAGAIN_MODE_HIGH_SENSITIVITY);
            Sx128x_SetRfPower_dbm(gconfig->Power_dbm);
            Sx128x_SetFlrcConfigurationByIndex(0, gconfig->FlrcSyncWord);
        }
        Sx128x_SetBufferBaseAddress(0, 0);
        Sx128x_SetDioIrqParams(SX1280_IRQ_ALL,
                    SX1280_IRQ_RX_DONE | SX1280_IRQ_TX_DONE | SX1280_IRQ_RX_TX_TIMEOUT,
                    SX1280_IRQ_NONE,SX1280_IRQ_NONE);
        Sx128x_ClearIrqStatus(SX1280_IRQ_ALL);
    Sx128x_SetFs();
}

//-- this are the API functions used in the loop
void Sx128x_ReadFrame(uint8_t* data, uint8_t len)
{
    uint8_t rxStartBufferPointer;
    uint8_t rxPayloadLength;
    // rxPayloadLength is always 0 if no header
    Sx128x_GetRxBufferStatus(&rxPayloadLength, &rxStartBufferPointer);
    // if one wants it, it could be obtained from what had been set
    // rxPayloadLength = ReadRegister(SX1280_REG_PayloadLength);
    Sx128x_ReadBuffer(rxStartBufferPointer, data, len);
}

void Sx128x_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms)
{
    WriteBuffer(0, data, len);
    Sx128x_ClearIrqStatus(SX1280_IRQ_ALL);
    Sx128x_SetTx(SX1280_PERIODBASE_62p5_US, tmo_ms*16); // 0 = no timeout, if a Tx timeout occurs we have a serious problem
}

void Sx128x_SetToRx(uint16_t tmo_ms)
{
    Sx128x_ClearIrqStatus(SX1280_IRQ_ALL);
    Sx128x_SetRx(SX1280_PERIODBASE_62p5_US, tmo_ms*16); // 0 = no timeout
}

void Sx128x_SetToIdle(void)
{
    Sx128x_SetFs();
    Sx128x_ClearIrqStatus(SX1280_IRQ_ALL);
}

void Sx128x_GetPacketStatus(int8_t* RssiSync, int8_t* Snr)
{
    int16_t rssi;
    if (gconfig->modeIsLora()) 
	{
        Sx128x_GetPacketStatus(&rssi, Snr);
    } 
	else 
	{
        // FLRC has no SNR
        Sx128x_GetPacketStatusFLRC(&rssi);
        *Snr = 0;
    }
    if (rssi > -1) rssi = -1; // we do not support values larger than this
    if (rssi < -127) rssi = -127; // we do not support values lower than this
    *RssiSync = rssi;
}

void Sx128x_HandleAFC(void) 
{
	
}

//-- RF power interface
//void RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) = 0;
//-- helper
void Sx128x_config_calc(void)
{
    int8_t power_dbm = gconfig->Power_dbm;
    Sx128x_RfPowerCalc(power_dbm, &sx_power, &actual_power_dbm);
    if (gconfig->modeIsLora()) 
	{
        uint8_t index = gconfig->LoraConfigIndex;
        if (index >= sizeof(Sx128xLoraConfiguration)/sizeof(Sx128xLoraConfiguration[0])) while (1) {} // must not happen
        lora_configuration = &(Sx128xLoraConfiguration[index]);
    } else 
	{
        flrc_configuration = &(Sx128xFlrcConfiguration[0]);
    }
}

// cumbersome to calculate in general, so use hardcoded for a specific settings
uint32_t Sx128x_TimeOverAir_us(void)
{
    if (lora_configuration == NULL && flrc_configuration == NULL) config_calc(); // ensure it is set
    return (gconfig->modeIsLora()) ? lora_configuration->TimeOverAir : flrc_configuration->TimeOverAir;
}

int16_t Sx128x_ReceiverSensitivity_dbm(void)
{
    if (lora_configuration == NULL && flrc_configuration == NULL) config_calc(); // ensure it is set
    return (gconfig->modeIsLora()) ? lora_configuration->ReceiverSensitivity : flrc_configuration->ReceiverSensitivity;
}

int8_t Sx128x_RfPower_dbm(void)
{
    if (lora_configuration == NULL && flrc_configuration == NULL) config_calc(); // ensure it is set
    return actual_power_dbm;
}

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
void Sx128x1_WaitOnBusy(void)
{
    while (sx_busy_read()) __NOP();
}

void Sx128x1_SpiSelect(void)
{
    spi_select();
    delay_ns(50); // datasheet says t1 = 25 ns, semtech driver doesn't do it, helps so do it
}

void Sx128x1_SpiDeselect(void) 
{
    delay_ns(50); // datasheet says t8 = 25 ns, semtech driver doesn't do it, helps so do it
    spi_deselect();
}

void Sx128x1_SpiTransferByte(uint8_t* byteout, uint8_t* bytein) 
{
    *bytein = spi_transmitchar(*byteout);
}

//-- RF power interface
void Sx128x1_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) 
{
    sx1280_rfpower_calc(power_dbm, sx_power, actual_power_dbm, POWER_GAIN_DBM, POWER_SX1280_MAX_DBM);
}

//-- init API functions
void Sx128x1_reset(void)
{
    gpio_low(SX_RESET);
    delay_ms(5); // 10 us seems to be sufficient, play it safe, semtech driver uses 50 ms
    gpio_high(SX_RESET);
    delay_ms(50); // semtech driver says "typically 2ms observed"
    Sx128x1_WaitOnBusy();
}

void Sx128x1_Init(void)
{
    Sx128x_Init();
    spi_init();
    sx_init_gpio();
    sx_dio_exti_isr_clearflag();
    sx_dio_init_exti_isroff();
    // no idea how long the SX1280 takes to boot up, so give it some good time
    // we could probably speed up by using WaitOnBusy()
    delay_ms(300);
    Sx128x1_reset(); // this is super crucial !
    Sx128x1_SetStandby(SX1280_STDBY_CONFIG_STDBY_RC); // should be in STDBY_RC after reset
    delay_us(1000); // this is important, 500 us ok
}

//-- high level API functions
void Sx128x1_StartUp(tSxGlobalConfig* global_config)
{
#ifdef SX_USE_DCDC // here ??? ELRS does it as last !!!
    Sx128x1_SetRegulatorMode(SX1280_REGULATOR_MODE_DCDC);
#endif
    Sx128x1_Configure(global_config);
    delay_us(125); // may not be needed if busy available
    sx_dio_enable_exti_isr();
}

//-- this are the API functions used in the loop
void Sx128x1_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms = 0)
{
    sx_amp_transmit();
    Sx128x_SendFrame(data, len, tmo_ms);
    delay_us(125); // may not be needed if busy available
}

void Sx128x1_SetToRx(uint16_t tmo_ms = 0)
{
    sx_amp_receive();
    Sx128x_SetToRx(tmo_ms);
    delay_us(125); // may not be needed if busy available
}

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

void Sx128x2_WaitOnBusy(void) 
{
    while (sx2_busy_read()) __NOP();
}

void Sx128x2SpiSelect(void) 
{
    spib_select();
    delay_ns(50); // datasheet says t1 = 25 ns, semtech driver doesn't do it, helps so do it
}

void Sx128x2SpiDeselect(void) 
{
    delay_ns(50); // datasheet says t8 = 25 ns, semtech driver doesn't do it, helps so do it
    spib_deselect();
}

void Sx128x2SpiTransferByte(uint8_t* byteout, uint8_t* bytein) 
{
    *bytein = spib_transmitchar(*byteout);
}

//-- RF power interface

void Sx128x2RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) 
{
#ifdef DEVICE_HAS_DUAL_SX126x_SX128x
    sx1280_rfpower_calc(power_dbm, sx_power, actual_power_dbm, POWER2_GAIN_DBM, POWER2_SX1280_MAX_DBM);
#else
    sx1280_rfpower_calc(power_dbm, sx_power, actual_power_dbm, POWER_GAIN_DBM, POWER_SX1280_MAX_DBM);
#endif
}

//-- init API functions
void Sx128x2reset(void)
{
    gpio_low(SX2_RESET);
    delay_ms(5); // 10 us seems to be sufficient, play it safe, semtech driver uses 50 ms
    gpio_high(SX2_RESET);
    delay_ms(50); // semtech driver says "typically 2ms observed"
    WaitOnBusy();
}

void Sx128x2Init(void)
{
    Sx128x_Init();
    spib_init();
    sx2_init_gpio();
    sx2_dio_exti_isr_clearflag();
    sx2_dio_init_exti_isroff();
    // no idea how long the SX1280 takes to boot up, so give it some good time
    // we could probably speed up by using WaitOnBusy()
    delay_ms(300);
    Sx128x2reset(); // this is super crucial !
    Sx128x2SetStandby(SX1280_STDBY_CONFIG_STDBY_RC); // should be in STDBY_RC after reset
    delay_us(1000); // this is important, 500 us ok
}

//-- high level API functions
void Sx128x2StartUp(tSxGlobalConfig* global_config)
{
//XX        SetStandby(SX1280_STDBY_CONFIG_STDBY_RC); // should be in STDBY_RC after reset
//XX        delay_us(1000); // this is important, 500 us ok
#ifdef SX2_USE_DCDC // here ??? ELRS does it as last !!!
    Sx128x2SetRegulatorMode(SX1280_REGULATOR_MODE_DCDC);
#endif
    Sx128x2Configure(global_config);
    delay_us(125); // may not be needed if busy available
    sx2_dio_enable_exti_isr();
}

//-- this are the API functions used in the loop
void Sx128x2SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms = 0)
{
    sx2_amp_transmit();
    Sx128x_SendFrame(data, len, tmo_ms);
    delay_us(125); // may not be needed if busy available
}

void Sx128x2SetToRx(uint16_t tmo_ms = 0)
{
    sx2_amp_receive();
    Sx128x2Sx128xDriverCommon::SetToRx(tmo_ms);
    delay_us(125); // may not be needed if busy available
}
#endif

#endif // SX128X_DRIVER_H
