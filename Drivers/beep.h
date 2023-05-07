#ifndef __BEEP_H__
#define __BEEP_H__

#include "sys.h"

#define BEEP_GPIO_PIN  GPIO_Pin_13
#define BEEP_GPIO_PORT GPIOC
#define BEEP_GPIO_CLK  RCC_APB2Periph_GPIOC
#define BEEP 					 PCout(13)

void BEEP_GPIO_Init(void);
void BEEP_GPIO_High(void);
void BEEP_GPIO_Low(void);
void BEEP_Change(void);

#endif
