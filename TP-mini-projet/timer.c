#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#endif
#include "led_g.h"

void timer_init(int max_us) {
    //active horloge du time TIM2
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    //reset TIM2 pour 
    //mettre a zero TIM2_ISR et TIMx_CNT
    //selectionner l'upcounting
    //autoriser l'update event
    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM2RST;
    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM2RST;

    //diviser clock par 80 TIM2_PSC
    TIM2->PSC = 79;

    //compter jusqu'a max_us
    TIM2->ARR = max_us;

    //update interrupt enable
    TIM2->DIER |= TIM_DIER_UIE;

    //autoriser l'interruption TIM2
    NVIC_EnableIRQ(28);

    //activer l'horloge
    TIM2->CR1 |= TIM_CR1_CEN;

}

void TIM2_IRQHandler() {
    TIM2->SR &= ~TIM_SR_UIF;
    led_g_toggle();
}