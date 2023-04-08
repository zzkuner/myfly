#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"

void Servo_PWM_Init(u16 ARR,u16 PSC);
void Servo_PWM_Set(int16_t servo1 , int16_t servo2);
#endif

