/**
 *
 *	//Buffer length for USART1 is 1kB
 *	#define USART1_BUFFER_SIZE 1024
 *
 *	Other possible settings are (for other U(S)ARTs):
 *		- USART1_BUFFER_SIZE
 *		- USART2_BUFFER_SIZE
 *		- USART3_BUFFER_SIZE
 *		- UART4_BUFFER_SIZE
 *		- UART5_BUFFER_SIZE
 *		- USART6_BUFFER_SIZE
 *		- UART7_BUFFER_SIZE
 *		- UART8_BUFFER_SIZE
 *	
 *	Pinout
 *
 *				
 *	U(S)ARTX	|TX		RX		|TX		RX		|TX		RX
 *	
 *	USART1		|PA9	PA10	|PB6	PB7		|-		-
 *	USART2		|PA2	PA3		|PD5	PD6		|-		-
 *	USART3		|PB10	PB11	|PC10	PC11	|PD8	PD9
 *	UART4		|PA0	PA1		|PC10	PC11	|-		-
 *	UART5		|PC12	PD2		|-		-		|-		-
 *	USART6		|PC6	PC7		|PG14	PG9		|-		-
 *	UART7		|PE8	PE7		|PF7	PF6		|-		-
 *	UART8		|PE1	PE0		|-		-		|-		-
 *
 * Possible changes in USART operation
 * 
 * 	//Change X with possible U(S)ARTs: USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8
 * 	//Set flow control
 *	#define X_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
 *	//Set mode
 *	#define X_MODE						USART_Mode_Tx | USART_Mode_Rx
 *	//Set parity
 *	#define X_PARITY						USART_Parity_No
 *	//Set stopbits
 *	#define X_STOP_BITS					USART_StopBits_1
 *	//Set USART datasize
 *	#define X_WORD_LENGTH				USART_WordLength_8b
 */
#ifndef _USART_H_
#define _USART_H_
/**
 * Library dependencies
 * - STM32F4xx
 * - STM32F4xx RCC
 * - STM32F4xx GPIO
 * - STM32F4xx USART
 * - defines.h
 * - attributes
 */
/**
 * Includes
 */
#include "main.h"
//#include "misc.h"
//#include "stm32f10x.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_usart.h"
//#include "stdio.h"


// STM3232f103rct6,STM3232f103c8t6
#if defined (STM32F10X_HD) //define chip flash
#define USE_USART1
#define USE_USART2
#define USE_USART3
#define USE_UART4
#define USE_UART5
#define USE_USART6
#endif
#if defined (STM32F10X_MD)
#define USE_USART1
#define USE_USART2
#define USE_USART3
#endif
/* STM32F40_41xxx */
#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define USE_USART1
#define USE_USART2
#define USE_USART3
#define USE_UART4
#define USE_UART5
#define USE_USART6
#define USE_UART7
#define USE_UART8
#endif /* STM32F427_437x || STM32F429_439xx */
#if defined (STM32F401xx) || defined(STM32F411xE)
#define USE_USART1
#define USE_USART2
#define USE_USART6
#endif /* STM32F401xx || STM32F411xx */

/* Default buffer size for each USART */
#ifndef USART_BUFFER_SIZE
#define USART_BUFFER_SIZE 				200 
#endif

/* Set default buffer size for specific USART if not set by user */
#ifndef USART1_BUFFER_SIZE
#define USART1_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef USART2_BUFFER_SIZE
#define USART2_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef USART3_BUFFER_SIZE
#define USART3_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef UART4_BUFFER_SIZE
#define UART4_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef UART5_BUFFER_SIZE
#define UART5_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef USART6_BUFFER_SIZE
#define USART6_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef UART7_BUFFER_SIZE
#define UART7_BUFFER_SIZE				USART_BUFFER_SIZE
#endif
#ifndef UART8_BUFFER_SIZE
#define UART8_BUFFER_SIZE				USART_BUFFER_SIZE
#endif

/* NVIC Priority */
#ifndef USART_NVIC_PRIORITY
#define USART_NVIC_PRIORITY				0x00 // do uu tien
#endif

//U(S)ART settings, can be changed in your defines.h project file
//USART1 default settings
#ifndef USART1_HARDWARE_FLOW_CONTROL
#define USART1_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef USART1_MODE
#define USART1_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef USART1_PARITY
#define USART1_PARITY					USART_Parity_No
#endif
#ifndef USART1_STOP_BITS
#define USART1_STOP_BITS					USART_StopBits_1
#endif
#ifndef USART1_WORD_LENGTH
#define USART1_WORD_LENGTH				USART_WordLength_8b
#endif

//USART2 default settings
#ifndef USART2_HARDWARE_FLOW_CONTROL
#define USART2_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef USART2_MODE
#define USART2_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef USART2_PARITY
#define USART2_PARITY					USART_Parity_No
#endif
#ifndef USART2_STOP_BITS
#define USART2_STOP_BITS					USART_StopBits_1
#endif
#ifndef USART2_WORD_LENGTH
#define USART2_WORD_LENGTH				USART_WordLength_8b
#endif

//USART3 default settings
#ifndef USART3_HARDWARE_FLOW_CONTROL
#define USART3_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef USART3_MODE
#define USART3_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef USART3_PARITY
#define USART3_PARITY					USART_Parity_No
#endif
#ifndef USART3_STOP_BITS
#define USART3_STOP_BITS					USART_StopBits_1
#endif
#ifndef USART3_WORD_LENGTH
#define USART3_WORD_LENGTH				USART_WordLength_8b
#endif

//UART4 default settings
#ifndef UART4_HARDWARE_FLOW_CONTROL
#define UART4_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef UART4_MODE
#define UART4_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef UART4_PARITY
#define UART4_PARITY						USART_Parity_No
#endif
#ifndef UART4_STOP_BITS
#define UART4_STOP_BITS					USART_StopBits_1
#endif
#ifndef UART4_WORD_LENGTH
#define UART4_WORD_LENGTH				USART_WordLength_8b
#endif

//UART5 default settings
#ifndef UART5_HARDWARE_FLOW_CONTROL
#define UART5_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef UART5_MODE
#define UART5_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef UART5_PARITY
#define UART5_PARITY						USART_Parity_No
#endif
#ifndef UART5_STOP_BITS
#define UART5_STOP_BITS					USART_StopBits_1
#endif
#ifndef UART5_WORD_LENGTH
#define UART5_WORD_LENGTH				USART_WordLength_8b
#endif

//USART6 default settings
#ifndef USART6_HARDWARE_FLOW_CONTROL
#define USART6_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef USART6_MODE
#define USART6_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef USART6_PARITY
#define USART6_PARITY					USART_Parity_No
#endif
#ifndef USART6_STOP_BITS
#define USART6_STOP_BITS					USART_StopBits_1
#endif
#ifndef USART6_WORD_LENGTH
#define USART6_WORD_LENGTH				USART_WordLength_8b
#endif

//UART7 default settings
#ifndef UART7_HARDWARE_FLOW_CONTROL
#define UART7_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef UART7_MODE
#define UART7_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef UART7_PARITY
#define UART7_PARITY						USART_Parity_No
#endif
#ifndef UART7_STOP_BITS
#define UART7_STOP_BITS					USART_StopBits_1
#endif
#ifndef UART7_WORD_LENGTH
#define UART7_WORD_LENGTH				USART_WordLength_8b
#endif

//UART8 default settings
#ifndef UART8_HARDWARE_FLOW_CONTROL
#define UART8_HARDWARE_FLOW_CONTROL		USART_HardwareFlowControl_None
#endif
#ifndef UART8_MODE
#define UART8_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef UART8_PARITY
#define UART8_PARITY						USART_Parity_No
#endif
#ifndef UART8_STOP_BITS
#define UART8_STOP_BITS					USART_StopBits_1
#endif
#ifndef UART8_WORD_LENGTH
#define UART8_WORD_LENGTH				USART_WordLength_8b
#endif

/**
 * When you initialize USARTx, you have to select which pins pack you will use
 *
 * 
 */
typedef enum { // USART PinsPack TX || RX
	Pins_PA9PA10,	//USART1 (F103RC)
	Pins_PB6PB7,	////USART1
	Pins_PA2PA3,	//USART2 (F103RC)
	Pins_PD5PD6,	//USART2
	Pins_PB10PB11,	//USART3 (F103RC)
	Pins_PC10PC11,	//USART3//UART4
	Pins_PD8PD9,	//USART3
	Pins_PA0PA1,	//UART4
	Pins_PC12PD2,	//UART5
	Pins_PC6PC7,	//USART6
	Pins_PG14PG9,	//USART6
	Pins_PB8PE7,	//UART7
	Pins_PF7PF6,	//UART7
	Pins_PE1PE0		//UART8
} USART_PinsPack_t;

/**
 * Initialize USARTx
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 * 	- USART_PinsPack_t pinspack: Pinspack used
 
 *	- uint32_t baudrate: baudrate for USARTx
 */
extern void USARTx_Init(USART_TypeDef* USARTx, USART_PinsPack_t pinspack, uint32_t baudrate); // 

/**
 * Put character to USARTx
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 *	- volatile char c: char to be sent to USART
 */
extern void USART_Putc(USART_TypeDef* USARTx, volatile char c);

/**
 * Put string to USARTx
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 *	- char* str: pointer to first character in string
 */
extern void USART_Puts(USART_TypeDef* USARTx, char* str);

/**
 * Get character from internal buffer
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 *
 * Returned character if exists in buffer, otherwise zero
 */
extern uint8_t USART_Getc(USART_TypeDef* USARTx);

/**
 * Get string from USART
 *
 * This function can create a string from USART received data.
 * It generates string until "\n" is not recognized or buffer length is full.
 *
 * As of version 1.5, this function automatically adds "\n" at the end of string
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 * 	- char* buffer: pointer to character buffer
 * 	- uint16_t bufsize: size of your buffer
 *
 * Returns number of valid characters in buffer
 */
extern uint16_t USART_Gets(USART_TypeDef* USARTx, char* buffer, uint16_t bufsize);

/**
 * Check if character is available in internal buffer
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 * 	- volatile char c: character you want to check if is available in buffer
 *
 * Returns 1 if character is available or 0 if not
 */
extern uint8_t USART_FindCharacter(USART_TypeDef* USARTx, volatile char c);

/**
 * Checks if internal buffer is empty
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 *
 * Returns 1 if buffer is empty, otherwise 0
 */
extern uint8_t USART_BufferEmpty(USART_TypeDef* USARTx);

/**
 * Checks if internal buffer is full
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 *
 * Returns 1 if buffer is full, otherwise 0
 */
extern uint8_t USART_BufferFull(USART_TypeDef* USARTx);

/**
 * Clear USART internal cyclic buffer
 *
 * Parameters:
 * 	- USART_TypeDef* USARTx: which USART channel
 * 		USART1, USART2, USART3, UART4, UART5, USART6, UART7. UART8
 *
 * No return
 */
extern void USART_ClearBuffer(USART_TypeDef* USARTx);

/**
 * These functions are used, if you want to make yourself interrupt handler.
 *
 * To enable them, you have to add corresponsing define in you defines.h file.
 * For example:
 *	- If you want to enable USART1 custom handler, then add following line in defines.h file:
 *		#define USART_USE_CUSTOM_IRQ
 *		and create function USART1_ReceiveHandler somewhere in your project
 *
 * Parameters:
 *	- uint8_t c: Character, received from USART
 *
 * Returns void
 * With '__weak' parameter for prevent link errors if function is not declared
 */
__weak void USART1_ReceiveHandler(uint8_t c);
__weak void USART2_ReceiveHandler(uint8_t c);
__weak void USART3_ReceiveHandler(uint8_t c);
__weak void UART4_ReceiveHandler(uint8_t c);
__weak void UART5_ReceiveHandler(uint8_t c);
__weak void USART6_ReceiveHandler(uint8_t c);
__weak void UART7_ReceiveHandler(uint8_t c);
__weak void UART8_ReceiveHandler(uint8_t c);


#endif
