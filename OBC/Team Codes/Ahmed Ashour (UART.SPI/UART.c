#include "stm32f10x.h"
#include "UART.h"


void USART_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN ;    // USART1 clock enable

	USART1->CR1 &= ~(1<<12);   // 8 data bits
	USART1->CR2 &= ~(3<<12);   // 1 stop bit
	USART1->BRR = 0x1d4c;      // baud rate = 9600
	USART1->CR1 |= (1<<7) ;    // transmit interrupt enable
	USART1->CR1 |= (1<<6) ;    // transmit complete interrupt enable
	USART1->CR3 |= (1<<0) ;    // Error interrupt enable

	USART1->CR1 |= (1<<3) ;     // transmit enable
	USART1->CR1 |= (1<<2) ;     // receive enable
	USART1->CR1 |= (1<<13);    // UART enable



}

void USART_GPIO_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ;   // port A clock enable
	//RCC->APB2ENR |=RCC_APB2ENR_AFIOEN ;

	GPIOA->CRH |= GPIO_CRH_MODE9 ;
	GPIOA->CRH |= GPIO_CRH_CNF9_1 ;     //  port A pin 9 (TX1)(Alternate function output Push-pull(50MHZ))

	GPIOA->CRH &= ~(GPIO_CRH_MODE10) ;
	GPIOA->CRH |= GPIO_CRH_CNF10_0 ;     //  port A pin 10 (RX1) (input floating)

}

void USART_TX(char x)
{

	while(!(((USART1->SR & (1<<7))>>7))){}

	USART1->DR = x ;

	while(!((USART1->SR & (1<<6))>>6)){}

}
void USART_TX_String(char *x)
{
 while(*x != '\0')
 {
	while(!(((USART1->SR & (1<<7))>>7)));
	USART1->DR = *x;
	x++;
	while(!((USART1->SR & (1<<6))>>6));
		//USART1->DR = x;
 }
}
char USART_RX(void)
{
	while(!((USART1->SR & (1<<5))>>5)){}
	return (USART1->DR) ;
}

void USART1_IRQHandler(void)
{
	if(getbit((USART1->SR),7)==1){
	USART1->DR = 0x55 ;
	LED_ON();

	}else if (getbit((USART1->SR),6)==1) {

		 USART1->CR1 &= ~(1<<13);    // UART disable
		// LED_OFF();
	}else if (getbit((USART1->SR),3)==1){
		LED_OFF();
	}


	}




void LED_ON(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; /// enable clock for GPIO_C
	GPIOC->CRH &=~ GPIO_CRH_CNF13 ;
    GPIOC->CRH |= GPIO_CRH_MODE13_0 ;
    GPIOC->BSRR &=~(1<<13) ;
	}

void LED_OFF(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; /// enable clock for GPIO_C
	GPIOC->CRH &=~ GPIO_CRH_CNF13 ;
    GPIOC->CRH |= GPIO_CRH_MODE13_0 ;
    GPIOC->BSRR |=(1<<13) ;
}


