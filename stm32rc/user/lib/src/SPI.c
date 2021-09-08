#include "SPI.h"

void SPI1_config_master(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_Set(SPI1_PORT,GPIO_Pin_5,GPIO_Mode_AF_PP,GPIO_Speed_50MHz); // sck
	GPIO_Set(SPI1_PORT,GPIO_Pin_7,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//	mosi
	GPIO_Set(SPI1_PORT,GPIO_Pin_6,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);// miso
	GPIO_Set(SPI1_PORT,GPIO_Pin_4,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);// cs
	
	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	//SPI_InitStructure.SPI_CRCPolynomial = 7; // check CRC
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &SPI_InitStructure);
}

void mode_master(SPI_TypeDef* SPIx, u16 SPI_MODE)
{
		SPI_InitTypeDef SPI_InitStructure;
	
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		//SPI_InitStructure.SPI_CRCPolynomial = 7; // check CRC
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
		SPI_InitStructure.SPI_Mode = SPI_MODE;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_Init(SPIx, &SPI_InitStructure);
}

void mode_slave(SPI_TypeDef* SPIx, u16 SPI_MODE)
{
		SPI_InitTypeDef SPI_InitStructure;
		
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		//SPI_InitStructure.SPI_CRCPolynomial = 7; // check CRC
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
		SPI_InitStructure.SPI_Mode = SPI_MODE;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_Init(SPIx, &SPI_InitStructure);
}

void SPI_config_mode(u16 CS_PINx,SPI_TypeDef* SPIx, u16 SPI_MODE)
{
	//enable clock
	if(SPIx == SPI1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
		if(SPI_MODE == SPI_Mode_Master)
		{
			GPIO_Set(SPI1_PORT,GPIO_Pin_5,GPIO_Mode_AF_PP,GPIO_Speed_50MHz); // sck
			GPIO_Set(SPI1_PORT,GPIO_Pin_7,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//	mosi
			GPIO_Set(SPI1_PORT,GPIO_Pin_6,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);// miso
			GPIO_Set(SPI1_PORT,CS_PINx,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);// cs
			mode_master(SPIx, SPI_MODE);
		}
		else if(SPI_MODE == SPI_Mode_Slave)
		{
			GPIO_Set(SPI1_PORT,GPIO_Pin_5,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz); // clk
			GPIO_Set(SPI1_PORT,GPIO_Pin_7,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//	mosi
			GPIO_Set(SPI1_PORT,GPIO_Pin_6,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);// miso
			GPIO_Set(SPI1_PORT,CS_PINx,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);// cs	
			mode_slave(SPIx, SPI_MODE);
		}
	}
	else if (SPIx == SPI2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		if(SPI_MODE == SPI_Mode_Master)
		{
			GPIO_Set(SPI2_PORT,GPIO_Pin_3,GPIO_Mode_AF_PP,GPIO_Speed_50MHz); // sck
			GPIO_Set(SPI2_PORT,GPIO_Pin_5,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//	mosi
			GPIO_Set(SPI2_PORT,GPIO_Pin_4,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);// miso
			GPIO_Set(SPI2_PORT,CS_PINx,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);// cs
			mode_master(SPIx, SPI_MODE);
		}
		else if(SPI_MODE == SPI_Mode_Slave)
		{
			GPIO_Set(SPI2_PORT,GPIO_Pin_3,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz); // clk
			GPIO_Set(SPI2_PORT,GPIO_Pin_5,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//	mosi
			GPIO_Set(SPI2_PORT,GPIO_Pin_4,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);// miso
			GPIO_Set(SPI2_PORT,CS_PINx,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);// cs	
			mode_slave(SPIx, SPI_MODE);
		}
	}
	else if (SPIx == SPI3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		if(SPI_MODE == SPI_Mode_Master)
		{
			GPIO_Set(SPI3_PORT,GPIO_Pin_13,GPIO_Mode_AF_PP,GPIO_Speed_50MHz); 				// sck
			GPIO_Set(SPI3_PORT,GPIO_Pin_14,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);					//	mosi
			GPIO_Set(SPI3_PORT,GPIO_Pin_15,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);		// miso
			GPIO_Set(SPI3_PORT,CS_PINx,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);						// cs
			mode_master(SPIx, SPI_MODE);
		}
		else if(SPI_MODE == SPI_Mode_Slave)
		{
			GPIO_Set(SPI3_PORT,GPIO_Pin_13,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz); 	// clk
			GPIO_Set(SPI3_PORT,GPIO_Pin_14,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);					//	mosi
			GPIO_Set(SPI3_PORT,GPIO_Pin_15,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);		// miso
			GPIO_Set(SPI3_PORT,CS_PINx,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);							// cs	
			mode_slave(SPIx, SPI_MODE);
		}
	}
}
//send data
uint8_t My_SPI_Exchange(SPI_TypeDef* SPIx,uint8_t u8Data)
{
	SPI_I2S_SendData(SPIx, u8Data);
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) {
	}
	return SPI_I2S_ReceiveData(SPIx);
}



