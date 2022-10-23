#ifndef MAT
#define MAT
#include "matrix.h"
#endif

static void color_buffer_set_pixel(rgb_color * color, int rgb[3]);
static void add_luminosity(int rgb[3]);
static void erase(int rgb[3]);

static void mat_set_row(int row, const rgb_color line[8]);