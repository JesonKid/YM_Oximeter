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
* @brief ����һ��ledModule_t�����
*/
ledModule_t ledModule;

/**
* @brief �̶߳���
*/

static pt pt_spo2;
static pt pt_bpm;
static pt pt_pi;
static pt pt_bar;

/**
* @brief ������л��ű�
*/

static pt_sem segSwitch;

/**
* @brief ��ʾ�߳�
*/

static void dispSpO2Thread(pt *pt);
static void dispBpmThread(pt *pt);
static void dispPiThread(pt *pt);
static void dispBarThread(pt *pt);

/**
* @brief �߳�����
*/

static void threadSetup(void)

/**
* @brief ����ײ��ʼ���ӿ�
*/

void lowLevelInit(void)
{
    GPIO_Init_t initStruct;
    io_t *Line = &ledModule.lowLevel.L1;

    Line->ioPort = L1_PORT;
    Line->ioPin = L1_PIN;
    //�������
    Line->highLight = ENABLE;
    Line->briSet = GPIO_20mA_Mode;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    //��ʼ��Ϊ����ģʽ
    Line->dir = GPIO_INPUT_MODE;
    Line->init = GPIO_Init;

    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    //��ʼ��Ϊ����ģʽ
    initStruct.GPIO_Ext_Mode = GPIO_PIN_PUSH_PULL;
    initStruct.GPIO_Mode = Line->dir;
    initStruct.GPIO_Pull_Mode = GPIO_PULL_NONE;
    Line->init(&initStruct);

    Line = &ledModule.lowLevel.L2;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L2_PORT;
    Line->ioPin = L2_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L3;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L3_PORT;
    Line->ioPin = L3_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L4;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L4_PORT;
    Line->ioPin = L4_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L5;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L5_PORT;
    Line->ioPin = L5_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L6;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L6_PORT;
    Line->ioPin = L6_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L7;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L7_PORT;
    Line->ioPin = L7_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L8;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L8_PORT;
    Line->ioPin = L8_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

    Line = &ledModule.lowLevel.L9;
    //������ͬ�Ĳ�������
    *Line = ledModule.lowLevel.L1;
    Line->ioPort = L9_PORT;
    Line->ioPin = L9_PIN;
    Line->briSet(Line->ioPort, Line->ioPin, Line->highLight);
    initStruct.GPIO_Port = Line->ioPort;
    initStruct.GPIO_Pin = Line->ioPin;
    Line.init(&initStruct);

}

/**
* @brief ����������ʾ���ýӿ�
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
* @brief ���嵹����ʾ���ýӿ�
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
* @brief ����Ĭ�����ýӿ�
*/

void defaultCfg(void)
{
    //Ĭ��������ʾ
    dispNormalCfg();
}

/**
* @brief ������ʾ��ʼ���ӿ�
*/

void dispInit(void)
{
    //�ײ��ʼ��
    void (*init)(void) = ledModule.lowLevel.init;
    init = lowLevelInit;
    init();
    if (ledModule.reloadCfgPar = inValid)
    {
        //����Ĭ��ֵ
        defaultCfg();
    }
    else
    {
        if (ledModule.showDir = Normal)dispNormalCfg();
        else dispReverseCfg();
    }
}

/**
* @brief ������ʾ�ӿ�
*/

void disp(void)
{

}

/**
* @brief Ѫ����ֵ��ʾ�߳�
*/

static void dispSpO2Thread(pt *pt)
{
    PT_BEGIN(pt);
    PT_WAIT_UNTIL(pt,);
    PT_END(pt);
}

/**
* @brief ������ֵ��ʾ�߳�
*/

static void dispBpmThread(pt *pt)
{

}

/**
* @brief ��עָ����ʾ�߳�
*/

static void dispPiThread(pt *pt)
{

}

/**
* @brief ״̬����ʾ�߳�
*/

static void dispBarThread(pt *pt)
{

}

/**
* @brief ��ʾ�߳�����
*/

static void threadSetup(void)
{

}


