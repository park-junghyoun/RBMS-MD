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

#ifndef _AFE_PWR_MAP_H
#define _AFE_PWR_MAP_H

#include "device_register.h"

volatile U8 __near * const p8_PCON_Reg_Mapping = &AFE_PCON;
U8 const u8_PCON_LowPower_Mapping = BUFCEN1_EN | BUFCEN2_EN | BUFCEN3_EN | BUFCEN4_EN | BUFCEN4_EN | VCPC_EN |REG1C_EN;
U8 const u8_PCON_Normal_Mapping = REG1C_DIS;
volatile U8 __near * const p8_CLCON_Reg_Mapping = &AFE_AMOCON;
U8 const u8_CLCON_LowPower_Mapping = MCLKSEL_ALOCO;
U8 const u8_CLCON_Normal_Mapping = MCLKSEL_AOCO;

#define U8_AFE_SWRST_SEQ	4
volatile U8 __near * const p8_SWRST_Reg_Mapping = &AFE_AFESWRST;
U8 const u8_SWRST_Sequence_Mapping[U8_AFE_SWRST_SEQ] = {0xAA,0x55,0xFF,0x00};


#endif
