/******************************************************************************
* DISCLAIMER                                                                    *
* This software is supplied by Renesas Electronics Corp. and is only 
* intended for use with Renesas products. No other uses are authorized.
*
* This software is owned by Renesas Electronics Corp. and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.
*
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORP. NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/

/*""FILE COMMENT""*******************************************************
* System Name	: RBMS-M Series Driver for Renesas
* File Name		: ad_mapping.h
* Contents		: afe ad mapping
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _AFE_AD_MAP_H
#define _AFE_AD_MAP_H
#include "define.h"
#include "afe.h"
#include "device_register.h"
/***********************************************************************
ADC BUFFER DEVICE PROFILE
***********************************************************************/
typedef enum {
	E_AD_MODE1 = 0,
	E_AD_MODE2, 
	E_AD_MODE4,
	E_AD_MODE5,
	E_AD_MODE6,
	E_AD_MODE_NUM
}E_AFE_AD_ITEM;

#define U8_AD_MEA_SIZE (U8)6

U8 const u8_Mode_Real_Size[E_AD_MODE_NUM] = {5,5,3,6,6};
// Numbers excluding offsets
// MODE1 = Offset, Cell 1-5
// MODE2 = Offset, Cell 6-10
// MODE4 = Offset, Pack, PON, Bat
// MODE5 = Offset, AN0, AN1, AN2, VREG AN0, VREG AN1, VREG AN2
// MODE6 = Offset, AD reference, CC reference, AD/CC Power, MCU reference, S Temp,VREG2

/***********************************************************************
ADC MAMPPING DEVICE PROFILE
***********************************************************************/
#define U16_INTAD_VECTOR_MAPPING INTP9

volatile U8 __near * const p8_ADIF_Reg_Mapping = &AFE_AFIF0;
U8 const u8_ADIR_Data_Mapping = INT_ADIR;
volatile U8 __near * const p8_ADMK_Reg_Mapping = &AFE_AFMK0;
U8 const u8_ADMK_Data_Mapping = INT_ADMSK;
volatile U8 __near * const p8_ADR_Reg_Mapping = &AFE_ADRL1;
volatile U8 __near * const p8_ADCEN_Reg_Mapping = &AFE_ADCON0;
U8 const u8_ADCEN_Data_Mapping[2] = {ADC_DIS,ADC_EN};
volatile U8 __near * const p8_ADMSEL_Reg_Mapping[E_AD_MODE_NUM] = {&AFE_ADMSEL0,&AFE_ADMSEL1,&AFE_ADMSEL3,&AFE_ADMSEL4,&AFE_ADMSEL5};
volatile U8 __near * const p8_ADTIME_Reg_Mapping = &AFE_ADCON2;
volatile U8 __near * const p8_ADMODSEL_Reg_Mapping = &AFE_ADCON1;
U8 const u8_ADMODSEL_Data_Mapping[E_AD_MODE_NUM] = {ADC_BTMODE1,ADC_BTMODE2,ADC_HVPMODE,ADC_THERMMODE,ADC_SFUNCMODE};

/***********************************************************************
ADC SETTING DEVICE PROFILE
***********************************************************************/

#define U8_AD_TIME_MAX						0x08
#define U8_AD_SETTIME_MAX					0x0A

typedef enum
{
	E_AD_TIME_80US = 0x00,								// 0H 80us(ADCLK=1MHz)
	E_AD_TIME_120US = 0x01,								// 1H 120us(ADCLK=1MHz)
	E_AD_TIME_160US = 0x02,								// 2H 160us(ADCLK=1MHz)
	E_AD_TIME_200US = 0x03,								// 3H 200us(ADCLK=1MHz)
	E_AD_TIME_250US = 0x04,								// 4H 250us(ADCLK=1MHz)
	E_AD_TIME_500US = 0x05,								// 5H 500us(ADCLK=1MHz)
	E_AD_TIME_750US = 0x06,								// 8H 750us(ADCLK=1MHz)
	E_AD_TIME_1000US = 0x07,								// 9H 1000us(ADCLK=1MHz)
	E_AD_TIME_36US = 0x08,								// aH 36us(ADCLK=1MHz)
} E_AFE_AD_TIME;

typedef enum
{
	E_AD_SETTIME_1MS = 0x00,								// 0H 1ms(ADCLK=1MHz)
	E_AD_SETTIME_2MS = 0x01,								// 1H 2ms(ADCLK=1MHz)
	E_AD_SETTIME_4MS = 0x02,								// 2H 4ms(ADCLK=1MHz)
	E_AD_SETTIME_8MS = 0x03,								// 3H 8ms(ADCLK=1MHz)
	E_AD_SETTIME_025MS = 0x04,							// 4H 0.25ms(ADCLK=1MHz)
	E_AD_SETTIME_05MS = 0x05,							// 5H 0.5ms(ADCLK=1MHz)
	E_AD_SETTIME_16MS = 0x08,							// 8H 16ms(ADCLK=1MHz)
	E_AD_SETTIME_32MS = 0x09,							// 9H 32ms(ADCLK=1MHz)
	E_AD_SETTIME_64MS = 0x0A,							// aH 64ms(ADCLK=1MHz)
} E_AFE_AD_SETTINGTIME;



#endif
