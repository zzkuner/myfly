#include "FrSky.h"

uint8_t inBuffer[25];
uint8_t sbus_data[25] = {
  0x00,0x00,0x00,0x20,0x00,0xff,0x07,0x40,0x00,0x02,0x10,0x80,0x2c,0x64,0x21,0x0b,0x59,0x08,0x40,0x00,0x02,0x10,0x80,0x00,0x00};
int16_t channels[18]  = {
  1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,0,0};
uint8_t toChannels = 0;
uint8_t  failsafe_status = SBUS_SIGNAL_FAILSAFE;
unsigned char bufferIndex=0;

void FrSky_Uart2_Init(u32 bound)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);   //GPIOA时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  //串口2时钟
		

		//IO初始化
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //复用推挽输出
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		//USART2中断设置
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);                 

		//USART2初始化设置
		USART_InitStructure.USART_BaudRate = bound;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_9b;
    USART_InitStructure.USART_StopBits = USART_StopBits_2;
		USART_InitStructure.USART_Parity = USART_Parity_Even;//偶校验位

//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	//USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		USART_InitStructure.USART_Mode = USART_Mode_Rx;	
		USART_Init(USART2, &USART_InitStructure); //初始化串口

		//开启中断
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
//	USART_ITConfig(USART2, USART_IT_TXE,  ENABLE);

		//使能串口
		USART_Cmd(USART2, ENABLE);       


}


void USART2_IRQHandler(void)
{
    unsigned char	Uart_Get_Data;
     // handle USART2 Rx interrupt
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {	 	
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        Uart_Get_Data = USART_ReceiveData(USART2)& 0xFF;
        if( bufferIndex==0 && Uart_Get_Data == 0x0F	)
        {
            bufferIndex = 0;
            inBuffer[bufferIndex] = Uart_Get_Data;
            inBuffer[24] = 0xff;
        }else
				{
						bufferIndex ++;
            inBuffer[bufferIndex] = Uart_Get_Data;
				}
        if (bufferIndex == 24 &  inBuffer[24] == 0x00) // SBUS frame complete
        {
            memcpy(sbus_data,inBuffer,25);
						toChannels = 1;
            bufferIndex = 0; 
        }			
     } 
} 

void update_channels(void)
{
        channels[0]  = ((sbus_data[1]|sbus_data[2]<< 8) & 0x07FF);
        channels[1]  = ((sbus_data[2]>>3|sbus_data[3]<<5) & 0x07FF);
        channels[2]  = ((sbus_data[3]>>6|sbus_data[4]<<2|sbus_data[5]<<10) & 0x07FF);
        channels[3]  = ((sbus_data[5]>>1|sbus_data[6]<<7) & 0x07FF);
        channels[4]  = ((sbus_data[6]>>4|sbus_data[7]<<4) & 0x07FF);
        channels[5]  = ((sbus_data[7]>>7|sbus_data[8]<<1|sbus_data[9]<<9) & 0x07FF);
        channels[6]  = ((sbus_data[9]>>2|sbus_data[10]<<6) & 0x07FF);
        channels[7]  = ((sbus_data[10]>>5|sbus_data[11]<<3) & 0x07FF); // & the other 8 + 2 channels if you need them
        channels[8]  = ((sbus_data[12]|sbus_data[13]<< 8) & 0x07FF);
        channels[9]  = ((sbus_data[13]>>3|sbus_data[14]<<5) & 0x07FF);
        channels[10] = ((sbus_data[14]>>6|sbus_data[15]<<2|sbus_data[16]<<10) & 0x07FF);
        channels[11] = ((sbus_data[16]>>1|sbus_data[17]<<7) & 0x07FF);
        channels[12] = ((sbus_data[17]>>4|sbus_data[18]<<4) & 0x07FF);
        channels[13] = ((sbus_data[18]>>7|sbus_data[19]<<1|sbus_data[20]<<9) & 0x07FF);
        channels[14] = ((sbus_data[20]>>2|sbus_data[21]<<6) & 0x07FF);
        channels[15] = ((sbus_data[21]>>5|sbus_data[22]<<3) & 0x07FF);
        // Failsafe
        failsafe_status = SBUS_SIGNAL_OK;
        if (sbus_data[23] & (1<<2))
        {
        failsafe_status = SBUS_SIGNAL_LOST;
        }
        if (sbus_data[23] & (1<<3))
        {
        failsafe_status = SBUS_SIGNAL_FAILSAFE;
        }
}

















