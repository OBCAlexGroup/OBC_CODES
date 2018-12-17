#ifndef __UART_H
#define __UART_H

#define getbit(x,bitnum) (x &(1<<bitnum))>>bitnum

void USART_init(void);
void USART_GPIO_init(void);
void USART_TX(char x);
char USART_RX(void);
void LED_ON(void);
void LED_OFF(void);




#endif
