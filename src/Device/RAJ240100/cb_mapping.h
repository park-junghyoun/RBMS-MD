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
* File Name		: cb_mapping.h
* Contents		: cb mapping
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _AFE_CB_MAP_H
#define _AFE_CB_MAP_H

#include "device_register.h"

/***********************************************************************
CELL BALANCING MAPPING DEVICE PROFILE
***********************************************************************/
typedef enum{
	E_CB1_C1 = 0,
	E_CB1_C2,
	E_CB1_C3,
	E_CB1_C4,
	E_CB1_C5,
	E_CB1_C6,
	E_CB1_C7,
	E_CB1_C8,
	E_CB1_ITEM_NUM
} E_AFE_CB1_ITEM;

typedef enum{
	E_CB2_C9 = E_CB1_ITEM_NUM,
	E_CB2_C10,
	E_CB2_ITEM_NUM
} E_AFE_CB2_ITEM;

#define U8_CB_MAXIMUM_CELL_NUM	10
#define U8_CB_REG_ITEM			2

/* CBEN register banks: COND0 controls C1..C8, COND1 controls C9..C10. */
volatile U8 __near * const p_CBEN_Reg_Mapping[U8_CB_REG_ITEM] = {&AFE_COND0, &AFE_COND1};

#endif
