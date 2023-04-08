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

u8 report=1;			//默认开启上报

 int main(void)
 {	 
//	float pitch,roll,yaw; 		//欧拉角
//	short aacx,aacy,aacz;		//加速度传感器原始数据
//	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
//	short temp;					//温度	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Usart_init();	 	//串口初始化
	delay_init();	  //延时初始化 delay_ms(1000);
	 

	
	Motor_PWM_Init(20000-1, 72-1);
	Servo_PWM_Init(20000-1, 72-1);
//	//	int x=10000,y=0;
//	Motor_Unlock(2000,1000);
//	delay_ms(1000);
//	delay_ms(1000);
	FrSky_Uart2_Init(100000);
	Adc_Init();
	SPI1_Init();
	SPL06_Init();
//	MPU_IIC_Init(); //MPU使用的IIC初始化

	 
//	while(MPU_Init())
//	{
//		printf("mpu error\n");
//		delay_ms(200);
//	};					//初始化MPU6050 
//	
//	while(mpu_dmp_init())
// 	{
//		printf("mpu dmp error\n");
// 		delay_ms(200);
//	} 



 	while(1)
	{

//		int i;
		static float Baro_Buf[20];
		Baro.Org_Alt = SPL06_Get_Altitude();
//		//气压原始数据缓存
////    for(i=19;i>0;i--)
////    {
////        Baro_Buf[i]=Baro_Buf[i-1];
////    }
//    Baro_Buf[0]=Baro.Org_Alt;

		printf("%f\n",Baro.Org_Alt );
		delay_ms(100);
		

//		Get_Bat_Voltage();
//		#ifdef Debug
//		printf("电池电压为 %f \n",Bat_Voltage);
//		#endif
//						update_channels();
//		        printf( "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", 
//                channels[0],
//                channels[1],
//                channels[2],
//                channels[3],
//                channels[4],
//                channels[5],
//                channels[6],
//                channels[7],
//                channels[8],
//                channels[9],
//                channels[10],
//                channels[11]
//               );   
//                 
//					Motor_PWM_Set();


		
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{ 
//			//printf("%f,%f,%f\r\n",pitch,roll,yaw);
//			temp=MPU_Get_Temperature();	//得到温度值
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
//			if(report)mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//用自定义帧发送加速度和陀螺仪原始数据
//			if(report)usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));

//		}
	} 	
}
 
