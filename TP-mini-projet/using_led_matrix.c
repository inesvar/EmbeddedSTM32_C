#include "using_led_matrix.h"

static void mat_set_row(int row, const rgb_color line[8]);

void show() 
{
    //envoie le color_buffer au DM163 
    for (int row = 0; row < 8; row++)
    {
        mat_set_row(row, image_on_matrix[row]);
    }
}

void update_image_on_matrix(uint8_t octet) {
    static int update_position = 0;
    if (octet == 0xFF) {
        update_position = 0;
        return;
    }
    int row = update_position/24;
    int col = 7 - (update_position%24)/3;
    switch (update_position%3) {
        case 0:
            image_on_matrix[row][col].r = octet;
            break;
        case 1:
            image_on_matrix[row][col].g = octet;
            break;
        case 2:
            image_on_matrix[row][col].b = octet;
    }
    update_position = (update_position + 1)%192;
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
    delay(70);
    pulse_LAT();

    activate_row(row);
}
