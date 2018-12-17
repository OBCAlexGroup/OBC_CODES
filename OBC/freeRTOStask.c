#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stm32f10x.h"

void vTask1( void *pvParameters )
{
 const char *pcTaskName = "Task 1 is running\n";
 for(;;)
 {
	  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; /// enable clock for GPIO_C
	  GPIOC->CRH &=~ GPIO_CRH_CNF13 ;
	  GPIOC->CRH |= GPIO_CRH_MODE13_0 ;
	  GPIOC->BSRR &=~(1<<13) ;
	  GPIOC->BSRR |= (1<<29) ;

 }

}
void vTask2( void *pvParameters )
{
 const char *pcTaskName = "Task 2 is running\n";
 for(;;)
 {
	 int x = 0 ;
	 x = 243;
 }

}
void vTask3( void *pvParameters )
{
 const char *pcTaskName = "Task 3 is running\n";
 for(;;)
 {
	 int x = 0 ;
	 x = 243;


 }

}
void vTask4( void *pvParameters )
{
 const char *pcTaskName = "Task 4 is running\n";
 for(;;)
 {

	 int x = 0 ;
	 x = 243;

 }

}
void vTask5( void *pvParameters )
{
 const char *pcTaskName = "Task 5 is running\n";
 for(;;)
 {
	  int x = 0 ;
	  x = 243;

 }

}
