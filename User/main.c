#include "sys.h"

//int main(void)
//{
//	delay_init();
//	Motor_PWM_Init(20000-1, 72-1);
//	Servo_PWM_Init(20000-1, 72-1);
//	//	int x=10000,y=0;
//	Motor_Unlock(2000,1000);

////	KEY_GPIO_Init();
////	LED_GPIO_Init();
////	delay_ms(100);
////	USART_Config();
////		while(1)
////		{

////			
////				delay_ms(1000);
////		}
////}

u8 report=1;			//Ĭ�Ͽ����ϱ�
int motor1,motor2,servo1,servo2;

 int main(void)
 {	 
//	float pitch,roll,yaw; 		//ŷ����
//	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
//	short gyrox,gyroy,gyroz;	//������ԭʼ����
//	short temp;					//�¶�	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Usart_init();	 	//���ڳ�ʼ��
	delay_init();	  //��ʱ��ʼ�� delay_ms(1000);
	BEEP_GPIO_Init(); 
	Motor_PWM_Init(20000-1, 72-1);
	Servo_PWM_Init(20000-1, 72-1);
//	//	int x=10000,y=0;
	Motor_Unlock(2000,1000);
	BEEP_GPIO_High();
//	delay_ms(1000);
//	delay_ms(1000);
	FrSky_Uart2_Init(100000);
	Adc_Init();
	SPI1_Init();
	SPL06_Init();
	MPU_IIC_Init(); //MPUʹ�õ�IIC��ʼ��

	 
//	while(MPU_Init())
//	{
//		printf("mpu error\n");
//		delay_ms(200);
//	};					//��ʼ��MPU6050 
//	
//	while(mpu_dmp_init())
// 	{
//		printf("mpu dmp error\n");
// 		delay_ms(200);
//	} 

	BEEP_GPIO_Low();

 	while(1)
	{

//		int i;
//		static float Baro_Buf[20];
//		Baro.Org_Alt = SPL06_Get_Altitude();
////		//��ѹԭʼ���ݻ���
//////    for(i=19;i>0;i--)
//////    {
//////        Baro_Buf[i]=Baro_Buf[i-1];
//////    }
//    Baro_Buf[0]=Baro.Org_Alt;

//		printf("%f\n",Baro.Org_Alt );
//		delay_ms(100);
/********������ص�ѹ********/
		
		Get_Bat_Voltage();
		if(Bat_Voltage<11)
		{
			BEEP_GPIO_High();
		}
		else
		{
			BEEP_GPIO_Low();
		}
////		printf("��ص�ѹΪ %f \n",Bat_Voltage);
		
/********����ң��������********/		
		update_channels();
		
//		printf( "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", 
//				channels[0],
//				channels[1],
//				channels[2],
//				channels[3],
//				channels[4],
//				channels[5],
//				channels[6],
//				channels[7],
//				channels[8],
//				channels[9],
//				channels[10],
//				channels[11]
//			 );   
/********ң�������Ƶ��ת��********/			
		motor1=motor2=channels[0]/2+900;		
		Motor_PWM_Set(motor1,motor2);
		servo1=channels[1];
		servo2=channels[2];
    Servo_PWM_Set(servo1,servo2);

		
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{ 
//			//printf("%f,%f,%f\r\n",pitch,roll,yaw);
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			if(report)mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���Զ���֡���ͼ��ٶȺ�������ԭʼ����
//			if(report)usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));

//		}
	} 	
}
 
