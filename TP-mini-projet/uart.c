#include "stm32l4xx.h"
//#include "stm32l475.h"


void uart_init()
{
    //on allume l'horloge du port B
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    //on va avoir B6 TX et B7 RX, on configure les broches en AF(10)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODE6_1;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODE7_1;
    
    //on va utiliser AF7(0111) pour les broches 6 et 7
    GPIOB->AFRL = GPIOB->AFRL & (GPIO_AFRL_AFSEL7 & ~GPIO_AFRL_AFSEL7_0);
    GPIOB->AFRL = GPIOB->AFRL & (GPIO_AFRL_AFSEL6 & ~GPIO_AFRL_AFSEL6_0);
    
    //Activer l'horloge du port série USART1.
    //Spécifier que l'horloge sur laquelle se base l'USART1 pour timer chaque bit est PCLK : registre RCC->CCIPR.
    //Faire un reset du port série par précaution : registre RCC->APB2RSTR.
    
    //Configurer la vitesse du port série à 115200 bauds
    //mettre 2b6 dans USARTDIV
    USART1->BRR = (USART1->BRR & ~USART1_BRR_DIV_FRACTION_Msk) | (6 << USART1_BRR_DIV_FRACTION_Pos);
    
    
    //configurer l'oversampling à 16 : bit a 0
    USART1->CR1 = USART1->CR1 & ~USART_CR1_OVER8;
    
    
    //il faut un clock output heeein
    
    /* mettre le port série en mode 8N1 */
    
    //trames de 8 bits : (00) dans M
    USART1->CR1 = USART1->CR1 & ~USART_CR1_M;
    //pas de controle de parité : (0) dans PCE
    USART1->CR1 = USART1->CR1 & ~USART_CR1_PCE;
    //un bit de stop : (00) dans STOP
    USART1->CR2 = USART1->CR2 & ~USART_CR2_STOP;

    //Activer l'USART1, le transmetteur et le récepteur
    USART1->CR1 |= USART_CR1_UE;
    
}