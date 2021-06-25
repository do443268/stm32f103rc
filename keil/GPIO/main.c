#include "stm32f10x.h"

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void Button(void);
int count = 0;
int main(void)
{
	// goi chuong trinh con da khai bao
	GPIO_Configuration();
	while (1)
	{

		Button();
		// if (count == 1)
		// {
		// 	GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)Bit_SET);
		// }
		// if (count == 2)
		// {
		// 	GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)Bit_RESET);
		// }
		// GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)(1 ^ GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)));
	}
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE); // cap clock cho Port D, Port C
	// cau hinh chan I/O su dung la PD2,toc do input,mode input la uotput pull-up
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	// cau hinh chan I/O su dung la PC1,toc do input,mode input la input pull-up
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
// ham delay tuong doi dung vong lap while
void Delay_ms(uint16_t time)
{
	// tang bien dem len 12000 lan
	uint32_t time_n = time * 12000;
	// cho den khi biem time_n giam =0 thi thoat
	while (time_n != 0)
	{
		time_n--;
	}
}
void Button(void)
{
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
	{
		Delay_ms(10);
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
		{
			while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
			{
			}
			count++;
			if (count > 2)
			{
				count = 1;
			}
		}
	}
	if (count == 1)
	{
		GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)Bit_SET);
	}
	if (count == 2)
	{
		GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)Bit_RESET);
	}
}
