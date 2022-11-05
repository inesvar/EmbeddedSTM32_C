enum State {LED_OFF, LED_YELLOW, LED_BLUE};
enum State state;

void led_g_on();
void led_g_off();
void led_init();
void led(enum State state);