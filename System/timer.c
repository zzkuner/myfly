#include "timer.h"

//通用定时器2中断初始化
//arr：自动重装值。
//psc：时钟预分频数

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

	//中断优先级NVIC设置
  NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}
//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
		{
			
/********pid控制舵机********/		
//pitch  servo2 下舵机
//roll  servo1 上舵机
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
			
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update );  //清除TIMx更新中断标志 

		}
}












