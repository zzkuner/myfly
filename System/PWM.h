#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

/*********
Ê¹ÓÃÊ¾Àý£º


//	PWM_Init(TIM1,CH1, GPIOA, GPIO_Pin_8, 20000-1, 72-1);
//	PWM_Init(TIM1,CH2, GPIOA, GPIO_Pin_9, 20000-1, 72-1);


//			TIM_SetCompare1(TIM1,x);
//			TIM_SetCompare2(TIM1,x);

**********/
#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 4

void PWM_Init(TIM_TypeDef* TIMx, u8 CHx, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x,  u16 arr, u16 psc);


#endif

