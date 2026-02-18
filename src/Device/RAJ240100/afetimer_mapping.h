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
* File Name		: afetimer_mapping.h
* Contents		: afetimer mapping
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _AFE_TIMER_MAP_H
#define _AFE_TIMER_MAP_H

#include "device_register.h"

/***********************************************************************
ADC MAMPPING DEVICE PROFILE
***********************************************************************/
typedef enum {
	E_TIMER_A_IR = 0,
	E_TIMER_B_IR,
	E_TIMER_IR_ITEM_NUM
}E_AFE_TIMER_IF_ITEM;

#define U16_INTTM_VECTOR_MAPPING   INTP13

volatile U8 __near * const p8_TIMERMK_Reg_Mapping = &AFE_AFMK3;
U8 const u8_TIMERMK_Data_Mapping[E_TIMER_IR_ITEM_NUM] = {INT_AFETRAMSK,INT_AFETRBMSK};



volatile U8 __near * const p8_TIMERIF_Reg_Mapping = &AFE_AFIF3;
U8 const u8_TIMERIR_data_Mapping[E_TIMER_IR_ITEM_NUM] = {INT_AFETRAIR,INT_AFETRBIR};
volatile U8 __near * const p8_ATMACR_Reg_Mapping = &AFE_ATMACR;
U8 const u8_ATMACR_Data_Mapping[2] = {AFETRASTOP | AFETRACLKSEL_16K,AFETRASTART_ST | AFETRACLKSEL_16K};
volatile U8 __near * const  p8_ATMAR_Reg_Mapping = &AFE_ATMAR;
U8 const u8_ATMAR_Data_Mapping = 3;
// Clock source: AOCO/ALOCO
// Underflow time (s) = 0.25 x (n + 1)
// 0.25 x (0+1) = 250ms
volatile U8 __near * const p8_ATMBCR_Reg_Mapping = &AFE_ATMBCR;
U8 const u8_AFETRB_Data_Mapping[2] = {AFETRBSTOP,AFETRBSTART_ST};
volatile U8 __near * const p8_ATMBPRE_Reg_Mapping = &AFE_ATMBPRE1;
U8 const u8_ATMBPRE_Data_Mapping = 163;
volatile U8 __near * const p8_ATMBR_Reg_Mapping = &AFE_ATMBR;
U8 const u8_ATMBR_Data_Mapping = 0;
// Clock source: AOCO/ALOCO
// Underflow time (ms) = 0.03052 x (m + 1) x (n + 1)
// 0.03052 x (163 + 1) x (0 + 1) = 5.00528ms
/***********************************************************************
ADC SETTING DEVICE PROFILE
***********************************************************************/
#endif
