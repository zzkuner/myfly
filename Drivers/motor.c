#include "motor.h"

void Motor_PWM_Init(u16 ARR,u16 PSC)
{
	//定义初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//使能对应RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	//初始化GPIO，设置为复用
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



	//初始化Timer
	TIM_TimeBaseStructure.TIM_Period = ARR;   							//定时器周期
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	//由于计数从0开始，所以此处应为理想周期减1，最大值为0xFFFF
	TIM_TimeBaseStructure.TIM_Prescaler = PSC;									//预分频器
	//设置用来作为TIMx时钟频率除数的预分频值，最大值为0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//时钟分频
	//设置定时器输入频率fCK_INT与数字滤波器采样频率基准fDTS使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//计数模式
	//中央对齐模式1 计数器交替地向上和向下计数。输出比较中断标志位，只在计数器向下计数时被设置
  //中央对齐模式2 计数器交替地向上和向下计数。输出比较中断标志位，只在计数器向上计数时被设置
  //中央对齐模式3 计数器交替地向上和向下计数。输出比较中断标志位，只在计数器向下和向上计数时均被设置
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);	//根据以上功能对定时器进行初始化
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式，TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//输出比较极性低
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);//根据结构体信息进行初始化
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
//  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
//  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能定时器TIM4在CCR1上的预装载值
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
//  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
//  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE); //使能定时器TIM4
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
