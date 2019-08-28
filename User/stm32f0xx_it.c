/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
	* @uCOSiiVersion 		uCOSII 2.93
  * @author 				  Fun JFK.
  * @STDDriverversion V1.5.0
  * @date    					2018-01-02
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "public.h"
#include "usart.h"
#include "SYN480R.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) // 系统调度函数    勿动
{

}

void TIM6_IRQHandler(void)//基本输入输出 Basic IO System
{

}

void USART1_IRQHandler(void)
{	
	uint16_t CRC16=0;
		uint8_t len=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
	
		usart1_RX_buf[usart1_RX_len++] =(uint8_t)USART_ReceiveData(USART1);
		if(usart1_RX_buf[0]==0xaa)
		{
				if(usart1_RX_len>4)
				{
					if(usart1_RX_buf[1]>=usart1_RX_len)
					{
						CRC16 =CRC16;
						len=usart1_RX_buf[1];
						if((CRC16&0xff)==usart1_RX_buf[len-1])
						{
							
						}
					}
				}
		}
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE)==SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);
		usart1_RX_len= 128-DMA_GetCurrDataCounter(DMA1_Channel3);
		Receive_data1();
		sys_flag.usart1_flag_idle=1;
	}
	
	if(USART_GetITStatus(USART1,USART_IT_TC)==SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
		USART_ITConfig(USART1,USART_IT_TC,DISABLE);
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	}
}
//void ADC1_IRQHandler()
//{

//	if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==SET)
//	{
//		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
//	

//	}
//	
//}
////////////////////////////////////////
//协议
// 
//                    ___            
//引导码:                ____________
//        500us高电平     12ms低电平 
//                    ___            
//数据0:                 ____________
//        500us高电平     1ms低电平 
//                    ___________            
//数据1:                         ___
//                   1ms高电平   500us低电平    
//void	EXTI4_15_IRQHandler()
//{			
//	uint32_t bufh =0,bufl=0;
//	EXTI_InitTypeDef EXTI_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	if(EXTI_GetFlagStatus(EXTI_Line9)==SET)//遥控
//	{
//		EXTI_ClearITPendingBit(EXTI_Line9);

//		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
//		{
//			EXTI_InitStruct.EXTI_Line=EXTI_Line9;
//			EXTI_InitStruct.EXTI_LineCmd=ENABLE;
//			EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
//			EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
//			EXTI_Init(&EXTI_InitStruct);
//			
//			NVIC_InitStruct.NVIC_IRQChannel=EXTI4_15_IRQn;
//			NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//			NVIC_InitStruct.NVIC_IRQChannelPriority=0;
//			NVIC_Init(&NVIC_InitStruct);
//			if(sys_flag.SYN480_time_count==2)
//			{
//				sys_flag.SYN480_time[sys_flag.SYN480_time_count++]=Get_syscore_tim();
//			}else
//			{
//				sys_flag.SYN480_time[0]=Get_syscore_tim();
//				sys_flag.SYN480_time_count=1;
//			}
//			
//		}else
//		{
//			EXTI_InitStruct.EXTI_Line=EXTI_Line9;
//			EXTI_InitStruct.EXTI_LineCmd=ENABLE;
//			EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
//			EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
//			EXTI_Init(&EXTI_InitStruct);
//			
//			NVIC_InitStruct.NVIC_IRQChannel=EXTI4_15_IRQn;
//			NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//			NVIC_InitStruct.NVIC_IRQChannelPriority=0;
//			NVIC_Init(&NVIC_InitStruct);
//			if(sys_flag.SYN480_time_count==1)
//			{
//				sys_flag.SYN480_time[1]=Get_syscore_tim();
//				sys_flag.SYN480_time_count=2;
//			}else//错误
//			{
//				
//			}
//			
//		}
//		
//		if(sys_flag.SYN480_time_count>2)
//		{
//			if(sys_flag.SYN480_time[0]>sys_flag.SYN480_time[1])//高电平时间
//			{
//				bufh=0xffff+sys_flag.SYN480_time[1];
//			}
//			bufh-=sys_flag.SYN480_time[0];
////			bufh*=1;
//			if(sys_flag.SYN480_time[1]>sys_flag.SYN480_time[2])//低电平时间
//			{
//				bufl=0xffff+sys_flag.SYN480_time[1];
//			}
//			bufl-=sys_flag.SYN480_time[1];
////			bufl*=1;
//			
//			
//			sys_flag.SYN480_time[0]=sys_flag.SYN480_time[2];//迭代保存
//			sys_flag.SYN480_time_count=1;
//			
//			if(((bufh>300)&&(bufh<800))&&((bufl>6000)&&(bufl<15000)))//引导码
//			{
//				sys_flag.SYN480_bytes_count=1;
//				sys_flag.SYN480_data=0;
//				sys_flag.SYN480_data_Recv=0;
//			}else if(sys_flag.SYN480_bytes_count>0)
//			{
//				sys_flag.SYN480_data<<=1;
//				if(((bufh>300)&&(bufh<800))&&((bufl>500)&&(bufl<1500)))//数据0
//				{
//					sys_flag.SYN480_bytes_count++;
//				}else if(((bufh>500)&&(bufh<1500))&&((bufl>300)&&(bufl<800)))//数据1
//				{
//					sys_flag.SYN480_data+=1;
//					sys_flag.SYN480_bytes_count++;
//				}else
//				{
//					sys_flag.SYN480_bytes_count=0;
//					sys_flag.SYN480_data=0;
//					sys_flag.SYN480_data_Recv=0;
//				}
//				if(sys_flag.SYN480_bytes_count>=25)
//				{
//					sys_flag.SYN480_data_Recv=1;
//				}
//			}
//		}
//	}
//	if(EXTI_GetFlagStatus(EXTI_Line8)==SET)//speed
//	{
//		EXTI_ClearITPendingBit(EXTI_Line8);
//		
//		
//		sys_flag.SPEED_count_s++;
//	}
//	
//	if(EXTI_GetFlagStatus(EXTI_Line12)==SET)//roll
//	{
//		EXTI_ClearITPendingBit(EXTI_Line12);
//		sys_flag.ROLL_count_s++;
//	}
//	
//	if(EXTI_GetFlagStatus(EXTI_Line16)==SET)//ZN_key
//	{
//		EXTI_ClearITPendingBit(EXTI_Line16);
//		sys_flag.ZN_KEY_EN=1;
//	}
//}
void DMA1_Channel2_3_IRQHandler()
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC2)==SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC2);
		USART_ITConfig(USART1,USART_IT_TC,ENABLE);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	
	}
}

void TIM17_IRQHandler()
{
	if(TIM_GetFlagStatus(TIM17,TIM_FLAG_Update))
	{
		TIM_ClearITPendingBit(TIM17,TIM_IT_Update);
		Tim_core.time_tick+=0xffff;
	}
}
/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
