#include "motor.h"

void Motor_PWM_Init(u16 ARR,u16 PSC)
{
	//�����ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//ʹ�ܶ�ӦRCCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	//��ʼ��GPIO������Ϊ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin8|GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
  GPIO_ResetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);



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
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);	//�������Ϲ��ܶԶ�ʱ�����г�ʼ��
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//����Ƚϼ��Ե�
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
//  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
//  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ�ܶ�ʱ��TIM4��CCR1�ϵ�Ԥװ��ֵ
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
//  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
//  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��TIM4
}

void Motor_PWM_Set(int16_t motor1 , int16_t motor2)
{
//    if(motor1>1900)motor1=1900;
//    if(motor1<0)motor1=0; 
//    if(motor2>1900)motor2=1900;
//    if(motor2<0)motor2=0;
	
    TIM_SetCompare1(TIM4,motor1);
    TIM_SetCompare2(TIM4,motor2);
}

void Motor_Unlock(int16_t MaxSpeed,int16_t MinSpeed)
{
	Motor_PWM_Set(MaxSpeed,MaxSpeed);
	delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
	Motor_PWM_Set(MinSpeed,MinSpeed);
	delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
}
