#include "exti.h"
//////////////////////////////////////////////////////////////////////////////////	 

//外部中断0服务程序
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

   //GPIOB.4	  中断线以及中断初始化配置  下降沿触发	//KEY
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
		EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}



void EXTI4_IRQHandler(void)
{
	
		delay_ms(5);
		if(KEY==0)
		{
			LED = !LED;
		}
		while(!KEY);
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}
 
