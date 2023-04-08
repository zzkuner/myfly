#ifndef _ADC_H
#define _ADC_H
#include "sys.h"
#include "delay.h"

extern float Bat_Voltage;

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
void Get_Bat_Voltage(void);

#endif

