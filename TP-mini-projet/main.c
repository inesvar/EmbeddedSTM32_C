#include <stdint.h>
#include "clocks.h"
#include "uart.h"
#include "matrix.h"


int main() {
    clocks_init();
    matrix_init();
    return 0;
}

//la transmission a vitesse maximale 115200 ne marche que si on ne met pas d'autre envoi dans la boucle