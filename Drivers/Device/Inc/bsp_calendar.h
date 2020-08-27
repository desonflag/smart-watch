/******************** (C) COPYRIGHT 2009 www.armjishu.com ************************
* File Name          : calendar.h
* Author             : www.armjishu.com Team
* Version            : V1.0
* Date               : 10/1/2009
* Description      : 超强的日历，支持农历，24节气几乎所有日历的功能
                          日历时间以1970年为元年，用32bit的时间寄存器可以运
                          行到2100年左右
*******************************************************************************/

#ifndef __CALENDAR_H
#define __CALENDAR_H
#include "stm32f4xx_hal.h"

extern uint8_t const *WEEK_STR[];
extern uint8_t const *zodiac_sign[];

uint8_t GetMoonDay(uint8_t month_p,unsigned short table_addr);
uint8_t GetChinaCalendar(uint16_t  year,uint8_t month,uint8_t day,uint8_t *p);
void GetSkyEarth(uint16_t year,uint8_t *p);
void StrCopy(uint8_t *target,uint8_t const *source,uint8_t no);
void GetChinaCalendarStr(uint16_t year,uint8_t month,uint8_t day,uint8_t *str);
uint8_t GetJieQi(uint16_t year,uint8_t month,uint8_t day,uint8_t *JQdate);
uint8_t GetJieQiStr(uint16_t year,uint8_t month,uint8_t day,uint8_t *str);
#endif 
