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
#include "pt.h"

/**
* @brief 定义一个ledModule_t类对象
*/
ledModule_t ledModule;

/**
* @brief 线程对象
*/

static pt pt_spo2;
static pt pt_bpm;
static pt pt_pi;
static pt pt_bar;

/**
* @brief 数码管切换信标
*/

static pt_sem segSwitch;

/**
* @brief 显示线程
*/

static void dispSpO2Thread(pt *pt);
static void dispBpmThread(pt *pt);
static void dispPiThread(pt *pt);
static void dispBarThread(pt *pt);

/**
* @brief 线程启动
*/

static void threadSetup(void)

/**
* @brief 定义底层初始化接口
*/

void lowLevelInit(void)
{
    GPIO_Init_t initStruct;
    io_t *Line = &ledModule.lowLevel.L1;

    Line->ioPort = L1_PORT;
    Line->ioPin = L1_PIN;
    //高亮输出
    Line->highLight = ENABLE;
    Line->briSet = GPIO_20mA_Mode;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    //初始化为输入模式
    Line->dir = GPIO_INPUT_MODE;
    Line->init = GPIO_Init;

    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    //初始化为推挽模式
    initStruct.GPIO_Ext_Mode = GPIO_PIN_PUSH_PULL;
    initStruct.GPIO_Mode = Line->dir;
    initStruct.GPIO_Pull_Mode = GPIO_PULL_NONE;
    Line->init(&initStruct);

    Line = &ledModule.lowLevel.L2;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L2_PORT;
    Line->ioPin = L2_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L3;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L3_PORT;
    Line->ioPin = L3_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L4;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L4_PORT;
    Line->ioPin = L4_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L5;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L5_PORT;
    Line->ioPin = L5_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L6;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L6_PORT;
    Line->ioPin = L6_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L7;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L7_PORT;
    Line->ioPin = L7_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L8;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L8_PORT;
    Line->ioPin = L8_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L9;
    //拷贝相同的参数配置
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L9_PORT;
    Line->ioPin = L9_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

}

/**
* @brief 定义正常显示配置接口
*/

void dispNormalCfg(void)
{
    seg_t *seg = &ledModule.SpO2.tens;

    seg->A   = &ledModule.lowLevel.L2;
    seg->B   = &ledModule.lowLevel.L3;
    seg->C   = &ledModule.lowLevel.L4;
    seg->D   = &ledModule.lowLevel.L5;
    seg->E   = &ledModule.lowLevel.L6;
    seg->F   = &ledModule.lowLevel.L7;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L1;

    seg = &ledModule.SpO2.ones;
    *seg = ledModule.SpO2.tens;
    seg->A = &ledModule.lowLevel.L1;
    seg->COM = &ledModule.lowLevel.L2;

    seg = &ledModule.PulseRate.hundreds;
    *seg = ledModule.SpO2.ones;
    seg->B = &ledModule.lowLevel.L2;
    seg->COM = &ledModule.lowLevel.L3;

    seg = &ledModule.PulseRate.tens;
    *seg = ledModule.PulseRate.hundreds;
    seg->C = &ledModule.lowLevel.L3;
    seg->COM = &ledModule.lowLevel.L4;

    seg = &ledModule.PulseRate.ones;
    *seg = ledModule.PulseRate.tens;
    seg->D = &ledModule.lowLevel.L4;
    seg->COM = &ledModule.lowLevel.L5;

    seg = &ledModule.PerfIndex.hundreds;
    *seg = ledModule.PulseRate.ones;
    seg->E = &ledModule.lowLevel.L5;
    seg->COM = &ledModule.lowLevel.L6;

    seg = &ledModule.PerfIndex.tens;
    *seg = ledModule.PerfIndex.hundreds;
    seg->F = &ledModule.lowLevel.L6;
    seg->COM = &ledModule.lowLevel.L7;

    seg = &ledModule.PerfIndex.ones;
    *seg = ledModule.PerfIndex.tens;
    seg->G = &ledModule.lowLevel.L7;
    seg->COM = &ledModule.lowLevel.L8;

    ledModule.Bar.bar2      = &ledModule.lowLevel.L1;
    ledModule.Bar.bar3      = &ledModule.lowLevel.L2;
    ledModule.Bar.bar4      = &ledModule.lowLevel.L3;
    ledModule.Bar.bar5      = &ledModule.lowLevel.L4;
    ledModule.Bar.bar6      = &ledModule.lowLevel.L5;
    ledModule.Bar.heartSign = &ledModule.lowLevel.L6;
    ledModule.Bar.COM       = &ledModule.lowLevel.L9;
}

/**
* @brief 定义倒置显示配置接口
*/

void dispReverseCfg(void)
{
    seg_t *seg = &ledModule.SpO2.tens;

    seg->A   = &ledModule.lowLevel.L4;
    seg->B   = &ledModule.lowLevel.L5;
    seg->C   = &ledModule.lowLevel.L6;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L3;
    seg->F   = &ledModule.lowLevel.L4;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L2;

    seg = &ledModule.SpO2.ones;
    seg->A   = &ledModule.lowLevel.L5;
    seg->B   = &ledModule.lowLevel.L6;
    seg->C   = &ledModule.lowLevel.L7;
    seg->D   = &ledModule.lowLevel.L2;
    seg->E   = &ledModule.lowLevel.L3;
    seg->F   = &ledModule.lowLevel.L4;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L1;

    seg = &ledModule.PulseRate.hundreds;
    seg->A   = &ledModule.lowLevel.L4;
    seg->B   = &ledModule.lowLevel.L6;
    seg->C   = &ledModule.lowLevel.L7;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L2;
    seg->F   = &ledModule.lowLevel.L3;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L5;

    seg = &ledModule.PulseRate.tens;
    seg->A   = &ledModule.lowLevel.L5;
    seg->B   = &ledModule.lowLevel.L6;
    seg->C   = &ledModule.lowLevel.L7;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L2;
    seg->F   = &ledModule.lowLevel.L3;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L4;

    seg = &ledModule.PulseRate.ones;
    seg->A   = &ledModule.lowLevel.L5;
    seg->B   = &ledModule.lowLevel.L6;
    seg->C   = &ledModule.lowLevel.L7;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L2;
    seg->F   = &ledModule.lowLevel.L4;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L3;

    seg = &ledModule.PerfIndex.hundreds;
    seg->A   = &ledModule.lowLevel.L4;
    seg->B   = &ledModule.lowLevel.L5;
    seg->C   = &ledModule.lowLevel.L6;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L2;
    seg->F   = &ledModule.lowLevel.L3;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L8;

    seg = &ledModule.PerfIndex.tens;
    seg->A   = &ledModule.lowLevel.L4;
    seg->B   = &ledModule.lowLevel.L5;
    seg->C   = &ledModule.lowLevel.L6;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L2;
    seg->F   = &ledModule.lowLevel.L3;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L7;

    seg = &ledModule.PerfIndex.ones;
    seg->A   = &ledModule.lowLevel.L4;
    seg->B   = &ledModule.lowLevel.L5;
    seg->C   = &ledModule.lowLevel.L7;
    seg->D   = &ledModule.lowLevel.L1;
    seg->E   = &ledModule.lowLevel.L2;
    seg->F   = &ledModule.lowLevel.L3;
    seg->G   = &ledModule.lowLevel.L8;
    seg->DP  = &ledModule.lowLevel.L9;
    seg->COM = &ledModule.lowLevel.L6;

    ledModule.Bar.bar2      = &ledModule.lowLevel.L1;
    ledModule.Bar.bar3      = &ledModule.lowLevel.L2;
    ledModule.Bar.bar4      = &ledModule.lowLevel.L3;
    ledModule.Bar.bar5      = &ledModule.lowLevel.L4;
    ledModule.Bar.bar6      = &ledModule.lowLevel.L5;
    ledModule.Bar.heartSign = &ledModule.lowLevel.L6;
    ledModule.Bar.COM       = &ledModule.lowLevel.L9;
}

/**
* @brief 加载默认配置接口
*/

void defaultCfg(void)
{
    //默认正常显示
    dispNormalCfg();
}

/**
* @brief 定义显示初始化接口
*/

void dispInit(void)
{
    //底层初始化
    void (*init)(void) = ledModule.lowLevel.init;
    init = lowLevelInit;
    init();
    if (ledModule.reloadCfgPar = inValid)
    {
        //加载默认值
        defaultCfg();
    }
    else
    {
        if (ledModule.showDir = Normal)dispNormalCfg();
        else dispReverseCfg();
    }
}

/**
* @brief 定义显示接口
*/

void disp(void)
{

}

/**
* @brief 血样数值显示线程
*/

static void dispSpO2Thread(pt *pt)
{
    PT_BEGIN(pt);
    PT_WAIT_UNTIL(pt,);
    PT_END(pt);
}

/**
* @brief 心率数值显示线程
*/

static void dispBpmThread(pt *pt)
{

}

/**
* @brief 灌注指数显示线程
*/

static void dispPiThread(pt *pt)
{

}

/**
* @brief 状态条显示线程
*/

static void dispBarThread(pt *pt)
{

}

/**
* @brief 显示线程启动
*/

static void threadSetup(void)
{

}


