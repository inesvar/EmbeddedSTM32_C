#ifndef CMSIS
#define CMSIS
#include "stm32l4xx.h"
#endif

void matrix_init();

void delay(int n);
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val, int bank);