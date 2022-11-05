#include "clocks.h"

#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#endif

#include "matrix.h"
#include "using_led_matrix.h"
#include "irq.h"
#include "uart.h"

rgb_color image_on_matrix[8][8];

int main() {

    clocks_init();
    matrix_init();
    irq_init();
    uart_init(38400);

    //transmitting the color buffer to the led matrix
    show(image_on_matrix);

    return 0;
}


