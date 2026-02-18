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
* File Name		: fet.c
* Contents		: charge/discharge FET initialization and on/off state control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _FET_C

#include "define.h"
#include "afe.h"
#include "fet_mapping.h"
#include "device_register.h"

// - Declare Internal function -------------------------------------------------

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: AFE_FET_Init
* Description  : Initialize FET control configuration registers.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_FET_Init( void )
{
	/* Program charge/discharge FET operation defaults from mapping tables. */
	AFE_Reg_Write(p8_CFOCON_Reg_Mapping,	u8_CFOCON_Data_Mapping);
	AFE_Reg_Write(p8_DFOCON_Reg_Mapping,u8_DFOCON_Data_Mapping);

}
/*******************************************************************************
* Function Name: AFE_FET_Set
* Description  : Set C-FET and D-FET state with MAINTAIN support.
* Arguments    : u8_cfet/u8_dfet : ON/OFF/MAINTAIN
* Return Value : void
*******************************************************************************/
void AFE_FET_Set( U8 u8_cfet, U8 u8_dfet)
{
	U8 u8_fetst = 0;
	U8 u8_fetcon = 0;
	
	/* Read current state first so MAINTAIN can preserve selected bits. */
	AFE_Reg_Read(p8_FCON_Reg_Mapping,1,&u8_fetst);

	/* Build new D-FET control bits based on requested policy. */
	if(u8_dfet == OFF)
	{
		u8_fetcon |= u8_FET_Data_Mapping[E_FET_D][OFF];
	}else if (u8_dfet == ON)
	{
		u8_fetcon |= u8_FET_Data_Mapping[E_FET_D][ON];
	}else
	{
		// d-fet = Old d-fet state
		u8_fetcon |= (u8_fetst & u8_FET_Data_Mapping[E_FET_D][ON]);
	}

	/* Build new C-FET control bits based on requested policy. */
	if(u8_cfet == OFF)
	{
		u8_fetcon |= u8_FET_Data_Mapping[E_FET_C][OFF];
	}else if (u8_cfet == ON)
	{
		u8_fetcon |= u8_FET_Data_Mapping[E_FET_C][ON];
	}else
	{
		// c-fet = Old c-fet state
		u8_fetcon |= (u8_fetst & u8_FET_Data_Mapping[E_FET_C][ON]);
	}


	/* Commit both FET decisions in one write to avoid transient mismatch. */
	AFE_Reg_Write(p8_FCON_Reg_Mapping, u8_fetcon);

}
/*******************************************************************************
* Function Name: AFE_FET_Get
* Description  : Get FET status
* Arguments    : void
* Return Value : U8 : FET ON/OFF bit flag
*******************************************************************************/
U8 AFE_FET_Get(void)
{
	U8 u8_Ret = 0;
	
	/* Return raw FCON state so caller can decode per-FET status bits. */
	AFE_Reg_Read(p8_FCON_Reg_Mapping,1,&u8_Ret);

	return u8_Ret;
}

