#include "servo.h"

void Servo_PWM_Init(u16 ARR,u16 PSC)
{
	//�����ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//ʹ�ܶ�ӦRCCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /*Timer3��������>��������
	CH1-->PA6 PB4 PC6
	CH2-->PA7 PB5 PC7
	CH3-->PB0 PC8
	CH4-->PB1 PC9
	*/
	//��ʼ��GPIO������Ϊ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
  GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
	
/*	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //ѡ��Timer3��ȫ��ӳ��*/


	//��ʼ��Timer
	TIM_TimeBaseStructure.TIM_Period = ARR;   							//��ʱ������
	//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	//���ڼ�����0��ʼ�����Դ˴�ӦΪ�������ڼ�1�����ֵΪ0xFFFF
	TIM_TimeBaseStructure.TIM_Prescaler = PSC;									//Ԥ��Ƶ��
	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ�����ֵΪ0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//ʱ�ӷ�Ƶ
	//���ö�ʱ������Ƶ��fCK_INT�������˲�������Ƶ�ʻ�׼fDTSʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//����ģʽ
	//�������ģʽ1 ��������������Ϻ����¼���������Ƚ��жϱ�־λ��ֻ�ڼ��������¼���ʱ������
  //�������ģʽ2 ��������������Ϻ����¼���������Ƚ��жϱ�־λ��ֻ�ڼ��������ϼ���ʱ������
  //�������ģʽ3 ��������������Ϻ����¼���������Ƚ��жϱ�־λ��ֻ�ڼ��������º����ϼ���ʱ��������
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);	//�������Ϲ��ܶԶ�ʱ�����г�ʼ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//����Ƚϼ��Ե�
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
//  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
//  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ�ܶ�ʱ��TIM2��CCR1�ϵ�Ԥװ��ֵ
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
//  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��TIM3
}

void Servo_PWM_Set(int16_t servo1 , int16_t servo2)
{
//    if(servo1>2500)servo1=2500;
//    if(servo1<250) servo1=250; 
//    if(servo2>2500)servo2=2500;
//    if(servo2<250)servo2=2;
	
    TIM_SetCompare1(TIM3,servo1);
    TIM_SetCompare2(TIM3,servo2);
}
