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

#ifndef _AFE_CI_MAP_H
#define _AFE_CI_MAP_H

#include "device_register.h"


#define U16_INTCC_VECTOR_MAPPING INTP8

/***********************************************************************
ADC MAMPPING DEVICE PROFILE
***********************************************************************/
typedef enum{
	E_CC_FST_IR = 0,
	E_CC_IR,
	E_CC_IR_ITEM_NUM,
} E_AFE_CC_IF_ITEM;

volatile U8 __near * const p8_CCIF_Reg_Mapping = &AFE_AFIF0;
U8 const u8_CCIR_data_Mapping[E_CC_IR_ITEM_NUM] = {INT_CCFSTFLG,INT_CCIR};
volatile U8 __near * const p_CCEN_Reg_Mapping = &AFE_CCCON;
U8 const u8_CCEN_Data_Mapping[2] = {CC_STOP,CC_START};

volatile U8 __near * const p8_CCR_Reg_Mapping = &AFE_CCRL;

volatile U8 __near * const p8_CCMK_Reg_Mapping = &AFE_AFIF0;
U8 const u8_CCMK_Data_Mapping = INT_CCMSK;


#endif
