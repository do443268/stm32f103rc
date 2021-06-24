#include "stm32f10x.h"

#define clock_16Mhz  0
#define clock_24Mhz  0x00040000
#define clock_32Mhz  0x00080000
#define clock_40Mhz  0x000C0000
#define clock_48Mhz  0x00100000
#define clock_56Mhz  0x00140000
#define clock_64Mhz  0x00180000
#define clock_72Mhz  0x001C0000

GPIO_InitTypeDef 					GPIO_InitStructure;
RCC_ClocksTypeDef 				RCC_ClockFreq;
ErrorStatus 							HSEStartUpStatus;

uint32_t clock_source=0;

void Clock_HSE_Configuration(uint32_t clock_in);
void GPIO_Configuration(void);
void Delay_ms(uint16_t time);

int main(void)
{
	Clock_HSE_Configuration(clock_72Mhz);		// goi chuong trinh cau hinh clock HSE
	GPIO_Configuration();										// goi chuong trinh cau hinh GPIO
	RCC_GetClocksFreq(&RCC_ClockFreq);			// goi ham get clock source de debug va quan sat
	clock_source = RCC_ClockFreq.SYSCLK_Frequency; // lay gia tri clock source
  while (1)
  {
		// dao trang thai led
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));
		// delay tuong doi
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
void Clock_HSE_Configuration(uint32_t clock_in) 
{
  RCC_DeInit(); 														
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON); // bat bo HSE					
  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2); // do tre flash 2 chu ky
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); // xac dinh bo chia AHB
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); // bo chia APB2 HS
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2); //bo chia APB1 LS
    /* PLLCLK = clock_in */
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, clock_in);	// cau hinh bo nhan PLL 
    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // cau hinh bo SYSCLK
			// RCC_SYSCLKSource_PLLCLK:  chon PLL lam clock he thong
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08){ }
  }
  else{ while (1){}}
}
