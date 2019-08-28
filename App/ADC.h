#ifndef _ADC_H
#define _ADC_H 


#include "public.h"
extern uint16_t ADC_buf[16];
void ADCDATA_Init(void);
uint32_t Get_48V_Val(void);
#endif

