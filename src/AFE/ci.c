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
* File Name		: ci.c
* Contents		: RAA241xxx Current integration control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _CI_C

#include "define.h"
#include "afe.h"
#include "ci_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------
#pragma interrupt _int_CI_Comple(vect=U16_INTCC_VECTOR_MAPPING)		// Current Integration complete
void afe_CI_Overflow_Chk(void);

// - Internal constant ---------------------------------------------------------
typedef union {
	U32		data;				// ADC raw count (e.g., 18-bit stored in 32-bit)
	U8		buffer[sizeof(U32)];
}U_CI_ADC;

// - Internal variable ---------------------------------------------------------
static U_CI_ADC u_ci_adc_raw;
// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: _int_CurrentIntegComp
* Description  : Current integration interrupt
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_CI_Init( void )
{
	U8 u8_reg_data = 0;
	
	AFE_CI_Stop();
	AFE_Reg_Write(p8_CCIF_Reg_Mapping,~(u8_CCIR_data_Mapping[E_CC_FST_IR]|u8_CCIR_data_Mapping[E_CC_IR]));
	AFE_Reg_Read(p8_CCMK_Reg_Mapping,1,&u8_reg_data);
	AFE_Reg_Write(p8_CCMK_Reg_Mapping,u8_reg_data | u8_CCMK_Data_Mapping);
}

void _int_CI_Comple( void )
{
	U8 u8_reg_data;
	
	f_AFE_Int_Opr = ON;
	AFE_Reg_Read(p8_CCIF_Reg_Mapping,1,&u8_reg_data);
	
	if( u8_reg_data & u8_CCIR_data_Mapping[E_CC_FST_IR])								// First CC interrupt request
	{
		AFE_Reg_Write(p8_CCIF_Reg_Mapping,~u8_CCIR_data_Mapping[E_CC_FST_IR]);
	}
	
	if( u8_reg_data & u8_CCIR_data_Mapping[E_CC_IR])									// CC interrupt request
	{
		AFE_Reg_Write(p8_CCIF_Reg_Mapping,~u8_CCIR_data_Mapping[E_CC_IR]);
		AFE_Reg_Read(p8_CCR_Reg_Mapping,3,u_ci_adc_raw.buffer);							// Get Current Integ count
		AFE_DispatchFrom_ISR(E_AFE_EVENT_CC);
		afe_CI_Overflow_Chk();
	}
	
	f_AFE_Int_Opr = OFF;
}

/*******************************************************************************
* Function Name: AFE_StartCurrentInteg
* Description  : Start current integration (1000ms period)
* Arguments    : void
* Return Value : void
*******************************************************************************/
U8 AFE_CI_Start( void )
{
	if(f_AFE_CC_Run == ON)
	{
		return FALSE;
	}
	AFE_Reg_Write(p_CCEN_Reg_Mapping,u8_CCEN_Data_Mapping[ON]);
	f_AFE_CC_Run = ON;

	return TRUE;
}


/*******************************************************************************
* Function Name: AFE_CI_CStopCC
* Description  : Stop current integration
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_CI_Stop( void )
{
	AFE_Reg_Write(p_CCEN_Reg_Mapping,u8_CCEN_Data_Mapping[OFF]);
}

U32 AFE_CI_Get_AdData( void )
{
	return u_ci_adc_raw.data;
}

void afe_CI_Overflow_Chk( void )
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_CCIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_CCIR_data_Mapping[E_CC_IR])
	{
		f_AFE_CC_Int_OVF = ON;
	}
}

