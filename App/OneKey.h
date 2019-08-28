#ifndef _ONEKEY_H
#define _ONEKEY_H
#include "public.h"
#define Onekey_Line_L GPIO_ResetBits(GPIOB,GPIO_Pin_6);
#define Onekey_Line_H GPIO_SetBits(GPIOB,GPIO_Pin_6);
void OnekeyInit(void);
void Task_onekey(void);
typedef union{
	 struct 
	{
		//0
			uint8_t DEV_Code;
		//1
			uint8_t SEQ_CODE_L;
		//2
			uint8_t RES0:4;
			uint8_t SEQ_CODE_H:4;  //

		//3

				uint8_t Erro_emotor:1;//�������
				uint8_t help:1;  //����
				uint8_t speed_stand:1;//Ѳ��
				uint8_t Low_pwr_protect:1;//Ƿѹ����
				uint8_t Conltrl_err:1;//����������
				uint8_t hand_err:1; //ת�ѹ���
				uint8_t  huoer_err :1;//��������
				uint8_t RES1:1;
		//4

				uint8_t tree_speed:2;//����
				uint8_t protect_car:1;  //���ɳ�����
				uint8_t floating_chg:1;//���г��
				uint8_t conltrl_pretoct:1;//����������
				uint8_t breake :1;//ɲ��
				uint8_t emotor_run:1;//�������
				uint8_t tree_speed_4:1;//����4

		//5	
				uint8_t Limit_speed :1;//����
				uint8_t E_break:1;//����ɲ��
				uint8_t BACK_car :1;//����
				uint8_t Block_protect:1;//��ת
				uint8_t I_protect:1;//��������
				uint8_t Backup_EKK_PWR:1;//����ekk���õ�Դ
				uint8_t Start_onekey:1;//����һ��ͨ
				uint8_t I_per70_flag:1;//70%������־

		//6
				uint8_t  I_val_run;//���е���

		//7
				uint8_t speed_H;//�ٶ�
		//8
				uint8_t speed_L;
		//9
				uint8_t V_val_per;//��ѹ�ٷֱ�
		//10
				uint8_t I_val_per;//�����ٷֱ�
		//11
				uint8_t crc8;
	};
	uint8_t data[12];
}REG;
extern REG Onekey_reg;
#endif
