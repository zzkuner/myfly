#include "exti.h"
//////////////////////////////////////////////////////////////////////////////////	 

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

   //GPIOB.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
		EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}



void EXTI4_IRQHandler(void)
{
	
		delay_ms(5);
		if(KEY==0)
		{
			LED = !LED;
		}
		while(!KEY);
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}
 
