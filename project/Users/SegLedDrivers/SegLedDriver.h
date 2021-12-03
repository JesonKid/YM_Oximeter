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

#ifndef __SEG_LED_DRV_H__
#define __SEG_LED_DRV_H__

#include "tcasxxx.h"
#include "drv_gpio.h"
#include "DataType.h"
#include "pt.h"
#include "pt-sem.h"

/**
* @brief LED���߷���
*/

#define L1_PORT GPIOPortA
#define L1_PIN GPIOPin0
#define L2_PORT GPIOPortA
#define L2_PIN GPIOPin1
#define L3_PORT GPIOPortB
#define L3_PIN GPIOPin2
#define L4_PORT GPIOPortB
#define L4_PIN GPIOPin3
#define L5_PORT GPIOPortB
#define L5_PIN GPIOPin4
#define L6_PORT GPIOPortB
#define L6_PIN GPIOPin5
#define L7_PORT GPIOPortB
#define L7_PIN GPIOPin6
#define L8_PORT GPIOPortB
#define L8_PIN GPIOPin7
#define L9_PORT GPIOPortC
#define L9_PIN GPIOPin7

/**
* @brief �������������ֵ��
*/

char code_table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

/**
* @brief io_t ������
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
} io_t;

/**
* @brief lowLevel_t ������
*/

typedef struct
{
    io_t L1;
    io_t L2;
    io_t L3;
    io_t L4;
    io_t L5;
    io_t L6;
    io_t L7;
    io_t L8;
    io_t L9;
    void (*init)(void);
} lowLevel_t;

/**
* @brief seg ������
*/

typedef struct
{
    io_t *A;
    io_t *B;
    io_t *C;
    io_t *D;
    io_t *E;
    io_t *F;
    io_t *G;
    io_t *DP;
    io_t *COM;
} seg_t;

/**
* @brief SpO2 ������
*/

typedef struct
{
    seg_t tens;
    seg_t ones;
    uint8_t num;
    BOOL isShowNum;
    BOOL isShowReverseSpO2Sign;
    BOOL isShowReverseBpmSign;
    uint16_t numShinePeriod; //ms��λ  0--����˸
    void (*show)(void);
} SpO2_t;

/**
* @brief PulseRate ������
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
    uint16_t numShinePeriod; //ms��λ  0--����˸
    void (*show)(void);
} PulseRate_t;

/**
* @brief PerfIndex_t ������
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
    uint16_t numShinePeriod;    //ms��λ  0--����˸
    uint16_t lowPwrShinePeriod; //ms��λ  0--����˸
    void (*show)(void);
} PerfIndex_t;

/**
* @brief BarState_t ö��������
*/

typedef enum
{
    barLevel_1 = 0,
    barLevel_2,
    barLevel_3,
    barLevel_4,
    barLevel_5,
    barLevel_6
} BarState_t;

/**
* @brief ShowDir_t ö��������
*/

typedef enum
{
    Normal = 0,
    Reverse
} ShowDir_t;

/**
* @brief reloadPar_t ö��������
*/

typedef enum
{
    inValid = 0,
    Valid   = 0xAA
} reloadPar_t;

/**
* @brief Bar_t ������
*/

typedef struct
{
    io_t *bar2;
    io_t *bar3;
    io_t *bar4;
    io_t *bar5;
    io_t *bar6;
    io_t *heartSign;
    io_t *COM;
    BOOL isShowHeartSign;
    BarState_t barState;
    uint16_t heartDuty;        //������˸ռ�ձ�
    uint16_t barChangePeriod;  //bar�л����
    uint16_t dynamicPeriod;    //��̬����
    void (*show)(void);
} Bar_t;

/**
* @brief ledModule_t ������
*/

typedef struct
{
    SpO2_t SpO2;
    PulseRate_t PulseRate;
    PerfIndex_t PerfIndex;
    Bar_t Bar;
    lowLevel_t lowLevel;
    ShowDir_t showDir;
    reloadPar_t reloadCfgPar;    //0xAA��Ч
} ledModule_t;

/**
* @brief ����һ��ledModule_t�����
*/
extern ledModule_t ledModule;

/**
* @brief ������ʾ��ʼ���ӿ�
*/

void dispInit(void);

/**
* @brief �����ײ��ʼ���ӿ�
*/

void lowLevelInit(void);

/**
* @brief ����Ĭ�����ýӿ�
*/

void defaultCfg(void);

/**
* @brief ����������ʾ���ýӿ�
*/

void dispNormalCfg(void);

/**
* @brief ����������ʾ���ýӿ�
*/

void dispReverseCfg(void);

/**
* @brief ������ʾ�ӿ�
*/

void disp(void);

#endif
