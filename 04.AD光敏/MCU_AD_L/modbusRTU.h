#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H

/*modbusRTUͷ�ļ���ʵ�ֵ�Ƭ���ϵ�ͨѶ����*/
#define MODBUS_LENTH  20   //modbus���շ��͵ĳ���
//=================================================================================================
#define MODBUS_ADDR			0X01//modbusЭ��վ��

//modbus���հ�״̬-----------------------------------
#define PACK_START		1	// ���ݿ�ʼ����
#define PACK_REC_ING		2//���ڽ�������
#define PACK_ADDR_ERR		4	// ��ַ������
#define PACK_REC_OK		8	// ������ֽ��� ��ͬ�ж� ����һ��֡�ɹ�

#define MODBUS_OK 1	  
#define MODBUS_REC 0

/*�ṹ�嶨��*/
/*modbus 16λֵ�Ķ��壬��ʼ��ַ0000H,ÿһ��ֵΪ16λ int�ͣ�ռ�����ֽ� */
struct MODBUS_ADD{
	int AD_Resist;//��ַ:0000H  ��λ��ADֵ
	int AD_Hot;//��ַ:0001H  ����ֵ
	int AD_Light;//��ַ:0002H ����ֵ
	int AD_Out;//��ַ:0003H �ⲿ����ֵ
	int DA_LED;//��ַ:0004H LED����ֵ
};

extern struct MODBUS_ADD modbus_Addt;//����һ��modbus�ṹ�����
extern struct MODBUS_ADD *modbusAdd;//�ṹ��ָ�룬ָ���������
extern int rec_time_out;//��ʱ
extern int rec_stat;//����״̬
extern int rec_num;//���յ��ֽ���
extern volatile int send_count;//Ҫ���͵��ֽ���
extern unsigned char modbus_recv_buf[MODBUS_LENTH];	 //  

unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);

unsigned int comp_crc16(unsigned char *pack, unsigned char num);
void init_MODBUS(void);
unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);
unsigned int comp_crc16(unsigned char *pack, unsigned char num);
void function_MODBUS(unsigned char *rec_buff);
void read_reg(unsigned char * rec_buff);
void force_reg(unsigned char * rec_buf);
int time_out_check_MODBUS(void);
#endif


