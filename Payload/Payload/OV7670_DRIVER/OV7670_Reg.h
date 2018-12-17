#ifndef OV7670_Reg
#define OV7670_Reg

#define WR_address 0x42
#define RD_address 0x43

#define QVGA_RGB565 0
#define QVQA_YUV    1
#define CIF_RGB565  2
#define CIF_YUV     3

typedef unsigned char         u8;

/*FORMAT AND MODES SELECTION */
#define COM7_RESET_MODES        *((volatile u8*)0x80) /*reset all the registers to its default values*/
#define COM7_QVGA_RGB565        *((volatile u8*)0x14)   /*select QVGA mode ,RGB565 */
#define COM7_QVGA_YUV           *((volatile u8*)0x10)   /*select QVGA mode ,YUV*/
#define COM7_CIF_RGB565         *((volatile u8*)0x24)  /*select CIF mode ,RGB565*/
#define COM7_CIF_YUV            *((volatile u8*)0x20)   /*select CIF mode ,YUV*/
#define COM15                   *((volatile u8*)0x40)   /*RGB type selection*/

#define COM15_RGB_MODE_NORMAL    0xC0   /*normal RGB mode*/
#define COM15_RGB_MODE_565       0xD0   /*RGB565 mode*/
#define COM15_RGB_MODE_555       0xF0   /*RGB555 mode*/

/*HARDWARE WINDOW */
#define VREF                    *((volatile u8*)0x0A)   /*vertical reference*/
#define VSTART                  *((volatile u8*)0x19)   /*vertical start*/
#define VSTOP                   *((volatile u8*)0x1A)   /*vertical stop*/
#define HREF                    *((volatile u8*)0x80)   /*horizontal reference*/
#define HSTART                  *((volatile u8*)0x17)   /*horizontal start*/
#define HSTOP                   *((volatile u8*)0x18)   /*vertical start*/
#define COM2_SLEEP_MODE         *((volatile u8*)0x09)   /*sleep mode selection*/
#define CLKRC                   *((volatile u8*)0x11)   /*clock selection (set max frequency value)*/
#define COM10                   *((volatile u8*)0x15)   /*VSYNC selection on falling edge or rising*/
#define PSHIFT                  *((volatile u8*)0x1B)   /*data format pixel delay*/

/*brightness , contras and lens correction*/
#define BRIGHT                  *((volatile u8*)0x55)
#define CONTRAS                 *((volatile u8*)0x56)
#define LCCS                    *((volatile u8*)0x66)   /*lens correction control */
#define REG76                   *((volatile u8*)0x76)   /*white color pixel correction and enable*/

/*scaling numbers settings*/
#define SCALING_XSC             *((volatile u8*)0x70)
#define SCALING_YSC             *((volatile u8*)0x71)
#define SCALING_PCLK_DCWTR      *((volatile u8*)0x72)
#define SCALING_PCLK_DIV        *((volatile u8*)0x73)

/*OTHER REGISTERES*/
#define COM11                   *((volatile u8*)0x3B)
#define RES_REG                 *((volatile u8*)0xA2)


void OV7670_INIT(void);
void OV7670_QVGA_RGB_565(void);
void OV7670_QVGA_YUV(void);
void OV7670_CIF_RGB_565(void);
void OV7670_CIF_YUV(void);
void OV7670_REST_REG (void);


#endif

