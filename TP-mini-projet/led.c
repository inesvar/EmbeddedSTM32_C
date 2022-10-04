#include <stdint.h>
#include "led.h"

// adresse de RCC : 0x4002 1000
// RCC_AHB2ENR : offset 0x4C
#define RCC_AHB2ENR (*(volatile uint32_t *)0x4002104C)

// adresse du peripherique B : 0x4800 0400
#define GPIO_B_MODER (*(volatile uint32_t *)0x48000400)
#define GPIO_B_BSRR (*(volatile uint32_t *)0x48000418)

// adresse du peripherique C :
#define GPIO_C_MODER (*(volatile uint32_t *)0x48000800)
#define GPIO_C_BSRR (*(volatile uint32_t *)0x48000818)

void led_init()
{
    // activer horloge
    // horloge GPIOB : bit 1 à 1
    // horloge GPIOC : bit 2 à 1
    RCC_AHB2ENR = (RCC_AHB2ENR & ~(3 << 1)) | (3 << 1);

    // PB14 en mode sortie :
    // on écrira 01 dans les bits [29:28] de GPIO_B_MODER
    GPIO_B_MODER = (GPIO_B_MODER & ~(3 << 28)) | (1 << 28);

    // PC9 en sortie :
    // 01 dans les bits [19:18] de GPIO_C_MODER
    GPIO_C_MODER = (GPIO_C_MODER & ~(3 << 18)) | (1 << 18);
}

void led_g_on()
{
    GPIO_B_BSRR = 1 << 14;
}

void led_g_off()
{
    GPIO_B_BSRR = 1 << 30;
}

void led(enum State state)
{
    switch (state)
    {
    case LED_OFF:
        //passer GPIOC en mode entree eteint les deux leds
        GPIO_C_MODER = (GPIO_C_MODER & ~(3 << 18));
        break;
    case LED_YELLOW:
        GPIO_C_MODER = (GPIO_C_MODER & ~(3 << 18)) | (1 << 18);
        GPIO_C_BSRR = 1 << 9;
        break;

    case LED_BLUE:
        GPIO_C_MODER = (GPIO_C_MODER & ~(3 << 18)) | (1 << 18);
        GPIO_C_BSRR = 1 << 25;
        break;
    }
}