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
* File Name		: afe.c
* Contents		: RAA241xxx AFE
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _AFE_C

#include "define.h"
#include "afe.h"
#include "device_register.h"
#include "device_mapping.h"
#include "afewindow_mapping.h"

// - Declare Internal function -------------------------------------------------


// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------
U8 u8_AFE_Window;

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: PSW_PUSH
* Description  : PSW_PUSH
* Arguments    : void
* Return Value : void
*******************************************************************************/
#pragma inline_asm PSW_PUSH
void PSW_PUSH(void)
{
	push psw
}
/*******************************************************************************
* Function Name: AFE_Init
* Description  : AFE_Init
* Arguments    : void
* Return Value : void
*******************************************************************************/
#pragma inline_asm PSW_POP
void PSW_POP(void)
{
	pop psw
}

/*******************************************************************************
* Function Name: PSW_POP
* Description  : PSW_POP
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_Init( st_afe_config_t st_afe_config )
{
	// - Trimming data setting -
	AFE_Trimming_Setting();
	
	// Clock setting
	AFE_PWR_Control(st_afe_config.u8_afe_clock); 														// Clock = OCO

	// AFE timer setting
	AFE_Timer_Init(); 													// Initialize AFE timer
	
	// AD settubg
	AFE_AD_Init(st_afe_config.st_afe_ad_config);

	// CC setting
	AFE_CI_Init();
	
	// Conditioning setting
	AFE_CB_Stop();

	// FET setting
	AFE_FET_Init();
	
	// HVP setting
	AFE_HVP_Init();

	// OC setting
	AFE_OC_Init(st_afe_config.st_afe_hw1_config);
	
	// Wakeup setting
	AFE_WKUP_Init(st_afe_config.st_afe_hw2_config);

}
/*******************************************************************************
* Function Name: AFE_Reg_Write
* Description  : AFE_Reg_Write
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_Reg_Write( volatile U8 __far *p_reg, U8 u8_data )
{
	if(f_AFE_Int_Opr == OFF)
	{
		PSW_PUSH();								// PSW -> STACK
		DI();									// Disable interrupt
	}

	CS = HI;										// CS = H
	*p_reg = u8_data;								// Write AFE register
	CS = LOW;									// CS = L
	
	if(f_AFE_Int_Opr == OFF)
	{
		PSW_POP(); 								// STACK -> PSW
	}
}


/*******************************************************************************
* Function Name: AFE_Reg_Read
* Description  : AFE_Reg_Read
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_Reg_Read( volatile U8 __far *p_reg, U8 u8_size, U8 *p_data )
{
	U8		u8_index;
	if( u8_size <=14 )								// Read size is valid ?
	
	{
		if(f_AFE_Int_Opr == OFF)
		{
			PSW_PUSH();							// PSW -> STACK
			DI();								// Disable interrupt
		}
		CS = HI;									// CS = H
		
		for( u8_index=0; u8_index<u8_size; u8_index++ )// Serial reading loop
		{
			p_data[u8_index] = p_reg[u8_index]; 		// Read AFE register
		}
		CS = LOW;								// CS = L
		
		if(f_AFE_Int_Opr == OFF)
		{
			PSW_POP(); 							// STACK -> PSW
		}
	}
}

void AFE_WindowTo( U8 u8_window )
{
	u8_AFE_Window = u8_window;
	AFE_Reg_Write(p8_WINDOW_Reg_Mapping,u8_WINDOW_Data_Mapping[u8_window]);
}
U8 AFE_Get_Window( void )
{
	return u8_AFE_Window;
}
void AFE_Interrupt_Clear( U32 u32_int_flg )
{
	u32_AFE_Int_Flg = u32_AFE_Int_Flg & ~u32_int_flg;
}

