#ifndef __SPI_H
#define __SPI_H


void GPIO_M_init(void);
void GPIO_S_init(void);
void SPI1_M_init(void);
void SPI1_S_init(void);
void SPI1_M_TX(char x);
void SPI1_M_RX(char* x);
void SPI1_S_TX(char x);
void SPI1_S_RX(char x);
void LED_ON(void);
void LED_OFF(void);

#endif
