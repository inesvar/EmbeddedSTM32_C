#include <stdint.h>
#define UINT
#include "clocks.h"
#include "matrix.h"
#define MAT
#include "using_leds.h"

int main() {
    clocks_init();
    matrix_init();
    test_pixels();
    return 0;
}
