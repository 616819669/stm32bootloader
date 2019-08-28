#ifndef _OTHER_H
#define _OTHER_H
#include "public.h"

#define Beep_Open GPIO_SetBits(GPIOF,GPIO_Pin_7);
#define Beep_Close GPIO_ResetBits(GPIOF,GPIO_Pin_7);

#define Lock_car GPIO_SetBits(GPIOF,GPIO_Pin_7);
#define Unlock_car  GPIO_ResetBits(GPIOF,GPIO_Pin_7);

#define Get_ZNKey_state()  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)
void Beep_Init(void);
void Speed_Init(void);
void Lock_car_Init(void);
void ROLL_Init(void);//震动传感器
void ZN_Key_Init(void);
void Task_ZN_Key(void);
void TASK_ROLL(void);
void TASK_speed(void);
void TASK_beep(void);
void  Beep_out_pwm(uint32_t pre);//输出pwm波形
#endif


