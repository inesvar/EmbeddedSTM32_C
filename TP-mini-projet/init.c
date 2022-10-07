#include <stdint.h>

extern uint8_t _bstart, _bend;

void init_bss() {
    for (uint8_t * zero = &_bstart; zero < &_bend ; zero++) {
        *zero = 0;
    } // on utilise des uint8 pour ne pas depasser de la bss
}
