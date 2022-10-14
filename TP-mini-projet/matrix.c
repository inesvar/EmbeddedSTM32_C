#include "stm32l4xx.h"
#include "matrix.h"


void matrix_init() {
    //on allume l'horloge des ports A, B et C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    
    //on configure les broches PA2,3,4,5,6,7,15 en mode sortie (01)
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) | (1 << GPIO_MODER_MODE2_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_Msk) | (1 << GPIO_MODER_MODE3_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_Msk) | (1 << GPIO_MODER_MODE4_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_Msk) | (1 << GPIO_MODER_MODE5_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_Msk) | (1 << GPIO_MODER_MODE6_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_Msk) | (1 << GPIO_MODER_MODE7_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) | (1 << GPIO_MODER_MODE15_Pos);

    //on configure les broches PA2,3,4,5,6,7,15 en très haute vitesse (11)
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) | (3 << GPIO_OSPEEDR_OSPEED2_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk) | (3 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4_Msk) | (3 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5_Msk) | (3 << GPIO_OSPEEDR_OSPEED5_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED6_Msk) | (3 << GPIO_OSPEEDR_OSPEED6_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED7_Msk) | (3 << GPIO_OSPEEDR_OSPEED7_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED15_Msk) | (3 << GPIO_OSPEEDR_OSPEED15_Pos);

    //on configure les broches PB0,1,2 en mode sortie (01)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk) | (1 << GPIO_MODER_MODE0_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_Msk) | (1 << GPIO_MODER_MODE1_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_Msk) | (1 << GPIO_MODER_MODE2_Pos);

    //on configure les broches PB0,1,2 en très haute vitesse (11)
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0_Msk) | (1 << GPIO_OSPEEDR_OSPEED0_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED1_Msk) | (1 << GPIO_OSPEEDR_OSPEED1_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) | (1 << GPIO_OSPEEDR_OSPEED2_Pos);

    //on configure les broches PC3,4,5 en mode sortie (01)
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE0_Msk) | (1 << GPIO_MODER_MODE0_Pos);
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE1_Msk) | (1 << GPIO_MODER_MODE1_Pos);
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE2_Msk) | (1 << GPIO_MODER_MODE2_Pos);

    //on configure les broches PC3,4,5 en très haute vitesse (11)
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0_Msk) | (1 << GPIO_OSPEEDR_OSPEED0_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED1_Msk) | (1 << GPIO_OSPEEDR_OSPEED1_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) | (1 << GPIO_OSPEEDR_OSPEED2_Pos);

    //reset le DM163
    GPIOC->BSRR |= GPIO_BSRR_BR3;

    //place les autres broches a des valeurs initiales acceptables
    //LAT : 1; SB : 1; SCK : 0; SDA : 0
    GPIOC->BSRR |= GPIO_BSRR_BS4;
    GPIOC->BSRR |= GPIO_BSRR_BS5;
    GPIOB->BSRR |= GPIO_BSRR_BR1;
    GPIOA->BSRR |= GPIO_BSRR_BR4;

    //eteindre toutes les lignes : C0 a C7 a 0
    GPIOC->BSRR |= GPIO_BSRR_BR2;
    GPIOC->BSRR |= GPIO_BSRR_BR0;
    GPIOA->BSRR |= GPIO_BSRR_BR2;
    GPIOA->BSRR |= GPIO_BSRR_BR3;
    GPIOA->BSRR |= GPIO_BSRR_BR5;
    GPIOA->BSRR |= GPIO_BSRR_BR6;
    GPIOA->BSRR |= GPIO_BSRR_BR7;
    GPIOA->BSRR |= GPIO_BSRR_BR15;

    for (int i=0; i< 6000000 ; i++) {
            asm volatile("nop");
    }  


    //repasse RST a l'etat haut
    GPIOC->BSRR |= GPIO_BSRR_BS3;



}