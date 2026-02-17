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
* File Name		: trim.c
* Contents		: RAA241xxx AFE Trimming data setup
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _TRIM_C

#include "define.h"
#include "afe.h"
#include "device_trimming.h"
#include "device_register.h"

/* Module overview: trimming-sequence write/verify flow for analog calibration data. */

// - Declare Internal function -------------------------------------------------

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: AFE_Trimming_Setting
* Description  : Initialize AFE
* Arguments    : void
* Return Value : void
*******************************************************************************/
U8 data;
U8 read_data;
U8 AFE_Trimming_Setting(void)
{
	U8 u8_seq_check = TRUE;
	U8 u8_reg_check = TRUE;
	U8 u8_index = 0;

	u8_seq_check = AFE_WindowTo(E_AFE_WINDOW2);

	if(u8_seq_check == FALSE)
	{
		return u8_seq_check;
	}
	
	for(u8_index =0; u8_index < U8_TRIM_SEQUENCE_NUMBER; u8_index++)
	{
		data = *p8_Trim_Sequence_Data_Mapping[u8_index];
		AFE_Reg_Write(p8_Trim_Sequence_Reg_Mapping[u8_index], data);
		AFE_Reg_Read(p8_Trim_Sequence_Reg_Mapping[u8_index],1, &read_data);
		if (data != read_data)
		{
			u8_reg_check = FALSE;
			break;
		}
	}
	u8_seq_check = AFE_WindowTo(E_AFE_WINDOW0);
	if(u8_seq_check == FALSE)
	{
		return u8_seq_check;
	}
	
	return u8_reg_check;
}

