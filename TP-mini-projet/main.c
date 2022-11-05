#include <stdint.h>
#include "clocks.h"
#include "uart.h"
#include "led.h"

#define HALF_PERIOD 6000000
void delay();

int main() {
    clocks_init();
    
    uart_init();
    uint32_t sum = 0;
    for (uint16_t i = 0 ; i < 1000 ; i++) {
        uint8_t octetSend = uart_getchar();
        sum = sum + octetSend;
    }
    return sum;

    /*
    led_init();
    for (int i = 0 ; i < 15 ; i++) {

        //eteindre les leds bleue et jaune, allumer la verte
        led(LED_OFF);
        led_g_on();
        delay();

        //eteindre la led verte, allumer la jaune     
        led_g_off();
        led(LED_YELLOW);
        delay();   

        //changer la led jaune pour la bleue   
        led(LED_BLUE);
        delay();
    }
    led(LED_OFF);
    return 0;
    */
}

//la transmission a vitesse maximale 115200 ne marche que si on ne met pas d'autre envoi dans la boucle

void delay() {
    for (int i=0; i< HALF_PERIOD; i++) {
            asm volatile("nop");
    }
}
