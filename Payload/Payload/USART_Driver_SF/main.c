#include <USART_Driver.h>

int main(void)
{

	void WaitAmoment(int moment)
	{
		//volatile int j;
	 while ( moment>0)
	 {
		 moment--;
	 }
	}

    USART_INIT ();
    while(1)
    {
    	USART_SEND_DATA(100);
    	WaitAmoment(1000);
    	USART_RECEIVE_DATA();
    	WaitAmoment(1000);
    }
}
