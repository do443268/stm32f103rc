#include "stm32f10x.h"

#define clock_8Mhz  	0
#define clock_12Mhz  	0x00040000
#define clock_16Mhz  	0x00080000
#define clock_20Mhz  	0x000C0000
#define clock_24Mhz  	0x00100000
#define clock_28Mhz  	0x00140000
#define clock_32Mhz  	0x00180000
#define clock_36Mhz  	0x001C000
#define clock_40Mhz  	0x00200000
#define clock_44Mhz  	0x00240000
#define clock_48Mhz  	0x00280000
#define clock_52Mhz  	0x002C0000
#define clock_56Mhz  	0x00300000
#define clock_60Mhz  	0x00340000
#define clock_64Mhz  	0x00380000

GPIO_InitTypeDef 					GPIO_InitStructure;
RCC_ClocksTypeDef 				RCC_ClockFreq;
ErrorStatus 							HSEStartUpStatus;

uint32_t clock_source=0;

void Clock_HSI_Configuration(uint32_t clock_in);
void GPIO_Configuration(void);
void Delay_ms(uint16_t time);

int main(void)
{
	Clock_HSI_Configuration(clock_64Mhz);
	SysTick_Config(SystemCoreClock/1000);
	GPIO_Configuration();
	RCC_GetClocksFreq(&RCC_ClockFreq);
	clock_source = RCC_ClockFreq.SYSCLK_Frequency;
  while (1)
  {
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));
		Delay_ms(1000);
  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}
}
void Clock_HSI_Configuration(uint32_t clock_in)
{
	  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();
	RCC_HSICmd(ENABLE);	
	/* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */
   RCC_PCLK2Config(RCC_HCLK_Div2);
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    /* PLLCLK = clock_in */
			RCC_PLLConfig(RCC_PLLSource_HSI_Div2, clock_in);
	/* Enable PLL */ 
   RCC_PLLCmd(ENABLE);
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08) {}
}
