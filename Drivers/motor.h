#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

void Motor_PWM_Init(u16 ARR,u16 PSC);
void Motor_PWM_Set(int16_t motor1 , int16_t motor2);
void Motor_Unlock(int16_t MaxSpeed,int16_t MinSpeed);
#endif

