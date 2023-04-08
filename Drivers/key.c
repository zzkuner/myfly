#include "key.h"
//extern int flag_led;
int flag_key=0;

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = KEY_GPIO_PIN;
	GPIO_Init(KEY_GPIO_PORT , &GPIO_InitStruct);
}

void KEY_Scan(void)
{
		if(KEY==0)
				{
					delay_ms(5);
					if(KEY==0)
						{
							flag_key = 1;
						}
					while(!KEY);
				}
}
