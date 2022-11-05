#include "led_g.h"
#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#endif


void led_g_init()
{
    // activer horloge dans RCC_AHB2ENR
    // horloge GPIOB : bit 1 à 1
    // horloge GPIOC : bit 2 à 1
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // PB14 en mode sortie :
    // on écrira 01 dans les bits [29:28] de GPIO_B_MODER
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;

    // PC9 en sortie :
    // 01 dans les bits [19:18] de GPIO_C_MODER
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
}

void led_g_on()
{
    GPIOB->BSRR |= GPIO_BSRR_BS14;


}

void led_g_off()
{
    GPIOB->BSRR |= GPIO_BSRR_BR14;
}

void led_g_toggle() {

    static int led_g_state = 0;

    led_g_state = 1 - led_g_state; //switch state

    if (led_g_state) {
        led_g_on();
    } else {
        led_g_off();
    }
}
