#ifndef __bmi160_H
#define __bmi160_H
#include "stm32f4xx_hal.h"

#include "MAX30100.h"
#include "bsp_urat.h"

void BMI160_init(void);
void bmi160_getStep(uint16_t *rawStep);


#endif