#include "other.h"
#include "usart.h"


void Beep_Init()
{
	 GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);
}
void Speed_Init()
{
	 GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line8;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource8);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_15_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=0;
	NVIC_Init(&NVIC_InitStruct);
}
void Lock_car_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	Unlock_car;
}
void ROLL_Init()//震动传感器
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
//	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line12;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource12);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_15_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	
}	
void ZN_Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line6;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,EXTI_PinSource6);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_15_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=0;
	NVIC_Init(&NVIC_InitStruct);
}
void Task_ZN_Key()
{
	if(sys_flag.ZN_KEY_EN)
	{
		Delay_Checkus_EN(5000,&sys_flag.ZN_KEY_TIME);//检测时间使能
		if(Delay_Checkus(&sys_flag.ZN_KEY_TIME))
		{
			if(Get_ZNKey_state()==0) 
			{
				 sys_flag.ZN_KEY_down=1;//按键按下
			}
			sys_flag.ZN_KEY_EN=0;
		}
	}
}
void  Beep_out_pwm(uint32_t pre)
{
	if(pre>500000)
	{
		return ;
	}
	Delay_Checkus_EN(1000000/pre/2,&sys_flag.BEEP_PWM_TIME);//更新时间c
	if(Delay_Checkus(&sys_flag.BEEP_PWM_TIME))
	{
		switch(sys_flag.BEEP_PWM_State)
		{
			case 0:Beep_Open;
			sys_flag.BEEP_PWM_State++;
				break;
			case 1:
				sys_flag.BEEP_PWM_State=0;
				Beep_Close;
				break;
			default :sys_flag.BEEP_PWM_State=0;break;
		}
	}
}
void TASK_beep()
{
	
}
void TASK_speed()
{
	Delay_Checkus_EN(5000000,&sys_flag.SPEED_time);//更新时间
	if(Delay_Checkus(&sys_flag.SPEED_time))
	{
		sys_flag.SPEED=sys_flag.SPEED_count_s;//速度
		sys_flag.SPEED_count_s=0;
	}
}
void TASK_ROLL()
{
	Delay_Checkus_EN(1000000,&sys_flag.ROLL_time);//更新时间
	if( Delay_Checkus(&sys_flag.ROLL_time))
	{
		if(sys_flag.ROLL_count_s>10)//震动了
		{
			sys_flag.ROLL_Flag_ROLL=1;
		}else
		{
			sys_flag.ROLL_Flag_ROLL=0;
		}
		sys_flag.ROLL_count_s=0;
	}
	if(sys_flag.ROLL_Flag_ROLL)
	{
		switch(sys_flag.ROLL_Flag_state)
		{
			case 0:
				sys_flag.ROLL_Flag_state=1; 
				Delay_Checkus_EN(5000000,&sys_flag.ROLL_time_long);//检测时间使能
				break;
			case 1:
				if(Delay_Checkus_Getstate(&sys_flag.ROLL_time_long))
				{
					sys_flag.ROLL_Flag_state=2;
					Delay_Checkus_Update(&sys_flag.ROLL_time_long);//更新时间
				}			
				break;
			case 2:Delay_Checkus_Update(&sys_flag.ROLL_time_long);//更新时间
				break;
			default :
			sys_flag.ROLL_Flag_state=0; 
			sys_flag.ROLL_Flag_ROLL=0;
			sys_flag.ROLL_count_s=0;
			break;
		}
		sys_flag.ROLL_Flag_ROLL=0;
	}
	if(Delay_Checkus(&sys_flag.ROLL_time_long))
	{
		sys_flag.ROLL_Flag_state=0; 
		sys_flag.ROLL_Flag_ROLL=0;
		sys_flag.ROLL_count_s=0;
	}
	
}
	
	
