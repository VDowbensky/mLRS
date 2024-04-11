//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// hal
//*******************************************************

//#define MLRS_FEATURE_DIVERSITY
//#define MLRS_FEATURE_NO_DIVERSITY

//-------------------------------------------------------
// RX DIY "easy-to-solder" E77 E22 dual, STM32WLE5CC
//-------------------------------------------------------

//#define DEVICE_HAS_DIVERSITY
#define DEVICE_HAS_OUT
#define DEVICE_HAS_DEBUG_SWUART

#ifdef MLRS_FEATURE_DIVERSITY
  #define DEVICE_HAS_DIVERSITY
#endif
#ifdef MLRS_FEATURE_NO_DIVERSITY
  #undef DEVICE_HAS_DIVERSITY
#endif

//-- Timers, Timing, EEPROM, and such stuff
#define DELAY_USE_DWT
#define SYSTICK_TIMESTEP          1000
#define SYSTICK_DELAY_MS(x)       (uint16_t)(((uint32_t)(x)*(uint32_t)1000)/SYSTICK_TIMESTEP)
#define EE_START_PAGE             120 // 256 kB flash, 2 kB page
#define MICROS_TIMx               TIM16
#define CLOCK_TIMx                TIM2
#define CLOCK_IRQn                TIM2_IRQn
#define CLOCK_IRQHandler          TIM2_IRQHandler
//#define CLOCK_IRQ_PRIORITY        10

//-- UARTS
// UARTB = serial port
// UART = output port, SBus or whatever
// UARTC = debug port
#define UARTB_USE_UART1_PB6PB7 // serial // PB6,PB7
#define UARTB_BAUD                RX_SERIAL_BAUDRATE
#define UARTB_USE_TX
#define UARTB_TXBUFSIZE           RX_SERIAL_TXBUFSIZE
#define UARTB_USE_TX_ISR
#define UARTB_USE_RX
#define UARTB_RXBUFSIZE           RX_SERIAL_RXBUFSIZE
#define UART_USE_UART2_PA2PA3 // out pin // PA2
#define UART_BAUD                 100000 // SBus normal baud rate, is being set later anyhow
#define UART_USE_TX
#define UART_TXBUFSIZE            256
#define UART_USE_TX_ISR
//#define UART_USE_RX
//#define UART_RXBUFSIZE            512
#define OUT_UARTx                 USART2 // UART_UARTx is not known yet, so define by hand
#define SWUART_USE_TIM17 // debug
#define SWUART_TX_IO              IO_PA9 // STx pad on board
#define SWUART_BAUD               115200
#define SWUART_USE_TX
#define SWUART_TXBUFSIZE          512
//#define SWUART_TIM_IRQ_PRIORITY   9

//-- SX12xx & SPI
#define SPI_USE_SUBGHZSPI
#define SPI_USE_CLOCKSPEED_12MHZ
#define SX_BUSY                   0 // busy is provided by subghz, we need to define a dummy to fool sx126x_driver lib
#define SX_HAS_NO_RESET           // SubGHz has no reset, reset is done by spi_init()
#define SX_RX_EN                  IO_PA7
#define SX_TX_EN                  IO_PA6
#define SX_DIO_EXTI_IRQn              SUBGHZ_Radio_IRQn
#define SX_DIO_EXTI_IRQHandler        SUBGHZ_Radio_IRQHandler
//#define SX_DIO_EXTI_IRQ_PRIORITY    11

#define SX_USE_CRYSTALOSCILLATOR

void sx_init_gpio(void);
bool sx_busy_read(void);
void sx_amp_transmit(void);
void sx_amp_receive(void);
void sx_dio_init_exti_isroff(void);
void sx_dio_enable_exti_isr(void);
void sx_dio_exti_isr_clearflag(void);

//-- SX12xx II & SPIB
#define SPIB_USE_SPI1             // PA5, PA11, PA12
#define SPIB_USE_SCK_IO           IO_PA5
#define SPIB_USE_MISO_IO          IO_PA11
#define SPIB_USE_MOSI_IO          IO_PA12
#define SPIB_CS_IO                IO_PB12
#define SPIB_USE_CLK_LOW_1EDGE    // datasheet says CPHA = 0  CPOL = 0
#define SPIB_USE_CLOCKSPEED_18MHZ // equals to 12 MHz

#define SX2_RESET                 IO_PB2
#define SX2_DIO1                  IO_PC13
#define SX2_BUSY                  IO_PA15
#define SX2_RX_EN                 IO_PA0
#define SX2_TX_EN                 IO_PB8

#define SX2_DIO1_SYSCFG_EXTI_PORTx    LL_SYSCFG_EXTI_PORTC
#define SX2_DIO1_SYSCFG_EXTI_LINEx    LL_SYSCFG_EXTI_LINE13
#define SX2_DIO_EXTI_LINE_x           LL_EXTI_LINE_13
#define SX2_DIO_EXTI_IRQn             EXTI15_10_IRQn
#define SX2_DIO_EXTI_IRQHandler       EXTI15_10_IRQHandler
//#define SX2_DIO_EXTI_IRQ_PRIORITY   11

void sx2_init_gpio(void);
bool sx2_busy_read(void);
void sx2_amp_transmit(void);
void sx2_amp_receive(void);
void sx2_dio_init_exti_isroff(void);
void sx2_dio_enable_exti_isr(void);
void sx2_dio_exti_isr_clearflag(void);

//-- Out port
void out_init_gpio(void);
void out_set_normal(void);
void out_set_inverted(void);

//-- Button
#define BUTTON                    IO_PA1

void button_init(void);
bool button_pressed(void);


//-- LEDs
#define LED_GREEN                 IO_PB4
#define LED_RED                   IO_PB3

void leds_init(void);
void led_green_off(void);
void led_green_on(void);
void led_green_toggle(void);
void led_red_off(void);
void led_red_on(void);
void led_red_toggle(void);

//-- POWER
#define POWER_GAIN_DBM            0 // gain of a PA stage if present
#define POWER_SX126X_MAX_DBM      SX126X_POWER_MAX // maximum allowed sx power
#define POWER_USE_DEFAULT_RFPOWER_CALC
#define RFPOWER_DEFAULT           2 // index into rfpower_list array

extern const rfpower_t rfpower_list[];
//-- TEST
extern uint32_t porta[];
extern uint32_t portb[];
extern uint32_t portc[];









