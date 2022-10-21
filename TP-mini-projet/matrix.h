typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;


void matrix_init();

void RST(int BIT);
void SB(int BIT);
void LAT(int BIT);
void SCK(int BIT);
void SDA(int BIT);

void ROW0(int BIT);
void ROW1(int BIT);
void ROW2(int BIT);
void ROW3(int BIT);
void ROW4(int BIT);
void ROW5(int BIT);
void ROW6(int BIT);
void ROW7(int BIT);

void delay(int n);
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val, int bank);
void mat_set_row(int row, const rgb_color *val);
void init_bank0();
void test();


void set_rgb_vector(rgb_color * color, int r, int g, int b);

void add_luminosity(int * i);

void mat_set_shaded_columns(int r, int g, int b);
void set_zero_color(int * rgb);



