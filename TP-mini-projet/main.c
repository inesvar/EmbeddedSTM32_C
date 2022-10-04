#include "led.h"

#define HALF_PERIOD 300000

int main() {
    led_init();
    for (int i = 0 ; i < 15 ; i++) {

        //eteindre les leds bleue et jaune, allumer la verte
        led(LED_OFF);
        led_g_on();
        for (int i=0; i< HALF_PERIOD; i++) {
            asm volatile("nop");
        }   

        //eteindre la led verte, allumer la jaune     
        led_g_off();
        led(LED_YELLOW);
        for (int i=0; i< HALF_PERIOD; i++) {
            asm volatile("nop");
        }     

        //changer la led jaune pour la bleue   
        led(LED_BLUE);
        for (int i=0; i< HALF_PERIOD; i++) {
            asm volatile("nop");
        }
    }
    
    led(LED_OFF);
    return 0;
}