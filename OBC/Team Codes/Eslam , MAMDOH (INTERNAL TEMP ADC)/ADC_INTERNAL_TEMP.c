#include"stm32f10x.h"

void initADC();
uint32_t getADCTempValue();

void initADC()
{
    RCC->APB2ENR |= (1<<9);      //Enable ADC1 Clock
    RCC->CFGR |= (0b10<<14);     //set ADC Prescaler '6'
    ADC1->CR1 |= (1<<4);         //Analog Watchdog Channel 16
    ADC1->SQR3 |=(0<<0);         //
    ADC1->SMPR1 |= (0b100<<18);  //41.5 cycles sample time (total time 4.5us)
    ADC1->CR2 |= (1<<23);        //Enable Temperature Sensor & Vref

    ADC1->CR2 |= (1<<0);         //Enable ADC and start conversion

    ADC1->CR2 |= (1<<3);         //Initialize calibration register
    while(ADC1->CR2 & (1<<3));   //Wait until calibration register initialized



    ADC1->CR2 |= (1<<2);         //Enable calibration
    while(ADC1->CR2 & (1<<2));   //Wait until calibration completed

}

uint32_t getADCTempValue()
{
    ADC1->CR2 |= (1<<0);         //Enable ADC and start conversion
    while(!(ADC1->SR & (1<<1))); //Wait until end of conversion
    return ADC1->DR;
}
int main (void)
{
	initADC();
	uint32_t adcVal;
	while(1)
	{
		adcVal = getADCTempValue();
		float temp=adcVal*(3.3/4096);
		float temp1 =((1.43 -temp ) / 4.3 )+ 25.0;
	}
}
