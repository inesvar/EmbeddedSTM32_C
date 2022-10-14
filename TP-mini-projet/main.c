#include "clocks.h"
#include "uart.h"

#define HALF_PERIOD 6000000

void delay();

int main() {
    clocks_init();

    uart_init();
    uart_putchar('c');
    uart_putchar('o');
    uart_putchar('m');
    uart_puts("Hello World!");
    while (1) {
        uint8_t textSend = uart_getchar();
        uart_putchar(textSend);
    }
    
    return 0;
}

void delay() {
    for (int i=0; i< HALF_PERIOD; i++) {
            asm volatile("nop");
    }
}