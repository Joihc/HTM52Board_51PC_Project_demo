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
#include "DS18B20.h"
#include <string.h>
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int

int temperbuf[5];

/*******************************************************************************
* �� �� �� ��main
* �������� ��������
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void main()
{
	int i=0;
	 SystemInit();
	 init_MODBUS();
	Init_DS18B20();
	Read_RomCord();
	while(1)
	{				
				//����Ҫ���������ݶ�ȡ��������
			  /*start*/
		 for(i=0;i<9;i++)//��ȡ5��ֵ
		{
			temperbuf[i] = Read_TemperatureInt();
			Delayms(15);
		}
		
		Bubblesort(temperbuf,9);//��С��������
		modbus_Addt.temperature = temperbuf[5];//����ʵ�ʲ��ԣ�ȡ�м�ƫ���ֵ��Ч�����
		  Delayms(100);
			  /*end*/
		 	//ͬ�����������ݵ�ʵ������Ч��
			  /*start*/

			  /*end*/
	}
}




