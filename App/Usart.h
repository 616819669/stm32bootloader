#ifndef USART_H_
#define USART_H_
#include "public.h"
#include "SYN480R.h"
#define    UPDATE_ADDR         0X05  
#define M_CMD 0x5a
#define T_cmd 0xaa
//flash  addr
#define  SECOND_START     0X3A
#define  START_UPDATE     0X81   //��ʼ����

typedef struct 
{
	uint8_t a0:1;
	uint8_t a1:1;
	uint16_t a2;
}_testbit ;
extern _testbit testbit ;
extern uint16_t usart1_RX_len;
extern  uint16_t usart1_TX_len;
extern uint8_t usart1_RX_buf[128];
 extern uint8_t usart1_TX_buf[128]; 
void IAP_Init(void);
void Send_data1(void *str,uint8_t len);
void Receive_data1(void);
void task485(void);

void Delay_Checkus_EN(uint32_t us,TIM_FLAG *TIM);//���ʱ��ʹ��
uint8_t Delay_Checkus(TIM_FLAG *TIM);//���ʱ��
void Delay_Checkus_Update(TIM_FLAG *TIM);//����ʱ��
uint8_t Delay_Checkus_Getstate(TIM_FLAG *TIM);//��ȡ
void Delay_Checkus_DISABLE(TIM_FLAG *TIM);//ȡ��ʱ��
#endif

