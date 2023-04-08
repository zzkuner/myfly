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
    float integral;
    
    float Diff; 
        
    float outPut;
}PID_Parameter;
extern PID_Parameter OUT_PIDx;
extern PID_Parameter OUT_PIDy;
extern PID_Parameter OUT_PIDz;

extern PID_Parameter IN_PIDx;
extern PID_Parameter IN_PIDy;
extern PID_Parameter IN_PIDz;

extern PID_Parameter High_PID;
extern PID_Parameter SpeedZ_PID;

extern PID_Parameter POSx_PID;
extern PID_Parameter POSy_PID;
extern PID_Parameter Speedx_PID;
extern PID_Parameter Speedy_PID;

//void pid_update(void);
void Get_AnglePID_Parameter(void);
void Get_GyroPID_Parameter(void);
void Get_HighPID_Parameter(void);
void Get_Alt_Speed_PID_Parameter(void);
void Get_FlowPosPID_Parameter(void);
void Get_FlowSpeedPID_Parameter(void);
void PID_Caculate(PID_Parameter *pid);
#endif

