/********************************* �����к�̫�������޹�˾ *******************************
* ʵ �� �� ���¶ȴ�������λ��ʵ��
* ʵ��˵�� ������modbusЭ�飬ʵʱͬ�����ݵ���λ��
* ʵ��ƽ̨ ����̫51��Ƭ�������� V1.1
* ���ӷ�ʽ ��
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

sbit PWM=P0^4;

//IO�ӿڶ���
sbit contrl_out=P0^7;

int count=0; //ÿ50us����һ�Σ�������Χ 0-200
int actuator_angle = 0;//��ȡ�ĽǶ�ֵ
volatile unsigned int plus_h;//����õ���IO�ڵ�ƽ�仯�ο�ֵ����Χ500 - 2500
volatile unsigned int plus_l;//����õ���IO�ڵ�ƽ�仯�ο�ֵ����Χ500 - 2500

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
  SystemInit();
	init_MODBUS();
	
	Timer1Init();
	modbus_Addt.actuator_angle = 0;
	plus_h = 65075 - 256*actuator_angle/25;
	plus_l = 47565 + 256*actuator_angle/25;
	Delayms(1000);//��ʱ1s�������λ
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


void Timer1Int() interrupt 3 using 0
{
	static data bit flag=0;
	unsigned int temp=0;
		temp = modbus_Addt.actuator_angle;

		if(temp != actuator_angle && temp < 180)
		{
			actuator_angle = temp;
		  //plus = actuator_angle*2000/180+500;//����õ�IO�仯ֵ
		//plus = actuator_angle*100/9+500;//����õ�IO�仯
			plus_h = 65075 - (actuator_angle<<8)/25;
			plus_l = 47565 + (actuator_angle<<8)/25;
		}
		
	if(flag == 1)
	{
		TH1 = plus_l>>8;
		TL1 = plus_l;
		contrl_out = 0;
		flag = 0;
	}else
	{
		TH1 = plus_h>>8;
		TL1 = plus_h;
		contrl_out = 1;	
		flag = 1;
	}
}
