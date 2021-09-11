#ifndef __SPI_H_
#define __SPI_H_  220721


#include "main.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "gpio.h"

// pin SPI1


// port SPI1
#define SPI1_PORT GPIOA
#define SPI2_PORT	GPIOB
#define SPI3_PORT	GPIOB


void mode_master(SPI_TypeDef* SPIx, u16 SPI_MODE);
void mode_slave(SPI_TypeDef* SPIx, u16 SPI_MODE);
void SPI_config_mode(u16 CS_PINx,SPI_TypeDef* SPIx,u16 SPI_MODE);
void SPI1_config_master(void);


//sd driver
uint8_t My_SPI_Exchange(SPI_TypeDef* SPIx,uint8_t u8Data);

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

