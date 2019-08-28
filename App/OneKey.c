#include "onekey.h"
#include "SYN480R.h"
#include "usart.h"
REG Onekey_reg;
void OnekeyInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
uint8_t get_plusCode(REG *buf)
{
	uint8_t  Pluscode=0;
	buf->SEQ_CODE_L++;
	if(buf->SEQ_CODE_L==0)
	{
		buf->SEQ_CODE_H++;
	}
	Pluscode=buf->SEQ_CODE_L+0xda;
	Pluscode^=0xbe;
	Pluscode+=0xbf;
	Pluscode^=0x1a;
	Pluscode+=(buf->SEQ_CODE_H&0x0f);
	Pluscode^=0x3a;
	Pluscode+=0xcb;
	Pluscode^=0x2f;
	Pluscode&=0x7f;
	
	return Pluscode;
}

void Get_Onekey_data(REG *SRC,REG *dest)
{
	uint8_t  Pluscode=0,i=0,j=0;
	Pluscode=get_plusCode(SRC);
	
	dest->data[i]=0x19;//0
	i++;
	dest->data[i]=SRC->data[i];//1
	i++;
	dest->data[i]=SRC->data[i];//2
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//3
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//4
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//5
	i++;
	dest->data[i]=SRC->data[i];//6
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//7
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//8
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//9
	i++;
	dest->data[i]=SRC->data[i]+Pluscode;//10
	i++;
	dest->data[i]=dest->data[0];
	for(j=1;j<11;j++)//11
	{
		dest->data[i]^=dest->data[j];
	}
}
void Task_onekey()
{
	static REG Send_data;
	uint8_t Byte ;
	if(!sys_flag.Onekey_flag_Bsy)//不在发送中
	{ 
		
		 Delay_Checkus_EN(1000000,&sys_flag.Onekey_Send_time);//检测时间  
		if(Delay_Checkus(&sys_flag.Onekey_Send_time))
		{ 
			
			
			Get_Onekey_data(&Onekey_reg,&Send_data);//生成数据
			sys_flag.Onekey_flag_Bsy=1;//  发送
			sys_flag.Onekey_Send_state=0;
			sys_flag.Onekey_Edge_count=0;
		}
	}
	if(sys_flag.Onekey_flag_Bsy)////发送
	{
		switch(sys_flag.Onekey_Send_state)
		{
			case 0:
				switch(sys_flag.Onekey_Edge_count)
				{
					case 0:
						Onekey_Line_H;//发送前导码
						Delay_Checkus_EN(500,&sys_flag.Onekey_Bit_Send_time);//检测时间  
						if(Delay_Checkus(&sys_flag.Onekey_Bit_Send_time))//检测时间
						{ 
							sys_flag.Onekey_Edge_count++;
						}
						break;
						case 1:
						Onekey_Line_L;//发送前导码
						Delay_Checkus_EN(15000,&sys_flag.Onekey_Bit_Send_time);//检测时间  
						if(Delay_Checkus(&sys_flag.Onekey_Bit_Send_time))//检测时间
						{ 
							sys_flag.Onekey_Edge_count++;
						}
						break;	
						
						case 2:
							Onekey_Line_H;
						Delay_Checkus_EN(500,&sys_flag.Onekey_Bit_Send_time);//检测时间  
						if(Delay_Checkus(&sys_flag.Onekey_Bit_Send_time))//检测时间
						{ 
							sys_flag.Onekey_Edge_count=0;
							sys_flag.Onekey_Send_state++;
							sys_flag.Onekey_bytes_count=0;
						}
							break;
				}
			break;
			default:
				if((sys_flag.Onekey_Send_state>0)&&((sys_flag.Onekey_Send_state<13)))
				{
					Byte=Send_data.data[sys_flag.Onekey_Send_state-1];
					switch(sys_flag.Onekey_Edge_count)//
					{
						case 0:	Onekey_Line_L;
							if(Byte&(0x80>>sys_flag.Onekey_bytes_count))
							{
									Delay_Checkus_EN(1000,&sys_flag.Onekey_Bit_Send_time);//检测时间 
							}else
							{
								Delay_Checkus_EN(500,&sys_flag.Onekey_Bit_Send_time);//检测时间 
							}
						 
							if(Delay_Checkus(&sys_flag.Onekey_Bit_Send_time))//检测时间
							{
								sys_flag.Onekey_Edge_count++;
							}
						break;
							
						case 1:
							Onekey_Line_H;
							if(Byte&(0x80>>sys_flag.Onekey_bytes_count))
							{
									Delay_Checkus_EN(500,&sys_flag.Onekey_Bit_Send_time);//检测时间 
							}else
							{
								Delay_Checkus_EN(1000,&sys_flag.Onekey_Bit_Send_time);//检测时间 
							}
						 
							if(Delay_Checkus(&sys_flag.Onekey_Bit_Send_time))//检测时间
							{
								sys_flag.Onekey_Edge_count=0;
								sys_flag.Onekey_bytes_count++;
								if(sys_flag.Onekey_bytes_count>7)//字节完成
								{
									sys_flag.Onekey_Send_state++;
									sys_flag.Onekey_bytes_count=0;
									if(sys_flag.Onekey_Send_state>11)//发送完成
									{
										Onekey_Line_L;
										sys_flag.Onekey_Send_state=0;
										sys_flag.Onekey_flag_Bsy=0;
										
									}
								}
							}
							break;
						default :sys_flag.Onekey_flag_Bsy=0;sys_flag.Onekey_Send_state=0;break;
					}
				}else
				{
					sys_flag.Onekey_flag_Bsy=0;
				}
			break;
		}
	}
	
}

