#include "stm32f10x.h"


#define WAITING_START_BIT    (((I2C1->SR1)  & (1<<0)) >> 0 )  //SB is set
#define WAITING_ACK          (((I2C1->SR1)  & (1<<7)) >> 7 )
#define WAITING_ADDR_SENDING (((I2C1->SR1)  & (1<<1)) >> 1 )
#define SUCCESSFUL_SENDING_or_RECEVING_BYTE (((I2C1->SR1)  & (1<<2)) >> 2 )
#define DATA_R_NOT_EMPTY     (((I2C1->SR1)  & (1<<6)) >> 6 )
#define BUS_ERROR            (((I2C1->SR1)  & (1<<8)) >> 8 )
#define ARBITERATION_LOSS    (((I2C1->SR1)  & (1<<9)) >> 9 )
#define ACK_FAILURE          (((I2C1->SR1)  & (1<<10)) >> 10 )
#define OVERRUN_UNDERRUN     (((I2C1->SR1)  & (1<<11)) >> 11)
#define TIME_OUT             (((I2C1->SR1)  & (1<<14)) >> 14 )
#define BUSY_BUS             (((I2C1->SR2)  & (1<<1)) >> 1)



void I2C1_EV_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
void I2C_enable (void);
void select_master_transmiter (void);
void select_slave_transmiter (void);
void select_master_reciver (void);
void select_slave_reciver (void);
