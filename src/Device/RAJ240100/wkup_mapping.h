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

#ifndef _AFE_WKUP_MAP_H
#define _AFE_WKUP_MAP_H

#include "device_register.h"

#define U16_WKUP_VECTOR_MAPPING INTP11

typedef enum{
	E_WKUP_CWU_IR = 0,
	E_WKUP_DWU_IR,
	E_WKUP_PON_IR,
	E_WKUP_IR_ITEM_NUM
} E_AFE_WKUP_IF_ITEM;

typedef enum{
	E_WKUP_GAIN_2 = 0,
	E_WKUP_GAIN_5,
	E_WKUP_GAIN_10,
	E_WKUP_GAIN_20,
	E_WKUP_GAIN_ITEM_NUM
} E_AFE_WKUP_GAIN_ITEM;

typedef enum{
	E_WKUP_FET_DIS = 0,
	E_WKUP_FET_EN,
	E_WKUP_FET_ITEM_NUM
} E_AFE_WKUP_FET_ITEM;


#define U8_WKUP_TIME_MAX	(U8)0x0F
#define U8_WKUP_TIME_MIN		(U8)0x00

#define U8_WKUP_DSG_MAX		(U8)0x70
#define U8_WKUP_DSG_MIN		(U8)0x00
#define U8_WKUP_CHG_MAX		(U8)0x70
#define U8_WKUP_CHG_MIN		(U8)0x00


volatile U8 __near * const p8_WKUPIF_Reg_Mapping = &AFE_AFIF0;
U8 const u8_WKUPIR_Data_Mapping[E_WKUP_IR_ITEM_NUM] = {INT_CWUIR,INT_DWUIR,INT_CHGIR};

volatile U8 __near * const p8_WKUPIRMK_Reg_Mapping = &AFE_AFMK0;
U8 const u8_WKUPIRMK_Data_Mapping[E_WKUP_IR_ITEM_NUM] = {INT_CWUMSK,INT_DWUMSK,INT_PONMSK};

volatile U8 __near * const p8_WKUPDICON_Reg_Mapping = &AFE_WUICON;
U8 const u8_WKUPDICON_Data_Mapping[E_WKUP_IR_ITEM_NUM] = {CWUIEN,DWUIEN,0x00};

volatile U8 __near * const p8_WKUPTIME_Reg_Mapping = &AFE_WUDTIME;
volatile U8 __near * const p8_WKUPDMPV_Reg_Mapping = &AFE_DWUDCON1;
volatile U8 __near * const p8_WKUPCMPV_Reg_Mapping = &AFE_CWUDCON1;

volatile U8 __near * const p8_WKUPDCON_Reg_Mapping = &AFE_DWUDCON2;
volatile U8 __near * const p8_WKUPCCON_Reg_Mapping = &AFE_CWUDCON2;

U8 const u8_WKUPDCON_EN_Data_Mapping = DWUEN;
U8 const u8_WKUPCCON_EN_Data_Mapping = CWUEN;

U8 const u8_WKUPDCON_Data_Mapping[E_WKUP_GAIN_ITEM_NUM][E_WKUP_FET_ITEM_NUM] =
{
    { (DWUGAIN_2 | DWUACALEN),               (DWUGAIN_2  | DWUACALEN | DWUFETEN) },
    { (DWUGAIN_5 | DWUACALEN),               (DWUGAIN_5  | DWUACALEN | DWUFETEN) },
    { (DWUGAIN_10 | DWUACALEN),              (DWUGAIN_10 | DWUACALEN | DWUFETEN) },
    { (DWUGAIN_20 | DWUACALEN),              (DWUGAIN_20 | DWUACALEN | DWUFETEN) }
};

U8 const u8_WKUPCCON_Data_Mapping[E_WKUP_GAIN_ITEM_NUM][E_WKUP_FET_ITEM_NUM] =
{
    { (CWUGAIN_2  | CWUACALEN),               (CWUGAIN_2  | CWUACALEN | CWUFETEN) },
    { (CWUGAIN_5  | CWUACALEN),               (CWUGAIN_5  | CWUACALEN | CWUFETEN) },
    { (CWUGAIN_10 | CWUACALEN),               (CWUGAIN_10 | CWUACALEN | CWUFETEN) },
    { (CWUGAIN_20 | CWUACALEN),               (CWUGAIN_20 | CWUACALEN | CWUFETEN) }
};


U8 const u8_WKUPDCAL_Data_Mapping = DWUACALEN;
U8 const u8_WKUPCCAL_Data_Mapping = CWUACALEN;

U8 const u8_WKUPCGAIN_Data_Mapping[E_WKUP_GAIN_ITEM_NUM] = {CWUGAIN_2,CWUGAIN_5,CWUGAIN_10,CWUGAIN_20};

volatile U8 __near * const p8_WKUPRESTART_Reg_Mapping = &AFE_WUDRSTRT;
U8 const u8_WKUPDRESTART_Data_Mapping = DWUDRSTRT;
U8 const u8_WKUPCRESTART_Data_Mapping = CWUDRSTRT;

volatile U8 __near * const p8_PONEG_Reg_Mapping = &AFE_WINCHG;
U8 const u8_PONEG_Data_Mapping[2] = {PONDIS,PONBE};
volatile U8 __near * const p8_PONMON_Reg_Mapping = &AFE_PONMON;


#endif
