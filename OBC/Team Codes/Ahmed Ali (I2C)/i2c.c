#include "i2c.h"
int datatobesent = 100;
int M_or_S = 0 ;   // M = 1 , S = 0
int MT_or_MR = 0 ; // MT = 1 , MR = 0
int ST_or_SR = 0 ; // ST = 1 , SR = 0
int datasent = 0 ;
int STM_ADDR = 9 ;
int NOT_STM_ADDR = 10 ;
int arduino_ADDR = 11 ;
int dumy = 0 ;
void  I2C1_EV_IRQHandler (void)
{


 if(M_or_S)
 {
     PC13_on_off(1);

	 if(MT_or_MR)
	 {
		if(WAITING_START_BIT)
		{
			dumy= I2C1->SR1 ;                              ///clear SB flag
        I2C1->DR = (NOT_STM_ADDR<<1) | (0);     /// sending address of slave and 0 indicates (0)--> write
        }
		else if(WAITING_ADDR_SENDING)
	    {
			dumy= I2C1->SR1 ;                              /// to  clear (ADDR) bit
			dumy=I2C1->SR2 ;                              /// to  clear (ADDR) bit
	     I2C1->DR = datatobesent;
	    }
	 }
     else
     {
	       if(WAITING_START_BIT)
	       {
	       I2C1->SR1 ;                              ///clear SB flag
	       I2C1->DR = (NOT_STM_ADDR<<1) | (1);     ///send device address and receive
	       }
	       else if(WAITING_ADDR_SENDING)
	 	   {
	 	    I2C1->SR1 ;                              /// to  clear (ADDR) bit
	 	    I2C1->SR2 ;                              /// to  clear (ADDR) bit
	 	    datasent = I2C1->DR ;                  /// read byte of data to device
	 	    ///controller sends ACK to transmiter
	 	   }
      }

}
 else
 {
   if(ST_or_SR)
   {

        if(WAITING_ADDR_SENDING)
	    {
	     I2C1->SR1 ;                              /// to  clear (ADDR) bit
	     I2C1->SR2 ;                              /// to  clear (ADDR) bit
	     I2C1->DR = datatobesent;                 /// send byte of data to device

	     //I2C1->CR1 |= (1<<9);                     ///generated stop transission
	    }
   }
   else
   {
	        if(WAITING_ADDR_SENDING)
	   	    {
	        	dumy=I2C1->SR1 ;                              /// to  clear (ADDR) bit
	        	dumy=I2C1->SR2 ;                              /// to  clear (ADDR) bit
	   	     for(int i = 0 ; i < 100;i++);
	   	     datatobesent = I2C1->DR  ;                 /// send byte of data to device
	   	     PC13_on_off(1);
	   	    }

   }
 }
}

void  I2C1_ER_IRQHandler(void)
{
	 PC13_on_off(1);
}
void I2C_enable (void)
{
	/*Clock enable and GPIO*/
    RCC->APB1ENR |= (1<<21) ;            /// enable clock for I2C1
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ; /// enable clock for GPIO_B
	RCC->APB2ENR |= (1<<0) ;             /// enable clock for AFIO
	GPIOB->CRL |= 0xEE000000 ;           /// open drain outputs
	AFIO->MAPR &=~(1<<1);                /// no mapping

	/*enable interrupt*/
	__enable_irq();                      ///enable global interrupt
	NVIC_EnableIRQ(31);                  ///enable event interrupt in NVIC
	NVIC_EnableIRQ(32);                  ///enable error interrupt in NVIC
	I2C1->CR2 |= (1<<8);                 ///enable peripheral error interrupt
	I2C1->CR2 |= (1<<9);                 ///enable peripheral event interrupt
	I2C1->CR2 |= (1<<10);                ///enable peripheral buffer interrupt

	/*i2c configuration*/
	I2C1->CR1 &=~ (1<<0);                ///disable i2c to make sure nothing goes wrong
	I2C1->CR1 &=~ (1<<7);                 ///disable clock stretching
    I2C1->CR1 |= (1<<6) ;                ///enable general call
	//I2C1->CR2 |= 0x1E ;                ///peripheral input clock = 36 MHZ
	I2C1->CR2 |= 0x8 ;                   ///peripheral input clock = 8 Mhz
	//I2C1->OAR1 |= (STM_ADDR<<1) ;    ///own address of OBC STM
	I2C1->OAR1 |= (NOT_STM_ADDR<<1) ;    ///own address of OBC STM
	I2C1->OAR1 &=~ (1<<15) ;             ///address 7 bit mode selected
	I2C1->OAR1 |= (1<<14) ;              ///should kept 1 by software
    I2C1->OAR2 &=~ (1<<0);               ///only OAR1 is used
	//I2C1->CCR |= 0x801E ;              ///peripheral clock is 36MHZ , duty cycle low/high = 2 , CCR = 30 decimal , FM mode , SCL FREQ= 400KHZ
	I2C1->CCR |= 0x28 ;                  ///peripheral clock is 36MHZ , duty cycle low/high = 2 , CCR = 30 decimal , FM mode , SCL FREQ= 400KHZ
	I2C1->CCR &=~ (1<<15) ;
    I2C1->CCR  &=~ (1<<14);
    //I2C1->TRISE = 0xA ;                ///max rise time
	I2C1->CR2 |= 0x8 ;                   ///max rise time
    I2C1->CR1 |= (1<<0);                 ///enable i2c
    I2C1->CR1 |= (1<<10);                ///enable I2C ACK


}
void select_master_transmiter (void)
{
	  M_or_S = 1 ;
	  MT_or_MR = 1 ;
      I2C1->CR1 |= (1<<8);             /// generate start bit

}
void select_master_reciver (void)
{
	  M_or_S = 1 ;
	  MT_or_MR = 0 ;
  I2C1->CR1 |= (1<<8);             /// generate start bit

}
void select_slave_transmiter (void)
{
	 I2C1->CR1 &=~ (1<<8);
	 M_or_S = 0 ;
	 ST_or_SR = 1 ;
}
void select_slave_reciver (void)
{
	 I2C1->CR1 &=~ (1<<8);
	 M_or_S = 0 ;
	 ST_or_SR = 0 ;
}
