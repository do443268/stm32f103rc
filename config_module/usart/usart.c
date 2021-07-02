/*
 * usart.c code by lochoangvan@gmail.com 
 * 
 */
#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

#define USE_USART1_INTERRUPT                      //Use USART1 Interrupt
//#define USE_USART2_INTERRUPT                      //Use USART3 Interrupt
//#define USE_USART3_INTERRUPT                      //Use USART3 Interrupt

#ifdef USE_USART1_INTERRUPT
#define MAX_USART1_BUFF 300
char usart1_buff[MAX_USART1_BUFF];
unsigned int count1_data_in = 0;
unsigned int count1_data_read = 0;
#endif

#ifdef USE_USART2_INTERRUPT
#define MAX_USART2_BUFF 300
char usart2_buff[MAX_USART2_BUFF];
unsigned int count2_data_in = 0;
unsigned int count2_data_read = 0;
#endif
#ifdef USE_USART3_INTERRUPT
#define MAX_USART3_BUFF 300
char usart3_buff[MAX_USART3_BUFF];
unsigned int count3_data_in = 0;
unsigned int count3_data_read = 0;
#endif
int fputc(int ch, FILE *f)
{
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
  return (ch);
}

void Usart1Init(unsigned int speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_InitClockStructure;
	 /* Enable GPIOA and USART1 clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );
#ifdef USE_USART1_INTERRUPT
	 NVIC_InitTypeDef NVIC_InitStructure;
	 // Configure the NVIC (nested vector interrupt controller)
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);										//USE group 4	
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init( &NVIC_InitStructure );
#endif	

		/* Configure USART1 Rx (PA10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init( GPIOA, &GPIO_InitStructure );

		/* Configure USART1 Tx (PA9) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init( GPIOA, &GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = speed;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitClockStructure.USART_Clock = USART_Clock_Disable;
		USART_InitClockStructure.USART_CPOL = USART_CPOL_Low;
		USART_InitClockStructure.USART_CPHA = USART_CPHA_2Edge;
		USART_InitClockStructure.USART_LastBit = USART_LastBit_Disable;

		USART_Init( USART1, &USART_InitStructure );
		USART_ClockInit( USART1, &USART_InitClockStructure);
#ifdef USE_USART1_INTERRUPT
		USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );											//Enable RX interrupt 
#endif
//		USART_DMACmd( USART1, ( USART_DMAReq_Tx | USART_DMAReq_Rx ), ENABLE );	
		USART_Cmd( USART1, ENABLE );
} 
void Usart1PutChar(char ch)
{
  USART1->DR = ch;
  while (!(USART1->SR & USART_FLAG_TXE));
}
void USART1PutString( const char *pcString )
{
	while(*pcString != '\0')
		{
			USART1->DR = *pcString;
			while (!(USART1->SR & USART_FLAG_TXE));
			pcString++;
		}
}


#ifdef USE_USART1_INTERRUPT
void USART1_IRQHandler(void)
{
	if((USART1->SR & USART_FLAG_RXNE) != (uint16_t)RESET)
	{			
		if(count1_data_in<MAX_USART1_BUFF)
		{
			usart1_buff[count1_data_in++] = USART1->DR & (uint16_t)0x01FF;
		}else count1_data_in = 0;
	}
}
unsigned char Usart1GetChar(char *data)
{
	if(count1_data_read >= count1_data_in) 
	{ 
		count1_data_read = 0;               //Reset count Read
		count1_data_in = 0;                 //Reset count Input
	  return 0;
	}else 
	{
		*data = usart1_buff[count1_data_read];//Read current data
	  count1_data_read++;
		return 1;
	}
}
#endif
//USART2 config
void Usart2Init(unsigned int speed)
{   
    USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_ClockInitTypeDef USART_InitClockStructure;
    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#ifdef USE_USART2_INTERRUPT
	  NVIC_InitTypeDef NVIC_InitStructure;                 // Configure the NVIC (nested vector interrupt controller)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;      // we want to configure the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       // the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);
#endif
    // Use PA2 and PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART2
    USART_InitStructure.USART_BaudRate = speed;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitClockStructure.USART_Clock = USART_Clock_Disable;
		USART_InitClockStructure.USART_CPOL = USART_CPOL_Low;
		USART_InitClockStructure.USART_CPHA = USART_CPHA_2Edge;
		USART_InitClockStructure.USART_LastBit = USART_LastBit_Disable;

    USART_Init(USART2, &USART_InitStructure);
		USART_ClockInit( USART2, &USART_InitClockStructure);
#ifdef USE_USART2_INTERRUPT
			//--------------------CONFIG---------------------
	  /* Enable USARTy Receive and Transmit interrupts */
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
#endif		

    // Enable usart
    USART_Cmd(USART2, ENABLE);
}

#ifdef USE_USART2_INTERRUPT
void USART2_IRQHandler(void)
{
	if((USART2->SR & USART_FLAG_RXNE) != (uint16_t)RESET)
	{			
		if(count2_data_in<MAX_USART2_BUFF)
		{
			usart2_buff[count2_data_in++] = USART2->DR & (uint16_t)0x01FF;
		}else count2_data_in = 0;
	}
}
unsigned char Usart2GetChar(char *data)
{
	if(count2_data_read >= count2_data_in) 
	{ 
		count2_data_read = 0;               //Reset count Read
		count2_data_in = 0;                 //Reset count Input
	  return 0;
	}else 
	{
		*data = usart2_buff[count2_data_read];//Read current data
	  count2_data_read++;
		return 1;
	}
}
#endif
void Usart2PutChar(char ch)
{
  USART2->DR = ch;
  while (!(USART2->SR & USART_FLAG_TXE));
}
void USART2PutString(const char *pcString )
{
	while(*pcString != '\0')
	{
		USART2->DR = *pcString;
		while (!(USART2->SR & USART_FLAG_TXE));
		pcString++;
	}
}
void Usart3Init(unsigned int speed)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;	 									           
    /* Enable GPIOB and USART3 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
#ifdef USE_USART3_INTERRUPT
	  NVIC_InitTypeDef NVIC_InitStructure; 
	  // Configure the NVIC (nested vector interrupt controller)	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   							 // we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    	   // this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      							 // the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);
#endif
    // USART3  Tx (PB10)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		// USART3 RX (PB10)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // USART3
    USART_InitStructure.USART_BaudRate = speed;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART3, &USART_InitStructure);
#ifdef USE_USART3_INTERRUPT
    // Enable interrupts
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
#endif
    // Enable usart
    USART_Cmd(USART3, ENABLE);
}
#ifdef USE_USART3_INTERRUPT
void USART3_IRQHandler(void)
{
	if((USART3->SR & USART_FLAG_RXNE) != (uint16_t)RESET)
	{			
		if(count3_data_in<MAX_USART3_BUFF)
		{
			usart3_buff[count3_data_in++] = USART3->DR & (uint16_t)0x01FF;
		}else count3_data_in = 0;
	}
}
unsigned char Usart3GetChar(char *data)
{
	if(count3_data_read >= count3_data_in) 
	{ 
		count3_data_read = 0;               //Reset count Read
		count3_data_in = 0;                 //Reset count Input
	  return 0;
	}else 
	{
		*data = usart3_buff[count3_data_read];//Read current data
	  count3_data_read++;
		return 1;
	}
}
#endif

void Usart3PutChar(char ch)
{
  USART3->DR = ch;
  while (!(USART3->SR & USART_FLAG_TXE));
}
void USART3PutString(const char *pcString )
{
	while(*pcString != '\0')
	{
		USART3->DR = *pcString;
		while (!(USART3->SR & USART_FLAG_TXE));
		pcString++;
	}
}
