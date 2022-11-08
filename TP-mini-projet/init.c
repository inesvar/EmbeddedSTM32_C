#include <stdint.h>

extern uint8_t _bstart, _bend, _data, _edata, _flashdata, _text, _etext, _flashtext, _vtor, _evtor, _flashvtor;

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

void init_text() {
    uint8_t * src = &_flashtext;
    for (uint8_t * p = &_text; p < &_etext ; p++) {
        *p = *src++;
    }
}

void init_vtor() {
    uint8_t * src = &_flashvtor;
    for (uint8_t * p = &_vtor; p < &_evtor ; p++) {
        *p = *src++;
    }
}
