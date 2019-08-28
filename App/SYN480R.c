#include "SYN480R.h"
////////////////////////////////////////
//Э��
// 
//                    ___            
//������:                ____________
//        500us�ߵ�ƽ     12ms�͵�ƽ 
//                    ___            
//����0:                 ____________
//        500us�ߵ�ƽ     1ms�͵�ƽ 
//                    ___________            
//����1:                         ___
//                   1ms�ߵ�ƽ   500us�͵�ƽ    
SYS_FLAG sys_flag;
void SYN480R_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line9;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource9);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_15_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
	
}


