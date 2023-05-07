#include "beep.h"


void BEEP_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = BEEP_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BEEP_GPIO_PORT , &GPIO_InitStruct);
}

void BEEP_GPIO_High(void)
{
	GPIO_SetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);

}

void BEEP_GPIO_Low(void)
{
	GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);
}


void BEEP_Change(void)
{
	BEEP = !BEEP;
}
