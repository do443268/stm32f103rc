#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "led_button.h"
void Delay(unsigned int tick);
int main(void)
{
	LedInit();
	ButtonInit();
  if(!GPIO_ReadInputDataBit(BUTTONPORT,BUTTON1))
  {
	  GPIO_SetBits(LEDPORT,LED1);
		Delay(0xFFFFF);
		GPIO_ResetBits(LEDPORT,LED1);
		Delay(0xFFFFF);
	}
  if(!GPIO_ReadInputDataBit(BUTTONPORT,BUTTON2))
  {
	  GPIO_SetBits(LEDPORT,LED2);
		Delay(0xFFFFF);
		GPIO_ResetBits(LEDPORT,LED2);
		Delay(0xFFFFF);
	}		
  if(!GPIO_ReadInputDataBit(BUTTONPORT,BUTTON3))
  {
	  GPIO_SetBits(LEDPORT_1,LED3);
		Delay(0xFFFFF);
		GPIO_ResetBits(LEDPORT_1,LED3);
		Delay(0xFFFFF);
	}	
  if(!GPIO_ReadInputDataBit(BUTTONPORT,BUTTON4))
  {
	  GPIO_SetBits(LEDPORT_1,LED4);
		Delay(0xFFFFF);
		GPIO_ResetBits(LEDPORT_1,LED4);
		Delay(0xFFFFF);
	}			
}
void Delay(unsigned int tick)
{
	while(tick) tick--;
}