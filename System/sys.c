#include "sys.h"
/********************************************************************************
引脚定义
舵机：TIM3  A6 A7 (B0 B1)
电机：TIM4  B6 B7 (B8 B9)

********************************************************************************/


//********************************************************************************  
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断ss
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

//uint8_t System_Init(void)
//{
////    //中断分组
////    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	 
////    
////    //打开AFIO时钟
////    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );

//    //开启SWD 禁用JTAG
//    AFIO->MAPR&=0xF8FFFFFF;
//    AFIO->MAPR|=0x02000000;
//    
////    //配置滴答定时器1ms中断
////    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
////    SysTick_Config(SystemCoreClock /(1000));

//}

