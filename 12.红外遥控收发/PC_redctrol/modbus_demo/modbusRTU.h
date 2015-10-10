#pragma once

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

#define MODBUS_ADDR			0X01//modbusЭ��վ��
//-----------------------------------
#define PACK_START		1	// ���ݿ�ʼ����
#define PACK_REC_ING		2//���ڽ�������
#define PACK_ADDR_ERR		4	// ��ַ������
#define PACK_REC_OK		8	// ������ֽ��� ��ͬ�ж� ����һ��֡�ɹ�

#define MODBUS_LENTH  20   //modbus���շ��͵ĳ���

#define MODBUS_OK 1	  
#define MODBUS_REC 0

/*�����붨��*/
#define FUN_READCOIL 1
#define FUN_READBIT 2
#define FUN_REGH 3
#define FUN_REG 4
#define FUN_WRITEBIT 5
#define FUN_WRITEREG 6
#define FUN_WRITENREG 16

/*modbus 16λֵ�Ķ��壬��ʼ��ַ0000H,ÿһ��ֵΪ16λ int�ͣ�ռ�����ֽ� */
struct MODBUS_ADD{
	Int16 key_value;//��ַ:0000H  ң�ؼ�ֵ
	Int16 key_add;//��ַ:0001H  ң�ص�ַ��
};

class modbusRTU
{
public:
	struct MODBUS_ADD modbus_Addt;//����һ��modbus�ṹ�����
	struct MODBUS_ADD *modbusAdd;//�ṹ��ָ�룬ָ���������
	int rec_time_out;//��ʱ
	int rec_stat;//����״̬
	int rec_num;//���յ��ֽ���
	int send_count;//Ҫ���͵��ֽ���
	unsigned char modbus_send_buf[MODBUS_LENTH]; //���ͻ���
	unsigned char modbus_recv_buf[MODBUS_LENTH]; //���ջ���
//=================================================================================================
// CRC ��λ�ֽ�ֵ�� 
//------------------
unsigned char CRC_H[256]; 
//=================================================================================================
// CRC��λ�ֽ�ֵ��
//----------------
unsigned char CRC_L[256];

public:
	modbusRTU(void);
	void init_MODBUS(void);
	unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);
	unsigned int comp_crc16(unsigned char *pack, unsigned char num); 
	int time_out_check_MODBUS(void);
	void SendReadCommand(unsigned char type,Int16 address,Int16 count);
	void ReadBit(unsigned char type,Int16 address,Int16 count);
	void ReadReg(unsigned char type,Int16 address,Int16 count);
	void SendWriteCommand(unsigned char type,Int16 address,Int16 count,Int16 *value);
	void ForceBit(unsigned char type,Int16 address,Int16 count,Int16 *value);
	void ForceReg(unsigned char type,Int16 address,Int16 count,Int16 *value);
	void ForceNReg(unsigned char type,Int16 address,Int16 count,Int16 *value);
	void RecProcess(unsigned char *buf,int length);
	void RecOKProcess();
	void RecReadReg();
	void RecReadBit();
	void ClearRevBuf();
};
