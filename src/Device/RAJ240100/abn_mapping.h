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
* File Name		: afe_abn_mapping.h
* Contents		: abn mapping
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _AFE_ABN_MAP_H
#define _AFE_ABN_MAP_H

#include "device_register.h"

#define U16_ANL_VECTOR_MAPPING INTP12

/***********************************************************************
ADC MAMPPING DEVICE PROFILE
***********************************************************************/
typedef enum{
	E_ABN_SCD_IR = 0,
	E_ABN_DOC_IR,
	E_ABN_COC_IR,
	E_ABN_WDT_IR,
	E_ABN_IR_ITEM_NUM
} E_AFE_ABN_IF_ITEM;

#define U8_ABN_SCCMPV_MAX	0x12
#define U8_ABN_SCCMPV_MIN	0x00
#define U8_ABN_SCCTIME_MAX	0x0F
#define U8_ABN_SCCTIME_MIN	0x00

#define U8_ABN_DOCMPV_MAX	0x36
#define U8_ABN_DOCMPV_MIN	0x00
#define U16_ABN_DOCTIME_MAX	0xFFFF
#define U16_ABN_DOCTIME_MIN	0x0000

#define U8_ABN_COCMPV_MAX	0x20
#define U8_ABN_COCMPV_MIN	0x00
#define U8_ABN_COCTIME_MAX	0xFF
#define U8_ABN_COCTIME_MIN	0x00

volatile U8 __near * const p8_ABIF_Reg_Mapping = &AFE_AFIF1;
U8 const u8_ABIR_Data_Mapping[E_ABN_IR_ITEM_NUM] = {INT_SCDIR,INT_DOC1DIR,INT_COCDIR,INT_WDTIR};

volatile U8 __near * const p8_ABIRMK_Reg_Mapping = &AFE_AFMK1;
U8 const u8_ABIRMK_Data_Mapping[E_ABN_IR_ITEM_NUM] = {INT_SCDMSK,INT_DOCDMSK,INT_COCDMSK,INT_AWDTMSK};

volatile U8 __near * const p8_SCCCON_Reg_Mapping = &AFE_SCDCON;
U8 const u8_SCCCON_Data_Mapping[3] = {SC_DIS,SC_EN,SC_EN|SC_FETEN};

volatile U8 __near * const p8_SCCTIME_Reg_Mapping = &AFE_SCDTIME;

volatile U8 __near * const p8_DOCCON_Reg_Mapping = &AFE_DOC1DCON;
U8 const u8_DOCCON_Data_Mapping[3] = {DOC1_DIS,DOC1_EN,DOC1_EN|DOC1_FETEN};

volatile U8 __near * const p8_DOCTIME1_Reg_Mapping = &AFE_DOC1DTIME1;
volatile U8 __near * const p8_DOCTIME2_Reg_Mapping = &AFE_DOC1DTIME2;

volatile U8 __near * const p8_COCCON_Reg_Mapping = &AFE_COCDCON;
U8 const u8_COCCON_Data_Mapping[3] = {COC_DIS,COC_EN,COC_EN|COC_FETEN};
volatile U8 __near * const p8_COCTIME_Reg_Mapping = &AFE_COCDTIME;

volatile U8 __near * const p8_DOCCAL_Reg_Mapping = &AFE_DOC1CAL;
U8 const u8_DOCCAL_Data_Mapping[2] = {DOC1CAL_DIS,DOC1CAL_EN};
U8 const u8_DOCCAL_InitVal_Mapping = 0x18;

volatile U8 __near * const p8_COCCAL_Reg_Mapping = &AFE_COCCAL;
U8 const u8_COCCAL_Data_Mapping[2] = {COCCAL_DIS,COCCAL_EN};
U8 const u8_COCCAL_InitVal_Mapping = 0x18;

volatile U8 __near * const p8_OCDSTS_Reg_Mapping = &AFE_OCDSTS;
U8 const u8_OCDSTS_DOC_Mapping = DOC1FLG;
U8 const u8_OCDSTS_SC_Mapping = SCRFLG;
U8 const u8_OCDSTS_COC_Mapping = COCRFLG;

volatile U8 __near * const p8_OCORSTS_Reg_Mapping = &AFE_OCDRSTRT;
U8 const u8_OCDRSTS_DOC_Mapping = DOC1RSTRT;
U8 const u8_OCDRSTS_SC_Mapping = SCRSTRT;
U8 const u8_OCDRSTS_COC_Mapping = COCRFLG;

volatile U8 __near * const p8_AWDTCON_Reg_Mapping = &AFE_AWDTCON;
U8 const u8_AWDTCON_DATA_Mapping[3] = {WDT_STOP,WDT_8S|WDT_MTRSEL_DIS,WDT_8S|WDT_MTRSEL_EN};

volatile U8 __near * const p8_AWDTRF_Reg_Mapping = &AFE_AWDTRF;
#endif
