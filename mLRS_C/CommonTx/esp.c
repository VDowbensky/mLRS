//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// EPS Wifi Bridge Interface Header
//********************************************************
#iclude "esp.h"


//-------------------------------------------------------
// ESP Helper
//-------------------------------------------------------

void esp_enable(uint8_t serial_destination)
{
#ifdef USE_ESP_WIFI_BRIDGE_RST_GPIO0
  #ifdef DEVICE_HAS_ESP_WIFI_BRIDGE_ON_SERIAL
    if (serial_destination == SERIAL_DESTINATION_SERIAL) 
	{  // enable/disable ESP on serial
  #endif
  #ifdef DEVICE_HAS_ESP_WIFI_BRIDGE_ON_SERIAL2
    if (serial_destination == SERIAL_DESTINATION_SERIAL2) 
	{  // enable/disable ESP on serial2
  #endif
        esp_gpio0_high(); esp_reset_high();
    } 
	else 
	{
        esp_reset_low();
    }
#endif
}

#ifdef USE_ESP_WIFI_BRIDGE

//private:
void tTxEspWifiBridge_passthrough_do_rts_cts(void);
void tTxEspWifiBridge_passthrough_do(void);

tSerialBase* com;
tSerialBase* ser;

bool initialized;
uint8_t task;

bool passthrough_is_running;
uint8_t dtr_rts_last;



void tTxEspWifiBridge_Init(tSerialBase* _comport, tSerialBase* _serialport)
{
    com = _comport;
    ser = _serialport;
    initialized = (com != nullptr && ser != nullptr) ? true : false;
    task = ESP_TASK_NONE;
    passthrough_is_running = false;
    dtr_rts_last = 0;
}

uint8_t tTxEspWifiBridge_Task(void)
{
    return task;
}

void tTxEspWifiBridge_Do(void)
{
#if defined USE_ESP_WIFI_BRIDGE_RST_GPIO0 && defined USE_ESP_WIFI_BRIDGE_DTR_RTS
    if (!initialized) return;
    uint8_t dtr_rts = esp_dtr_rts();

    if ((dtr_rts_last == 3) && !(dtr_rts & 0x02)) 
	{
        //dbg.puts("\npst");
        passthrough_do_rts_cts();
        task = ESP_TASK_RESTART_CONTROLLER;
        //dbg.puts("\nend");delay_ms(500);
    }
    dtr_rts_last = dtr_rts;
#endif
}

void tTxEspWifiBridge_passthrough_do_rts_cts(void)
{
#if defined USE_ESP_WIFI_BRIDGE_RST_GPIO0 && defined USE_ESP_WIFI_BRIDGE_DTR_RTS
    if (!initialized) return;
    uint32_t serial_tlast_ms = millis32();

    disp.DrawNotify("ESP\nFLASHING");
    ser->SetBaudRate(115200);
    leds.InitPassthrough();

    while (1) 
	{

        if (doSysTask) 
		{
            doSysTask = 0;
            leds.TickPassthrough_ms();
        }
        uint8_t dtr_rts = esp_dtr_rts();

        if (dtr_rts != dtr_rts_last) 
		{
            if (dtr_rts & 0x02) esp_reset_high(); 
			else esp_reset_low();
            if (dtr_rts & 0x01) esp_gpio0_high();
			else esp_gpio0_low();
            //dbg.puts("\ndtr,rts ="); dbg.putc(dtr_rts + '0');
        }
        dtr_rts_last = dtr_rts;
        uint32_t tnow_ms = millis32();

        if (com->available()) 
		{
            char c = com->getc();
            ser->putc(c);
            serial_tlast_ms = tnow_ms;
        }
        if (ser->available()) 
		{
            char c = ser->getc();
            com->putc(c);
        }
        if (tnow_ms - serial_tlast_ms > ESP_PASSTHROUGH_TMO_MS) 
		{
            passthrough_is_running = false;
            esp_reset_low();
            delay_ms(100);
            esp_reset_high();
            disp.DrawNotify("");
            return;
        }
    }
#endif // USE_ESP_WIFI_BRIDGE_RST_GPIO0 && USE_ESP_WIFI_BRIDGE_DTR_RTS
}

// enter esp flashing, can only be exited by re-powering
void tTxEspWifiBridge_EnterFlash(void)
{
    if (!initialized) return;
    disp.DrawNotify("FLASH ESP");
#ifdef USE_ESP_WIFI_BRIDGE_RST_GPIO0
    esp_reset_low();
    esp_gpio0_low();
    delay_ms(100);
    esp_reset_high();
    delay_ms(100);
    esp_gpio0_high();
    delay_ms(100);
#endif
    passthrough_do();
}

// enter esp passthrough, can only be exited by re-powering
void tTxEspWifiBridge_EnterPassthrough(void)
{
    if (!initialized) return;
    passthrough_do();
}

// enter esp cli, can only be exited by re-powering
void tTxEspWifiBridge_EnterCli(void)
{
    if (!initialized) return;
    // set GPIO0 to low, but don't do RESET, allows ESP to detect it should go into CLI mode
#ifdef USE_ESP_WIFI_BRIDGE_RST_GPIO0
    esp_gpio0_low();
    delay_ms(100);
#endif
    passthrough_do();
}

void tTxEspWifiBridge_passthrough_do(void)
{
    if (!initialized) return;
    ser->SetBaudRate(115200);
    leds.InitPassthrough();
    while (1) 
	{
        if (doSysTask) 
		{
            doSysTask = 0;
            leds.TickPassthrough_ms();
        }
        if (com->available()) 
		{
            char c = com->getc();
            ser->putc(c);
        }
        if (ser->available()) 
		{
            char c = ser->getc();
            com->putc(c);
        }
    }
}
#endif // USE_ESP_WIFI_BRIDGE
