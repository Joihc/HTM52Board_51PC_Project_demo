#ifndef __SYSTEM_H
#define __SYSTEM_H

//һ��Ҫȫ������unsigned char�ͣ������������Ż����������
struct SEND_BUF{
unsigned char busy_falg;//æ��־�����ڷ�������ʱ��λ1�����ڿ�ʼ������λ1�����ͽ�����λ0
unsigned char index;//������ָ����Ҫ���������λ��
unsigned char length;//��������֡�ĳ���
unsigned char *buf;//ָ����Ҫ���͵�����֡������Ϊȫ�ֱ���������һ����ʼ���ͣ�����ȵ����ͽ��������ж�busy_falgΪ
} ;

void SystemInit();
void PutNChar(char *buf,int length);
void PutSring(char *buf);

#endif
