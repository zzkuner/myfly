#include "sys.h"
/********************************************************************************
���Ŷ���
�����TIM3  A6 A7 (B0 B1)
�����TIM4  B6 B7 (B8 B9)

********************************************************************************/


//********************************************************************************  
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�ss
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

//uint8_t System_Init(void)
//{
////    //�жϷ���
////    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	 
////    
////    //��AFIOʱ��
////    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );

//    //����SWD ����JTAG
//    AFIO->MAPR&=0xF8FFFFFF;
//    AFIO->MAPR|=0x02000000;
//    
////    //���õδ�ʱ��1ms�ж�
////    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
////    SysTick_Config(SystemCoreClock /(1000));

//}

