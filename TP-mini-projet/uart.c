#include "stm32l4xx.h"
#include "uart.h"
#include "using_led_matrix.h"


void uart_init(int baudrate)
{
    //on allume l'horloge du port B
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    
    //on va utiliser AF7(0111) pour les broches 6 et 7
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk) | (0x7 << GPIO_AFRL_AFSEL7_Pos);
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk) | (0x7 << GPIO_AFRL_AFSEL6_Pos);

    //on va avoir B6 TX et B7 RX, on configure les broches en AF(10)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk) | (2 << GPIO_MODER_MODE6_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk) | (2 << GPIO_MODER_MODE7_Pos);
    
    //Activer l'horloge du port serie USART1.
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  

    //PCLK horologe de USART1 : (00) dans USART1SEL
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;

    //reset du port serie 
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
    
    //Configurer la vitesse du port serie a baudrate bauds
    USART1->BRR = (80000000/baudrate);  
    
    //configurer l'oversampling a 16 : bit a 0
    USART1->CR1 &= ~USART_CR1_OVER8;
    
    /* mettre le port serie en mode 8N1 */

    //trames de 8 bits : (00) dans M
    USART1->CR1 &= ~USART_CR1_M;
    //pas de controle de parite : (0) dans PCE
    USART1->CR1 &= ~USART_CR1_PCE;
    //un bit de stop : (00) dans STOP
    USART1->CR2 &= ~USART_CR2_STOP;

    //autorise l'interruption si un octet est reçu (si RXNE vaut 1)
    USART1->CR1 |= USART_CR1_RXNEIE;

    //autoriser l'interruption USART1
    NVIC_EnableIRQ(37);

    //Activer l'USART1, le transmetteur et le recepteur
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    
}

void USART1_IRQHandler() {
    //lit dans le RDR
    uint8_t image_octet = 0xFF & (USART1->RDR & USART_RDR_RDR_Msk);
    update_image_on_matrix(image_octet);
}


