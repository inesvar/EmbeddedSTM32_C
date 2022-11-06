#include "clocks.h"

#ifndef CMSISandMAT
#define CMSISandMAT
#include "matrix.h"
#endif

#include "using_led_matrix.h"
#include "irq.h"
#include "uart.h"
#include "led_g.h"
#include "timer.h"

rgb_color image_on_matrix[8][8];

int main() {

    clocks_init();
    matrix_init();
    irq_init();
    uart_init(38400);
    led_g_init();
    timer_init(1000000);

    //transmitting the color buffer to the led matrix
    show();

    return 0;
}


