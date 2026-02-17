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
#define _MCU_C

#include "define.h"
#include "afe.h"
#include "mcu_mapping.h"

// - Declare Internal function -------------------------------------------------
static U8 mcu_get_clock(void);
static void mcu_tm03_100usWaitTime(void);
// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------


// - Define function -----------------------------------------------------------
void MCU_Pin_Init(void)
{
	U8 u8_index = 0;
	
	for(u8_index =0; u8_index < U8_AFE_SEQUENCE_NUMBER; u8_index++)
	{
		*p8_MCU_Pin_Sequence_Reg_Mapping[u8_index] = u8_MCU_Pin_Sequence_Data_Mapping[u8_index];
	}
}
void MCU_AFE_Pin_Init(void)
{
	U8 u8_index = 0;
	
	for(u8_index =0; u8_index < U8_AFE_SEQUENCE_NUMBER; u8_index++)
	{
		*p8_AFE_Pin_Sequence_Reg_Mapping[u8_index] = u8_AFE_Pin_Sequence_Data_Mapping[u8_index];
	}

}
U8 mcu_get_clock(void)
{
	U8 u8_clock = 0;
	U8 u8_index = 0;
	
	u8_clock = P8_HOCO_CLOCK;
	u8_clock &= U8_HOCO_CLOCK_MASK;

	for(u8_index = 0; u8_index <=E_MCU_CLOCK_ITEM_NUM; u8_index++)
	{
		if(u8_clock == u8_MCU_CLOCK_Data_Mapping[u8_index])
		{
			return u8_index;
		}
	}
	
	return 0xFF;
}

void mcu_tm03_100usWaitTime(void)
{
	U8 u8_tau0_en = OFF;
	U8 u8_clock = 0;
	
	if(PER0 & U8_PER0_TAU0EN_MASK)
	{
		u8_tau0_en = ON;
	}else
	{
		TAU0EN = 1;
	}
	u8_clock =mcu_get_clock();
	TPS0 &= U16_TAU_CKm3_MASK;
	TPS0 |= U16_TAU_CKm3_FCLK_256;			// CKm3 Setting

	TMMK03 = 1;								// Disable INTTM03 interrupt
	TMIF03 = 0;								// Clear INTTM03 interrupt flag

	TMPR003 = 1;								// TM03 interrupt priority
	TMPR103 = 0;								//  Level 1

	//TMR03 = TMR_CKm3_8Bit;					// Select CKm3, 8Bit
	TMR03 = U16_TAU_CKm3_16BIT;				// Select CKm3, 16Bit
	
	TDR03 = u8_MCU_TAU_TDR03_Data_Mapping[u8_clock];

	TS0L_bit.no3 = 1;								// Start TM03
	while( TMIF03 == 0 ) ;						// Wait for interrupt
	TMIF03 = 0;								// Clear INTTM03 interrupt flag

	TT0L_bit.no3 = 1;								// Stop TM03
	
	if(u8_tau0_en == OFF)
	{
		TAU0EN = 0;
	}
}

void MCU_100us_WaitTime(U8 u8_n00us_wait)
{
	U8 u8_index = 0;
	
	for(u8_index = 0; u8_index < u8_n00us_wait; u8_index++)
	{	
		mcu_tm03_100usWaitTime();
	}	
}
