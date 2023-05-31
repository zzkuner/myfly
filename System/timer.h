#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
extern float pitch,roll,yaw; 		//欧拉角
extern short aacx,aacy,aacz;		//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
extern short temp;					//温度	
extern float Setpitch,Setroll;
extern int motor1,motor2,servo1,servo2;

void TIM2_Int_Init(u16 arr,u16 psc);
 
#endif
