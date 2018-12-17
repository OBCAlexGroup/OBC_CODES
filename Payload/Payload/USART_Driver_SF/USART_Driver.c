#include <USART_Driver.h>
#include <stm32f10x.h>

void USART_INIT (void)
{
   //enable the clock for the USART
   RCC ->APB2ENR |=RCC_APB2ENR_USART1EN;
   //enable the GPIO clock for PORTA
   RCC ->APB2ENR |=RCC_APB2ENR_IOPAEN;
   //enable the alternative function enable
   RCC ->APB2ENR |=RCC_APB2ENR_AFIOEN;
   //select no remapping for pins
   AFIO ->MAPR &=~(AFIO_MAPR_USART1_REMAP);
   //set PA9 (TX PIN) as output push and pull
   GPIOA ->CRH |=GPIO_CRH_CNF9_1;
   GPIOA ->CRH |=GPIO_CRH_MODE9_0;
   //set PA10(RX PIN)as input floating
   GPIOA ->CRH |=GPIO_CRH_CNF10;
   GPIOA ->CRH |=GPIO_CRH_MODE10;
   //disable the USART
   USART1 ->CR1 &=~(USART_CR1_UE);
   //baud rate calculation for USART1 fclk = 72MHZ
   //baud rate 96000
   //BRR value will be equal to 468.75
   USART1 ->BRR = (USART_BRR_DIV_Mantissa |468)&(USART_BRR_DIV_Fraction |1200);
   //enable the USART
   USART1 ->CR1 |=(USART_CR1_UE);
   //the M bit word selection 8bits data
   USART1 ->CR1 &=~(USART_CR1_M);
   //select one stop bit
   USART1 ->CR2 &=~(USART_CR2_STOP);
   //Transmitter enable
   USART1 ->CR1 |=USART_CR1_TE;
   	//receiver enable
   USART1 ->CR1 |=USART_CR1_RE;

}

void USART_SEND_DATA (const u16 data)
{
	USART1->DR = data;
	//polling until the complete transission bit is enabled
	while(USART1 ->SR &=~USART_SR_TXE){}

}

u16 USART_RECEIVE_DATA (void)
{
   while(USART1->SR |= USART_SR_RXNE){}
   return((USART1 -> DR )& 0xFF);
}
