#include <stdint.h>

extern uint8_t _bstart, _bend, _data, _edata, _flashdata;

void init_data() {
    uint8_t * src = &_flashdata;
    for (uint8_t * p = &_data; p < &_edata ; p++) {
        *p = *src++;
    }
}
void init_bss() {
    for (uint8_t * zero = &_bstart; zero < &_bend ; zero++) {
        *zero = 0;
    } // on utilise des uint8 pour ne pas depasser de la bss
}
