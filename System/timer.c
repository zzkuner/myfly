#include "timer.h"

//ͨ�ö�ʱ��2�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM2��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

	//�ж����ȼ�NVIC����
  NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
			
/********pid���ƶ��********/		
//pitch  servo2 �¶��
//roll  servo1 �϶��
		servo1_pid.Error = Setroll - roll;
		servo1_pid.integral += servo1_pid.Error;

		if(servo1_pid.integral > servo1_pid.intetegralMax )
		{
			servo1_pid.integral = servo1_pid.intetegralMax;
		}
		else if (servo1_pid.integral < servo1_pid.intetegralMin)
		{
			servo1_pid.integral = servo1_pid.intetegralMin;
		}

		servo1_pid.outPut = servo1_pid.Kp * servo1_pid.Error + servo1_pid.Ki * servo1_pid.integral + servo1_pid.Kd * (servo1_pid.Error - servo1_pid.lastError);
		servo1_pid.lastError =servo1_pid.Error;

		if(servo1_pid.outPut>servo1_pid.outPutMax)
		{
			servo1_pid.outPut=servo1_pid.outPutMax;
		}else if(servo1_pid.outPut < servo1_pid.outPutMin)
		{
			servo1_pid.outPut = servo1_pid.outPutMin;
		}
		servo1 =1020 + servo1_pid.outPut;



		servo2_pid.Error = Setpitch - pitch;
		servo2_pid.integral += servo2_pid.Error;

		if(servo2_pid.integral > servo2_pid.intetegralMax )
		{
			servo2_pid.integral = servo2_pid.intetegralMax;
		}
		else if (servo2_pid.integral < servo2_pid.intetegralMin)
		{
			servo2_pid.integral = servo2_pid.intetegralMin;
		}

		servo2_pid.outPut = servo2_pid.Kp * servo2_pid.Error + servo2_pid.Ki * servo2_pid.integral + servo2_pid.Kd * (servo2_pid.Error - servo2_pid.lastError);
		servo2_pid.lastError =servo2_pid.Error;
		if(servo2_pid.outPut>servo2_pid.outPutMax)
		{
			servo2_pid.outPut = servo2_pid.outPutMax;
		}else if(servo2_pid.outPut < servo2_pid.outPutMin)
		{
			servo2_pid.outPut = servo2_pid.outPutMin;
		}
		servo2 =1000 + servo2_pid.outPut;

		Servo_PWM_Set(servo1,servo2);
			
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update );  //���TIMx�����жϱ�־ 

		}
}












