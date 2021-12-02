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
* @brief ����һ��ledModule_t�����
*/
ledModule_t ledModule;

/**
* @brief ������ʾ��ʼ���ӿ�
*/

void dispInit(void)
{
    GPIO_Init_t initStruct;
    led_t *led = &ledModule.SpO2.tens.A;

    led->init = GPIO_Init;
    led->briSet = GPIO_20mA_Mode;

    led->ioPort = GPIOPortA;
    led->ioPin = GPIOPin0;

    led->highLight = ENABLE;

    led->briSet(led->ioPort,led->ioPin,led->highLight);

    initStruct.GPIO_Port = led->ioPort ;
    initStruct.GPIO_Pin = led->ioPin;
    initStruct.GPIO_Ext_Mode = GPIO_PIN_PUSH_PULL;
    //��ʼ��Ϊ����ģʽ
    initStruct.GPIO_Mode = GPIO_INPUT_MODE;
    //��������
    initStruct.GPIO_Pull_Mode = GPIO_PULL_NONE;
    led->init(&initStruct);
    
    ledModule.SpO2.tens.B = ledModule.SpO2.tens.A;
    



}

/**
* @brief ������ʾ�ӿ�
*/

void disp(void)
{

}
