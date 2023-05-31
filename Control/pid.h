#ifndef _PID_H
#define _PID_H
#include "sys.h"

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    
    float intetegralMax;
    float intetegralMin;
    
    float outPutMax;
    float outPutMin;
    
    float Error;
    float lastError;
		float nexttolastError;
    float integral;
    
    float Diff; 
        
    float outPut;
}PID_Parameter;

extern PID_Parameter servo1_pid;
extern PID_Parameter servo2_pid;
extern PID_Parameter High_PID;
extern PID_Parameter Speed_PID;


void PID_Init(void);
void PID_Update(void);

#endif

