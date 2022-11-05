#include "clocks.h"

#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#endif

#ifndef MAT
#define MAT
#include "matrix.h"
#endif

#include "using_led_matrix.h"
#include "irq.h"
#include "buttons.h"

int main() {

    clocks_init();
    matrix_init();
    irq_init();
    button_init();

    rgb_color color_buffer[8][8];

    
    //receiving data and writing it in _binary_raw_image


    //updating the color buffer and transmitting it to the led matrix
    fill_color_buffer(color_buffer);
    show(color_buffer);

    return 0;
}