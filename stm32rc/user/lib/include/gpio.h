#ifndef _GPIO_H_
#define _GPIO_H_

#include "main.h"

// gpio mode
#define	Mode_AIN					GPIO_Mode_AIN 				// Analog: mode ADC or DAC
#define	Mode_IN_FLOATING			GPIO_Mode_IN_FLOATING //	chan ngo vao de noi
#define	Mode_IPD					GPIO_Mode_IPD 				// 	tro keo xuong GND
#define	Mode_IPU					GPIO_Mode_IPU 				// 	tro keo len VCC
#define	Mode_Out_OD				GPIO_Mode_Out_OD 
#define	Mode_Out_PP				GPIO_Mode_Out_PP 
#define	Mode_AF_OD				GPIO_Mode_AF_OD 			// mode uart,spi,i2c
#define	Mode_AF_PP				GPIO_Mode_AF_PP 			// mode uart,spi,i2c

// gpio pin
#define Pin_0		GPIO_Pin_0
#define Pin_1		GPIO_Pin_1
#define Pin_2		GPIO_Pin_2
#define Pin_3		GPIO_Pin_3
#define Pin_4		GPIO_Pin_4
#define Pin_5		GPIO_Pin_5
#define Pin_6		GPIO_Pin_6
#define Pin_7		GPIO_Pin_7
#define Pin_8		GPIO_Pin_8
#define Pin_9		GPIO_Pin_9
#define Pin_10	GPIO_Pin_10
#define Pin_11	GPIO_Pin_11
#define Pin_12	GPIO_Pin_12
#define Pin_13	GPIO_Pin_13
#define Pin_14	GPIO_Pin_14
#define Pin_15	GPIO_Pin_15
#define Pin_All GPIO_Pin_All

// GPIOSpeed
#define		Speed_10MHz			GPIO_Speed_10MHz
#define		Speed_2MHz			GPIO_Speed_2MHz
#define		Speed_50MHz			GPIO_Speed_50MHz

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void GPIO_Set(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed);


#endif
