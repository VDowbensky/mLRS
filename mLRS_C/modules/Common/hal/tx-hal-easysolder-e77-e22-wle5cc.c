//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// hal
//*******************************************************
// 5.Aug.2023: jrpin5 changed from JRPIN5_RX_TX_INVERT_SWAP_INTERNAL to JRPIN5_FULL_INTERNAL
// 5.Sep.2023: jrpin5 and in simultaneously supported

//#define MLRS_DEV_FEATURE_JRPIN5_SDIODE
//#define MLRS_FEATURE_DIVERSITY
//#define MLRS_FEATURE_NO_DIVERSITY

//-------------------------------------------------------
// TX DIY "easy-to-solder" E77 E22 dual, STM32WLE5CC
//-------------------------------------------------------

#include "tx-hal-easysolder-e77-e22-wle5cc.h"

//-- POWER
const rfpower_t rfpower_list[] = {
    { .dbm = POWER_MIN, .mW = INT8_MIN },
    { .dbm = POWER_0_DBM, .mW = 1 },
    { .dbm = POWER_10_DBM, .mW = 10 },
    { .dbm = POWER_20_DBM, .mW = 100 },
    { .dbm = POWER_22_DBM, .mW = 158 },
};

//-- TEST
uint32_t porta[] = {
    LL_GPIO_PIN_0, LL_GPIO_PIN_1, LL_GPIO_PIN_2, LL_GPIO_PIN_3, LL_GPIO_PIN_5,
    LL_GPIO_PIN_9, LL_GPIO_PIN_10, LL_GPIO_PIN_11, LL_GPIO_PIN_12,
    LL_GPIO_PIN_15,
};

uint32_t portb[] = {
    LL_GPIO_PIN_2, LL_GPIO_PIN_3, LL_GPIO_PIN_4, LL_GPIO_PIN_6, LL_GPIO_PIN_7,
    LL_GPIO_PIN_8,
    LL_GPIO_PIN_12,
};

uint32_t portc[] = {
    //LL_GPIO_PIN_13,
};

void sx_init_gpio(void)
{
    gpio_init(SX_TX_EN, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_VERYFAST);
    gpio_init(SX_RX_EN, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_VERYFAST);
}

bool sx_busy_read(void)
{
    return subghz_is_busy();
}

void sx_amp_transmit(void)
{
    gpio_low(SX_RX_EN);
    gpio_high(SX_TX_EN);
}

void sx_amp_receive(void)
{
    gpio_low(SX_TX_EN);
    gpio_high(SX_RX_EN);
}

void sx_dio_init_exti_isroff(void)
{
    // there is no EXTI_LINE_44 interrupt flag
    //LL_EXTI_DisableEvent_32_63(SX_DIO_EXTI_LINE_x);
    //LL_EXTI_DisableIT_32_63(SX_DIO_EXTI_LINE_x);

    NVIC_SetPriority(SX_DIO_EXTI_IRQn, SX_DIO_EXTI_IRQ_PRIORITY);
    //NVIC_EnableIRQ(SX_DIO_EXTI_IRQn);
}

void sx_dio_enable_exti_isr(void)
{
    // there is no EXTI_LINE_44 interrupt flag
    //LL_EXTI_ClearFlag_32_63(SX_DIO_EXTI_LINE_x);
    //LL_EXTI_EnableIT_32_63(SX_DIO_EXTI_LINE_x);

    NVIC_EnableIRQ(SX_DIO_EXTI_IRQn);
}

void sx_dio_exti_isr_clearflag(void)
{
    // there is no EXTI_LINE_44 interrupt flag
}

//-- SX12xx II & SPIB
void sx2_init_gpio(void)
{
    gpio_init(SX2_RESET, IO_MODE_OUTPUT_PP_HIGH, IO_SPEED_VERYFAST);
    gpio_init(SX2_DIO1, IO_MODE_INPUT_PD, IO_SPEED_VERYFAST);
    gpio_init(SX2_BUSY, IO_MODE_INPUT_PU, IO_SPEED_VERYFAST);
    gpio_init(SX2_TX_EN, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_VERYFAST);
    gpio_init(SX2_RX_EN, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_VERYFAST);
}

bool sx2_busy_read(void)
{
    return (gpio_read_activehigh(SX2_BUSY)) ? true : false;
}

void sx2_amp_transmit(void)
{
    gpio_low(SX2_RX_EN);
    gpio_high(SX2_TX_EN);
}

void sx2_amp_receive(void)
{
    gpio_low(SX2_TX_EN);
    gpio_high(SX2_RX_EN);
}

void sx2_dio_init_exti_isroff(void)
{
    LL_SYSCFG_SetEXTISource(SX2_DIO1_SYSCFG_EXTI_PORTx, SX2_DIO1_SYSCFG_EXTI_LINEx);

    // let's not use LL_EXTI_Init(), but let's do it by hand, is easier to allow enabling isr later
    LL_EXTI_DisableEvent_0_31(SX2_DIO_EXTI_LINE_x);
    LL_EXTI_DisableIT_0_31(SX2_DIO_EXTI_LINE_x);
    LL_EXTI_DisableFallingTrig_0_31(SX2_DIO_EXTI_LINE_x);
    LL_EXTI_EnableRisingTrig_0_31(SX2_DIO_EXTI_LINE_x);

    NVIC_SetPriority(SX2_DIO_EXTI_IRQn, SX2_DIO_EXTI_IRQ_PRIORITY);
    NVIC_EnableIRQ(SX2_DIO_EXTI_IRQn);
}

void sx2_dio_enable_exti_isr(void)
{
    LL_EXTI_ClearFlag_0_31(SX2_DIO_EXTI_LINE_x);
    LL_EXTI_EnableIT_0_31(SX2_DIO_EXTI_LINE_x);
}

void sx2_dio_exti_isr_clearflag(void)
{
    LL_EXTI_ClearFlag_0_31(SX2_DIO_EXTI_LINE_x);
}

//-- In port
// this is nasty, UARTE defines not yet known, but cumbersome to add, so we include the lib
#ifdef DEVICE_HAS_IN
#include "../../modules/stm32ll-lib/src/stdstm32-uarte.h"

void in_init_gpio(void)
{
	
}

void in_set_normal(void)
{
    LL_USART_Disable(UARTE_UARTx);
    LL_USART_SetTXRXSwap(UARTE_UARTx, LL_USART_TXRX_SWAPPED);
    LL_USART_SetRXPinLevel(UARTE_UARTx, LL_USART_RXPIN_LEVEL_STANDARD);
    LL_USART_Enable(UARTE_UARTx);
    gpio_init_af(UARTE_TX_IO, IO_MODE_INPUT_PU, UARTE_IO_AF, IO_SPEED_VERYFAST);
}

void in_set_inverted(void)
{
    LL_USART_Disable(UARTE_UARTx);
    LL_USART_SetTXRXSwap(UARTE_UARTx, LL_USART_TXRX_SWAPPED);
    LL_USART_SetRXPinLevel(UARTE_UARTx, LL_USART_RXPIN_LEVEL_INVERTED);
    LL_USART_Enable(UARTE_UARTx);
    gpio_init_af(UARTE_TX_IO, IO_MODE_INPUT_PD, UARTE_IO_AF, IO_SPEED_VERYFAST);
}
#endif

//-- Button

void button_init(void)
{
    gpio_init(BUTTON, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
}

bool button_pressed(void)
{
    return gpio_read_activelow(BUTTON);
}

//-- LEDs
void leds_init(void)
{
    gpio_init(LED_GREEN, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_DEFAULT);
    gpio_init(LED_RED, IO_MODE_OUTPUT_PP_LOW, IO_SPEED_DEFAULT);
}

void led_green_off(void) 
{ 
	gpio_low(LED_GREEN); 
}

void led_green_on(void) 
{ 
	gpio_high(LED_GREEN); 
}

void led_green_toggle(void) 
{ 
	gpio_toggle(LED_GREEN); 
}

void led_red_off(void) 
{ 
	gpio_low(LED_RED); 
}

void led_red_on(void) 
{ 
	gpio_high(LED_RED); 
}

void led_red_toggle(void) 
{ 
	gpio_toggle(LED_RED); 
}

//-- Serial or Com Switch
// use com if BUTTON is pressed during power up, else use serial
// BUTTON becomes bind button later on

bool easysolder_ser_or_com_serial = true; // we use serial as default

void ser_or_com_init(void)
{
    gpio_init(BUTTON, IO_MODE_INPUT_PU, IO_SPEED_DEFAULT);
    uint8_t cnt = 0;
    for (uint8_t i = 0; i < 16; i++) 
	{
        if (gpio_read_activelow(BUTTON)) cnt++;
    }
    easysolder_ser_or_com_serial = !(cnt > 8);
}

bool ser_or_com_serial(void)
{
    return easysolder_ser_or_com_serial;
}
