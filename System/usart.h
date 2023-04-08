#ifndef __USART_H
#define __USART_H
#include "sys.h"

#include <stdio.h>


#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记

/** 
  * 串口宏定义，不同的串口挂载的总线和IO不一样，移植时需要修改这几个宏
	* 1-修改总线时钟的宏，uart1挂载到apb2总线，其他uart挂载到apb1总线
	* 2-修改GPIO的宏
  */
	
	
// 串口1-USART1
#define  USARTx                   USART1
#define  USART_CLK                RCC_APB2Periph_USART1
#define  USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  USART_TX_GPIO_PORT       GPIOA   
#define  USART_TX_GPIO_PIN        GPIO_Pin_9
#define  USART_RX_GPIO_PORT       GPIOA
#define  USART_RX_GPIO_PIN        GPIO_Pin_10

#define  USART_IRQ                USART1_IRQn
#define  USART_IRQHandler         USART1_IRQHandler


void Usart_init(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif	   

//使用示例

//char a[]={"11"};
//char b[]={'a','b','\n'};
//uint16_t c = 0x73b6;


//printf("aaaa\n\r");
//Usart_SendByte( USART1, 'a');
//Usart_SendString( USART1, a);
//Usart_SendArray(USART1, b, 3);
//Usart_SendHalfWord( USART1, c);













