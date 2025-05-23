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
#include "sx126x_driver.h"


//-------------------------------------------------------
// SX Driver
//-------------------------------------------------------


const tSxLoraConfiguration Sx126xLoraConfiguration[] = 
{
    { .SpreadingFactor = SX126X_LORA_SF5,
      .Bandwidth = SX126X_LORA_BW_500,
      .CodingRate = SX126X_LORA_CR_4_5,
      .PreambleLength = 12,
      .HeaderType = SX126X_LORA_HEADER_DISABLE,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcEnabled = SX126X_LORA_CRC_DISABLE,
      .InvertIQ = SX126X_LORA_IQ_NORMAL,
      .TimeOverAir = 13200,
      .ReceiverSensitivity = -111,
    },
    { .SpreadingFactor = SX126X_LORA_SF6,
      .Bandwidth = SX126X_LORA_BW_500,
      .CodingRate = SX126X_LORA_CR_4_5,
      .PreambleLength = 12,
      .HeaderType = SX126X_LORA_HEADER_DISABLE,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CrcEnabled = SX126X_LORA_CRC_DISABLE,
      .InvertIQ = SX126X_LORA_IQ_NORMAL,
      .TimeOverAir = 22560,
      .ReceiverSensitivity = -112, // Q: SF5 with CR4/8 would be -111 dBm, 20.1 ms, better option??
    }
};


const tSxGfskConfiguration Sx126xGfskConfiguration[] = 
{
    { .br_bps = 100000,
      .PulseShape = SX126X_GFSK_PULSESHAPE_BT_1,
      .Bandwidth = SX126X_GFSK_BW_312000,
      .Fdev_hz = 50000,
      .PreambleLength = 16,
      .PreambleDetectorLength = SX126X_GFSK_PREAMBLE_DETECTOR_LENGTH_8BITS,
      .SyncWordLength = 16,
      .AddrComp = SX126X_GFSK_ADDRESS_FILTERING_DISABLE,
      .PacketType = SX126X_GFSK_PKT_FIX_LEN,
      .PayloadLength = FRAME_TX_RX_LEN,
      .CRCType = SX126X_GFSK_CRC_OFF,
      .Whitening = SX126X_GFSK_WHITENING_ENABLE,
      .TimeOverAir = 7600,
      .ReceiverSensitivity = -106  // This is a guess, data sheet is vague here
    }
};


//protected:
uint8_t osc_configuration; // "hidden" variable, TXCO 1.8 V per default, allow child access

//private:
const tSxLoraConfiguration* lora_configuration;
const tSxGfskConfiguration* gfsk_configuration;
tSxGlobalConfig* gconfig;
uint8_t sx_power;
int8_t actual_power_dbm;

#ifdef POWER_USE_DEFAULT_RFPOWER_CALC
void sx126x_rfpower_calc(const int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm, const uint8_t GAIN_DBM, const uint8_t SX126X_MAX_DBM)
{
    int16_t power_sx = (int16_t)power_dbm - GAIN_DBM;

    if (power_sx < SX126X_POWER_MIN) power_sx = SX126X_POWER_MIN;
    if (power_sx > SX126X_POWER_MAX) power_sx = SX126X_POWER_MAX;
    if (power_sx > SX126X_MAX_DBM) power_sx = SX126X_MAX_DBM;
    *sx_power = power_sx;
    *actual_power_dbm = power_sx + GAIN_DBM;
}
#endif

void Sx126x_Init(void)
{
    osc_configuration = SX12xx_OSCILLATOR_CONFIG_TXCO_1P8_V;
    lora_configuration = NULL;
    gfsk_configuration = NULL;
}

//-- high level API functions
bool Sx126x_isOk(void)
{
    uint16_t firmwareRev = Sx126x_GetFirmwareRev();
    return ((firmwareRev != 0) && (firmwareRev != 65535));
}

void Sx126x_SetLoraConfiguration(const tSxLoraConfiguration* config)
{
    Sx126x_SetModulationParams(config->SpreadingFactor,config->Bandwidth,config->CodingRate);
    Sx126x_SetPacketParams(config->PreambleLength,config->HeaderType,config->PayloadLength,config->CrcEnabled,config->InvertIQ);
    // set LoRaSymbNumTimeout for false detection of preamble
    // must come in this order, datasheet 14.5 Issuing Commands in the Right Order, p.103
    Sx126x_SetSymbNumTimeout((config->PreambleLength * 3) >> 2);
}

void Sx126x_SetLoraConfigurationByIndex(uint8_t index)
{
    if (index >= sizeof(Sx126xLoraConfiguration)/sizeof(Sx126xLoraConfiguration[0])) while (1) {} // must not happen

    lora_configuration = &(Sx126xLoraConfiguration[index]);
    Sx126x_SetLoraConfiguration(lora_configuration);
}

void Sx126x_ResetToLoraConfiguration(void)
{
    Sx126x_SetLoraConfigurationByIndex(gconfig->LoraConfigIndex);
}

void Sx126x_SetGfskConfiguration(const tSxGfskConfiguration* config, uint16_t sync_word)
{
    Sx126x_SetModulationParamsGFSK(config->br_bps,
                                config->PulseShape,
                                config->Bandwidth,
                                config->Fdev_hz);

    Sx126x_SetPacketParamsGFSK(config->PreambleLength,
                            config->PreambleDetectorLength,
                            config->SyncWordLength,
                            config->AddrComp,
                            config->PacketType,
                            config->PayloadLength,
                            config->CRCType,
                            config->Whitening);

    Sx126x_SetSyncWordGFSK(sync_word);
}

void Sx126x_SetGfskConfigurationByIndex(uint8_t index, uint16_t sync_word)
{
    if (index >= sizeof(Sx126xGfskConfiguration)/sizeof(Sx126xGfskConfiguration[0])) while (1) {} // must not happen
    gfsk_configuration = &(Sx126xGfskConfiguration[index]);
    Sx126x_SetGfskConfiguration(gfsk_configuration, sync_word);
}

void Sx126x_SetRfPower_dbm(int8_t power_dbm)
{
    Sx126x_RfPowerCalc(power_dbm, &sx_power, &actual_power_dbm);
    Sx126x_SetTxParams(sx_power, SX126X_RAMPTIME_10_US);
}

void Sx126x_Configure(tSxGlobalConfig* global_config)
{
    gconfig = global_config;
    if (gconfig->modeIsLora()) Sx126x_SetPacketType(SX126X_PACKET_TYPE_LORA);
	else Sx126x_SetPacketType(SX126X_PACKET_TYPE_GFSK);
    // WORKAROUND: Better Resistance of the SX1262 Tx to Antenna Mismatch,
    // fixes overly eager PA clamping
    // see SX1262/SX1268 datasheet, chapter 15 Known Limitations, section 15.2 for details
    uint8_t data = ReadRegister(SX126X_REG_TX_CLAMP_CONFIG); //??? this for 126x only!!!
    data |= 0x1E;
    WriteRegister(SX126X_REG_TX_CLAMP_CONFIG, data);
    Sx126x_ClearDeviceError(); // XOSC_START_ERR is raised, datasheet 13.3.6 SetDIO3AsTCXOCtrl, p.84
    // set DIO3 as TCXO control
    if (osc_configuration != SX12xx_OSCILLATOR_CONFIG_CRYSTAL) 
	{
        Sx126x_SetDio3AsTcxoControl(osc_configuration, 250); // set output to 1.6V-3.3V, ask specification of TCXO to maker board
    }
    // Image calibration per datasheet 9.2.1
    // default for SX1261/2 (E22/E77-900) is 902 to 928 MHz
    // default for SX1268 (E22/E77-400) is 470 to 510 MHz
    switch (gconfig->FrequencyBand) //this must be rewrited for all possible freq. from ~70 to ~1300 MHz!
	{
        case SETUP_FREQUENCY_BAND_915_MHZ_FCC: 
		Sx126x_CalibrateImage(SX126X_CAL_IMG_902_MHZ_1, SX126X_CAL_IMG_902_MHZ_2); 
		break;
			
        case SETUP_FREQUENCY_BAND_868_MHZ: 
		Sx126x_CalibrateImage(SX126X_CAL_IMG_863_MHZ_1, SX126X_CAL_IMG_863_MHZ_2); 
		break;
			
        case SETUP_FREQUENCY_BAND_866_MHZ_IN: 
		Sx126x_CalibrateImage(SX126X_CAL_IMG_863_MHZ_1,CX126X_CAL_IMG_863_MHZ_2); 
		break;
			
        case SETUP_FREQUENCY_BAND_433_MHZ: 
		Sx126x_CalibrateImage(SX126X_CAL_IMG_430_MHZ_1, SX126X_CAL_IMG_430_MHZ_2); 
		break;
			
        case SETUP_FREQUENCY_BAND_70_CM_HAM: 
		Sx126x_CalibrateImage(SX126X_CAL_IMG_430_MHZ_1, SX126X_CAL_IMG_430_MHZ_2); 
		break;
			
        default:
		break;
           //while (1) {}  // protection
    }
    // set DIO2 as RF control switching
    // check the RF module if antenna switching is internally connected to DIO2
    // E22-900M rf switching controlled by IO pin of MCU
    // SetDio2AsRfSwitchControl(SX126X_DIO2_AS_RF_SWITCH);
    Sx126x_SetAutoFs(true); // SetRxTxFallbackMode to FS
    Sx126x_SetRxGain(SX126X_RX_GAIN_BOOSTED_GAIN);
    Sx126x_SetOverCurrentProtection(SX126X_OCP_CONFIGURATION_140_MA); // default for SX1262 according to data sheet, but can't hurt
    Sx126x_SetPaConfig_22dbm();
    //SetTxParams(calc_sx_power(Config.Power), SX126X_RAMPTIME_10_US);
    Sx126x_SetRfPower_dbm(gconfig->Power_dbm);
    if (gconfig->modeIsLora()) Sx126x_SetLoraConfigurationByIndex(gconfig->LoraConfigIndex);
	else Sx126x_SetGfskConfigurationByIndex(0, Config.FrameSyncWord);
    Sx126x_SetBufferBaseAddress(0, 0);
    Sx126x_SetDioIrqParams(SX126X_IRQ_ALL,
                        SX126X_IRQ_RX_DONE|SX126X_IRQ_TX_DONE|SX126X_IRQ_RX_TX_TIMEOUT,
                        SX126X_IRQ_NONE,
                        SX126X_IRQ_NONE);
    Sx126x_ClearIrqStatus(SX126X_IRQ_ALL);
    Sx126x_SetFs();
}

    //-- this are the API functions used in the loop
void Sx126x_ReadFrame(uint8_t* data, uint8_t len)
{
    uint8_t rxStartBufferPointer;
    uint8_t rxPayloadLength;

    Sx126x_GetRxBufferStatus(&rxPayloadLength, &rxStartBufferPointer);
    Sx126x_ReadBuffer(rxStartBufferPointer, data, len);
}

void Sx126x_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms)
{
    Sx126x_WriteBuffer(0, data, len);
    Sx126x_ClearIrqStatus(SX126X_IRQ_ALL);
    Sx126x_SetTx(tmo_ms * 64); // 0 = no timeout. TimeOut period inn ms. sx1262 have static 15p625 period base, so for 1 ms needs 64 tmo value
}

void Sx126x_SetToRx(uint16_t tmo_ms)
{
    Sx126x_ClearIrqStatus(SX126X_IRQ_ALL);
    Sx126x_SetRx(tmo_ms * 64); // 0 = no timeout
}

void Sx126x_SetToIdle(void)
{
    Sx126x_SetFs();
    Sx126x_ClearIrqStatus(SX126X_IRQ_ALL);
}

void Sx126x_GetPacketStatus(int8_t* RssiSync, int8_t* Snr)
{
    int16_t rssi;
    if (gconfig->modeIsLora()) Sx126x_GetPacketStatus(&rssi, Snr);
	else 
	{
     	Sx126x_GetPacketStatusGFSK(&rssi);
       	*Snr = 0;
    }
    if (rssi > -1) rssi = -1; // we do not support values larger than this
    if (rssi < -127) rssi = -127; // we do not support values lower than this
    *RssiSync = rssi;
}

void Sx126x_HandleAFC(void) 
{
	
}

//-- RF power interface

//void Sx126x_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) = 0;

    //-- helper

void Sx126x_config_calc(void)
{
    int8_t power_dbm = gconfig->Power_dbm;
    RfPowerCalc(power_dbm, &sx_power, &actual_power_dbm);
    if (gconfig->modeIsLora()) 
	{
		uint8_t index = gconfig->LoraConfigIndex;
        if (index >= sizeof(Sx126xLoraConfiguration)/sizeof(Sx126xLoraConfiguration[0])) while (1) {} // must not happen
        lora_configuration = &(Sx126xLoraConfiguration[index]);
    } 
	else gfsk_configuration = &(Sx126xGfskConfiguration[0]);
}

// cumbersome to calculate in general, so use hardcoded for a specific settings
uint32_t Sx126x_TimeOverAir_us(void)
{
    if (lora_configuration == NULL && gfsk_configuration == NULL) config_calc(); // ensure it is set
    return (gconfig->modeIsLora()) ? lora_configuration->TimeOverAir : gfsk_configuration->TimeOverAir;
}

int16_t Sx126x_ReceiverSensitivity_dbm(void)
{
    if (lora_configuration == NULL && gfsk_configuration == NULL) Sx126x_config_calc(); // ensure it is set
    return (gconfig->modeIsLora()) ? lora_configuration->ReceiverSensitivity : gfsk_configuration->ReceiverSensitivity;
}

int8_t Sx126x_RfPower_dbm(void)
{
    if (lora_configuration == NULL && gfsk_configuration == NULL) config_calc(); // ensure it is set
    return actual_power_dbm;
}


//-------------------------------------------------------
// Driver for SX1
//-------------------------------------------------------

#ifndef SX_BUSY
  #error SX must have a BUSY pin!
#endif
#if !defined SX_RESET && !defined SX_HAS_NO_RESET
  #error SX must have a RESET pin!
#endif

//public:

void Sx126x1_WaitOnBusy(void)
{
    while (sx_busy_read()) __NOP();
}

void Sx126x1_SpiSelect(void) 
{
    spi_select();
    delay_ns(50); // datasheet says t6 = 15 ns, NSS falling to MISO delay, t1 = 32 ns, NSS falling edge to SCK setup time
}

void Sx126x1_SpiDeselect(void) 
{
    delay_ns(50); // datasheet says t8 = 31.25 ns, SCK to NSS rising edge hold time
    spi_deselect();
}

void Sx126x1_SpiTransferByte(uint8_t* byteout, uint8_t* bytein)
{
    *bytein = spi_transmitchar(*byteout);
}

//-- RF power interface
void Sx126x1_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm)
{
    Sx126x_rfpower_calc(power_dbm, sx_power, actual_power_dbm, POWER_GAIN_DBM, POWER_SX126X_MAX_DBM);
}

//-- init API functions
void Sx126x1_reset(void)
{
#ifndef SX_HAS_NO_RESET
    gpio_low(SX_RESET);
    delay_ms(5); // datasheet says > 100 us
    gpio_high(SX_RESET);
    delay_ms(50);
    WaitOnBusy();
#endif
}

void Sx126x1_Init(void)
{
    Sx126x_Init(); //!!!
#ifdef SX_USE_CRYSTALOSCILLATOR
    osc_configuration = SX12xx_OSCILLATOR_CONFIG_CRYSTAL;
#endif
    spi_init();
    sx_init_gpio();
    sx_dio_exti_isr_clearflag();
    sx_dio_init_exti_isroff();
    // no idea how long the SX126x takes to boot up, so give it some good time
    // we could probably speed up by using WaitOnBusy()
    delay_ms(300);
    Sx126x1_reset(); // this is super crucial ! was so for SX1280, is it also for the SX1262 ??
    Sx126x_SetStandby(SX126X_STDBY_CONFIG_STDBY_RC); // should be in STDBY_RC after reset
    delay_us(1000); // is this needed ???? No!
}

//-- high level API functions
void Sx126x1_StartUp(tSxGlobalConfig* global_config)
{
#ifdef SX_USE_DCDC // here ??? ELRS does it as last !!!
    Sx126x_SetRegulatorMode(SX126X_REGULATOR_MODE_DCDC);
#endif
    Sx126x_Configure(global_config);
    delay_us(125); // may not be needed if busy available
    sx_dio_enable_exti_isr();
}

//-- this are the API functions used in the loop
void Sx126x1_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms = 0)
{
    sx_amp_transmit();
    Sx126x_SendFrame(data, len, tmo_ms);
    delay_us(125); // may not be needed if busy available
}

void Sx126x1_SetToRx(uint16_t tmo_ms = 0)
{
    sx_amp_receive();
    Sx126x_SetToRx(tmo_ms);
    delay_us(125); // may not be needed if busy available
}

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


void Sx126x2_WaitOnBusy(void) 
{
    while (sx2_busy_read()) { __NOP(); };
}

void Sx126x2_SpiSelect(void) 
{
    spib_select();
    delay_ns(50); // datasheet says t6 = 15 ns, NSS falling to MISO delay, t1 = 32 ns, NSS falling edge to SCK setup time
}

void Sx126x2_SpiDeselect(void) 
{
    delay_ns(50); // datasheet says t8 = 31.25 ns, SCK to NSS rising edge hold time
    spib_deselect();
}

void Sx126x2_SpiTransferByte(uint8_t* byteout, uint8_t* bytein) 
{
    *bytein = spib_transmitchar(*byteout);
}

//-- RF power interface
void Sx126x2_RfPowerCalc(int8_t power_dbm, uint8_t* sx_power, int8_t* actual_power_dbm) 
{
    sx126x_rfpower_calc(power_dbm, sx_power, actual_power_dbm, POWER_GAIN_DBM, POWER_SX126X_MAX_DBM);
}

//-- init API functions
void Sx126x2_reset(void)
{
    gpio_low(SX2_RESET);
    delay_ms(5); // datasheet says > 100 us
    gpio_high(SX2_RESET);
    delay_ms(50);
    WaitOnBusy();
}

void Sx126x2_Init(void)
{
    Sx126x_Init();
#ifdef SX2_USE_CRYSTALOSCILLATOR
    osc_configuration = SX12xx_OSCILLATOR_CONFIG_CRYSTAL;
#endif
    spib_init();
    sx2_init_gpio();
    sx2_dio_init_exti_isroff();
    sx2_dio_exti_isr_clearflag();
    // no idea how long the SX126x takes to boot up, so give it some good time
    // we could probably speed up by using WaitOnBusy()
    delay_ms(300);
    Sx126x2_reset(); // this is super crucial ! was so for SX1280, is it also for the SX1262 ??
    Sx126x2_SetStandby(SX126X_STDBY_CONFIG_STDBY_RC); // should be in STDBY_RC after reset
    delay_us(1000); // is this needed ????
}

//-- high level API functions
void Sx126x2_StartUp(tSxGlobalConfig* global_config)
{
#ifdef SX2_USE_DCDC // here ??? ELRS does it as last !!!
    Sx126x2_SetRegulatorMode(SX126X_REGULATOR_MODE_DCDC);
#endif
    Sx126x2_Configure(global_config);
    Sx126x2_delay_us(125); // may not be needed if busy available
    sx2_dio_enable_exti_isr();
}

//-- this are the API functions used in the loop
void Sx126x2_SendFrame(uint8_t* data, uint8_t len, uint16_t tmo_ms = 0)
{
    sx2_amp_transmit();
    Sx126x_SendFrame(data, len, tmo_ms);
    delay_us(125); // may not be needed if busy available
}

void Sx126x2_SetToRx(uint16_t tmo_ms = 0)
{
    sx2_amp_receive();
    Sx126x2_SetToRx(tmo_ms);
    delay_us(125); // may not be needed if busy available
}
#endif

