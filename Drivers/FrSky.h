#ifndef _FrSky_H
#define _FrSky_H
#include "sys.h"
#include <stdio.h>
#include <string.h>

#define SBUS_SIGNAL_OK          0x00
#define SBUS_SIGNAL_LOST        0x01
#define SBUS_SIGNAL_FAILSAFE    0x03
#define ALL_CHANNELS


extern uint8_t inBuffer[25];
extern uint8_t sbus_data[25];
extern int16_t channels[18];
extern uint8_t toChannels;
extern uint8_t failsafe_status;


void FrSky_Uart2_Init(u32 bound);
void update_channels(void);

#endif


