/**
  ******************************************************************************/
#include "usart.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 


//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* Ƕ�������жϿ�������ѡ�� */
//	/* ��ʾ NVIC_PriorityGroupConfig() ����������ֻ��Ҫ����һ�����������ȼ�����*/
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* �������ȼ�*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */

 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void Usart_init(void){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	USART_APBxClkCmd(USART_CLK, ENABLE);	//ʹ��USARTʱ��
  USART_GPIO_APBxClkCmd(USART_GPIO_CLK, ENABLE);//ʹ��GPIOAʱ��
	//USART1_TX   
  GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO
   
  //USART1_RX	  ��ʼ��
  GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = USART_BAUDRATE;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USARTx, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USARTx, ENABLE);                    //ʹ�ܴ���1 

}

/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
	
	//	// ʹ�ܴ��ڷ����ж�
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
		//	// ʹ�ܴ��ڷ����ж�
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
		//	// ʹ�ܴ��ڷ����ж�
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx);
}


void USART1_IRQHandler(void)
{
    uint16_t Res;
		/*�����ж�*/
    //�ж��Ƿ�ΪUSART1�Ľ����ж�
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
			Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
//			//printf("���յ����ݣ�");
			USART_SendData(USART1,Res);
			
			
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else 
					{
						USART_RX_STA|=0x8000;
					}					//��������� 
				}
			else //��û�յ�0X0d
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				 }
			}
			
				
				
				
     }   
		
		/*�����ж�*/
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {  
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET)
			{
			
			};
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE); //�رշ����ж�
    }   
} 
#endif	
