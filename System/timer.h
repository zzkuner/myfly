#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
extern float pitch,roll,yaw; 		//ŷ����
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����
extern short temp;					//�¶�	
extern float Setpitch,Setroll;
extern int motor1,motor2,servo1,servo2;

void TIM2_Int_Init(u16 arr,u16 psc);
 
#endif
