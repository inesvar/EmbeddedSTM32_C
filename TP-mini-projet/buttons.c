#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#include "core_cm4.h"
#endif
#include "led_g.h"

void button_init() {
    //on allume l'horloge du port C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    //on configure PC13 en mode entree
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE13_Msk);
    
    //selectionne la broche PC13 comme source d'IRQ pour EXTI13
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13_Msk) | SYSCFG_EXTICR4_EXTI13_PC;

    //autoriser EXTI13 comme source d'interruptions
    EXTI->IMR1 |= EXTI_IMR1_IM13;

    //envoyer une interruption sur front descendant
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;

    //ne pas envoyer d'interruptions sur front montant
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13;

    //autoriser l'interruption EXTI15_10 
    NVIC_EnableIRQ(40);

    //initialise la led verte qui sera togglee pendant l'interruption
    led_g_init();
}

void EXTI15_10_IRQHandler() {
    //acquittement de l'interruption
    EXTI->PR1 |= EXTI_PR1_PIF13;

    led_g_toggle();
}
