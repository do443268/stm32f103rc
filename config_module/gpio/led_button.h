#ifndef _LED_BUTTON_H_
#define _LED_BUTTON_H_

//file module config gpio, rcc
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#define LED1          GPIO_Pin_6       
#define LED2          GPIO_Pin_7
#define LED3          GPIO_Pin_6
#define LED4          GPIO_Pin_13

#define LEDPORT        GPIOC
#define LEDPORT_1      GPIOD
#define LEDPORTCLK     RCC_APB2Periph_GPIOC
#define LEDPORTCLK_1   RCC_APB2Periph_GPIOD

#define BUTTON1 GPIO_Pin_2 
#define BUTTON2 GPIO_Pin_3
#define BUTTON3 GPIO_Pin_4
#define BUTTON4 GPIO_Pin_5

#define BUTTONPORT GPIOE
#define BUTTONPORTCLOCK RCC_APB2Periph_GPIOE
void LedInit(void);
void ButtonInit(void);
void Delay(unsigned int tick);
#endif
