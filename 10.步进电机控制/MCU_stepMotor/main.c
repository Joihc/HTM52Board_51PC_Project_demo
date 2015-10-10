/********************************* �����к�̫�������޹�˾ *******************************
* ʵ �� �� ���¶ȴ�������λ��ʵ��
* ʵ��˵�� ������modbusЭ�飬ʵʱͬ�����ݵ���λ��
* ʵ��ƽ̨ ����̫51��Ƭ�������� V1.1
* ���ӷ�ʽ ������ñCN9 ����1,2�̽ӣ�����3,4�̽ӣ�����5,6�̽ӣ�����7,8�̽ӣ�
*            ����������ӷ�ʽ�����߽�WX1���ۺ��߽�WX2�����߽�WX3�����߽�WX4,���߽�VCC
* ע    �� ��
* ��    �� ����̫���Ӳ�Ʒ�з���    QQ ��1909197536
* ��    �� ��http://shop120013844.taobao.com/
****************************************************************************************/
#include "REG52.H"
#include "system.h"
#include "modbusRTU.h"
#include <string.h>
#include <stdio.h>

sfr T2MOD  = 0xC9;
sfr IPH    = 0xB7;

#define uchar unsigned char
#define uint unsigned int
#define FOSC 11059200L //�������ã�Ĭ��ʹ��11.0592M Hz
//#define FOSC 12000000L //�������ã�ʹ��12M Hz
//#define FOSC 24000000L //�������ã�ʹ��24M Hz
#define T1MS (65536-FOSC/12/1000) 

//IO�ӿڶ���
sbit WX1 = P0^0;	  //����ܽ�
sbit WX2 = P0^1;
sbit WX3 = P0^2;
sbit WX4 = P0^3;

sbit dula = P2^6;
sbit wela = P2^7;


int stepmotor_speed = 0;
unsigned char MotorStep = 0;

void Timer1Init();

/*******************************************************************************
* �� �� �� ��main
* �������� ��������
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void main()
{
	unsigned int temp=0;
	//�ر������
	dula = 1;
	P0 = 0xff;
	dula = 0;
	
  SystemInit();
	init_MODBUS();
	
	Timer1Init();
	Delayms(200);
	while(1)
	{				
				//����Ҫ���������ݶ�ȡ��������
			  /*start*/

			  /*end*/
		 	//ͬ�����������ݵ�ʵ������Ч��
			  /*start*/
				
//		  temp++; 
//		if(temp == 180) 
//		{
//				temp = 0;
//				Delayms(2000);
//		}
//		Delayms(30);
		

		
			  /*end*/
	}
}

void Timer1Init()
{
	 //�������ȼ�,��Ϊ���
	  IPH |= 0x80;
	  IP |= 0x80;
	
	  TMOD = TMOD | 0x10;                    //set timer1 as mode1 (16-bit)
    TL1 = (65536 - 20000)%256;                     //initial timer1 low byte
    TH1 = (65536 - 20000)/256;                //initial timer1 high byte
    TR1 = 1;                        //timer1 start running
    ET1 = 1;                        //enable timer1 interrupt
}

/*******************************************************************************
* �� �� �� ��InitMotor
* �������� ����ʼ���������
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void InitMotor()
{
  WX1 = 1;
  WX2 = 1;
  WX3 = 1;
  WX4 = 1;
}

/*******************************************************************************
* �� �� �� ��SetMotor
* �������� �����Ʋ������
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void SetMotor()
{
		switch(MotorStep)
		{
		   case 0:	
				WX1 = 0;		 // WX1	   
				WX2 = 1;
				WX3 = 1;
				WX4 = 1;
				MotorStep = 1;
		   break;

		   case 1:		 
				WX1 = 0;		 // WX1WX2 
				WX2 = 0;
				WX3 = 1;
				WX4 = 1;
				MotorStep = 2;
		   break;

		   case 2:	   //WX2
				WX1 = 1;
				WX2 = 0;		 
				WX3 = 1;
				WX4 = 1;		   
				MotorStep = 3;
		   break;
		   
		   case 3:		//WX2WX3
				WX1 = 1;
				WX2 = 0;		   
				WX3 = 0;
				WX4 = 1;
				MotorStep = 4;
		   break;
		   case 4:		 //WX3
				WX1 = 1;
				WX2 = 1;		   
				WX3 = 0;
				WX4 = 1;
				MotorStep = 5;
		   break;
		   
		   case 5:			  //WX3WX4
				WX1 = 1;
				WX2 = 1;		    
				WX3 = 0;
				WX4 = 0;
				MotorStep = 6;
		   break;
		   case 6:			  //WX4
				WX1 = 1;
				WX2 = 1;		  
				WX3 = 1;
				WX4 = 0;
				MotorStep = 7;
		   break;
		   case 7:			//WX4WX1
				WX1 = 0;
				WX2 = 1;		   
				WX3 = 1;
				WX4 = 0;
				MotorStep = 0;
		   break;		
		}
}

/*******************************************************************************
* �� �� �� ��SetMotor
* �������� �����Ʋ������
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void SetMotorRev()
{
		switch(MotorStep)
		{
		   case 0:	
				WX1 = 0;		 // WX1	   
				WX2 = 1;
				WX3 = 1;
				WX4 = 1;
				MotorStep = 7;
		   break;

		   case 1:		 
				WX1 = 0;		 // WX1WX2 
				WX2 = 0;
				WX3 = 1;
				WX4 = 1;
				MotorStep = 0;
		   break;

		   case 2:	   //WX2
				WX1 = 1;
				WX2 = 0;		 
				WX3 = 1;
				WX4 = 1;		   
				MotorStep = 1;
		   break;
		   
		   case 3:		//WX2WX3
				WX1 = 1;
				WX2 = 0;		   
				WX3 = 0;
				WX4 = 1;
				MotorStep = 2;
		   break;
		   case 4:		 //WX3
				WX1 = 1;
				WX2 = 1;		   
				WX3 = 0;
				WX4 = 1;
				MotorStep = 3;
		   break;
		   
		   case 5:			  //WX3WX4
				WX1 = 1;
				WX2 = 1;		    
				WX3 = 0;
				WX4 = 0;
				MotorStep = 4;
		   break;
		   case 6:			  //WX4
				WX1 = 1;
				WX2 = 1;		  
				WX3 = 1;
				WX4 = 0;
				MotorStep = 5;
		   break;
		   case 7:			//WX4WX1
				WX1 = 0;
				WX2 = 1;		   
				WX3 = 1;
				WX4 = 0;
				MotorStep = 6;
		   break;		
		}
}

void Timer1Int() interrupt 3 using 0
{
	int temp;
//	stepmotor_speed = modbus_Addt.stepmotor_speed * 100;// 0ms - 10ms
//	temp = 65536 - 921.6*(1000+stepmotor_speed);
	temp = 64614 - 92*(100-modbus_Addt.stepmotor_speed);
	TH1 = temp>>8;
	TL1 = temp;
	if(modbus_Addt.stepmotor_switch == 0 || modbus_Addt.stepmotor_speed == 0) return;
	if(modbus_Addt.stepmotor_dir == 0)
	{
		SetMotor();//��ת
	}else
	{
		SetMotorRev();//��ת
	}	
}
