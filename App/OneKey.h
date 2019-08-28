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

				uint8_t Erro_emotor:1;//电机故障
				uint8_t help:1;  //助力
				uint8_t speed_stand:1;//巡航
				uint8_t Low_pwr_protect:1;//欠压保护
				uint8_t Conltrl_err:1;//控制器故障
				uint8_t hand_err:1; //转把故障
				uint8_t  huoer_err :1;//霍尔故障
				uint8_t RES1:1;
		//4

				uint8_t tree_speed:2;//三速
				uint8_t protect_car:1;  //防飞车保护
				uint8_t floating_chg:1;//滑行充电
				uint8_t conltrl_pretoct:1;//控制器保护
				uint8_t breake :1;//刹车
				uint8_t emotor_run:1;//电机运行
				uint8_t tree_speed_4:1;//三速4

		//5	
				uint8_t Limit_speed :1;//限速
				uint8_t E_break:1;//电子刹车
				uint8_t BACK_car :1;//倒车
				uint8_t Block_protect:1;//堵转
				uint8_t I_protect:1;//过流保护
				uint8_t Backup_EKK_PWR:1;//启用ekk备用电源
				uint8_t Start_onekey:1;//启用一键通
				uint8_t I_per70_flag:1;//70%电流标志

		//6
				uint8_t  I_val_run;//运行电流

		//7
				uint8_t speed_H;//速度
		//8
				uint8_t speed_L;
		//9
				uint8_t V_val_per;//电压百分比
		//10
				uint8_t I_val_per;//电流百分比
		//11
				uint8_t crc8;
	};
	uint8_t data[12];
}REG;
extern REG Onekey_reg;
#endif
