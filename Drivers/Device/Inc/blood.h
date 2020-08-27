#ifndef __BLOOD_H
#define __BLOOD_H
#include "stdio.h"

#include "stm32f4xx_hal.h"
typedef enum
{
	BLD_NORMAL,		//正常
	BLD_ERROR,		//侦测错误
	
}BloodState;//血液状态

typedef struct
{
	uint16_t 		heart;		//心率数据
	float 			SpO2;			//血氧数据
	BloodState	state;		//状态
	uint8_t   	update;		//信息更新标志位
	uint8_t   	display;	//数据更新标志位
}BloodData;
//BloodData g_blooddata = {0};					//血液数据存储
extern uint8_t heat_INT;
extern uint8_t TIM3_data;
BloodData ffheart(void);
void blood_Setup(void);
void blood_Loop(int sport_data,uint8_t sent_data)
;uint16_t ffrawStep(void);
void tft_draw_windows(void);
extern RTC_DateTypeDef sdatestructureget;
extern RTC_TimeTypeDef stimestructureget;
#endif /*__BLOOD_H*/
