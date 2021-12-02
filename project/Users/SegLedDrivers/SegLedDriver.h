/**
*****************************************************************************
* @brief
*
* @file   SegLedDriver.h
* @author
* @date   2021-11-26
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

#ifndef  __SEG_LED_DRV_H__
#define  __SEG_LED_DRV_H__

#include "tcasxxx.h"
#include "drv_gpio.h"
#include "DataType.h"
#include "pt.h"
#include "pt-sem.h"

/**
* @brief LED口线分配
*/

#define LED1_PORT   GPIOPortA
#define LED1_PIN    GPIOPin0
#define LED2_PORT   GPIOPortA
#define LED2_PIN    GPIOPin1
#define LED3_PORT   GPIOPortB
#define LED3_PIN    GPIOPin2
#define LED4_PORT   GPIOPortB
#define LED4_PIN    GPIOPin3
#define LED5_PORT   GPIOPortB
#define LED5_PIN    GPIOPin4
#define LED6_PORT   GPIOPortB
#define LED6_PIN    GPIOPin5
#define LED7_PORT   GPIOPortB
#define LED7_PIN    GPIOPin6
#define LED8_PORT   GPIOPortB
#define LED8_PIN    GPIOPin7
#define LED9_PORT   GPIOPortC
#define LED9_PIN    GPIOPin7


/**
* @brief led 类属性
*/

typedef struct
{
    GPIO_PORT_ENUM_E ioPort;
    GPIO_PIN_ENUM_E ioPin;
    GPIO_MODE_E dir;
    BitAction state;
    FunctionalState highLight;
    void (*init)(GPIO_Init_t *init);
    void (*dirSet)(GPIO_PORT_ENUM_E ioPort, GPIO_PIN_ENUM_E ioPin, GPIO_MODE_E dir);
    void (*outState)(GPIO_PORT_ENUM_E ioPort, GPIO_PIN_ENUM_E ioPin, BitAction state);
    void (*briSet)(GPIO_PORT_ENUM_E ioPort, GPIO_PIN_ENUM_E ioPin, FunctionalState highLight);
} led_t;

/**
* @brief seg 类属性
*/

typedef struct
{
    led_t A;
    led_t B;
    led_t C;
    led_t D;
    led_t E;
    led_t F;
    led_t G;
    led_t DP;
    led_t COM;
} seg_t;

/**
* @brief SpO2 类属性
*/

typedef struct
{
    seg_t tens;
    seg_t ones;
    uint8_t num;
    BOOL isShowNum;
    BOOL isShowReverseSpO2Sign;
    BOOL isShowReverseBpmSign;
    void (*show)(void);
} SpO2_t;

/**
* @brief PulseRate 类属性
*/

typedef struct
{
    seg_t hundreds;
    seg_t tens;
    seg_t ones;
    uint8_t num;
    BOOL isShowNum;
    BOOL isShowBpmSign;
    BOOL isShowPiSign;
    BOOL isShowSpO2Sign;
    void (*show)(void);
} PulseRate_t;

/**
* @brief PerfIndex_t 类属性
*/

typedef struct
{
    seg_t hundreds;
    seg_t tens;
    seg_t ones;
    uint8_t num;
    BOOL isShowNum;
    BOOL isShowReversePiSign;
    BOOL isShowLowBatSign;
    BOOL isShowBar1Sign;
    void (*show)(void);
} PerfIndex_t;

/**
* @brief BarState_t 枚举类属性
*/

typedef enum
{
    barLevel_1   = 0,
    barLevel_2      ,
    barLevel_3      ,
    barLevel_4      ,
    barLevel_5      ,
    barLevel_6
} BarState_t;

/**
* @brief Bar_t 类属性
*/

typedef struct
{
    led_t bar2;
    led_t bar3;
    led_t bar4;
    led_t bar5;
    led_t bar6;
    led_t heartSign;
    BOOL isShowHeartSign;
    BarState_t barState;
    void (*show)(void);
} Bar_t;

/**
* @brief ledModule_t 类属性
*/

typedef struct
{
    SpO2_t      SpO2;
    PulseRate_t PulseRate;
    PerfIndex_t PerfIndex;
    Bar_t       Bar;
} ledModule_t;

/**
* @brief 声明一个ledModule_t类对象
*/
extern ledModule_t ledModule;

/**
* @brief 声明显示初始化接口
*/

void dispInit(void);

/**
* @brief 声明显示接口
*/

void disp(void);


#endif

