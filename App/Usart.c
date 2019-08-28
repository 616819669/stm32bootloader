#include "usart.h"
#include "SYN480R.h"
#include "Flash.h"
_testbit testbit ;
uint16_t usart1_RX_len=0,usart1_TX_len=0;
uint8_t usart1_RX_buf[128]; 
 uint8_t usart1_TX_buf[128]; 
void IAP_Init(void)
{
NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	
	USART_InitStruct.USART_BaudRate=9600;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);
	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//接受终端
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);

	USART_ClearITPendingBit(USART1,USART_IT_IDLE);//空闲终端
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
	
	
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=1;
	
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART1,ENABLE);
	
	//dma
	//tx
	DMA_InitStruct.DMA_BufferSize=128;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)usart1_TX_buf;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&USART1->TDR;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel2, &DMA_InitStruct);
	DMA_SetCurrDataCounter(DMA1_Channel2, 16);
	DMA_Cmd(DMA1_Channel2, ENABLE);
	
	DMA_ClearITPendingBit(DMA1_IT_TC2);
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);//dma 结束中断
	NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel2_3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	//rx
	DMA_InitStruct.DMA_BufferSize=128;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)usart1_RX_buf;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&USART1->RDR;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel3, &DMA_InitStruct);
	DMA_SetCurrDataCounter(DMA1_Channel3, 128);
	DMA_Cmd(DMA1_Channel3, ENABLE);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	DMA_Cmd(DMA1_Channel3, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel3, 128);
	USART_DMACmd(USART1,USART_DMAReq_Rx, ENABLE);
	DMA_Cmd(DMA1_Channel3, ENABLE);
//	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);//dma 结束中断
//	NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel2_3_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPriority=1;
//	NVIC_Init(&NVIC_InitStruct);

}
void Receive_data1()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	DMA_Cmd(DMA1_Channel3, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel3, 128);
	USART_DMACmd(USART1,USART_DMAReq_Rx, ENABLE);
	DMA_Cmd(DMA1_Channel3, ENABLE);
	
}
void Send_data1(void *str,uint8_t len)
{
//	uint8_t i=0;
//	GPIO_SetBits(GPIOA,GPIO_Pin_11);
// delay_time17_us(1);//X20 us

//	for(i=0;i<len;)
//	{
//		USART_SendData(USART1,*(uint8_t *)str);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//		str++;i++;
//	}
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
	
		Delay_Checkus_EN(1000,&sys_flag.usart1_time);//开启检测时间	
		if(Delay_Checkus(&sys_flag.usart1_time))//检测时间到了没
		{
			memcpy(usart1_TX_buf,str,len);

			DMA_Cmd(DMA1_Channel2, DISABLE);
			DMA_SetCurrDataCounter(DMA1_Channel2, len);
			USART_DMACmd(USART1,USART_DMAReq_Tx, ENABLE);
			DMA_Cmd(DMA1_Channel2, ENABLE);
			sys_flag.usart1_flag_Send=0;
		}
//	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
//	delay_time17_us(1);//X20 us
}

void Usart1_send()
{
	
}	
uint16_t  CRCSUM16(uint8_t *buf ,uint8_t len)
{
	uint16_t i=0;
	uint16_t data=0;
	for(;i<len;i++)
	{
		data+=(*buf);
		buf++;
	}
	return data;
}
unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen)  
{  
  unsigned short wCRCin = 0x0000;  
  unsigned short wCPoly = 0x1021;  
  unsigned char wChar = 0;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        wCRCin ^= (wChar << 8);  
        for(int i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  
  return (wCRCin) ;  
}  
void task485()
{
//	void *p=0;
	uint32_t buf=0;
	uint16_t  crc16;
	void (*func)()  ;
	if(sys_flag.usart1_flag_idle)//接受处理
	{
				
		switch(usart1_RX_buf[0])
		{
			case 0:
				break;
//			case UPDATE_ADDR: 
//				 __disable_irq();   // 关闭总中断
//			buf=START_UPDATE;
//			buf<<=8;
//			buf+=SECOND_START;
//			writeflash(0, &buf,1);
//		 FLASH_Lock();
//		 __enable_irq();    // 开启总中断
//			
//			NVIC_SystemReset();
//			break;
			case M_CMD:
			usart1_TX_len=0;
//			crc16=CRCSUM16(usart1_RX_buf ,usart1_RX_buf[1]-2);
			crc16=	CRC16_XMODEM(usart1_RX_buf,usart1_RX_buf[1]-2)  ;
			if(usart1_RX_buf[usart1_RX_buf[1]-1]==(crc16&0xff)&&(usart1_RX_buf[usart1_RX_buf[1]-2]==((crc16>>8)&0xff)))//校验通过
			{
															usart1_TX_buf[0]=usart1_RX_buf[0];//respone   cmd0 len cmd1 state crc16
															usart1_TX_len++;
															usart1_TX_buf[1]=6;
															usart1_TX_len++;
															usart1_TX_buf[2]=usart1_RX_buf[2];
															usart1_TX_len++;
															usart1_TX_buf[3]=0;
															usart1_TX_len++;
															switch(usart1_RX_buf[2])
															{
																case START_UPDATA://5a len a6 ph pl crch crcl
																	
																	
																	sys_flag.Updata=1;
																	sys_flag.Updata_ALL=(usart1_RX_buf[3]<<8)+usart1_RX_buf[4];
																	sys_flag.Updata_count=0;
																
																//擦除数据
																	RCC_HSICmd(ENABLE);	
																	FLASH_Unlock();
																	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);
																	for(buf=0;buf<	50;buf++)
																	{
																		IWDG_ReloadCounter();//复位看门狗
																		FLASH_ErasePage(APP_FLASH_ADDR+buf*1024);
																	}
																	FLASH_Lock();
																	RCC_HSICmd(DISABLE);
																	break;
																case UPDATA ://5a len a5 aph apl ph pl data crch crcl
																	
																if(sys_flag.Updata)
																{
																	if(sys_flag.Updata_count==((usart1_RX_buf[3]<<8)+usart1_RX_buf[4]))
																	{
																		buf=APP_FLASH_ADDR+sys_flag.Updata_count*64;
																		writeflash_bytes(buf,&usart1_RX_buf[7],64);
									//									writeflash_bytes(buf,(void *)buf,64);
																		sys_flag.Updata_count++;
									//									if(sys_flag.Updata_count==sys_flag.Updata_ALL)
									//									{
									//										
									//										
									//									}
																	}
																}else{
																	usart1_TX_buf[3]=1;
									//								usart1_TX_len++;
																}
																break;
																case UPDATA_finish:
																	crc16=	CRC16_XMODEM((void *)APP_FLASH_ADDR ,sys_flag.Updata_ALL*64) ;
																if(((crc16>>8)==usart1_RX_buf[5])&&(((crc16>>0)&0xff)==usart1_RX_buf[6]))
																{
																	if(((*(uint32_t *)APP_FLASH_ADDR)&0x2FFE0000)==0x20000000)
																	{
							//												 __disable_irq();   // 关闭总中断
	//																				func =*((uint32_t *)(APP_FLASH_ADDR+4));
	//																			__set_MSP((*(uint32_t *)(APP_FLASH_ADDR)));
	//																			
	//																			func();
																		buf=flash_code_Reboot;
																		writeflash(flash_addr_iap_state,&buf,1);
																		while(1) NVIC_SystemReset();
																			
																	}else
																	{
																		usart1_TX_buf[3]=0xaa;
							//											usart1_TX_len++;
																	} 
																}else
																{
																		usart1_TX_buf[3]=0x7;
																}
																break;
																case sys_CMD_STATE:
//																usart1_TX_buf[usart1_TX_len]=0;
//																usart1_TX_len++;
																usart1_TX_buf[usart1_TX_len]=0;//程序状态
																usart1_TX_len++;
															
																memcpy(&usart1_TX_buf[usart1_TX_len],&flash_data[flash_addr_HARD_ver],4);//硬件版本
																usart1_TX_len+=4;
																memcpy(&usart1_TX_buf[usart1_TX_len],&flash_data[flash_addr_SOFT_ver],4);//软件版本
																usart1_TX_len+=4;
																memcpy(&usart1_TX_buf[usart1_TX_len],&flash_data[flash_addr_Bootloader_ver],4);//软件版本
																usart1_TX_len+=4;
																break;
																default :
												
																		usart1_TX_buf[3]=2;
										//								usart1_TX_len++;
																break;
															}
	//				usart1_TX_buf[0]=M_CMD;
	//				usart1_TX_len++;
	//				usart1_TX_buf[1]=5;
	//				usart1_TX_len++;
	//				usart1_TX_buf[2]=0;
	//				usart1_TX_len++;
				}else
				{
					usart1_TX_buf[3]=3;
//					usart1_TX_len++;

				}
				usart1_TX_buf[1]=usart1_TX_len+2;
//				crc16=CRCSUM16(usart1_TX_buf ,usart1_TX_len);
				crc16=	CRC16_XMODEM(usart1_TX_buf ,usart1_TX_len) ;
				usart1_TX_buf[usart1_TX_len]=(crc16>>8)&0xff;
				usart1_TX_len++;
				usart1_TX_buf[usart1_TX_len]=(crc16>>0)&0xff;
				usart1_TX_len++;
				sys_flag.usart1_flag_Send=1;
				break;
			case T_cmd:
				
	

					
			memcpy(usart1_TX_buf,usart1_RX_buf,usart1_RX_len);
			usart1_TX_len=usart1_RX_len;
			sys_flag.usart1_flag_Send=1;
			break;
			default :
			memcpy(usart1_TX_buf,usart1_RX_buf,usart1_RX_len);
			usart1_TX_len=usart1_RX_len;
			sys_flag.usart1_flag_Send=1;
			break;
		}
//		usart1_TX_len=3;
//	sys_flag.usart1_flag_Send=1;
		sys_flag.usart1_flag_idle=0;
	}
	
	if(sys_flag.usart1_flag_Send)//发送
	{
		Send_data1(usart1_TX_buf,usart1_TX_len);
	}
}
