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
* System Name	: RAA241xxx RBMS-P Firmware for Renesas
* File Name		: fet.c
* Contents		: RAA241xxx Charge/Discharge MOSFET control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _HVP_C

#include "define.h"
#include "afe.h"
#include "hvp_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
void AFE_HVP_Init(void)
{
	U8 u8_index = 0;
	U8 u8_pmhv_data = 0;
	U8 u8_pomhv_data = 0;
	U8 u8_phv_data = 0;
	
	for(u8_index = 0; u8_index < E_HVP_NUM; u8_index++)
	{
		u8_pmhv_data |= u8_PMHV_Data_Mapping[u8_index][OUTPUT];
		u8_pomhv_data |= u8_POMHV_Data_Mapping[u8_index][E_HV_OUTPUT_P_CH];
		u8_phv_data |= u8_PHV_Data_Mapping[u8_index][LOW];
	}

	
	AFE_Reg_Write(p8_PMHV_Reg_Mapping,	u8_pmhv_data);
	AFE_Reg_Write(p8_POMHV_Reg_Mapping,	u8_pomhv_data);
	AFE_Reg_Write(p8_PHV_Reg_Mapping,	u8_phv_data);
}

void AFE_HVP_Control(U8 u8_hvp_onoff)
{
	U8 u8_index = 0;
	U8 u8_bitmask = 0;
	U8 u8_phv_data = 0;

	for(u8_index = 0; u8_index < E_HVP_NUM; u8_index++)
	{	
		u8_bitmask = (u8_hvp_onoff >> u8_index) & 0x01;
		
		u8_phv_data |= u8_PHV_Data_Mapping[u8_bitmask][HI];
	}
	
	AFE_Reg_Write(p8_PHV_Reg_Mapping,	u8_phv_data);
}


