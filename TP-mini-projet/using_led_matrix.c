#ifndef MAT
#define MAT
#include "matrix.h"
#endif

#include "using_led_matrix.h"
#include "using_led_matrix_private.h"

extern int leds;
extern uint8_t _binary_image_raw_start, _binary_image_raw_end;

void fill_color_buffer(rgb_color color_buffer[8][8]) {
    //lit le fichier image.o et place les octets dans le bon endroit dans le buffer
    for (int row = 0; row < 8; row++) {
        for (int col = 0 ; col < 8 ; col++) {
            color_buffer[row][col].b = *(&_binary_image_raw_start + 24 * row + (7 - col) * 3 + 2);
            color_buffer[row][col].g = *(&_binary_image_raw_start + 24 * row + (7 - col) * 3 + 1);
            color_buffer[row][col].r = *(&_binary_image_raw_start + 24 * row + (7 - col) * 3);
        }
    }
}

void show(rgb_color color_buffer[8][8]) 
{
    //envoie le color_buffer au DM163
    while (1)
    {
        for (int row = 0; row < 8; row++)
        {
            mat_set_row(row, color_buffer[row]);
        }
    }
}

void test_pixels()
{
    int rgb[3];
    rgb_color color_buffer[8][8];

    for (int step = 0; step < 88; step++)
    {
        //prepare le color_buffer avant d'envoyer les valeurs au DM163
        for (int row = step; row < step + 3; row++)
        {
            erase(rgb);
            rgb[(row - step) % 3] = 1; //choisit la couleur rouge, vert ou bleu

            //cree un degrade de la couleur choisie et stocke les valeurs dans color_buffer
            for (int col = 0; col < 8; col++)
            {
                color_buffer_set_pixel(&color_buffer[row % 8][col], rgb);
                add_luminosity(rgb);
            }
        }

        //envoie le color_buffer au DM163
        for (int time = 0; time < 100; time++)
        {
            for (int row = step; row < step + 3; row++)
            {
                mat_set_row(row % 8, color_buffer[row % 8]);
            }
        }
        deactivate_rows();
    }
}

static void erase(int rgb[3])
{
    for (int step = 0; step < 3; step++)
    {
        rgb[step] = 0;
    }
}

static void color_buffer_set_pixel(rgb_color *color, int rgb[3])
{

    color->r = rgb[0] & 0xFF;
    color->g = rgb[1] & 0xFF;
    color->b = rgb[2] & 0xFF;
}

static void add_luminosity(int rgb[3])
{
    for (int step = 0; step < 3; step++)
    {
        rgb[step] = 2 * rgb[step];
    }
}

static void mat_set_row(int row, const rgb_color line[8])
{
    // chaque colonne a une couleur
    for (int col = 0; col < 8; col++)
    {
        send_byte(line[col].b, 1);
        send_byte(line[col].g, 1);
        send_byte(line[col].r, 1);
    }
    deactivate_rows();
    delay(10);
    pulse_LAT();

    activate_row(row);
}