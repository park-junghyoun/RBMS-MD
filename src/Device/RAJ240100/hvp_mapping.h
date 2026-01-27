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

#ifndef _AFE_HVP_MAP_H
#define _AFE_HVP_MAP_H

#include "device_register.h"

/***********************************************************************
ADC MAMPPING DEVICE PROFILE
***********************************************************************/
typedef enum{
	E_HV_OUTPUT_DISABLE = 0,
	E_HV_OUTPUT_N_CH,
	E_HV_OUTPUT_P_CH,
	E_HV_OUTPUT_NUM
} E_AFE_HVP_OUTPUT_SETTING;

typedef enum{
	E_HVP = 0,
	E_HVP1,
	E_HVP2,
	E_HVP_NUM
} E_AFE_HVP_PIN;

volatile U8 __near * const p8_PMHV_Reg_Mapping = &AFE_PMHV;
U8 const u8_PMHV_Data_Mapping[E_HVP_NUM][2] = 
{
	{HVP0_INPUT,HVP0_OUTPUT},
	{HVP1_INPUT,HVP1_OUTPUT},	
	{HVP2_INPUT,HVP2_OUTPUT}

};

volatile U8 __near * const p8_POMHV_Reg_Mapping = &AFE_POMHV;
U8 const u8_POMHV_Data_Mapping[E_HVP_NUM][E_HV_OUTPUT_NUM] =
{
	{HVP0OUT_DIS,HVP0OUT_NCH,HVP0OUT_PCH},
	{HVP1OUT_DIS,HVP1OUT_NCH,HVP1OUT_PCH},
	{HVP2OUT_DIS,HVP2OUT_NCH,HVP2OUT_PCH}

};
volatile U8 __near * const p8_PHV_Reg_Mapping = &AFE_PHV;
U8 const u8_PHV_Data_Mapping[E_HVP_NUM][2] =
{
	{HVP0_LOW,HVP0_HIGH},
	{HVP1_LOW,HVP1_HIGH},
	{HVP2_LOW,HVP2_HIGH}
};

/***********************************************************************
ADC SETTING DEVICE PROFILE
***********************************************************************/
#endif
