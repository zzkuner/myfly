#include "PWM.h"


/*
程序功能:定时器综合使用函数


1、定时器类型
通用定时器：TIM2 TIM3 TIM4
高级定时器：TIM1
高级定时器可以输出三对互补pwm信号外加ch4通道，也就是一共七路

2、定时器通道
CH1 CH2 CH3 CH4

3、IO口类型

4、端口号

5、arr, psc

Note:STM32F103C6T6A没有TIM4!


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
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //使能TIM1定时器时钟线 
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
 
	//端口复用为PWM输出模式
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				 //LED0-->PB.5 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOx, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	//定时器初始化
	TIM_TimeBaseInitStrue.TIM_Period=arr; //自动装载值
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//预分频系数
	TIM_TimeBaseInitStrue.TIM_CounterMode= TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//时钟系数Tclk
	if(TIMx==TIM1)
	{
			/*
		STM32高级定时器PWM输出响应延迟解决办法_21考研人的博客-CSDN博客
		https://blog.csdn.net/qq_41787254/article/details/108889255
		
		*/
		TIM_TimeBaseInitStrue.TIM_RepetitionCounter=0;
		
	}
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStrue);
	
	//初始化比较函数
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM1;//PWM模式1
	TIM_OCInitTypeStrue.TIM_OCNPolarity=TIM_OCNPolarity_High; //CNT<CCR为高电平
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable;//使能
	TIM_OCInitTypeStrue.TIM_Pulse = 0;//初始状态占空比为0
	
	
	if(TIMx==TIM1)
	{
		//下面这句是高级定时器才有，输出PWM必须打开
		TIM_CtrlPWMOutputs(TIM1,ENABLE);  //确定让TIM1输入PWM
		
	}
	//通道预装载  字符类型
	switch(CHx)
	{
		case 1:
			TIM_OC1Init(TIMx, &TIM_OCInitTypeStrue);//通道初始化
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 2:
			TIM_OC2Init(TIMx, &TIM_OCInitTypeStrue);//通道初始化
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 3:
			TIM_OC3Init(TIMx, &TIM_OCInitTypeStrue);//通道初始化
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		case 4:
			TIM_OC4Init(TIMx, &TIM_OCInitTypeStrue);//通道初始化
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
			break;
		default:
			break;
		
	}
		
	//使能定时器
	TIM_Cmd(TIMx,ENABLE);
 
}
