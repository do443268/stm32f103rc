#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "stm32f10x_gpio.h"
void BUTTON_Init(GPIO_TypeDef* BUTTON_PORT,unsigned char BUTTON_NUMBER,unsigned char Pule_Type);
#endif
