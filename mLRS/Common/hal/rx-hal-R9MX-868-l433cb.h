//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// hal
//********************************************************

//-------------------------------------------------------
// R9MX RX Module STM32L433CB
//-------------------------------------------------------
// https://github.com/ExpressLRS/ExpressLRS/blob/master/src/include/target/Frsky_RX_R9M.h
// many THX to the ExpressLRS project !
// Connection pads:
//   Pin1 GND
//   Pin2 VCC
//   Pin3 SPort/FPort PA5  (looks strange)
//   Pin4 Inv SPort   PB11
//   Pin5 SBusOut     PA2 inverted
//   Pin6 SBusIn      ???
//   Ch1    PA11
//   Ch2    PA10 / U1Rx
//   Ch3    PA9 / U1Tx
//   Ch4    PA8

//#define DEVICE_HAS_NO_SERIAL
#define DEVICE_HAS_NO_DEBUG


//-- Timers, Timing and such stuff

#define DELAY_USE_DWT

#define SYSTICK_TIMESTEP          1000
#define SYSTICK_DELAY_MS(x)       (uint16_t)(((uint32_t)(x)*(uint32_t)1000)/SYSTICK_TIMESTEP)


//-- UARTS
// UARTB = serial port
// UARTC = debug port
// UART = output port, SBus or whatever

#define UARTB_USE_UART1 // serial
#define UARTB_BAUD                SETUP_RX_SERIAL_BAUDRATE
#define UARTB_USE_TX
#define UARTB_TXBUFSIZE           1024 // 512
#define UARTB_USE_TX_ISR
#define UARTB_USE_RX
#define UARTB_RXBUFSIZE           1024 // 512

#define UARTC_USE_UART1 //3 // debug
#define UARTC_BAUD                115200
#define UARTC_USE_TX
#define UARTC_TXBUFSIZE           512
#define UARTC_USE_TX_ISR
//#define UARTC_USE_RX
//#define UARTC_RXBUFSIZE           512

#define UART_USE_UART2 // SBus
#define UART_BAUD                 100000 // SBus normal baud rate, is being set later anyhow
#define UART_USE_TX
#define UART_TXBUFSIZE            256 // 512
#define UART_USE_TX_ISR
//#define UART_USE_RX
//#define UART_RXBUFSIZE            512


//-- SX1: SX12xx & SPI

#define SPI_USE_SPI2              // PB13, PB14, PB15
#define SPI_CS_IO                 IO_PB12
#define SPI_USE_CLK_LOW_1EDGE     // datasheet says CPHA = 0  CPOL = 0
#define SPI_USE_CLOCKSPEED_9MHZ

#define SX_RESET                  IO_PC14
#define SX_DIO0                   IO_PA15
#define SX_DIO1                   // IO_PA1 ???
#define SX_RX_EN                  //
#define SX_TX_EN                  //

#define SX_DIO0_SYSCFG_EXTI_PORTx     LL_SYSCFG_EXTI_PORTA
#define SX_DIO0_SYSCFG_EXTI_LINEx     LL_SYSCFG_EXTI_LINE15
#define SX_DIO_EXTI_LINE_x            LL_EXTI_LINE_15
#define SX_DIO_EXTI_IRQn              EXTI15_10_IRQn
#define SX_DIO_EXTI_IRQHandler        EXTI15_10_IRQHandler
//#define SX_DIO_EXTI_IRQ_PRIORITY    11

void sx_init_gpio(void)
{
  gpio_init(SX_RESET, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_VERYFAST);
  gpio_init(SX_DIO0, IO_MODE_INPUT_PD, IO_SPEED_VERYFAST);
}

bool sx_dio0_read(void)
{
  return (gpio_read_activehigh(SX_DIO0)) ? true : false;
}

void sx_amp_transmit(void)
{
}

void sx_amp_receive(void)
{
}

void sx_dio_init_exti_isroff(void)
{
  LL_SYSCFG_SetEXTISource(SX_DIO0_SYSCFG_EXTI_PORTx, SX_DIO0_SYSCFG_EXTI_LINEx);

  // let's not use LL_EXTI_Init(), but let's do it by hand, is easier to allow enabling isr later
  LL_EXTI_DisableEvent_0_31(SX_DIO_EXTI_LINE_x);
  LL_EXTI_DisableIT_0_31(SX_DIO_EXTI_LINE_x);
  LL_EXTI_DisableFallingTrig_0_31(SX_DIO_EXTI_LINE_x);
  LL_EXTI_EnableRisingTrig_0_31(SX_DIO_EXTI_LINE_x);

  NVIC_SetPriority(SX_DIO_EXTI_IRQn, SX_DIO_EXTI_IRQ_PRIORITY);
  NVIC_EnableIRQ(SX_DIO_EXTI_IRQn);
}

void sx_dio_enable_exti_isr(void)
{
  LL_EXTI_ClearFlag_0_31(SX_DIO_EXTI_LINE_x);
  LL_EXTI_EnableIT_0_31(SX_DIO_EXTI_LINE_x);
}


//-- SBus output pin

#define OUT                       IO_PA2 // UART2 TX, the pin is inverted in hardware

void out_init_gpio(void)
{
}

void out_set_normal(void)
{
  LL_USART_Disable(USART2);
  LL_USART_SetTXPinLevel(USART2, LL_USART_TXPIN_LEVEL_INVERTED);
  LL_USART_Enable(USART2);
}

void out_set_inverted(void)
{
  LL_USART_Disable(USART2);
  LL_USART_SetTXPinLevel(USART2, LL_USART_TXPIN_LEVEL_STANDARD);
  LL_USART_Enable(USART2);
}


//-- Button

#define BUTTON                    IO_PB0

void button_init(void)
{
//  gpio_init(BUTTON, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
}

bool button_pressed(void)
{
  return false; //gpio_read_activelow(BUTTON);
}


//-- LEDs

#define LED_GREEN                 IO_PB3
#define LED_RED                   IO_PB2

#define LED_GREEN_ON              gpio_high(LED_GREEN)
#define LED_RED_ON                gpio_high(LED_RED)

#define LED_GREEN_OFF             gpio_low(LED_GREEN)
#define LED_RED_OFF               gpio_low(LED_RED)

#define LED_GREEN_TOGGLE          gpio_toggle(LED_GREEN)
#define LED_RED_TOGGLE            gpio_toggle(LED_RED)

void leds_init(void)
{
  gpio_init(LED_GREEN, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_DEFAULT);
  gpio_init(LED_RED, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_DEFAULT);
  LED_GREEN_OFF;
  LED_RED_OFF;
}


//-- POWER

#define POWER_GAIN_DBM            0 // gain of a PA stage if present
#define POWER_SX1276_MAX_DBM      SX1276_OUTPUT_POWER_MAX // maximum allowed sx power
#define POWER_USE_DEFAULT_RFPOWER_CALC

#define RFPOWER_LIST_NUM           5

const rfpower_t rfpower_list[RFPOWER_LIST_NUM] = {
    { .dbm = POWER_0_DBM, .mW = 1 },
    { .dbm = POWER_10_DBM, .mW = 10 },
    { .dbm = POWER_17_DBM, .mW = 50 },
};


//-- TEST

#define PORTA_N  14

uint32_t porta[PORTA_N] = {
    LL_GPIO_PIN_0, LL_GPIO_PIN_1, LL_GPIO_PIN_2, LL_GPIO_PIN_3,
    LL_GPIO_PIN_4, LL_GPIO_PIN_5, LL_GPIO_PIN_6, LL_GPIO_PIN_7,
    LL_GPIO_PIN_8, LL_GPIO_PIN_9, LL_GPIO_PIN_10, LL_GPIO_PIN_11,
    LL_GPIO_PIN_12, LL_GPIO_PIN_15,
};

#define PORTB_N  13

uint32_t portb[PORTB_N] = {
    LL_GPIO_PIN_0, LL_GPIO_PIN_1, LL_GPIO_PIN_3,
    LL_GPIO_PIN_4, LL_GPIO_PIN_5, LL_GPIO_PIN_6, LL_GPIO_PIN_7,
    LL_GPIO_PIN_10, LL_GPIO_PIN_11, LL_GPIO_PIN_12, LL_GPIO_PIN_13,
    LL_GPIO_PIN_14, LL_GPIO_PIN_15,
};

#define PORTC_N  3

uint32_t portc[PORTC_N] = {
    LL_GPIO_PIN_1,
    LL_GPIO_PIN_13, LL_GPIO_PIN_14,
};
/*

#define PORTA_N  6

uint32_t porta[PORTA_N] = {
    LL_GPIO_PIN_2, LL_GPIO_PIN_5,
    LL_GPIO_PIN_8, LL_GPIO_PIN_9, LL_GPIO_PIN_10, LL_GPIO_PIN_11,
};

#define PORTB_N  2

uint32_t portb[PORTB_N] = {
    LL_GPIO_PIN_3,
    LL_GPIO_PIN_11,
};

#define PORTC_N  1

uint32_t portc[PORTC_N] = {
    LL_GPIO_PIN_1,
};
*/