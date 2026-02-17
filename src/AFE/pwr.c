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
* File Name		: pwr.c
* Contents		: RAA241xxx AFE Operation Mode control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _PWR_C

#include "define.h"
#include "afe.h"
#include  "pwr_mapping.h"
#include  "device_register.h"

/* Module overview: AFE power/clock mode transitions and reset-sequence control. */


// - Declare Internal function -------------------------------------------------

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------
static U8 u8_pwr_state;
// - Define function -----------------------------------------------------------
U8 AFE_PWR_Control( E_AFE_CLOCK_ITEM e_pwr_con )
{
	U8 u8_reg_data = 0;
	U8 u8_reg_check = TRUE;
	
	if(e_pwr_con > E_AFE_CLOCK_LOWPOWER)
	{
		return FALSE;
	}
	MCU_PSW_PUSH();														// PSW -> STACK

																	// AFE Power ctrl
	if(e_pwr_con == E_AFE_CLOCK_NORMAL)												// AFE Power limit
	{
		AFE_Reg_Write(p8_PCON_Reg_Mapping,	u8_PCON_LowPower_Mapping);
		AFE_Reg_Write(p8_CLCON_Reg_Mapping,	u8_CLCON_LowPower_Mapping); 	// ALOCO select

		MCU_100us_WaitTime(2);
		AFE_Reg_Read(p8_CLCON_Reg_Mapping,1,&u8_reg_data);			// Read MCLKSTS of AMOCON
		if(u8_reg_data == u8_CLCON_LowPower_Mapping)
		{
			u8_pwr_state = 1;
		}else
		{
			u8_reg_check = FALSE;
		}
		
	}else
	{
		AFE_Reg_Write(p8_PCON_Reg_Mapping,	u8_PCON_Normal_Mapping);
		AFE_Reg_Write(p8_CLCON_Reg_Mapping,	u8_CLCON_Normal_Mapping); 	// ALOCO select
		
		MCU_100us_WaitTime(2);
		AFE_Reg_Read(p8_CLCON_Reg_Mapping,1,&u8_reg_data);			// Read MCLKSTS of AMOCON
		if(u8_reg_data == u8_CLCON_Normal_Mapping)
		{
			u8_pwr_state = 0;
		}else
		{
			u8_reg_check = FALSE;
		}

	}
	
	MCU_PSW_POP();														// STACK -> PSW

	return u8_reg_check;
}

U8 AFE_PWR_Get_State(void)
{
	return u8_pwr_state;
}

U8 AFE_PWR_PowerDown(void)
{
	return TRUE;
}
U8 AFE_PWR_Reset(void)
{
	U8 u8_afe_seq = 0;
	U8 u8_reg_data = 0xFF;
	U8 u8_reg_check = TRUE;
	
	for(u8_afe_seq = 0; u8_afe_seq < U8_AFE_SWRST_SEQ; u8_afe_seq++)
	{
		AFE_Reg_Write(p8_SWRST_Reg_Mapping,	u8_SWRST_Sequence_Mapping[u8_afe_seq]);	
	}
	
	MCU_100us_WaitTime(2);		// wait 130us

	AFE_Reg_Read(p8_SWRST_Reg_Mapping,1,&u8_reg_data);

	if(u8_reg_data != 0x00)
	{
		u8_reg_check = FALSE;
	}
	
	return u8_reg_check;
}
