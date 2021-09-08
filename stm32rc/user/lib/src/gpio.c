#include "gpio.h"


void GPIO_Set(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//enable clock: cap xung
	if( GPIO == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	}
	else if(GPIO == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(GPIO == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	// gpio init
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin; // set pin gpio
	GPIO_InitStructure.GPIO_Mode = Mode;		// set mode
	GPIO_InitStructure.GPIO_Speed = Speed;	// set speed
	
	
	GPIO_Init(GPIO, &GPIO_InitStructure);		// init cac thong so tren
}














