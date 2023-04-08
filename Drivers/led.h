#ifndef __LED_H__
#define __LED_H__

#include "sys.h"


#define LED_GPIO_PIN GPIO_Pin_15
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_CLK RCC_APB2Periph_GPIOB
#define LED PBout(15)

void LED_GPIO_Init(void);
void LED_GPIO_High(void);
void LED_GPIO_Low(void);
void LED_Change(void);

extern int flag_led;

#endif

