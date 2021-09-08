#include "exti.h"

//ngat ngoai
void EXTI_Set(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin,EXTI_Trigger_t trigger,uint8_t CP_Priority)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	uint8_t pinsource, portsource, irqchannel;
	//uint8_t gpio_mode;
	uint32_t gpio_clock;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // cap clock
	
	/* Get proper settings */
	if (GPIO == GPIOA) {
		gpio_clock = RCC_APB2Periph_GPIOA; // clock port
		portsource = GPIO_PortSourceGPIOA;	// gpio port EXTI
	} else if (GPIO == GPIOB) {
		gpio_clock = RCC_APB2Periph_GPIOB;
		portsource = GPIO_PortSourceGPIOB;
	} else if (GPIO == GPIOC) {
		gpio_clock = RCC_APB2Periph_GPIOC;
		portsource = GPIO_PortSourceGPIOC;
	}
	
	switch (GPIO_Pin) {
		case Pin_0:
			pinsource = GPIO_PinSource0; // gpio pin EXTI
			irqchannel = EXTI0_IRQn;  	// channel EXTI
			break;
		case Pin_1:
			pinsource = GPIO_PinSource1;
			irqchannel = EXTI1_IRQn;
			break;
		case Pin_2:
			pinsource = GPIO_PinSource2;
			irqchannel = EXTI2_IRQn;
			break;
		case Pin_3:
			pinsource = GPIO_PinSource3;
			irqchannel = EXTI3_IRQn;
			break;
		case Pin_4:
			pinsource = GPIO_PinSource4;
			irqchannel = EXTI4_IRQn;
			break;
		case Pin_5:
			pinsource = GPIO_PinSource5;
			irqchannel = EXTI9_5_IRQn;
			break;
		case Pin_6:
			pinsource = GPIO_PinSource6;
			irqchannel = EXTI9_5_IRQn;
			break;
		case Pin_7:
			pinsource = GPIO_PinSource7;
			irqchannel = EXTI9_5_IRQn;
			break;
		case Pin_8:
			pinsource = GPIO_PinSource8;
			irqchannel = EXTI9_5_IRQn;
			break;
		case Pin_9:
			pinsource = GPIO_PinSource9;
			irqchannel = EXTI9_5_IRQn;
			break;
		case Pin_10:
			pinsource = GPIO_PinSource10;
			irqchannel = EXTI15_10_IRQn;
			break;
		case Pin_11:
			pinsource = GPIO_PinSource11;
			irqchannel = EXTI15_10_IRQn;
			break;
		case Pin_12:
			pinsource = GPIO_PinSource12;
			irqchannel = EXTI15_10_IRQn;
			break;
		case Pin_13:
			pinsource = GPIO_PinSource13;
			irqchannel = EXTI15_10_IRQn;
			break;
		case Pin_14:
			pinsource = GPIO_PinSource14;
			irqchannel = EXTI15_10_IRQn;
			break;
		case Pin_15:
			pinsource = GPIO_PinSource15;
			irqchannel = EXTI15_10_IRQn;
			break;
		default:
			break;
	}
	
		/* Enable clock for GPIO */
	RCC_APB2PeriphClockCmd(gpio_clock, ENABLE); // cap clock cho port
	
	/* Set pin as input */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;	// chon pin 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	// cau hinh toc do
	
	if (trigger == Trigger_Falling) {
		//gpio_mode = Mode_IPU;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // gpio mode
	} else if (trigger == Trigger_Rising) {
		//gpio_mode = Mode_IPD;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	} else {
		//gpio_mode =	Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	
	GPIO_Init(GPIO, &GPIO_InitStruct);	// init thong so cau hinhg GPIO cho EXTI
	/* Initialize pin */
	//GPIO_Set(GPIO,pinsource,gpio_mode,Speed_50MHz);
	
	/* Connect proper GPIO */
	GPIO_EXTILineConfig(portsource, pinsource); // Cai dat pin la ngat ngoai cho chan
	
	/* Enable EXTI */
	EXTI_InitStruct.EXTI_Line = GPIO_Pin; //// chi dinh line ngat duoc bat	(EXTI_Line2 va cac gpio duoc khai bao gia tri giong nhau)
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; //chi dinh trang thai hoat dong cho line ngat
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; // chon mode ngat 
	EXTI_InitStruct.EXTI_Trigger = (EXTITrigger_TypeDef)trigger; //	chi dinh suon ngat hoat dong 
	EXTI_Init(&EXTI_InitStruct);		// init thong so cau hinh EXTI

	/* Add to NVIC */
	NVIC_InitStruct.NVIC_IRQChannel = irqchannel; // channel ngat
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = CP_Priority; // cau hinh do uu tien
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = pinsource; 
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // bat channel
	NVIC_Init(&NVIC_InitStruct);// khoi tao cac thong so da set ben tren
	
}



