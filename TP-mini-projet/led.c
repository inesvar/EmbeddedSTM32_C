#include <stdint.h>
#include "led.h"
//#include "stm32l475xx.h"
#include "stm32l4xx.h"

#define GPIO_B_BSRR (*(volatile uint32_t *)0x48000418)


void led_init()
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

void led(enum State state)
{
    switch (state)
    {
    case LED_OFF:
        //passer GPIOC en mode entree eteint les deux leds
        // PC9 en entree 
        // 00 dans les bits [19:18] de GPIO_C_MODER
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk);
        break;
    case LED_YELLOW:
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
        GPIOC->BSRR |= GPIO_BSRR_BS9;
        break;

    case LED_BLUE:
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
        GPIOC->BSRR |= GPIO_BSRR_BR9;
        break;
    }
}