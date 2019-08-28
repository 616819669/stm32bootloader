#include "ACC.h"
#include "SYN480R.h"
#include "usart.h"
void initACC()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	Close_fz_ACC;
	Close_ACC;
	sys_flag.ACC_state=0;
	
}
//void GPIO_init()
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB,ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
//	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);
//	
//	
//}
void open_ACC()
{
	if(sys_flag.ACC_state==0)
	{
		Open_fz_ACC;
		Delay_Checkus_EN(100000,&sys_flag.ACC_Time);
		if(Delay_Checkus(&sys_flag.ACC_Time))
		{
			if(GetACCState)
			{
				Open_ACC	
				Close_fz_ACC;
				if(GetACCState)
				{
					sys_flag.ACC_state=1;
				}else//打开acc失败
				{
					
				}
				
			}else//打开acc失败
			{
				
			}
		}

	}
}

void CLOSE_ACC()
{
	if(sys_flag.ACC_state==1)
	{
		Close_fz_ACC;
		Close_ACC;
		sys_flag.ACC_state=0;
	}
}

