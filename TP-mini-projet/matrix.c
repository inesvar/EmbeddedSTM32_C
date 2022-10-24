#include "stm32l4xx.h"
#include "matrix.h"
#include "matrix_init_private.h"

void matrix_init() {
    //on allume l'horloge des ports A, B et C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    
    //on configure les broches PA2,3,4,5,6,7,15 en mode sortie (01)
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) | (1 << GPIO_MODER_MODE2_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_Msk) | (1 << GPIO_MODER_MODE3_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_Msk) | (1 << GPIO_MODER_MODE4_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_Msk) | (1 << GPIO_MODER_MODE5_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_Msk) | (1 << GPIO_MODER_MODE6_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_Msk) | (1 << GPIO_MODER_MODE7_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) | (1 << GPIO_MODER_MODE15_Pos);

    //on configure les broches PA2,3,4,5,6,7,15 en très haute vitesse (11)
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) | (3 << GPIO_OSPEEDR_OSPEED2_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk) | (3 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4_Msk) | (3 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5_Msk) | (3 << GPIO_OSPEEDR_OSPEED5_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED6_Msk) | (3 << GPIO_OSPEEDR_OSPEED6_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED7_Msk) | (3 << GPIO_OSPEEDR_OSPEED7_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED15_Msk) | (3 << GPIO_OSPEEDR_OSPEED15_Pos);

    //on configure les broches PB0,1,2 en mode sortie (01)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk) | (1 << GPIO_MODER_MODE0_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_Msk) | (1 << GPIO_MODER_MODE1_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_Msk) | (1 << GPIO_MODER_MODE2_Pos);

    //on configure les broches PB0,1,2 en très haute vitesse (11)
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0_Msk) | (3 << GPIO_OSPEEDR_OSPEED0_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED1_Msk) | (3 << GPIO_OSPEEDR_OSPEED1_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) | (3 << GPIO_OSPEEDR_OSPEED2_Pos);

    //on configure les broches PC3,4,5 en mode sortie (01)
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_Msk) | (1 << GPIO_MODER_MODE3_Pos);
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4_Msk) | (1 << GPIO_MODER_MODE4_Pos);
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5_Msk) | (1 << GPIO_MODER_MODE5_Pos);

    //on configure les broches PC3,4,5 en très haute vitesse (11)
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk) | (3 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4_Msk) | (3 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5_Msk) | (3 << GPIO_OSPEEDR_OSPEED5_Pos);

    //reset le DM163
    RST(0);

    //place les autres broches a des valeurs initiales acceptables
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);

    //eteindre toutes les lignes : C0 a C7 a 0
    deactivate_rows();

    delay(10000000);
    //this delay lasts approximately a second

    //repasse RST a l'etat haut
    RST(1);

    init_bank0();
}

void send_byte(uint8_t val, int bank) {
    SB(bank);
    uint8_t nb_bits = bank ? 8 : 6;
    for (int led = nb_bits -1 ; led >= 0 ; led--) {
        uint8_t bit = (val >> (led)) & 0x1;
        SDA(bit);
        delay(1);
        pulse_SCK();
    }
}

void pulse_SCK() {
    // 25 ns * 80MHz = 2, on met 3 par securite
    SCK(0);
    delay(2);
    SCK(1);
    delay(2);
    SCK(0);
    delay(2);
}

void pulse_LAT() {
    // 25 ns * 80MHz = 2, on met 3 par securite
    LAT(1);
    delay(2);
    LAT(0);
    delay(2);
    LAT(1);
    delay(2);
}

void delay(int n) {
    for (int i=0; i< n ; i++) {
            asm volatile("nop");
    }  
}

void deactivate_rows() {
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row) {
    switch (row) {
        case 0 :
            ROW0(1);
            break;
        case 1 :
            ROW1(1);
            break; 
        case 2 :
            ROW2(1);
            break;
        case 3 :
            ROW3(1);
            break;
        case 4 :
            ROW4(1);
            break;
        case 5 :
            ROW5(1);
            break;
        case 6 :
            ROW6(1);
            break;
        case 7 :
            ROW7(1);
            break;
    }
}

static void init_bank0() {
    for (int led = 0 ; led < 24 ; led++) {
        send_byte(63,0);
    }
    delay(1);
    pulse_LAT();
}

static void RST(int BIT) {
    if (BIT) {
        GPIOC->BSRR |= GPIO_BSRR_BS3;
    } else {
        GPIOC->BSRR |= GPIO_BSRR_BR3;
    }
} 

static void SB(int BIT) {
    if (BIT) {
        GPIOC->BSRR |= GPIO_BSRR_BS5;
    } else {
        GPIOC->BSRR |= GPIO_BSRR_BR5;
    }
}     

static void LAT(int BIT) {
    if (BIT) {
        GPIOC->BSRR |= GPIO_BSRR_BS4;
    } else {
        GPIOC->BSRR |= GPIO_BSRR_BR4;
    }
}

static void SCK(int BIT) {
    if (BIT) {
        GPIOB->BSRR |= GPIO_BSRR_BS1;
    } else {
        GPIOB->BSRR |= GPIO_BSRR_BR1;
    }
}

static void SDA(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS4;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR4;
    }
}

static void ROW0(int BIT) {
    if (BIT) {
        GPIOB->BSRR |= GPIO_BSRR_BS2;
    } else {
        GPIOB->BSRR |= GPIO_BSRR_BR2;
    }
}

static void ROW1(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS15;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR15;
    }
}

static void ROW2(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS2;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR2;
    }
}

static void ROW3(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS7;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR7;
    }
}

static void ROW4(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS6;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR6;
    }
}

static void ROW5(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS5;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR5;
    }
}

static void ROW6(int BIT) {
    if (BIT) {
        GPIOB->BSRR |= GPIO_BSRR_BS0;
    } else {
        GPIOB->BSRR |= GPIO_BSRR_BR0;
    }
}

static void ROW7(int BIT) {
    if (BIT) {
        GPIOA->BSRR |= GPIO_BSRR_BS3;
    } else {
        GPIOA->BSRR |= GPIO_BSRR_BR3;
    }
}
