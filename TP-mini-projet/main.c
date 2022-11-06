#include "clocks.h"

#ifndef CMSISandMAT
#define CMSISandMAT
#include "matrix.h"
#endif

#include "using_led_matrix.h"
#include "irq.h"
#include "uart.h"
#include "timer.h"

rgb_color image_on_matrix[8][8];

int main() {

    clocks_init();
    matrix_init();
    irq_init();
    uart_init(38400);
    timer_init(10000);

    while (1) {
        if (enable_show) {
            enable_show = 0;
            show();
        }
    }
    return 0;
}


