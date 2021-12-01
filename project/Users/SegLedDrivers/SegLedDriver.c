/**
*****************************************************************************
* @brief
*
* @file     SegLedDriver.c
* @version
* @author
* @date     2021-12-01
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* Copyright (c) 2022 Tinychip Microelectronics Co.,Ltd.
*
*****************************************************************************
*/

#include "SegLedDriver.h"

/**
* @brief 初始化LED模组硬件
*/

void led_module_init(void)
{
   GPIO_ClrAFMode(LED1_PORT,LED1_PIN);
   GPIO_ClrAFMode(LED2_PORT,LED2_PIN);
   GPIO_ClrAFMode(LED3_PORT,LED3_PIN);
   GPIO_ClrAFMode(LED4_PORT,LED4_PIN);
   GPIO_ClrAFMode(LED5_PORT,LED5_PIN);
   GPIO_ClrAFMode(LED6_PORT,LED6_PIN);
   GPIO_ClrAFMode(LED7_PORT,LED7_PIN);
   GPIO_ClrAFMode(LED8_PORT,LED8_PIN);
   GPIO_ClrAFMode(LED9_PORT,LED9_PIN);
}


void state_led_show(uint8_t num)
{

}



void digit_led_show(DIG_INDEX index, uint8_t num, BOOL point)
{

}



void DIG1_show(uint8_t num, BOOL show_mirro_spo2)
{

}



void DIG2_show(uint8_t num, BOOL show_mirro_bpm)
{

}



void DIG3_show(uint8_t num, BOOL show_pi)
{

}



void DIG4_show(uint8_t num, BOOL show_spo2)
{

}



void DIG5_show(uint8_t num, BOOL show_bpm)
{

}



void DIG6_show(uint8_t num, BOOL show_mirro_pi)
{

}



void DIG7_show(uint8_t num, BOOL show_battery)
{

}



void DIG8_show(uint8_t num, BOOL show_s1)
{

}



void DIG9_show(STATE_LEVEL_T level, BOOL show_heart)
{

}


void thread_setup(void)
{

}


void demo_show(void)
{

}