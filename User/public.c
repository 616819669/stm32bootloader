#include "public.h"
#include "SYN480R.h"
#include "onekey.h"
uint32_t test11=0 ;
TIM_FLAG TEST_TIME;
TIME_BASE Tim_core;
void delay_us(uint32_t data)
{
	uint32_t i=48 ;
	i*=data;
	while(i)
	{
		i--;
	}
}
void delay_ms(uint32_t data)
{
	uint32_t i=1 ;
	i*=data;
	while(i--)
	{
		delay_us(1000);
	}
}

void timeInit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//延時定時其
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17|RCC_APB2Periph_TIM16,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=0xffff;
	TIM_TimeBaseInitStruct.TIM_Prescaler=48;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM17,&TIM_TimeBaseInitStruct);
	TIM_ARRPreloadConfig(TIM17,ENABLE);

	TIM_Cmd(TIM17, ENABLE);
	TIM_ITConfig(TIM17,TIM_IT_Update,ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel=TIM17_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;//計數定時器 20us
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=0xffff;
	TIM_TimeBaseInitStruct.TIM_Prescaler=48;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM16,&TIM_TimeBaseInitStruct);
	TIM_ARRPreloadConfig(TIM16,ENABLE);
	TIM_Cmd(TIM16, ENABLE);
	
}

//void delay_time17_us(uint16_t us)//X20 us
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17,ENABLE);
//	TIM_Cmd(TIM17, DISABLE);
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStruct.TIM_Period=us+10;
//	TIM_TimeBaseInitStruct.TIM_Prescaler=48;
//	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
//	TIM_TimeBaseInit(TIM17,&TIM_TimeBaseInitStruct);
//	TIM_ARRPreloadConfig(TIM17,ENABLE);

//	TIM_Cmd(TIM17, ENABLE);
//	
//	while(TIM_GetCounter(TIM17)<us);
//	
//	TIM_Cmd(TIM17, DISABLE);
//		
//}

	
//void delay_time17_ms(uint16_t ms)//X20 us
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17,ENABLE);
//	TIM_Cmd(TIM17, DISABLE);
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStruct.TIM_Period=ms+10;
//	TIM_TimeBaseInitStruct.TIM_Prescaler=48000;
//	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
//	TIM_TimeBaseInit(TIM17,&TIM_TimeBaseInitStruct);
//	TIM_ARRPreloadConfig(TIM17,ENABLE);

//	TIM_Cmd(TIM17, ENABLE);
//	
//	while(TIM_GetCounter(TIM17)<ms);
//	
//	TIM_Cmd(TIM17, DISABLE);
//	
//}
uint32_t Get_syscore_tim()//获取内核时间
{
	return TIM_GetCounter(TIM17)+Tim_core.time_tick;
}
uint8_t Delay_Checkus(TIM_FLAG *TIM)//检测时间
{
	uint32_t data=0;
	if(TIM->FLAGCHECK_EN==0)
	{
		return 0;
	}
	data= Get_syscore_tim();
	if(data<(TIM->TIM_count))
	{
		data=0xffff-TIM->TIM_count+data;
	}else
	{
		data-=(TIM->TIM_count);
	}
	

	if((data)>TIM->TIM_count_len)
	{
		TIM->FLAGCHECK_EN=0;
		return 1;
	}
	return 0;
}
void Delay_Checkus_EN(uint32_t us,TIM_FLAG *TIM)//检测时间
{
	if(TIM->FLAGCHECK_EN==0)
	{
		TIM->FLAGCHECK_EN=1;
		TIM->TIM_count= Get_syscore_tim();
		TIM->TIM_count_len=us;
		 
	}
	
}
void Delay_Checkus_Update(TIM_FLAG *TIM)//更新时间
{
	if(TIM->FLAGCHECK_EN==1)
	{
		TIM->TIM_count= Get_syscore_tim();
	}
	
}
uint8_t Delay_Checkus_Getstate(TIM_FLAG *TIM)//获取等待时间到了没·
{
	uint32_t data=0;
	if(TIM->FLAGCHECK_EN)
	{
		data= Get_syscore_tim();
		if(data<(TIM->TIM_count))
		{
			data=0xffff-TIM->TIM_count+data;
		}else
		{
			data-=(TIM->TIM_count);
		}
		if((data)<TIM->TIM_count_len)
		{
//			TIM->FLAGCHECK_EN=0;
			return 1;
		}
	}
	return 0;
}
void Delay_Checkus_DISABLE(TIM_FLAG *TIM)//取消时间
{
	TIM->FLAGCHECK_EN=0;
}
void DataINit()
{
	memset(&sys_flag,0,sizeof(sys_flag));
//	memset(&Onekey_reg,0,sizeof(Onekey_reg));
	memset(&Tim_core,0,sizeof(Tim_core)); 
}
void WWDGInit()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)!=SET);
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_8);
	IWDG_SetReload(1500);//300ms  复位
	IWDG_ReloadCounter();
	IWDG_Enable();
}

