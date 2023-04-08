#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

 
 				  	    													  
void SPI1_Init(void);			 //³õÊ¼»¯SPI¿Ú 

u8 SPI1_RW_Byte(u8 txc);
u8 SPI1_Write_Reg(u8 reg_addr,u8 reg_val);
u8 SPI1_Read_Reg(u8 reg_addr);
u8 SPI1_Read_Reg_Buffer(u8 reg_addr,void *buffer,u16 len);



#endif

