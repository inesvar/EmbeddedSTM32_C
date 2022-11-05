#include "led.h"
#include "stm32l4xx.h"


void led_init()
{
    // activer horloge B et C dans RCC_AHB2ENR
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // PB14 en mode sortie :
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;

    // PC9 en sortie :
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