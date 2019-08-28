#include "public.h"
#include "ACC.h"
#include "ADC.h"
#include "usart.h"
#include "SYN480R.h"
#include "other.h"
#include "flash.h"
#include "onekey.h"
int main()
{

void (*func)()  ;
	SystemInit();
	#if USE_IAP==1 
	 
	memcpy((void *)0x20000000,(void *)APP_FLASH_ADDR,0x100);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 
	SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);
	#endif
	DataINit();//数据
//	initACC();//acc
//	GPIO_init();
	timeInit();
//	Beep_Init();
//	Speed_Init();  
//	Lock_car_Init();
//  ADCDATA_Init();
//	SYN480R_init();
//	OnekeyInit();
//	ROLL_Init();//震动传感器
//	
//	ZN_Key_Init();
	WWDGInit();
	IAP_Init();
	readflash(0, flash_data,flash_len);
//	WWDGInit();
//	for(;;)
//		{
////			memcpy(usart1_TX_buf,usart1_RX_buf,10);
////			usart1_TX_len=10;
////	

////			sys_flag.usart1_flag_Send=1;
////			IWDG_ReloadCounter();//复位看门狗
//	//		IWDG_ReloadCounter();//复位看门狗
//			task485();
//	//		Task_ZN_Key();
//	//		Task_onekey();
//	//		TASK_ROLL(); 
//	//		TASK_speed();
//	//		TASK_beep();
//			 
//		}
	IWDG_ReloadCounter();//复位看门狗
	if((flash_data[flash_addr_iap_state]==flash_code_nomallboot)||(flash_data[flash_addr_iap_state]==flash_code_Reboot))//
	{
			if(((*(uint32_t *)APP_FLASH_ADDR)&0x2FFE0000)==0x20000000)
			{
//												 __disable_irq();   // 关闭总中断
					func =*((uint32_t *)(APP_FLASH_ADDR+4));
				__set_MSP((*(uint32_t *)(APP_FLASH_ADDR)));
				func();
			}else
			{
				usart1_TX_buf[2]=0xaa;
//											usart1_TX_len++;
			}
	}
//	else
//	{
		for(;;)
		{
			IWDG_ReloadCounter();//复位看门狗
			task485();
		}
//	}
	
}
