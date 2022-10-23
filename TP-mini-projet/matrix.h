#ifndef UINT
#define UINT
#include <stdint.h>
#endif

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

void matrix_init();

void delay(int n);
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val, int bank);