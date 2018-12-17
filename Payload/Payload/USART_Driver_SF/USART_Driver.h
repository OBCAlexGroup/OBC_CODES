
#ifndef USART_Driver
#define USART_Driver

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

void USART_INIT (void);
void USART_SEND_DATA(const u16 data);
u16 USART_RECEIVE_DATA (void);
#endif


