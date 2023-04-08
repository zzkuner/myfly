#ifndef __SPL06_H
#define __SPL06_H
#include "sys.h"
#include "math.h"
typedef struct 
{
    int32_t Original_press;
    int32_t Original_temp;
    
    float temp;
    float press;
    float ground_press;
    float ground_temp;
    
    
    float Org_Alt;
    float Org_Speed;
    float Fus_Speed;
    float Fus_Alt;
    
    float EP_Alt;
    float LP_Alt;
    float LP_Alt2;
    float LP_Speed;
    float offset_Alt;
    u8 check;
    
}Baro_Parameter;

extern Baro_Parameter Baro;

//��ѹ��������(sample/sec),Background ģʽʹ��
#define  PM_RATE_1			(0<<4)		//1 measurements pr. sec.
#define  PM_RATE_2			(1<<4)		//2 measurements pr. sec.
#define  PM_RATE_4			(2<<4)		//4 measurements pr. sec.			
#define  PM_RATE_8			(3<<4)		//8 measurements pr. sec.
#define  PM_RATE_16			(4<<4)		//16 measurements pr. sec.
#define  PM_RATE_32			(5<<4)		//32 measurements pr. sec.
#define  PM_RATE_64			(6<<4)		//64 measurements pr. sec.
#define  PM_RATE_128		(7<<4)		//128 measurements pr. sec.

//��ѹ�ز�������(times),Background ģʽʹ��
#define PM_PRC_1			0		//Sigle			kP=524288	,3.6ms
#define PM_PRC_2			1		//2 times		kP=1572864	,5.2ms
#define PM_PRC_4			2		//4 times		kP=3670016	,8.4ms
#define PM_PRC_8			3		//8 times		kP=7864320	,14.8ms
#define PM_PRC_16			4		//16 times		kP=253952	,27.6ms
#define PM_PRC_32			5		//32 times		kP=516096	,53.2ms
#define PM_PRC_64			6		//64 times		kP=1040384	,104.4ms
#define PM_PRC_128			7		//128 times		kP=2088960	,206.8ms




//�¶Ȳ�������(sample/sec),Background ģʽʹ��
#define  TMP_RATE_1			(0<<4)		//1 measurements pr. sec.
#define  TMP_RATE_2			(1<<4)		//2 measurements pr. sec.
#define  TMP_RATE_4			(2<<4)		//4 measurements pr. sec.			
#define  TMP_RATE_8			(3<<4)		//8 measurements pr. sec.
#define  TMP_RATE_16		(4<<4)		//16 measurements pr. sec.
#define  TMP_RATE_32		(5<<4)		//32 measurements pr. sec.
#define  TMP_RATE_64		(6<<4)		//64 measurements pr. sec.
#define  TMP_RATE_128		(7<<4)		//128 measurements pr. sec.

//�¶��ز�������(times),Background ģʽʹ��
#define TMP_PRC_1			0		//Sigle
#define TMP_PRC_2			1		//2 times
#define TMP_PRC_4			2		//4 times
#define TMP_PRC_8			3		//8 times
#define TMP_PRC_16			4		//16 times
#define TMP_PRC_32			5		//32 times
#define TMP_PRC_64			6		//64 times
#define TMP_PRC_128			7		//128 times


//SPL06_MEAS_CFG
#define MEAS_COEF_RDY		0x80
#define MEAS_SENSOR_RDY		0x40		//��������ʼ�����
#define MEAS_TMP_RDY		0x20		//���µ��¶�����
#define MEAS_PRS_RDY		0x10		//���µ���ѹ����

#define MEAS_CTRL_Standby				0x00		//����ģʽ
#define MEAS_CTRL_PressMeasure			0x01	//������ѹ����
#define MEAS_CTRL_TempMeasure			0x02	//�����¶Ȳ���
#define MEAS_CTRL_ContinuousPress		0x05	//������ѹ����
#define MEAS_CTRL_ContinuousTemp		0x06	//�����¶Ȳ���
#define MEAS_CTRL_ContinuousPressTemp	0x07	//������ѹ�¶Ȳ���



//FIFO_STS
#define SPL06_FIFO_FULL		0x02
#define SPL06_FIFO_EMPTY	0x01


//INT_STS
#define SPL06_INT_FIFO_FULL		0x04
#define SPL06_INT_TMP			0x02
#define SPL06_INT_PRS			0x01


//CFG_REG
#define SPL06_CFG_T_SHIFT	0x08	//oversampling times>8ʱ����ʹ��
#define SPL06_CFG_P_SHIFT	0x04



#define SP06_PSR_B2		0x00		//��ѹֵ
#define SP06_PSR_B1		0x01
#define SP06_PSR_B0		0x02
#define SP06_TMP_B2		0x03		//�¶�ֵ
#define SP06_TMP_B1		0x04
#define SP06_TMP_B0		0x05




#define SP06_PSR_CFG	0x06		//��ѹ��������
#define SP06_TMP_CFG	0x07		//�¶Ȳ�������
#define SP06_MEAS_CFG	0x08		//����ģʽ����

#define SP06_CFG_REG	0x09
#define SP06_INT_STS	0x0A
#define SP06_FIFO_STS	0x0B

#define SP06_RESET		0x0C
#define SP06_ID			0x0D

#define SP06_COEF		0x10		//-0x21,12���ֽ�
#define SP06_COEF_SRCE	0x28


#define SPL06_ADDRESS	0xEE

#define CS_SPL	PAout(15)

u8 SPL06_Init(void);
u8 SPL06_Write_Reg(u8 reg,u8 val);
u8 SPL06_Read_Reg(u8 reg);
u8 SPL06_Read_Buffer(u8 reg,void *buffer,u8 len);
void SPL06_Config_Temperature(u8 rate,u8 oversampling);
void SPL06_Config_Pressure(u8 rate,u8 oversampling);
void SPL06_Start(u8 mode);
int32_t SPL06_Get_Pressure_Adc(void);
int32_t SPL06_Get_Temperature_Adc(void);
void SPL06_Update_Pressure(void);
void SPL06_Update(void);
float SPL06_Get_Altitude(void);

void SPL06_Get_Ground_Parameter(void);


#endif

