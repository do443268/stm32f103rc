void EXTI2_IRQHandler(void)
{ 
 if(LED_tick <(0xFFFF-300)) LED_tick+=300; 
 EXTI_ClearFlag(EXTI_Line2);
}
void EXTI3_IRQHandler(void)
{
 if(LED_tick>300) LED_tick-=300;
 EXTI_ClearFlag(EXTI_Line3);
}
void EXTI4_IRQHandler(void)
{
 if(LED_tick>300) LED_tick-=300;
 EXTI_ClearFlag(EXTI_Line4);
}
void EXTI9_5_IRQHandler(void)
{
 if(LED_tick <(0xFFFF-300)) LED_tick+=300;
 EXTI_ClearFlag(EXTI_Line5);
}
void Delay(unsigned int tick)
{
	while(tick) tick--;
}
void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(LEDPORTCLK|LEDPORTCLK_1,ENABLE);	//ENABLE CLOCK cho GPIOC va GPIOD
	RCC_APB2PeriphClockCmd(BUTTONPORTCLOCK,ENABLE);	         //ENABLE CLOCK cho GPIOE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		
}

void NVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;
  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // set bit ưu tiên
  
  /* Enable the EX2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; // channel ngat
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // do uu tien
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // bat channel
  NVIC_Init(&NVIC_InitStructure);  // khoi tao cac thong so da set ben tren
	/* Enable the EX3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	/* Enable the EX4 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	/* Enable the EX5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
}
void GPIO_Configuration(void) // config gpio cho ngat
{
	GPIO_InitTypeDef GPIO_InitStructure;										
  GPIO_InitStructure.GPIO_Pin = LED1|LED2;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//Output, tro keo
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//Clock GPIO 50Mhz
  GPIO_Init(LEDPORT, &GPIO_InitStructure);								//Cai dat GPIOC

	GPIO_InitStructure.GPIO_Pin = LED3|LED4;								//Cai dat GPIOD
	GPIO_Init(LEDPORT_1, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = BUTTON1|BUTTON2|BUTTON3|BUTTON4;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //Input floating
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				 //Clock GPIO 50Mhz
  GPIO_Init(BUTTONPORT, &GPIO_InitStructure);							 //Cai dat GPIOE
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);//Cai dat pin la ngat ngoai cho chan 2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);//Cai dat pin la ngat ngoai cho chan 3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);//Cai dat pin la ngat ngoai cho chan 4
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);//Cai dat pin la ngat ngoai cho chan 5
}
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	// Reset EXTI init struct
	EXTI_StructInit(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5;	// chi dinh line ngat dươc bat										
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// chon mode ngat 
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;		//Ngat canh xuong // chi dinh canh hoat dong 
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; // chi dinh trang thai hoat dong cho line ngat
	EXTI_Init(&EXTI_InitStruct); // khoi tao cac thong so da set ben tren
}
	
