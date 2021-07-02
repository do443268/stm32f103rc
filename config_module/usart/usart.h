/*
 * usart.h
 */

#ifndef _USART_H_
#define _USART_H_
#include "STM32f10x.h"
#include <stdio.h>
#include <stdbool.h>
void Usart1Init(unsigned int speed);
unsigned char Usart1GetChar(char *data);
void Usart1PutChar(char ch);
void  USART1PutString( const char * const pcString);
void USART1_IRQHandler( void );

void Usart2Init(unsigned int speed);
unsigned char Usart2GetChar(char *data);
void Usart2PutChar(char ch);
void USART2PutString( const char * const pcString);
void USART2_IRQHandler( void );

void Usart3Init(unsigned int speed);
void Usart3PutChar(char ch);
void USART3PutString( const char * const pcString);
void USART3_IRQHandler( void );


unsigned char Usart3GetChar(char *data);
#endif /* USART_H_ */
