#include "servo.h"

void Servo_PWM_Init(u16 ARR,u16 PSC)
{
	//定义初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//使能对应RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /*Timer3————>复用引脚
	CH1-->PA6 PB4 PC6
	CH2-->PA7 PB5 PC7
	CH3-->PB0 PC8
	CH4-->PB1 PC9
	*/
	//初始化GPIO，设置为复用
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
	
/*	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //选择Timer3完全重映像*/


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
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);	//根据以上功能对定时器进行初始化
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式，TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//输出比较极性低
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);//根据结构体信息进行初始化
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
//  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
//  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能定时器TIM2在CCR1上的预装载值
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
//  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE); //使能定时器TIM3
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
