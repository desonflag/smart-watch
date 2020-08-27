#ifndef __USER_MAIN_H
#define __USER_MAIN_H
#include "main.h"

#include "stm32f4xx_hal.h"
extern RTC_DateTypeDef sdatestructureget;
extern RTC_TimeTypeDef stimestructureget;
void Time_set_page(void);
extern uint8_t roll_data;
void Show_1(void);
void Chose_time(void);
void Change_time(void) ;
void Time_page_reten(void);
void Foot_page(void);
void Chose_foot(void);
void Change_foot(void);
void Foot_page_reten(void);
	void Tip_page(void);
void Host_page();
	void Upset_time(void)
;
	void Heart_page(void)
;
#endif






