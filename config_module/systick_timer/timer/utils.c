#include "utils.h"

static __IO uint32_t _delay;
TIM_TypeDef *Timer2,*Timer3,*Timer4;
void setup_delay_timer(TIM_TypeDef *timer) 
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	
    TIM_DeInit(timer);
    // Enable Timer clock
    if (timer == TIM2) {
			  Timer2 = timer;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    } else if (timer == TIM3) {
			  Timer3 = timer;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    } else if (timer == TIM4) {
			  Timer4 = timer;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			  
    } else {
        // TODO: not implemented
        while(1){}
    }
    // Configure timer
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Prescaler = SystemCoreClock / 1000000 - 1; //72Mhz/1Mhz = 72
    TIM_InitStructure.TIM_Period = 10000 - 1; // Update event every 10000 us (10 ms)
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(timer, &TIM_InitStructure);

    TIM_Cmd(timer, ENABLE);
}

void delay(__IO uint32_t nTime)
{
  _delay = nTime;
  while(_delay != 0);
}


//Use Timer 2
void delay_us_2(unsigned int time) {
    Timer2->CNT = 0;
    time -= 3;
    while (Timer2->CNT <= time) {}
}

void delay_ms_2(unsigned int time) {
    while (time--) {
        delay_us_2(1000);
    }
}
//Use timer 3
void delay_us_3(unsigned int time) {
    Timer3->CNT = 0;
    time -= 3;
    while (Timer3->CNT <= time) {}
}

void delay_ms_3(unsigned int time) {
    while (time--) {
        delay_us_3(1000);
    }
}
//Use timer 4
void delay_us_4(unsigned int time) {
    Timer3->CNT = 0;
    time -= 3;
    while (Timer3->CNT <= time) {}
}

void delay_ms_4(unsigned int time) {
    while (time--) {
        delay_us_4(1000);
    }
}
