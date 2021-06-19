#include "stm32f10x.h"

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);

int main(void)
{
	// goi chuong trinh con da khai bao
	GPIO_Configuration();                                 
  while (1)
  {
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		Delay_ms(300);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		Delay_ms(300);																									
  }
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	// cap clock cho Port B, Port C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE); 
	// cau hinh chan I/O su dung la PC13,toc do input,mode input la Input pull-up
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;						
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;			
	
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
// ham delay tuong doi dung vong lap while
void Delay_ms(uint16_t time)														
{
	// tang bien dem len 12000 lan
	uint32_t time_n=time*12000;		
	// cho den khi biem time_n giam =0 thi thoat	
	while(time_n!=0){time_n--;}													

}

