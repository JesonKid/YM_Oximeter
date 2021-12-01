/**
*****************************************************************************
* @brief
*
* @file   main.c
* @author   lt
* @date   2021-11-11
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* Copyright (c) 2021 Tinychip Microelectronics Co.,Ltd.
*
*****************************************************************************
*/
#include "DataType.h"
#include "SystemDriver.h"
#include "Spo2Interface.h"
#include "trace.h"
#include "interrupt.h"
#include "wdg.h"
#include "gpio.h"
#include "stdbool.h"
#include "delay.h"
#include "rcc.h"
#include "SegLedDriver.h"


/*******************************************************************************
* Definitions
******************************************************************************/
/* 私有(仅本源文件内使用)宏、枚举、结构体的定义 */


// Main Procedure
#if defined   ( __ICCARM__   ) /* iar */
int main(void)
#elif defined ( __CC_ARM )     /* keil */
int TCmain(void)
#endif
{
    //延时10秒用于program
    delay1ms(10000);
    
#ifdef LOG
    PrintInit();
#endif

    IC_PowupInit();

    SYS_Hardware_Init();

    SYS_Interrupt_Enable();

    while (1)
    {
       ;
    }
}
