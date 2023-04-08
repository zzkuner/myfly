#include "spi.h"

void SPI1_Init(void)
{
 	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  
    
    //SPI1��ӳ�䵽B3��B4��B5
    AFIO->MAPR|=0x00000001;
    //IO��ʼ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
    //SPI����
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);
}   



u8 SPI1_RW_Byte(u8 txc)
{
	while((SPI1->SR&SPI_SR_TXE)==0);
	SPI1->DR = txc;
	while((SPI1->SR&SPI_SR_RXNE)==0);
	return SPI1->DR;	
}


u8 SPI1_Write_Reg(u8 reg_addr,u8 reg_val)
{
	SPI1_RW_Byte(reg_addr&0x7f);
	SPI1_RW_Byte(reg_val);
	return 0;
}


u8 SPI1_Read_Reg(u8 reg_addr)
{
	SPI1_RW_Byte(reg_addr|0x80);
	return SPI1_RW_Byte(0xff);
}

u8 SPI1_Read_Reg_Buffer(u8 reg_addr,void *buffer,u16 len)
{
	u8 *p = buffer;
	u16 i;
	SPI1_RW_Byte(reg_addr|0x80);
	for(i=0;i<len;i++)
	{
		*p++= SPI1_RW_Byte(0xff);
	}
	return 0;
}



////������SPI2ģ��ĳ�ʼ�����룬���ó�����ģʽ������SD Card/W25Q64/NRF24L01						  
////SPI�ڳ�ʼ��
////�������Ƕ�SPI2�ĳ�ʼ��



//void SPI2_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	SPI_InitTypeDef  SPI_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//PORTBʱ��ʹ�� 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//SPI2ʱ��ʹ�� 	

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB

//	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);  //PB13/14/15����

//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
//	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
//	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

//	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����

//	SPI2_ReadWriteByte(0xff);//��������		 


//}
////SPI �ٶ����ú���
////SpeedSet:
////SPI_BaudRatePrescaler_2   2��Ƶ   
////SPI_BaudRatePrescaler_8   8��Ƶ   
////SPI_BaudRatePrescaler_16  16��Ƶ  
////SPI_BaudRatePrescaler_256 256��Ƶ 

//void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
//{
//	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
//	SPI2->CR1 &= 0XFFC7;
//	SPI2->CR1 |= SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
//	SPI_Cmd(SPI2, ENABLE);

//}

////SPIx ��дһ���ֽ�
////TxData:Ҫд����ֽ�
////����ֵ:��ȡ�����ֽ�
//u8 SPI2_RW_Byte(u8 TxData)
//{
//	u8 retry = 0;
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
//	{
//		retry++;
//		if (retry > 200)return 0;
//	}
//	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
//	retry = 0;

//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
//	{
//		retry++;
//		if (retry > 200)return 0;
//	}
//	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
//}

