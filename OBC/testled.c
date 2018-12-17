#include "stm32f10x.h"
void PC13_on_off (int x)
{

 RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; /// enable clock for GPIO_C
 GPIOC->CRH &=~ GPIO_CRH_CNF13 ;
 GPIOC->CRH |= GPIO_CRH_MODE13_0 ;
 if (x==0)
 {
 GPIOC->BSRR |= (1<<13) ;
 GPIOC->BSRR &=~ (1<<29) ;
 }
 else
 {GPIOC->BSRR &=~(1<<13) ;
 GPIOC->BSRR |= (1<<29) ;
 }
}
