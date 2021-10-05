#include "main.h"

int main(void)
{	
	uint8_t c = 0;
	USARTx_Init(USART1,Pins_PA9PA10,9600);
	while(1)
	{
		c = USART_Getc(USART1);
		if(c) USART_Putc(USART1,c);
	}
}

 

