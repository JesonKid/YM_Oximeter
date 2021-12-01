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

#include "DataType.h"
#include "pt.h"
#include "pt-sem.h"
/****************************************************************************
*/
#define LED1_PORT  GPIOPortA
#define LED1_PIN   GPIOPin0
#define LED2_PORT  GPIOPortA
#define LED2_PIN   GPIOPin1
#define LED3_PORT  GPIOPortB
#define LED3_PIN   GPIOPin2
#define LED4_PORT  GPIOPortB
#define LED4_PIN   GPIOPin3
#define LED5_PORT  GPIOPortB
#define LED5_PIN   GPIOPin4    
#define LED6_PORT  GPIOPortB
#define LED6_PIN   GPIOPin5
#define LED7_PORT  GPIOPortB
#define LED7_PIN   GPIOPin6
#define LED8_PORT  GPIOPortB
#define LED8_PIN   GPIOPin7
#define LED9_PORT  GPIOPortC
#define LED9_PIN   GPIOPin7

#define POS  TRUE
#define NEG  FALSE

extern uint8_t show_dir;
extern uint8_t tick;
extern BOOL tick_500ms;

//�߳�
extern struct pt pt_seg;
extern struct pt pt_dig9;

//��ѯ�ź�
extern volatile struct pt_sem poll_sem; 
extern volatile struct pt_sem slot_sem; 

//���������
typedef enum
{
    DIG_1,
    DIG_2,
    DIG_3,
    DIG_4,
    DIG_5,
    DIG_6,
    DIG_7,
    DIG_8,
    DIG_9
} DIG_INDEX;
//���������

typedef enum
{
    LEVEL_0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    LEVEL_6
} STATE_LEVEL_T;

/*
*****************************************************************************/

/********************************************************
@brief  state_led_show
@param  ��ʾ������
@retval void
*********************************************************/
void state_led_show(uint8_t num);


/********************************************************
@brief  digit_led_show
@param  index   ���������
@param  num     ��ʾ������
@param  point   �Ƿ���ʾС��
@retval void
*********************************************************/
void digit_led_show(DIG_INDEX index, uint8_t num, BOOL point);


/********************************************************
@brief  DIG1_show
@param  num               ��ʾ����
@param  show_mirro_spo2   �Ƿ���ʾ��SpO2
@retval void
*********************************************************/
void DIG1_show(uint8_t num, BOOL show_mirro_spo2);


/********************************************************
@brief  DIG1_show
@param  num               ��ʾ����
@param  show_mirro_bpm    �Ƿ���ʾ��BPM
@retval void
*********************************************************/
void DIG2_show(uint8_t num, BOOL show_mirro_bpm);


/********************************************************
@brief  DIG3_show
@param  num               ��ʾ����
@param  show_pi   �Ƿ���ʾ��PI
@retval void
*********************************************************/
void DIG3_show(uint8_t num, BOOL show_pi);


/********************************************************
@brief  DIG4_show
@param  num               ��ʾ����
@param  show_spo2         �Ƿ���ʾSpO2
@retval void
*********************************************************/
void DIG4_show(uint8_t num, BOOL show_spo2);


/********************************************************
@brief  DIG5_show
@param  num               ��ʾ����
@param  show_bpm          �Ƿ���ʾBPM
@retval void
*********************************************************/
void DIG5_show(uint8_t num, BOOL show_bpm);


/********************************************************
@brief  DIG6_show
@param  num               ��ʾ����
@param  show_mirro_pi     �Ƿ���ʾ��PI
@retval void
*********************************************************/
void DIG6_show(uint8_t num, BOOL show_mirro_pi);


/********************************************************
@brief  DIG7_show
@param  num            ��ʾ����
@param  show_battery   �Ƿ���ʾ�����
@retval void
*********************************************************/
void DIG7_show(uint8_t num, BOOL show_battery);


/********************************************************
@brief  DIG8_show
@param  num       ��ʾ����
@param  show_s1   �Ƿ���ʾ��S1
@retval void
*********************************************************/
void DIG8_show(uint8_t num, BOOL show_s1);


/********************************************************
@brief  DIG9_show
@param  level          ��ʾ״̬
@param  show_heart     �Ƿ���ʾ����
@retval void
*********************************************************/
void DIG9_show(STATE_LEVEL_T level, BOOL show_heart);

/********************************************************
@brief  thread_setup
@param  void        
@retval void
*********************************************************/
void thread_setup(void);

/********************************************************
@brief  demo_show
@param  void        
@retval void
*********************************************************/
void demo_show(void);

#endif

