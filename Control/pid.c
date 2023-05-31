#include "pid.h"
PID_Parameter servo1_pid;
PID_Parameter servo2_pid;
void PID_Init()
{
//    printf("PID_init begin \n");
    servo1_pid.Error=0.0;
    servo1_pid.lastError=0.0;
    servo1_pid.integral=0.0;   
    servo1_pid.Diff=0.0;
	
	  servo1_pid.outPutMax=1000;
    servo1_pid.outPutMin=-1000;
	  servo1_pid.intetegralMax=30;
    servo1_pid.intetegralMin=-30;   
  
    servo1_pid.Kp=5;
    servo1_pid.Ki=1;
    servo1_pid.Kd=0.4;
		servo1_pid.outPut=0;
	
	
	
	  servo2_pid.Error=0.0;
    servo2_pid.lastError=0.0;
    servo2_pid.integral=0.0;   
    servo2_pid.Diff=0.0;
	       
	  servo2_pid.outPutMax=1000;
    servo2_pid.outPutMin=-1000;
	  servo2_pid.intetegralMax=30;
    servo2_pid.intetegralMin=-30;   
		
    servo2_pid.Kp=5;
    servo2_pid.Ki=1;
    servo2_pid.Kd=0.4;
		servo2_pid.outPut=0;
		
//    printf("PID_init end \n");
}


void PID_Update(void)
{
	if(USART_RX_STA&0x8000)
	{
			char newpid[6][20];
			int i=0,x=0,p=0;
			while (i<=5)
			{
					if( USART_RX_BUF[x] == 0x0a)
					{
						p=0;
						i++;	
					}
					else
						{
								if(USART_RX_BUF[x] !=  ',')
								{
									newpid[i][p]=USART_RX_BUF[x];
									p++;
								}
								if( USART_RX_BUF[x] == ',')
								{
									newpid[i][p]='\0';
									p=0;
									i++;	
								}
						}
					x++;
			}
			sscanf(newpid[0],"%f",&servo1_pid.Kp);
			sscanf(newpid[1],"%f",&servo1_pid.Ki);
			sscanf(newpid[2],"%f",&servo1_pid.Kd);
			sscanf(newpid[3],"%f",&servo2_pid.Kp);
			sscanf(newpid[4],"%f",&servo2_pid.Ki);
			sscanf(newpid[5],"%f",&servo2_pid.Kd);
			
			USART_RX_STA=0;
		}


}

