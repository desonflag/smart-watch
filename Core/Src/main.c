/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ST7735.h"
#include "gui.h"
#include "MAX30100.h"
#include "bmi160.h"
#include "blood.h"
#include "bsp_rtc.h"
#include "user_main.h"
#include "bsp_usartx_CC2541.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#define  EEPROM_SET_ONE max30100_Bus_Write
#define  EEPROM_READ_ONE max30100_Bus_Read
RTC_DateTypeDef sdatestructureget;
RTC_TimeTypeDef stimestructureget;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
int ascii_to_integer(char *str)
{
    int count = 0;
    int sum = 0;
    count = strlen(str);

    if((*str) < 0 && (*str) > 9)
    {
        return 0;
    }                                         //如果不为数字结果返回0

    while(count)
    {
        sum = sum + ((int) * str - 48) * (pow(10, count - 1));   //因为1的assci码值为49，所以这里统一-48，就可以得到整数的大小
        str++;
        count--;
    }

    return sum;
}
typedef struct
{
    char **str;     //the PChar of string array
    size_t num;     //the number of string
} IString;
int Split(char *src, char *delim, IString* istr)//split buf
{
    int i;
    char *str = NULL, *p = NULL;

    (*istr).num = 1;
    str = (char*)calloc(strlen(src) + 1, sizeof(char));

    if (str == NULL) return 0;

    (*istr).str = (char**)calloc(1, sizeof(char *));

    if ((*istr).str == NULL) return 0;

    strcpy(str, src);
    p = strtok(str, delim);
    (*istr).str[0] = (char*)calloc(strlen(p) + 1, sizeof(char));

    if ((*istr).str[0] == NULL) return 0;

    strcpy((*istr).str[0], p);

    for(i = 1; p = strtok(NULL, delim); i++)
    {
        (*istr).num++;
        (*istr).str = (char**)realloc((*istr).str, (i + 1) * sizeof(char *));

        if ((*istr).str == NULL) return 0;

        (*istr).str[i] = (char*)calloc(strlen(p) + 1, sizeof(char));

        if ((*istr).str[0] == NULL) return 0;

        strcpy((*istr).str[i], p);
    }

    free(str);
    str = p = NULL;
    return 1;
}
/* USER CODE END Includes */
int sport_data = 0;
uint8_t light_data = 0;
uint8_t TIM3_data = 0;
uint8_t heat_INT = 1; //心率跳出
uint8_t aRxBuffer;
uint8_t aRxBuffer2;
uint8_t page_data = 0;
uint8_t roll_data = 1;
/* USER CODE END 0 */
extern uint8_t backup_number;
char* redata;
char* redata2;
//char* redata3;
//uint8_t sport_number;
uint8_t show_number_data = 0;
uint16_t len;
uint16_t len2;
uint8_t action_data = 0;
uint8_t TIM5_data = 0;
uint8_t TIM5_blood_data = 0;
    uint16_t len3;
    char * redata3;
		char s[]="S|2";
		char z[]="ggggggggg";
		    uint8_t time;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void delay_ms(uint16_t time)

{

    uint16_t i = 0;

    while(time--)

    {

        i = 12000; //自己定义

        while(i--) ;

    }

}
int main(void)
{
    IString istr;
    int i;

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */


    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
//    MX_USART1_UART_Init();
    MX_RTC_Init();

    MX_USART2_UART_Init();

    /* USER CODE BEGIN 2 */
    /* USER CODE END 2 */
    LCD_Init();

// HAL_Delay(1000);/
//标题和两侧
//LCD_Fill(0,0,135,240,WHITE);
//	LCD_ShowPicture(0,133,27,35,0);
//		LCD_ShowPicture(108,133,27,35,1);
//标题和两侧
//	printf("123");
//	blood_Loop(1)
//    MX_RTC_Init();

//    /* 获取当前时间 */
		   MX_TIM3_Init();
    MX_TIM5_Init();
    HAL_UART_Receive_IT(&huart2, &aRxBuffer, 1);
//    __disable_irq();
    Host_page();
    max30100_init();
    BMI160_init();
//    htim3.Instance->SR &= 0xfffe;
//    HAL_TIM_Base_Start_IT(&htim3);
//    htim5.Instance->SR &= 0xfffe;
//    HAL_TIM_Base_Start_IT(&htim5);
    light_data = 1;
//		   htim5.Instance->SR &= 0xfffe;
//			     htim3.Instance->SR &= 0xfffe;

    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim5);
    while(1)
    {
//		delay_ms(10);
        time = 1;
        redata3 = get_rebuff(&len3);
        if(len3 > 0)
        {
if(len3<5){
					printf("len3=%d",len3);
            if(strstr(redata3, "S"))
            {
							for(int j=0;j<len3;j++){
								z[j]=redata3[j];
							}
															z[len3]=0x2E;
							printf("%s",z);
                if ( Split(z, ".", &istr) )
                {
                    if(istr.num == 3)
                    {
                        sport_data = ascii_to_integer(istr.str[1]);
                        printf("sport_data%d", sport_data);
                    }

                    for (i = 0; i < istr.num; i++)
                    {
                        free(istr.str[i]);
                    }

                    free(istr.str);
                }

            }
            else if(strstr(redata, "T"))
            {
                //提醒锻炼
            }

            backup_number = 0;
					}
            clean_rebuff(1);

        }

//		    while(time--)

//    {
//    }
//  MX_TIM3_Init();

//HAL_TIM_Base_Start_IT(&htim3);

        if(light_data)
        {
//					    LCD_ShowPicture(0,0,135,240,66);

            TIM3_data = 0;

            if(page_data == 0)
            {

                action_data = 1;
                HAL_TIM_Base_Stop_IT(&htim3);
                Upset_time();
                HAL_TIM_Base_Start_IT(&htim3);
                action_data = 0;

                for(int i = 1; i < 1000; i++)
                {
                    if(page_data == 0)
                    {
                        delay_ms(10);
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if(page_data == 2 && roll_data == 4)
            {
                for(int i = 1; i < 9; i++)
                {
                    if(page_data == 2 && roll_data == 4)
                    {
                        if(TIM3_data)
                        {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                            light_data = 0;
                            roll_data = 1;
                            page_data = 0;
                            TIM3_data = 0;
                            break;
                        }

                        action_data = 1;
                        LCD_ShowPicture_action_foot(54, 192, 26, 43, i);
                        action_data = 0;
                        delay_ms(100);
                    }
                }
            }

            if(page_data == 2 && roll_data == 2)
            {

                for(int i = 1; i < 9; i++)
                {

                    if(page_data == 2 && roll_data == 2)
                    {
                        if(TIM3_data)
                        {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                            light_data = 0;
                            roll_data = 1;
                            page_data = 0;
                            TIM3_data = 0;
                            break;

                        }

                        action_data = 1;
                        LCD_ShowPicture_action_cal(50, 182, 36, 56, i);
                        action_data = 0;
                        delay_ms(100);
                    }
                    else
                    {
                        break;
                    }

                }
            }

            if(page_data == 2 && roll_data == 3 && heat_INT == 1)
            {
                HAL_Delay(10);

                if(page_data == 2)
                {
                    blood_Loop(sport_data, 0);

                    if(TIM3_data)
                    {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                        light_data = 0;
                        roll_data = 1;
                        page_data = 0;
                        TIM3_data = 0;
                    }

                }
            }
        }
        else
        {
//												printf("%d",TIM5_blood_data);

            if(TIM5_blood_data == 1)
            {
                TIM5_blood_data = 0;
                blood_Loop(sport_data, 1);
            }
        }
    }

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    /* USER CODE END 3 */
}

//判断是否连续下滑
void roll_continuity_down(void)
{
    if(0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2))
    {

        if(roll_data == 5)
        {
            roll_data = 1;
            Show_roll(39, 60, 55, 180, 0, 1);
            Show_top(3, 5, 128, 24, WHITE, BLACK, 0);
        }
        else
        {
            Show_roll(39, 60, 55, 180, roll_data, 1);
            Show_top(3, 5, 128, 24, WHITE, BLACK, roll_data);
            roll_data++;
        }
    }
    else
    {

        return;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//action_data=action_data;
//	printf("2");
    if(action_data == 0)
    {
        if(GPIO_Pin == GPIO_PIN_2)
        {
            if(light_data == 1)
            {
                HAL_Delay(10);

                if(0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2))
                {
                    TIM3->CNT = 0;
                    TIM5->CNT = 0;
                    TIM5_data = 0;

                    if(page_data == 0)
                    {
                        page_data = 1;
                        Show_1();

                    }
                    else if(page_data == 1)
                    {
                        for(int i = 0; i < 10; i++)
                        {
                            roll_continuity_down();
                        }
                    }
                    else if(page_data == 2)
                    {
                        if (roll_data == 1)
                        {
                            Chose_time();
                        }

                        if (roll_data == 2)
                        {
                            page_data = 1;
                            Show_1();


                        }

                        if (roll_data == 3)
                        {
                            page_data = 1;

                            if (heat_INT == 0)
                            {
                                Show_1();
                                heat_INT = 1;

                            }
                            else
                            {
                                page_data = 2;
                            }
                        }

                        if (roll_data == 4)
                        {
                            Chose_foot();
                        }

                        if (roll_data == 5)
                        {
                        }

                    }
                }
            }
        }
        else if(GPIO_Pin == GPIO_PIN_1)
        {

            HAL_Delay(10);

            if(0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
            {


                TIM3->CNT = 0;
                TIM5->CNT = 0;
                TIM5_data = 0;


                if(page_data == 0)
                {
                    light_data = !light_data;


                    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);//开关屏幕

                    if(light_data == 1)
                    {

                        Host_page();
                        Upset_time();
                    }
                }
                else if(page_data == 1)
                {
                    page_data = 2;

                    if (roll_data == 1)
                    {
                        Time_set_page();
                    }

                    if (roll_data == 2)
                    {
                        Cal_page();
                    }

                    if (roll_data == 3)
                    {
                        Heart_page();
                    }

                    if (roll_data == 4)
                    {
                        Foot_page();
                    }

                    if (roll_data == 5)
                    {
                        Tip_page();
                    }
                }
                else if(page_data == 2)
                {
                    if (roll_data == 1)
                    {
                        Change_time();//修改时间
                    }

                    if (roll_data == 2)
                    {
                    }				if (roll_data == 3)

                    {
                        page_data = 1;

                        if (heat_INT == 0)
                        {
                            Show_1();
                            heat_INT = 1;

                        }
                        else
                        {
                            page_data = 2;
                        }
                    }

                    if (roll_data == 4)
                    {
                        Change_foot();
                    }

                    if (roll_data == 5)
                    {
                    }

                }

            }

        }
        else if(GPIO_Pin == GPIO_PIN_0)
        {
            TIM3->CNT = 0;
            TIM5->CNT = 0;
            TIM5_data = 0;

            if(light_data == 1)
            {
                HAL_Delay(10);

                if(0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
                {
                    if(page_data == 0)
                    {
                        page_data = 1;
                        Show_1();

                    }
                    else if(page_data == 1)
                    {
                        roll_data = 1;
                        page_data = 0;
                        Host_page();
                    }
                    else if(page_data == 2)
                    {
                        page_data = 1;

                        if (roll_data == 1)
                        {
                            Time_page_reten();//重新载入时间
                            Show_1();
                        }

                        if (roll_data == 2)
                        {
                            Show_1();
                        }

                        if (roll_data == 3)
                        {
                            if (heat_INT == 0)
                            {
                                Show_1();
                                heat_INT = 1;

                            }
                            else
                            {
                                page_data = 2;
                            }

                        }

                        if (roll_data == 4)
                        {
                            Foot_page_reten();
                            Show_1();

                        }

                        if (roll_data == 5)
                        {
                            Show_1();

                        }

                    }

//	                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);//开启屏幕
                }

            }
        }

        HAL_Delay(10);
    }

    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);



}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 12;
    RCC_OscInitStruct.PLL.PLLN = 96;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM4)
    {
        HAL_IncTick();
    }
    else if(htim == (&htim3))
    {
        time = 1;
			printf(".");//没这个动不了，这你敢信？
//				delay_ms(100);
//                    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);//开关屏幕

        if(light_data == 1)
        {
            if(page_data == 2)
            {
                if(roll_data == 3 || roll_data == 2 || roll_data == 4)
                {
                    TIM3_data = 1;
                    heat_INT = 1;

                }
                else
                {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

                    light_data = 0;
                    roll_data = 1;
                    page_data = 0;
                }

            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

                light_data = 0;
                roll_data = 1;
                page_data = 0;
            }
        }



    }
    else if(htim == (&htim5))
    {
        if(light_data == 0)
        {
            if(TIM5_data > 10)
            {
                TIM5_blood_data = 1;
                TIM5_data = 0;
            }
            else
            {
                TIM5_data++;
            }
        }

    }

    /* USER CODE BEGIN Callback 1 */

    /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
