#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#include "stm32f0xx.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"
typedef struct 
{
	uint32_t time_tick;
	}TIME_BASE;
extern TIME_BASE Tim_core;
extern uint32_t test11 ;

void delay_us(uint32_t data);
void timeInit(void);
void delay_ms(uint32_t data);
void delay_time17_us(uint16_t us);//X20 us
void delay_time17_ms(uint16_t ms);//X20 us
void DataINit(void);
uint32_t Get_syscore_tim(void);//获取内核时间
	void WWDGInit(void);
#endif 
