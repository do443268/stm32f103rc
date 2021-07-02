#include "stm32f10x.h"

void GPIO_Configuration(void);
void TIM4_config(void);
void blink(void);
void delay_ms_4(unsigned int time);

int main(void)
{
	GPIO_Configuration();
	TIM4_config();
	while (1)
	{
		blink();
	}
}

void delay_us_4(unsigned int time) {
   while(time--)
	 {
     TIM4->CNT = 0;
		 TIM4->CCR4 = 10000/2;
     while (TIM4->CNT < 1) {}
	 }
}

void delay_ms_4(unsigned int time) {
    while (time--) {
        delay_us_4(1000);
    }
}

void delay_ms(uint16_t time)
{
	// tang bien dem len 12000 lan
	uint32_t time_n = time * 12000;
	// cho den khi biem time_n giam =0 thi thoat
	while (time_n != 0)
	{
		time_n--;
	}
}

void blink(void)
{
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		delay_ms_4(1000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		delay_ms_4(1000);
}

void GPIO_Configuration(void) // gpio config
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE); // cap clock cho Port D, Port A
	// cau hinh chan I/O su dung la PD2,toc do input,mode input la uotput pull-up
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	// cau hinh chan I/O su dung la PC1,toc do input,mode input la input pull-up
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM4_config(void) // timer 4 config
{
	TIM_TimeBaseInitTypeDef TimerInit;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TimerInit.TIM_CounterMode = TIM_CounterMode_Up; // mode dem len
	TimerInit.TIM_Period = 1; // bo chia
	TimerInit.TIM_Prescaler = SystemCoreClock / 1000000 - 1;//  gia tri dem nap vao timer (0x0000 -> 0xffff) 72
	
	TimerInit.TIM_ClockDivision = TIM_CKD_DIV1; // chia clock
  TimerInit.TIM_RepetitionCounter = 0; // gia tri bo dem lap lai
	TIM_TimeBaseInit(TIM4, &TimerInit); // init cac tham so bo dem
	
	TIM_Cmd(TIM4,ENABLE); // chay bo dem
}

//void pwm

