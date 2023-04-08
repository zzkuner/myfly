#ifndef __KEY_H__
#define __KEY_H__

#include "sys.h"

#define KEY_GPIO_PIN  GPIO_Pin_12
#define KEY_GPIO_PORT GPIOB
#define KEY_GPIO_CLK  RCC_APB2Periph_GPIOB
#define KEY PBin(12)

void KEY_Init(void);
void KEY_Scan(void);

extern int flag_key;
#endif

