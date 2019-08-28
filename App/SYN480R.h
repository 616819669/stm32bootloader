#ifndef SYN480R_H
#define SYN480R_H
#include "public.h"
typedef struct 
{
	uint8_t USE_MS:1;//��ʱ��ʹ��ms
	uint8_t FLAGCHECK_EN:1;//���ճɹ�
	uint32_t TIM_count;
	uint32_t TIM_count_len;//ʱ����ʱ����
}TIM_FLAG;


typedef struct 
{
	//SYN480R
	uint32_t SYN480_CMD:4;//����״̬
	uint32_t SYN480_data_Recv;//���ճɹ�
	uint8_t SYN480_bytes_count;
	uint8_t SYN480_time_count;
	uint16_t SYN480_test:2;
	uint16_t SYN480_State;
	uint32_t SYN480_time[3];
	uint32_t SYN480_data;
	
	//ACC
//	uint32_t ACC_state:1;//����״̬
//	TIM_FLAG ACC_Time;//
	//usart
	uint32_t usart1_flag_idle:1;
	uint32_t usart1_flag_Send:1;
	TIM_FLAG usart1_time;
	TIM_FLAG usart1_waitTime;
	//speed 
//	uint32_t SPEED_count_s;
//	uint32_t SPEED_count;
//	uint32_t SPEED;
//	TIM_FLAG SPEED_time;
	//updata
	uint32_t  Updata :1;
	uint32_t  Updata_ALL;
	uint32_t Updata_count;
	
	//onekey

//	uint8_t Onekey_Edge_count:4;//���豣��
//	uint8_t	Onekey_bytes_count ;//�ֽڱ���
//	uint8_t Onekey_Send_state; //����״̬
//	uint32_t Onekey_flag_Bsy:1;//������� 1æ 
//	TIM_FLAG Onekey_Send_time;//ʱ������
//	TIM_FLAG Onekey_Bit_Send_time;//ʱ������
//	
//	//roll  ��
//	uint32_t ROLL_Flag_Sort_buz:1;//������
//	uint32_t ROLL_Flag_long_buz:1;
//	uint32_t ROLL_Flag_ROLL:1;//����
//	uint32_t ROLL_Flag_state:3;//��״̬ ��0 ������ ��1С�� ������2
//	uint32_t  ROLL_count_s;//һ������
//	TIM_FLAG ROLL_time;//ʱ������
//	TIM_FLAG ROLL_time_long;//ʱ������
//	
//	//beep
//	TIM_FLAG BEEP_PWM_TIME;//pwm �����ʱ
//	uint32_t BEEP_PWM_State;//����״̬��¼
	
	
	//zn_key
//	uint32_t  ZN_KEY_down:1;
//	uint32_t ZN_KEY_EN:1;//�������
//	TIM_FLAG ZN_KEY_TIME;
	
}SYS_FLAG;
extern	TIM_FLAG TEST_TIME;
void SYN480R_init(void);

extern SYS_FLAG sys_flag;
#endif

