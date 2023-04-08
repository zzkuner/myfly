#ifndef __USART_H
#define __USART_H
#include "sys.h"

#include <stdio.h>


#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���

/** 
  * ���ں궨�壬��ͬ�Ĵ��ڹ��ص����ߺ�IO��һ������ֲʱ��Ҫ�޸��⼸����
	* 1-�޸�����ʱ�ӵĺ꣬uart1���ص�apb2���ߣ�����uart���ص�apb1����
	* 2-�޸�GPIO�ĺ�
  */
	
	
// ����1-USART1
#define  USARTx                   USART1
#define  USART_CLK                RCC_APB2Periph_USART1
#define  USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  USART_BAUDRATE           115200

// USART GPIO ���ź궨��
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

//ʹ��ʾ��

//char a[]={"11"};
//char b[]={'a','b','\n'};
//uint16_t c = 0x73b6;


//printf("aaaa\n\r");
//Usart_SendByte( USART1, 'a');
//Usart_SendString( USART1, a);
//Usart_SendArray(USART1, b, 3);
//Usart_SendHalfWord( USART1, c);













