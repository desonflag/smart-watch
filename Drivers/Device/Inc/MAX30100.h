#ifndef __MAX30100_H
#define __MAX30100_H

#include "stm32f4xx_hal.h"
/*define ---------------------------------------------------------------------*/
#define max30100_WR_address 0xAE
#define MAX30102_Device_address max30100_WR_address
#define I2C_WR	0		/* Ð´¿ØÖÆbit */
#define I2C_RD	1		/* ¶Á¿ØÖÆbit */
#define REG_INTR_STATUS_1 	0x00
#define REG_INTR_STATUS_2 	0x01
#define REG_INTR_ENABLE_1 	0x02
#define REG_INTR_ENABLE_2 	0x03
#define REG_FIFO_WR_PTR 		0x04
#define REG_OVF_COUNTER 		0x05
#define REG_FIFO_RD_PTR 		0x06
#define REG_FIFO_DATA 			0x07
#define REG_FIFO_CONFIG 		0x08
#define REG_MODE_CONFIG 		0x09
#define REG_SPO2_CONFIG 		0x0A
#define REG_LED1_PA 				0x0C
#define REG_LED2_PA 				0x0D
#define REG_PILOT_PA 				0x10
#define REG_MULTI_LED_CTRL1 0x11
#define REG_MULTI_LED_CTRL2 0x12
#define REG_TEMP_INTR 			0x1F
#define REG_TEMP_FRAC 			0x20
#define REG_TEMP_CONFIG 		0x21
#define REG_PROX_INT_THRESH 0x30
#define REG_REV_ID 					0xFE
#define REG_PART_ID 				0xFF
#define INTERRUPT_REG  							0X00
#define INTERRUPT_REG_A_FULL  			(0X01<<7)
#define INTERRUPT_REG_TEMP_RDY  		(0X01<<6)
#define INTERRUPT_REG_HR_RDY  			(0X01<<5)
#define INTERRUPT_REG_SPO2_RDY  		(0X01<<4)
#define INTERRUPT_REG_PWR_RDY  			(0X01<<0)
#define EEPROM_DEV_ADDR 0xa0
#define EEPROM_SIZE 8
#define SAMPLES_PER_SECOND 					100	//¼ì²âÆµÂÊ
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);

uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t max30100_Bus_Write(uint8_t Register_Address, uint8_t Word_Data,uint8_t address);
uint8_t max30100_Bus_Read(uint8_t Register_Address,uint8_t address);
void max30100_FIFO_Read(uint8_t Register_Address,uint16_t  Word_Data[][2],uint8_t count);
void max30100_init(void);


#endif /*__MAX30100_h*/

