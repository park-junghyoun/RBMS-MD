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

/* Module overview: high-voltage pin mode initialization and per-pin mode control API. */


// - Declare Internal function -------------------------------------------------

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------
U8 e_hvp_mode_setting[E_AFE_HVP_NUM];
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
	
	for(u8_index = 0; u8_index < E_AFE_HVP_NUM; u8_index++)
	{
		AFE_HVP_Mode_Control((E_AFE_HVIO_ITEM)u8_index,E_AFE_HVP_MODE_OUTPUT_PCH);
	}
}

U8 AFE_HVP_Mode_Control(E_AFE_HVIO_ITEM e_hvio, E_AFE_HVP_MODE_ITEM e_mode)
{
	U8 u8_pmhv_data = 0;
	U8 u8_pomhv_data = 0;
	U8 u8_phv_data = 0;

	if(e_hvio >= E_AFE_HVP_NUM)
	{
		return FALSE;
	}

	if(e_mode > E_AFE_HVP_MODE_NUM)
	{
		return FALSE;
	}
	AFE_Reg_Read(p8_PMHV_Reg_Mapping,1, 	&u8_pmhv_data);
	AFE_Reg_Read(p8_POMHV_Reg_Mapping,1, 	&u8_pomhv_data);
	AFE_Reg_Read(p8_PHV_Reg_Mapping,1, 	&u8_phv_data);
	u8_pmhv_data &= ~u8_PMHV_Data_Mapping[e_hvio][INPUT];
	u8_pomhv_data &= ~(u8_POMHV_Data_Mapping[e_hvio][E_AFE_HVP_MODE_OUTPUT_PCH]|u8_POMHV_Data_Mapping[e_hvio][E_AFE_HVP_MODE_OUTPUT_NCH]);
	u8_pmhv_data &= ~u8_PHV_Data_Mapping[e_hvio][HI];
	switch(e_mode)
	{
		case E_AFE_HVP_MODE_INPUT:
			u8_pmhv_data |= u8_PMHV_Data_Mapping[e_hvio][INPUT];
			u8_pomhv_data |= u8_POMHV_Data_Mapping[e_hvio][E_AFE_HVP_MODE_INPUT];
			e_hvp_mode_setting[e_hvio] = E_AFE_HVP_MODE_INPUT;
			break;
		case E_AFE_HVP_MODE_OUTPUT_NCH:
			u8_pmhv_data |= u8_PMHV_Data_Mapping[e_hvio][OUTPUT];
			u8_pomhv_data |= u8_POMHV_Data_Mapping[e_hvio][E_AFE_HVP_MODE_OUTPUT_NCH];
			e_hvp_mode_setting[e_hvio] = E_AFE_HVP_MODE_OUTPUT_NCH;
			break;
		case E_AFE_HVP_MODE_OUTPUT_PCH:
			u8_pmhv_data |= u8_PMHV_Data_Mapping[e_hvio][OUTPUT];
			u8_pomhv_data |= u8_POMHV_Data_Mapping[e_hvio][E_AFE_HVP_MODE_OUTPUT_PCH];
			e_hvp_mode_setting[e_hvio] = E_AFE_HVP_MODE_OUTPUT_PCH;
			break;
		default:
			break;
	}
	AFE_Reg_Write(p8_PMHV_Reg_Mapping,	u8_pmhv_data);
	AFE_Reg_Write(p8_POMHV_Reg_Mapping,	u8_pomhv_data);
	AFE_Reg_Write(p8_PMHV_Reg_Mapping,	u8_pmhv_data);

	return TRUE;
}

U8 AFE_HVP_Output_Control(E_AFE_HVIO_ITEM e_hvio, U8 u8_con)
{
	U8 u8_phv_data = 0;

	if(e_hvio >= E_AFE_HVP_NUM)
	{
		return FALSE;
	}

	if(u8_con > HI)
	{
		return FALSE;
	}
	
	if(e_hvp_mode_setting[e_hvio] == E_AFE_HVP_MODE_INPUT)
	{
		return FALSE;
	}
	
	AFE_Reg_Read(p8_PHV_Reg_Mapping,1, 	&u8_phv_data);
	
	if( u8_con == HI)
	{
		u8_phv_data |= u8_PHV_Data_Mapping[e_hvio][HI];
	}else
	{
		u8_phv_data &=  ~(u8_PHV_Data_Mapping[e_hvio][HI]);
	}
	
	AFE_Reg_Write(p8_PHV_Reg_Mapping,	u8_phv_data);

	return TRUE;
}

U8 AFE_HVP_Get_State(E_AFE_HVIO_ITEM e_hvio)
{
	U8 u8_phv_data = 0;

	if(e_hvio >= E_AFE_HVP_NUM)
	{
		return 0xFF;
	}

	AFE_Reg_Read(p8_PHV_Reg_Mapping,1, 	&u8_phv_data);

	if(u8_phv_data & u8_PHV_Data_Mapping[e_hvio][HI])
	{
		return HI;
	}else
	{
		return LOW;
	}
}


