#include "SPI.h"
#include "UART.h"
#include "stm32f10x.h"
/////////////////////////FATAL WARNING : don't enable CLOCK of anything twice//////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////WARNING NEEDS OPTIMIZATION////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
char TX_G_variable ;
extern char flag ;
extern char RX_G_variable ;
extern char t ;
char j,i = 0 ;
int y, x  ;

/////////////////////////////////WARNING CHANGE THIS GPIO INIZALIZATION WITH HAL DRIVER GPIO_i2c....
/////////////////////////////////WARNING CHANGE THIS GPIO INIZALIZATION WITH HAL DRIVER GPIO_i2c....
void GPIO_M_init(void)
{
	RCC->APB2RSTR |= RCC_APB2ENR_IOPAEN;      // port A clock enable

	GPIOA->CRL |= GPIO_CRL_MODE5;
	GPIOA->CRL |= GPIO_CRL_CNF5_1;            // port A pin 5 (CLK) (Alternate function push pull (50MHz))

	GPIOA->CRL |= GPIO_CRL_MODE7;
	GPIOA->CRL |= GPIO_CRL_CNF7_1;            // port A pin 7(MOSI)   (Alternate function push pull (50MHz))

	GPIOA->CRL |= (GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_1;            // port A pin 6 (MISO)   (Alternate function push pull (50MHz))

    GPIOA->CRL |= GPIO_CRL_MODE4;
   // GPIOA->CRL &= ~(GPIO_CRL_CNF4);            // port A pin 4 (CS)      (output push pull (50MHz))
}
/////////////////////////////////WARNING CHANGE THIS GPIO INIZALIZATION WITH HAL DRIVER GPIO_i2c....
/////////////////////////////////WARNING CHANGE THIS GPIO INIZALIZATION WITH HAL DRIVER GPIO_i2c....

void GPIO_S_init(void)
{
	//RCC->APB2RSTR |= RCC_APB2ENR_IOPAEN;    // port A clock enable

	GPIOA->CRL |= GPIO_CRL_MODE6;
	GPIOA->CRL |= GPIO_CRL_CNF6_1;            // port A pin 6 (SO) (Alternate function push pull(50MHZ))

	GPIOA->CRL |= GPIO_CRL_MODE5;
	GPIOA->CRL |= GPIO_CRL_CNF5_1;            // port A pin 5 (CLK)  (Alternate function push pull (50MHz))

	GPIOA->CRL |= GPIO_CRL_MODE7;
	GPIOA->CRL |= GPIO_CRL_CNF7_1;            // port A pin 7 (SI)      (Alternate function push pull (50MHz))

	GPIOA->CRL &= ~(GPIO_CRL_MODE4);
	GPIOA->CRL |= GPIO_CRL_CNF4_0;            // port A pin 4 (CS)  (input  pull up /pull down (50MHz)

}



// master configuration

void SPI1_M_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;  // clock for SPI 1

	SPI1->CR1 |= (1<<5);          // Baud Rate at Fcpu/128
	SPI1->CR1 |= (1<<4);

	SPI1->CR1 |= (1<<0) ;         // clock phase (toggle then sample), clock polarity (low level when idle)
	SPI1->CR1 |= (1<<1) ;

	SPI1->CR1 &= ~(1<<11);        // 8 bit data mode
	SPI1->CR1 &=~ (1<<15);        // full-duplex mode enable

	SPI1->CR1 &= ~(1<<7);         // MSB will be transmitted first

	SPI1->CR1 |= (1<<9);          //  set SSM bit (slave select (software mode))
	SPI1->CR1 |= (1<<8);          //  set SSI bit

	SPI1->CR1 |= (1<<2);          // master mode select

	SPI1->CR1 |= (1<<6);          // SPI enable

	GPIOA->BSRR |= (1<<4);      //  CS High (slave disable)

	}


// slave configuration

void SPI1_S_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;  // clock for SPI 1


	SPI1->CR1 |= (1<<0) ;         // clock phase (toggle then sample), clock polarity (low level when idle)
	SPI1->CR1 |= (1<<1) ;

	SPI1->CR1 &= ~(1<<11);        // 8 bit data mode
    SPI1->CR1 &=~ (1<<15);        // full-duplex mode enable

	SPI1->CR1 &= ~(1<<7);         // MSB will be transmitted first

	SPI1->CR1 |= (1<<9);          //  set SSM bit (slave select (hardware mode))
	SPI1->CR2 &= ~(1<<8);         //  clear SSI bit

	SPI1->CR1 &= ~(1<<2);         // slave mode select

	//SPI1->CR2 &= ~(1<<7);       // Tx buffer empty interrupt enable
	SPI1->CR2 |= (1<<6);          // Rx buffer not empty interrupt enable
	//SPI1->CR2 &= ~(1<<5);       // error interrupt enable

	SPI1->CR1 |= (1<<6);          // SPI enable


	}


// master transmit

void SPI1_M_TX(char x)
{
	j = 1 ;

	GPIOA->BRR |= (1<<4);      //  CS low (slave enable)

	SPI1->DR |= x ;

	while((((SPI1->SR)&(1<<1))>>1)==0){}

	while((((SPI1->SR)&(1<<7))>>7)==1){}

	LED_ON();

	GPIOA->BSRR |= (1<<4);      //  CS High (slave disable)



	}


// master receive

void SPI1_M_RX(char* x)
{
	SPI1->CR1 &= ~(1<<14);      // Receive only mode
	SPI1->CR1 |= (1<<6);       // SPI enable
    RX_G_variable = x ;
     j = 2 ;

	}


// slave transmit

void SPI1_S_TX(char x)
{
	j = 1 ;
	SPI1->CR1 |= (1<<14);      // Transmit only mode
	SPI1->CR1 |= (1<<6);       // SPI enable
	TX_G_variable = x ;


	}



// slave receive

void SPI1_S_RX(char x)
{
    j = 2;
    //RX_G_variable = x ;

	}



void SPI1_IRQHandler(void)
{
	//LED_ON();
	if ((((SPI1->SR)&(1<<1))>>1)==1){

	   //LED_ON();

    }else if((((SPI1->SR)&(1<<0))>>0)==1){
	  // LED_ON();
    }else if((((SPI1->SR)&(1<<7)>>7))==1){
	  // LED_ON();
}
    if(j==1){

	    SPI1->DR = TX_G_variable ;

	}else if(j==2){
		//LED_ON();
	RX_G_variable = SPI1->DR;
if(RX_G_variable=='K')
{
	LED_ON();
}



	}

}

