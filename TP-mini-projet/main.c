#include "clocks.h"
#define MAT
#include "matrix.h"
#include "using_leds.h"
#include "irq.h"
#include "buttons.h"
#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#endif

int leds = 0;

int main() {
    clocks_init();
    matrix_init();
    irq_init();
    button_init();
    rgb_color color_buffer[8][8];
    create_color_buffer(color_buffer);
    show(color_buffer);
    return 0;
}


void EXTI15_10_IRQHandler() {
    EXTI->PR1 |= EXTI_PR1_PIF13;
    leds = 1 - leds;
}