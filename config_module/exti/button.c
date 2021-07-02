#include "button.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
void BUTTON_Init(GPIO_TypeDef* BUTTON_PORT,unsigned char BUTTON_NUMBER,unsigned char Pule_Type)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;
	if(BUTTON_PORT == GPIOA) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	else if(BUTTON_PORT == GPIOB) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	else if(BUTTON_PORT == GPIOC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	else if(BUTTON_PORT == GPIOD) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	else if(BUTTON_PORT == GPIOE) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);      // 2 bit for preemption priority
	if(BUTTON_NUMBER < 5) 	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn + 6;    //In interrupt table
	else if(BUTTON_NUMBER < 10) NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn + 6; //In interrupt table
	else  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn + 6; //In interrupt table
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);							

	GPIO_InitStructure.GPIO_Pin = 1<<BUTTON_NUMBER;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //Input floating
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				  //Clock GPIO 50Mhz
  GPIO_Init(BUTTON_PORT, &GPIO_InitStructure);						  //Cai dat GPIO
	if(BUTTON_PORT == GPIOA) GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,BUTTON_NUMBER);
	else if(BUTTON_PORT == GPIOB) GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,BUTTON_NUMBER);
	else if(BUTTON_PORT == GPIOC) GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,BUTTON_NUMBER);
	else if(BUTTON_PORT == GPIOD) GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,BUTTON_NUMBER);
	else if(BUTTON_PORT == GPIOE) GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,BUTTON_NUMBER);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	// Reset EXTI init struct
	EXTI_StructInit(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = 1<<BUTTON_NUMBER;											
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStruct.EXTI_Trigger = Pule_Type;		//Ngat canh xuong
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}
