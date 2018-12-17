#include <OV7670_Reg.h>


void OV7670_INIT(void)
{    /*reseting all registers to its default values*/
	 COM7_RESET_MODES |=(0x80);

}

void OV7670_QVGA_RGB_565(void)
{   /*QVGA FORMAT AND RGB MODE*/
	COM7_RESET_MODES |= (COM7_QVGA_RGB565) ;
	/*RGB565 SELECION*/
	COM15 |= (COM15_RGB_MODE_565);
	/*COLOR MODE*/
	//NOT FOUNDED IN ORIGINAL DATASHEET AS ITS RESERVED BUT ADDING
	//IN THE APLLICATION NOTES
}
void OV7670_QVGA_YUV(void)
{
	/*QVGA FORMAT AND YUV MODE*/
	COM7_RESET_MODES |= COM7_QVGA_YUV;
	/*YUV SELECION SO MAKE RGB AS NORMAL*/
	COM15 |= COM15_RGB_MODE_NORMAL ;
}
void OV7670_CIF_RGB_565(void)
{
	/*CIF FORMAT AND RGB565 MODE*/
	COM7_RESET_MODES |= COM7_CIF_RGB565;
	/*RGB565 SELECION*/
	COM15 |= COM15_RGB_MODE_565;
}

void OV7670_CIF_YUV(void)
{
	/*CIF FORMAT AND RGB565 MODE*/
	COM7_RESET_MODES |= COM7_CIF_YUV ;
	/*YUV SELECION SO MAKE RGB AS NORMAL*/
	COM15 |= COM15_RGB_MODE_NORMAL ;
}

void OV7670_CONFIGURATION(void)
{
	/*hardware window*/
   /*select max output frequency of 24MHZ*/
	CLKRC |= 0x01;
	HREF |= 0x80;
	HSTOP |= 0x05;
	VREF |= 0x0A;
	VSTART |= 0x02;
	VSTOP |= 0x7A;

	/*scaling numbers*/
	SCALING_XSC |= 0x3A;/*for no o/p selection if not try 0x4A*/
	SCALING_YSC |= 0x35;
	SCALING_PCLK_DCWTR |= 0x11;
	/*clock divider control*/
	/*selected divided by 4*/
	/*for 2(0x01),8(0x03),16(0x04)*/
	SCALING_PCLK_DIV |= 0x02;

}
void OV7670_REST_REG (void)
{
    COM10 |= 0x00;
    RES_REG |=0x02;
}
