#ifndef CMSISandMAT
#define CMSISandMAT
#include "matrix.h"
#endif

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

extern rgb_color image_on_matrix[8][8];
void update_image_on_matrix(uint8_t octet);
void show();
