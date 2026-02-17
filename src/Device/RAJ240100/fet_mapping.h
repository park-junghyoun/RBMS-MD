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

#ifndef _AFE_FET_MAP_H
#define _AFE_FET_MAP_H

#include "device_register.h"

typedef enum{
	E_FET_C = 0,
	E_FET_D,
	E_FET_ALL_NUM
} E_AFE_FET;

/***********************************************************************
ADC MAMPPING DEVICE PROFILE
***********************************************************************/
volatile U8 __near * const p8_CFOCON_Reg_Mapping = &AFE_CFOCON;
U8 const u8_CFOCON_Data_Mapping = CFET_VBAT| CFCLP_DIS| CFOFFBST_DIS| CFOFFBSTC_DIS;
volatile U8 __near * const p8_DFOCON_Reg_Mapping = &AFE_DFOCON;
U8 const u8_DFOCON_Data_Mapping = DFET_VPACK| DFCLP_DIS| DFOFFBST_DIS| DFOFFBSTC_DIS;

volatile U8 __near * const p8_FCON_Reg_Mapping = &AFE_FCON;
U8 const u8_FET_Data_Mapping[E_FET_ALL_NUM][2] =
{
	{FET_OFF,FET_C},
	{FET_OFF,FET_D},	

};
/***********************************************************************
ADC SETTING DEVICE PROFILE
***********************************************************************/
#endif
