#ifndef __BSP_USARTX_CC2541_H__
#define __BSP_USARTX_CC2541_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/
#define CC2541_USARTx                                 USART2
#define CC2541_USARTx_BAUDRATE                        9600
#define CC2541_USART_RCC_CLK_ENABLE()                 __HAL_RCC_USART2_CLK_ENABLE()
#define CC2541_USART_RCC_CLK_DISABLE()                __HAL_RCC_USART2_CLK_DISABLE()

#define CC2541_USARTx_GPIO_ClK_ENABLE()               __HAL_RCC_GPIOA_CLK_ENABLE()
#define CC2541_USARTx_Tx_GPIO_PIN                     GPIO_PIN_2
#define CC2541_USARTx_Tx_GPIO                         GPIOA
#define CC2541_USARTx_Rx_GPIO_PIN                     GPIO_PIN_3
#define CC2541_USARTx_Rx_GPIO                         GPIOA
#define HC05_DEBUG_ON                   0
#define HC05_DEBUG(fmt,arg...)          do{\
                                          if(HC05_DEBUG_ON)\
                                          printf("<<-HC05-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)
#define husartx huart2
/* 扩展变量 ------------------------------------------------------------------*/
extern UART_HandleTypeDef husartx;

/* 函数声明 ------------------------------------------------------------------*/
void CC2541_USARTx_Init(void);
char *get_rebuff(uint16_t *len);
void clean_rebuff(int a);
void Usart_SendString(uint8_t *str);
void Usart_SendByte(uint8_t ch );
void Usart_SendStr_length(uint8_t *str,uint32_t strlen );
uint8_t CC2541_Send_CMD(char* cmd);
										 uint8_t CC2541_Send_CMD2(uint8_t clean);
										  char *get_rebuff2(uint16_t *len) ;
uint8_t CC2541_Send_CMD_blue(char* cmd)
;
 uint8_t CC2541_Send_CMD_power(char* cmd)
;
#endif  /* __BSP_USARTX_CC2541_H__ */

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
