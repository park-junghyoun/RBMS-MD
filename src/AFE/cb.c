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
#define _CB_C

#include "define.h"
#include "afe.h"
#include "cb_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------
U8 u8_cb_item[U8_CB_REG_ITEM] ={0,0};

// - Define function -----------------------------------------------------------
void AFE_CB_Stop( void )
{
	U8 u8_cb_reg = 0;
	
	for(u8_cb_reg = 0; u8_cb_reg < U8_CB_REG_ITEM; u8_cb_reg++)
	{
		u8_cb_item[u8_cb_reg] = 0x00;
		AFE_Reg_Write(p_CBEN_Reg_Mapping[u8_cb_reg],u8_cb_item[u8_cb_reg]);
	}

}

void AFE_CB_Start( void )
{
	U8 u8_cb_reg = 0;
	
	for(u8_cb_reg = 0; u8_cb_reg < U8_CB_REG_ITEM; u8_cb_reg++)
	{
		AFE_Reg_Write(p_CBEN_Reg_Mapping[u8_cb_reg],u8_cb_item[u8_cb_reg]);
	}
}

void AFE_CB_Con( U16 u16_balancing )
{
	U16 u16_index = 0;
	U8 u8_cb_reg = 0;
	
	for(u16_index = 0; u16_index < U8_CB_MAXIMUM_CELL_NUM; u16_index++)
	{
		if(E_CB1_ITEM_NUM <= u16_index)
		{
			u8_cb_reg = 1;
		}
		u8_cb_item[u8_cb_reg] |= (u16_balancing >> u16_index);
	}
}



