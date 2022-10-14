#include <stdint.h>
#include "clocks.h"
#include "uart.h"

    

int main() {
    clocks_init();
    uart_init();
    uint32_t sum = 0;
    for (uint16_t i = 0 ; i < 1000 ; i++) {
        uint8_t octetSend = uart_getchar();
        sum = sum + octetSend;
    }
    return sum;
}

//la transmission a vitesse maximale 115200 ne marche que si on ne met pas d'autre envoi dans la boucle