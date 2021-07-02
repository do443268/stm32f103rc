#include "led_button.h"
void LedInit(void)
{ 
	RCC_APB2PeriphClockCmd(LEDPORTCLK|LEDPORTCLK_1,ENABLE);     //Cap xung CLOCK cho GPIOC va GPIOD
	GPIO_InitTypeDef GPIO_InitStructure; 
  GPIO_InitStructure.GPIO_Pin = LED1|LED2; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //Output, tro keo
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //Clock GPIO 50Mhz
  GPIO_Init(LEDPORT, &GPIO_InitStructure);                      //Cai dat GPIOC
 
 GPIO_InitStructure.GPIO_Pin = LED3|LED4;                      //Cai dat GPIOD
 GPIO_Init(LEDPORT_1, &GPIO_InitStructure);
}
void ButtonInit(void)
{
	RCC_APB2PeriphClockCmd(BUTTONPORTCLOCK,ENABLE);                //Cung cap xung CLOCK cho GPIOE
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = BUTTON1|BUTTON2|BUTTON3|BUTTON4; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;          //Input floating do có tro kéo lên 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              //Clock GPIO 50Mhz
	GPIO_Init(BUTTONPORT, &GPIO_InitStructure);                     //Cai dat GPIOE
}

void Delay(unsigned int tick)
{
	while(tick) tick--;
}
