#include "led.h"
int flag_led;

void LED_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LED_GPIO_PORT , &GPIO_InitStruct);
}

void LED_GPIO_High(void)
{
	GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);

}

void LED_GPIO_Low(void)
{
	GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}


void LED_Change(void)
{
	
		if(flag_led==1)
		{
			flag_led=0;
			LED = !LED;
		
		}
}

