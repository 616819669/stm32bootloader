#ifndef _ACC_H
#define _ACC_H



#include "public.h"

#define Close_fz_ACC GPIO_ResetBits(GPIOA,GPIO_Pin_15);
#define Open_fz_ACC GPIO_SetBits(GPIOA,GPIO_Pin_15);

#define Close_ACC GPIO_ResetBits(GPIOB,GPIO_Pin_3);
#define Open_ACC GPIO_SetBits(GPIOB,GPIO_Pin_3);

#define GetACCState  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//acc×´Ì¬»ñÈ¡
void initACC(void);
void GPIO_init(void);
#endif
