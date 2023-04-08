#ifndef _IIC_H
#define _IIC_H
#include "sys.h"

#define IIC_SCL         PBout(8)
#define IIC_SDA_OUT     PBout(9)
#define IIC_SDA_IN      PBin(9)

#define SDA_OUT()       {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=(u32)3<<4;}//推挽输出
#define SDA_IN()        {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=(u32)8<<4;}//上拉输入


void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(u8 dat);
u8 IIC_Read_Byte(u8 ack);

void delay_2us(void);
#endif
