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
* System Name	: RBMS-M Firmware for Renesas
* File Name		: afe_ad_map.h
* Contents		: general define
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _AFE_AD_MAP_H
#define _AFE_AD_MAP_H
#include "define.h"
#include "device_register.h"
/***********************************************************************
ADC BUFFER DEVICE PROFILE
***********************************************************************/
/* ---- 1H: Battery cell measurement mode 1 ----*/
typedef enum {
	E_MEA_MODE1_OFFSET = 0,
	E_MEA_MODE1_CELL1,
	E_MEA_MODE1_CELL2,
	E_MEA_MODE1_CELL3,
	E_MEA_MODE1_CELL4,
	E_MEA_MODE1_CELL5,
	E_MEA_MODE1_END  /* 6 */
}E_MEA_MODE1_ITEM;

/* ---- 2H: Battery cell measurement mode 2 ----*/
typedef enum {
	E_MEA_MODE2_OFFSET = E_MEA_MODE1_END,
	E_MEA_MODE2_CELL6,
	E_MEA_MODE2_CELL7,
	E_MEA_MODE2_CELL8,
	E_MEA_MODE2_CELL9,
	E_MEA_MODE2_CELL10,
	E_MEA_MODE2_END  /* 12 */
}E_MEA_MODE2_ITEM;



/* ---- 4H: High voltage pin measurement mode ----*/
typedef enum {
	E_MEA_MODE4_OFFSET = E_MEA_MODE2_END,
	E_MEA_MODE4_PACKV,
	E_MEA_MODE4_PON,
	E_MEA_MODE4_TOTALV,
	E_MEA_MODE4_END  /* 16 */
}E_MEA_MODE4_ITEM;



/* ---- 5H: Thermistor measurement mode ----*/
typedef enum {
	E_MEA_MODE5_OFFSET = E_MEA_MODE4_END,
	E_MEA_MODE5_AN0,
	E_MEA_MODE5_AN1,
	E_MEA_MODE5_AN2,
	E_MEA_MODE5_VREG_AN0,
	E_MEA_MODE5_VREG_AN1,
	E_MEA_MODE5_VREG_AN2,
	E_MEA_MODE5_END  /* 23 */
}E_MEA_MODE5_ITEM;



/* ---- 6H: Functional safety measurement mode ----*/
typedef enum {
	E_MEA_MODE6_OFFSET = E_MEA_MODE5_END,
	E_MEA_MODE6_ADREF,
	E_MEA_MODE6_CCREF,
	E_MEA_MODE6_ADCC,
	E_MEA_MODE6_MCUREF,
	E_MEA_MODE6_STEMP,
	E_MEA_MODE6_VREG2,
	E_MEA_MODE6_END  /* 30 */
}E_MEA_MODE6_ITEM;

#define U8_MEA_MODE1_NUM (E_MEA_MODE1_END)
#define U8_MEA_MODE2_NUM (E_MEA_MODE2_END - E_MEA_MODE1_END)
#define U8_MEA_MODE4_NUM (E_MEA_MODE4_END - E_MEA_MODE2_END)
#define U8_MEA_MODE5_NUM (E_MEA_MODE5_END - E_MEA_MODE4_END)
#define U8_MEA_MODE6_NUM (E_MEA_MODE5_END - E_MEA_MODE4_END)
#define U8_TOTAL_ADC_COUNT (E_MEA_MODE6_END)

const U8 u8_Mode_Start_index[U8_TOTAL_ADC_COUNT] = {E_MEA_MODE1_OFFSET,E_MEA_MODE2_OFFSET,E_MEA_MODE4_OFFSET,E_MEA_MODE5_OFFSET,E_MEA_MODE6_OFFSET};
const U8 u8_Mode_Size[U8_TOTAL_ADC_COUNT] = {U8_MEA_MODE1_NUM,U8_MEA_MODE2_NUM,U8_MEA_MODE4_NUM,U8_MEA_MODE5_NUM,U8_MEA_MODE6_NUM};

#define U8_MAX_MODE_SIZE MAX2( MAX2( MAX2(U8_MEA_MODE1_NUM, U8_MEA_MODE2_NUM),MAX2(U8_MEA_MODE4_NUM, U8_MEA_MODE5_NUM) ),U8_MEA_MODE6_NUM )

typedef enum {
	E_AD_MODE1 = 0,
	E_AD_MODE2,	
	E_AD_MODE4,
	E_AD_MODE5,
	E_AD_MODE6,
	E_AD_ITEM_NUM
}E_AFE_AD_ITEM;
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
volatile U8 __near * const p8_ADR_Reg_Mapping = &AFE_ADORL;
volatile U8 __near * const p8_ADCEN_Reg_Mapping = &AFE_ADCON0;
U8 const u8_ADCEN_Data_Mapping[2] = {ADC_DIS,ADC_EN};
volatile U8 __near * const p8_ADMSEL_Reg_Mapping[E_AD_ITEM_NUM] = {&AFE_ADMSEL0,&AFE_ADMSEL1,&AFE_ADMSEL3,&AFE_ADMSEL4,&AFE_ADMSEL5};
volatile U8 __near * const p8_ADTIME_Reg_Mapping = &AFE_ADCON2;
volatile U8 __near * const p8_ADMODSEL_Reg_Mapping = &AFE_ADCON1;
U8 const u8_ADMODSEL_Data_Mapping[E_AD_ITEM_NUM] = {ADC_BTMODE1,ADC_BTMODE2,ADC_HVPMODE,ADC_THERMMODE,ADC_SFUNCMODE};

/***********************************************************************
ADC SETTING DEVICE PROFILE
***********************************************************************/
#define U64_AD_CV_LOW_OFFSET_EN				(1<<E_MEA_MODE1_OFFSET)
#define U64_AD_CV1_EN						(1<<E_MEA_MODE1_CELL1)
#define U64_AD_CV2_EN						(1<<E_MEA_MODE1_CELL2)
#define U64_AD_CV3_EN						(1<<E_MEA_MODE1_CELL3)
#define U64_AD_CV4_EN 						(1<<E_MEA_MODE1_CELL4)
#define U64_AD_CV5_EN						(1<<E_MEA_MODE1_CELL5)

#define U64_AD_CV_HI_OFFSET_EN				(1<<E_MEA_MODE2_OFFSET)
#define U64_AD_CV6_EN						(1<<E_MEA_MODE2_CELL6)
#define U64_AD_CV7_EN						(1<<E_MEA_MODE2_CELL7)
#define U64_AD_CV8_EN						(1<<E_MEA_MODE2_CELL8)
#define U64_AD_CV9_EN 						(1<<E_MEA_MODE2_CELL8)
#define U64_AD_CV10_EN						(1<<E_MEA_MODE2_CELL10)

#define U64_AD_HV_OFFSET_EN					(1<<E_MEA_MODE4_OFFSET)
#define U64_AD_PACKV_EN						(1<<E_MEA_MODE4_PACKV)
#define U64_AD_PON_EN						(1<<E_MEA_MODE4_PON)
#define U64_AD_TOTALV_EN						(1<<E_MEA_MODE4_TOTALV)

#define U64_AD_TH_OFFSET_EN					(1<<E_MEA_MODE5_OFFSET)
#define U64_AD_AN0_EN						(1<<E_MEA_MODE5_AN0)
#define U64_AD_AN1_EN						(1<<E_MEA_MODE5_AN1)
#define U64_AD_AN2_EN						(1<<E_MEA_MODE5_AN2)
#define U64_AD_AN0_VREG_EN					(1<<E_MEA_MODE5_VREG_AN0)
#define U64_AD_AN1_VREG_EN					(1<<E_MEA_MODE5_VREG_AN1)
#define U64_AD_AN2_VREG_EN					(1<<E_MEA_MODE5_VREG_AN2)

#define U64_AD_SF_OFFSET_EN					(1<<E_MEA_MODE6_OFFSET)
#define U64_AD_ADREF_EN						(1<<E_MEA_MODE6_ADREF)
#define U64_AD_CCREF_EN						(1<<E_MEA_MODE6_CCREF)
#define U64_AD_ADCC_EN						(1<<E_MEA_MODE6_ADCC)
#define U64_AD_MCUREF_EN					(1<<E_MEA_MODE6_MCUREF)
#define U64_AD_STEMP_EN						(1<<E_MEA_MODE6_STEMP)
#define U64_AD_VREG2_EN						(1<<E_MEA_MODE6_VREG2)

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
