#include "PWM.h"


/*
������:��ʱ���ۺ�ʹ�ú���


1����ʱ������
ͨ�ö�ʱ����TIM2 TIM3 TIM4
�߼���ʱ����TIM1
�߼���ʱ������������Ի���pwm�ź����ch4ͨ����Ҳ����һ����·

2����ʱ��ͨ��
CH1 CH2 CH3 CH4

3��IO������

4���˿ں�

5��arr, psc

Note:STM32F103C6T6Aû��TIM4!


*/
void PWM_Init(TIM_TypeDef* TIMx, u8 CHx, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x,   u16 arr, u16 psc)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	 TIM_OCInitTypeDef TIM_OCInitTypeStrue;
	 
	 //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		 
	 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO ,ENABLE);
	 
	 if(TIMx==TIM1)
	 {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //ʹ��TIM1��ʱ��ʱ���� 
	 }
	 if(TIMx==TIM2)
	 {
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	 
	 }
	 if(TIMx==TIM3)
	 {
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	  
	 }
	 if(TIMx==TIM4)
	 {
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	 }
	 if(GPIOx==GPIOA)
	 {
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO ,ENABLE);
	 }
	 if(GPIOx==GPIOB)
	 {
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ,ENABLE);
	 }
	 if(GPIOx==GPIOC)
	 {
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO ,ENABLE);
	 }
 
	//�˿ڸ���ΪPWM���ģʽ
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				 //LED0-->PB.5 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOx, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	
	//��ʱ����ʼ��
	TIM_TimeBaseInitStrue.TIM_Period=arr; //�Զ�װ��ֵ
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//Ԥ��Ƶϵ��
	TIM_TimeBaseInitStrue.TIM_CounterMode= TIM_CounterMode_Up;//����ģʽ
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ��ϵ��Tclk
	if(TIMx==TIM1)
	{
			/*
		STM32�߼���ʱ��PWM�����Ӧ�ӳٽ���취_21�����˵Ĳ���-CSDN����
		https://blog.csdn.net/qq_41787254/article/details/108889255
		
		*/
		TIM_TimeBaseInitStrue.TIM_RepetitionCounter=0;
		
	}
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStrue);
	
	//��ʼ���ȽϺ���
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM1;//PWMģʽ1
	TIM_OCInitTypeStrue.TIM_OCNPolarity=TIM_OCNPolarity_High; //CNT<CCRΪ�ߵ�ƽ
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable;//ʹ��
	TIM_OCInitTypeStrue.TIM_Pulse = 0;//��ʼ״̬ռ�ձ�Ϊ0
	
	
	if(TIMx==TIM1)
	{
		//��������Ǹ߼���ʱ�����У����PWM�����
		TIM_CtrlPWMOutputs(TIM1,ENABLE);  //ȷ����TIM1����PWM
		
	}
	//ͨ��Ԥװ��  �ַ�����
	switch(CHx)
	{
		case 1:
			TIM_OC1Init(TIMx, &TIM_OCInitTypeStrue);//ͨ����ʼ��
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 2:
			TIM_OC2Init(TIMx, &TIM_OCInitTypeStrue);//ͨ����ʼ��
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 3:
			TIM_OC3Init(TIMx, &TIM_OCInitTypeStrue);//ͨ����ʼ��
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 4:
			TIM_OC4Init(TIMx, &TIM_OCInitTypeStrue);//ͨ����ʼ��
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		default:
			break;
		
	}
		
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIMx,ENABLE);
 
}
