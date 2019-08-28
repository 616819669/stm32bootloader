#include "ADC.h"
uint16_t ADC_buf[16];

void ADCDATA_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T1_CC4;
	ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanDirection=ADC_ScanDirection_Upward;
	ADC_Init(ADC1, & ADC_InitStruct);
	ADC_ChannelConfig(ADC1, ADC_Channel_3,ADC_SampleTime_55_5Cycles);
	
	
	
//	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
//	NVIC_InitStruct.NVIC_IRQChannel=ADC1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPriority=1;
//	NVIC_Init(&NVIC_InitStruct);
	
	
	ADC_GetCalibrationFactor(ADC1);
	
	DMA_InitStruct.DMA_BufferSize=16;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)ADC_buf;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	DMA_SetCurrDataCounter(DMA1_Channel1, 16);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_DMARequestModeConfig(ADC1,ADC_DMAMode_Circular);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_StartOfConversion(ADC1);
}

uint32_t Get_48V_Val()
{
	uint8_t i=0;
	uint32_t buf=0;
	for(i=0;i<16;i++)
	{
		buf+=ADC_buf[i];
	}
	buf/=16;
	return (buf*3300/0xfff)*103/3;
}
