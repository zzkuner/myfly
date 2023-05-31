#include "sys.h"

u8 report=0;			//默认开启上报
int motor1,motor2,servo1,servo2;
float Setpitch=0,Setroll=0;
float pitch,roll,yaw; 		//欧拉角
short aacx,aacy,aacz;		//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
short temp;					//温度	
 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Usart_init();	 	//串口初始化
	delay_init();	  //延时初始化 delay_ms(1000);
	BEEP_GPIO_Init(); 
	Motor_PWM_Init(20000-1, 72-1);
	Servo_PWM_Init(20000-1, 72-1);
	TIM2_Int_Init(200-1,720-1);
//	//	int x=10000,y=0;
	Motor_Unlock(1900,1100);
	BEEP_GPIO_High();
	FrSky_Uart2_Init(100000);
	Adc_Init();
	SPI1_Init();
	SPL06_Init();
	MPU_IIC_Init(); //MPU使用的IIC初始化
	while(MPU_Init())
	{
		printf("mpu error\n");
		delay_ms(200);
	};					//初始化MPU6050 
	
	while(mpu_dmp_init())
 	{
		printf("mpu dmp error\n");
 		delay_ms(200);
	} 
  PID_Init();
	BEEP_GPIO_Low();

 	while(1)
	{

//		int i;
//		static float Baro_Buf[20];
//		Baro.Org_Alt = SPL06_Get_Altitude();
////		//气压原始数据缓存
//////    for(i=19;i>0;i--)
//////    {
//////        Baro_Buf[i]=Baro_Buf[i-1];
//////    }
//    Baro_Buf[0]=Baro.Org_Alt;

//		printf("%f\n",Baro.Org_Alt );
//		delay_ms(100);
/********测量电池电压********/
		
		Get_Bat_Voltage();
		if(Bat_Voltage<11)
		{
			BEEP_GPIO_High();
		}
		else
		{
			BEEP_GPIO_Low();
		}
//////		printf("电池电压为 %f \n",Bat_Voltage);
///**********陀螺仪数据输出***************/		
if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
{ 
//	printf("%f,%f,%f\r\n",pitch,roll,yaw);
	temp=MPU_Get_Temperature();	//得到温度值
	MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
	if(report)mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//用自定义帧发送加速度和陀螺仪原始数据
	if(report)usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));

}
/********     根据无线串口输入并调整pid   ********/
	PID_Update();	
		
/********更新遥控器数据********/		
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
/********遥控器控制电机********/			
		motor1=motor2=channels[0]/2+1000;	
		//printf("%d\r\n",channels[0]);
		Motor_PWM_Set(motor1,motor2);
		
/********遥控器控制舵机********/		
//		servo1=channels[1];
//		servo2=channels[2];
//    Servo_PWM_Set(servo1,servo2);
	
printf("%f,%f,%f,%f\n",Setroll,roll,Setpitch,pitch);
	} 	
}
 
