#include "reg52.H"
#include "system.h"
#include "modbusRTU.h"
#include <string.h>

#define FOSC 11059200L //�������ã�Ĭ��ʹ��11.0592M Hz
//#define FOSC 12000000L //�������ã�ʹ��12M Hz
//#define FOSC 24000000L //�������ã�ʹ��24M Hz
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
#define BAUD 28800

volatile struct SEND_BUF send_buf;
int temper_h = 0xefff;
int temper_l = -50;

/*******************************************************************************
* �� �� �� ��Delayms
* �������� ��ʵ�� ms������ʱ
* ��    �� ��ms
* ��    �� ����
*******************************************************************************/
void Delayms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	#if FOSC == 11059200L
	for(j=0;j<114;j++);
	#elif FOSC == 12000000L
	for(j=0;j<123;j++);
	#elif FOSC == 24000000L
	for(j=0;j<249;j++);
	#else
	for(j=0;j<114;j++);
	#endif
}

void SystemInit()
{
	//�򿪴���
	SCON=0X50;			//����Ϊ������ʽ1	10λ�첽�շ���
	TMOD=0x20; //���ü�����������ʽ2  8λ�Զ���װ������	
	PCON=0X80;//�����ʼӱ�	SMOD = 1  28800
	TH1= 256 -(FOSC/12/32/(BAUD/2)); //���������
	TL1= 256 -(FOSC/12/32/(BAUD/2));
	TR1=1;	
	ES=1;

	//���ö�ʱ��0
    TMOD = TMOD | 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
	EA=1;

	send_buf.busy_falg = 0;
}

//����һ֡
void PutSring(char *buf)
{
	int i;
	ES=0;
	for(i=0;i<strlen(buf);i++)
	{
		SBUF = buf[i];//д��SBUF����ʼ���ͣ�������Զ������жϷ���
		while(!TI);		  //�ȴ������������
		TI=0;			  //���������ɱ�־λ
	}
	ES=1;
}
void PutNChar(char *buf,int length)
{
	while(send_buf.busy_falg);//��ѯ�����Ƿ�æ������ѭ���ȴ�
	send_buf.length = length;
	send_buf.index = 0;	
	send_buf.buf = buf;
	send_buf.busy_falg = 1;
	SBUF = send_buf.buf[0];//д��SBUF����ʼ���ͣ�������Զ������жϷ���	
}

//�����ж�
void SerISR() interrupt 4 using 2
{
	if(RI == 1)
	{
		unsigned char data_value;
		RI=0;
		if(send_buf.busy_falg == 1) return;//����δ���ʱ��ֹ����
		data_value = SBUF;
		rec_time_out = 0;//һ�����յ����ݣ���ճ�ʱ����
		switch(rec_stat)
		{
			case PACK_START:
				rec_num = 0;
				if(data_value == PACK_START)//Ĭ�ϸտ�ʼ����һ���ֽڣ�����Ƿ�Ϊ��վ��
				{
					modbus_recv_buf[rec_num++] = data_value;
					rec_stat = PACK_REC_ING;
				}
				else
				{
					rec_stat = PACK_ADDR_ERR;
				}
				break;
	
			case PACK_REC_ING:	// ��������
	
				modbus_recv_buf[rec_num++] = data_value;
				break;
	
			case PACK_ADDR_ERR:	// ��ַ������ �ȴ���ʱ ֡����
				break;
			default : break;
		}
		
	}
	if(TI == 1)	 //���뷢������жϣ�����Ƿ�����Ҫ���͵����ݲ����з���
	{
		TI = 0;
		send_buf.index++;
		if(send_buf.index >= send_buf.length)
		{
			send_buf.busy_falg = 0;//���ͽ���
			return;
		}
		SBUF = send_buf.buf[send_buf.index];//����������һ��	
	}
}

/* ��ʱ���ж� 1ms*/
void Time0ISR() interrupt 1 using 1
{
    TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;                //reload timer0 high byte

	if(PACK_REC_OK == time_out_check_MODBUS()) 
	{
		//�ɹ�����һ֡���ݺ󣬴���modbus��Ϣ��ͬ������������
		function_MODBUS(modbus_recv_buf);
	}
}

void Bubblesort(int *buf,int n)
{
	int i,j,tag,temp;
	for(i=0,tag=1;tag==1&&i<n-1;i++) //�����ŵĴ�������n����һ��������n-1�Σ�
	{
		tag=0;
		for(j=1;j<n-i;j++)//������һ�������У�������֮��Ľ�������
		if(buf[j-1]>buf[j])
		{
			temp=buf[j-1];
			buf[j-1] =buf[j];
			buf[j]=temp;
			tag=1;
		}
	}
}


