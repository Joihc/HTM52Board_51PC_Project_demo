#include "REG52.H"
#include "system.h"
#include "modbusRTU.h"

#include <string.h>

#define uchar unsigned char
#define uint unsigned int
	
#define LED_PORT P1
#define COMM_PC 0 //����PC����
#define COMM_FLOW 1//��ˮ��

void LedFlow();

void delay(int n_ms)
{
	int i = 0;
	uchar j=0;
	for(i=0;i<n_ms;i++)
	for(j=0;j<114;j++);
}

void main()
{
	 SystemInit();
	 init_MODBUS();
	 modbus_Addt.LED_ctrl = COMM_PC;
	while(1)
	{				
				//����Ҫ���������ݶ�ȡ��������
			  /*start*/
		if(modbus_Addt.LED_ctrl != COMM_PC)
		{
			 modbus_Addt.LED_value = LED_PORT;
		}
			  /*end*/
	//	delay(5);
			   if(rec_stat == PACK_REC_OK)
	   {
	   	//	function_MODBUS(modbus_recv_buf);
	   }
			 
		 	//ͬ�����������ݵ�ʵ������Ч��
			  /*start*/
			 switch(modbus_Addt.LED_ctrl)
			 {
				 case COMM_PC: 
					 LED_PORT = ~(uchar)(modbus_Addt.LED_value & 0x00ff);
				 break;
				 case COMM_FLOW:
					 LedFlow();
				 break;
				 default:
					 LED_PORT = ~(uchar)(modbus_Addt.LED_value & 0x00ff);
				 break;
			 }
			  /*end*/
	}
}

//��ˮ��
void LedFlow()
{
	static uchar LED_count=0;
	LED_count++;
	if(LED_count >= 8) LED_count = 0;
	LED_PORT = ~(0x01<<LED_count);//ȡ����LED�Ƶ͵�ƽ��Ч
	modbus_Addt.LED_value = ~LED_PORT;
	delay(500);
}



