#include "REG52.H"
#include "system.h"
#include "modbusRTU.h"

#include <string.h>

#define uchar unsigned char
#define uint unsigned int
#define  PCF8591 0x90    //PCF8591 ��ַ

sbit SCL=P2^3;         //����ʱ�������
sbit SDA=P2^4;   //�������������

void delay()   //��ʱ4-5��΢��
{;;}
	
void delay_1ms(int n_ms)
{
	int i = 0;
	uchar j=0;
	for(i=0;i<n_ms;i++)
	for(j=0;j<114;j++);
}

void start()//��ʼ�ź�
{
 SDA=1;
    delay();
  SCL=1;
    delay();
  SDA=0;
    delay();
}

void stop()      //ֹͣ�ź�
{
 SDA=0;
    delay();
  SCL=1;
    delay();
  SDA=1;
    delay();  
}


void respons()//Ӧ��   �൱��һ�����ܵ���ʱ����
{
        uchar i;
  SCL=1;
    delay();
  while((SDA==1)&&(i<250))
           i++;
      SCL=0;
    delay();
}

void init()      //��ʼ��
{
  SDA=1;
    delay();
  SCL=1;
    delay();    
}

uchar read_byte()
{
   uchar i,k;
        SCL=0;
    delay();
  SDA=1;
    delay();
  for(i=0;i<8;i++)
   {
         SCL=1;
            delay();
          k=(k<<1)|SDA;//������һλ���������λ���ܵ�ǰλ
             SCL=0;
            delay();
  }
 return k;

}

void write_byte(uchar date)       //дһ�ֽ�����
{
       uchar i,temp;
     temp=date;
        for(i=0;i<8;i++)
   {
         temp=temp<<1; //����һλ �Ƴ���һλ��CY��
          SCL=0;                      //ֻ����scl=0ʱsda�ܱ仯ֵ
                delay();
          SDA=CY;
           delay();
          SCL=1;
            delay();            
  }   
  SCL=0;
    delay();
  SDA=1;
    delay();
}



void write_add(uchar control,uchar date)
{
        start();
  write_byte(PCF8591);        //10010000  ǰ��λ�̶� ��������λȫ�����ӵ��� ���Զ���0 ���һλ��д ����Ϊ�͵�ƽ
        respons();
        write_byte(control);
      respons();
        write_byte(date);
 respons();
        stop();

}

uchar read_add(uchar control)
{
  uchar date;
       start();
  write_byte(PCF8591);
      respons();
        write_byte(control);
      respons();
        start();
  write_byte(PCF8591+1);       //�����һλ���1����
     respons();
        date=read_byte();
 stop();
   return date;

}

void main()
{
	 SystemInit();
	 init_MODBUS();
	while(1)
	{				
				//����Ҫ���������ݶ�ȡ��������
			  /*start*/
		//��������β���ȷ
         modbus_Addt.AD_Resist=read_add(0x40);  //��λ��AD��������ȡ��ַ0x40
		 delay_1ms(1);		 //����AD����֮����Ҫ���һ����ʱ�����������ȡ
//		
//		 modbus_Addt.AD_Hot=read_add(0x41);	//��������ȡ��ַ0x41
//	     delay_1ms(1);
//		
//		 modbus_Addt.AD_Light=read_add(0x42);	 //��������ȡ��ַ0x42
//	     delay_1ms(1);
//		
//		 modbus_Addt.AD_Out=read_add(0x43);	 //�ⲿ����ȡ��ַ0x43	
//	     delay_1ms(1);
			  /*end*/
		
		 	//ͬ�����������ݵ�ʵ������Ч��
			  /*start*/
		write_add(0x40,modbus_Addt.DA_LED);  //дDAֵ��д���ַ0x40
		delay_1ms(1);
			  /*end*/
	}
}




