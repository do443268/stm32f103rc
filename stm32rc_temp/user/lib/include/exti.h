#ifndef _EXTI_H_
#define _EXTI_H_

#include "main.h"


#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

typedef enum { // chon suon ngat
	Trigger_Rising = 0x08,
	Trigger_Falling = 0x0C,
	Trigger_Rising_Falling = 0x10
} EXTI_Trigger_user;

void EXTI_Set(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,EXTI_Trigger_user trigger,uint8_t CP_Priority);

#endif
