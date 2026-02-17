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
* File Name		: afetimer.c
* Contents		: RAA241xxx AFE Timer control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _AFETIMER_C

#include "define.h"
#include "afe.h"
#include "afetimer_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------
#pragma interrupt _int_AfeTimer(vect=U16_INTTM_VECTOR_MAPPING)	// AFE Timer underflow detection

static void afe_TimerA_1sec_Init( void );
static void afe_TimerB_5ms_Init ( void);
static void afe_TimerB_Overflow_Chk(void);
static void afe_TimerA_Overflow_Chk(void);

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: Init_AfeTimer
* Description  : Timer interrupt routine (AFE Timer A or B)
* Arguments    : void
* Return Value : void
*******************************************************************************/
void _int_AfeTimer(void)
{
	U8 u8_reg_data = 0;
	
	f_AFE_Int_Opr = ON;
	AFE_Reg_Read(p8_TIMERIF_Reg_Mapping,1,&u8_reg_data);
	
	if( u8_reg_data & u8_TIMERIR_data_Mapping[E_TIMER_A_IR])								// AFE timer A interrupt
	{
		AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_A_IR]);// AFE timer A interrupt request flag
		AFE_DispatchFrom_ISR(E_AFE_EVENT_TIMERA);
		afe_TimerA_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_TIMERIR_data_Mapping[E_TIMER_B_IR])								// AFE timer B interrupt
	{
		AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_B_IR]);// AFE timer B interrupt request flag
		AFE_DispatchFrom_ISR(E_AFE_EVENT_TIMERB);
		afe_TimerB_Overflow_Chk();
	}
	f_AFE_Int_Opr = OFF;
}

/*******************************************************************************
* Function Name: AFE_TimerA_Start
* Description  : Initialize and start 1sec timer by using AFE Timer A.
* Arguments    : void
* Return Value : void
*******************************************************************************/
U8 AFE_TimerA_Control(U8 u8_con)
{
	if(u8_con > ON)
	{
		return FALSE;
	}
	if((f_AFE_TIMERA_Run == ON) &&(u8_con == ON))
	{
		return FALSE;
	}
	if(u8_con >= ON)
	{
		f_AFE_TIMERA_Run = ON;
		AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_A_IR]);
		AFE_Reg_Write(p8_ATMAR_Reg_Mapping,u8_ATMAR_Data_Mapping);												// 0.25[s] * (3+1) = 1[s]
		AFE_Reg_Write(p8_ATMACR_Reg_Mapping,u8_ATMACR_Data_Mapping[ON]);
	}else
	{
		f_AFE_TIMERA_Run = OFF;
		AFE_Reg_Write(p8_ATMACR_Reg_Mapping,u8_ATMACR_Data_Mapping[OFF]);
		AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_A_IR]);

	}
	return TRUE;
}

/*******************************************************************************
* Function Name: AFE_TimerAStartReg
* Description  : Initialize and start AFE Timer A. Register value specified.
* Arguments    : U8 u8_CountReg : ATMAR register value
* Return Value : void
*******************************************************************************/
void afe_TimerA_1sec_Init( void )
{
	U8 u8_reg_data = 0;

	AFE_Reg_Write(p8_ATMACR_Reg_Mapping,u8_ATMACR_Data_Mapping[OFF]);				// AFE timer stop / count source 16kHz / Timer mode
	AFE_Reg_Write(p8_ATMAR_Reg_Mapping,u8_ATMAR_Data_Mapping);												// 0.25[s] * (3+1) = 1[s]

	AFE_Reg_Read(p8_TIMERMK_Reg_Mapping,1,&u8_reg_data);
	AFE_Reg_Write(p8_TIMERMK_Reg_Mapping,u8_reg_data |u8_TIMERMK_Data_Mapping[E_TIMER_A_IR]);
	AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_A_IR]);
}


/*******************************************************************************
* Function Name: AFE_Timer_Init
* Description  : AFE Timer A interrupt
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_Timer_Init( void )
{
	afe_TimerA_1sec_Init();
	afe_TimerB_5ms_Init();
}

/*******************************************************************************
* Function Name: AFE_TimerBStartReg
* Description  : Initialize and start AFE Timer B. Register value specified.
* Arguments    : U8 u8_CountReg : ATMBR register value
*              : U8 u8_PreScalerReg : ATMBPRE1 register value
* Return Value : void
*******************************************************************************/
void afe_TimerB_5ms_Init( void )
{
	U8 u8_reg_data = 0;

	AFE_Reg_Write(p8_ATMBCR_Reg_Mapping,u8_AFETRB_Data_Mapping[OFF]);									// AFE timer stop 
	AFE_Reg_Write(p8_ATMBPRE_Reg_Mapping,	u8_ATMBPRE_Data_Mapping );										// 0.03052 x (163 + 1) x (0 + 1) = 5.00528ms
	AFE_Reg_Write(p8_ATMBR_Reg_Mapping,		u8_ATMBR_Data_Mapping);

	// Clock source: AOCO/ALOCO
	// Underflow time (ms) = 0.03052 x (m + 1) x (n + 1)
	// Clock source: LOCO
	// Underflow time (ms) = 0.06667 x (m/2 + 1) x (n + 1)
	// 0.03052 x (163 + 1) x (0 + 1) = 5.00528ms

	AFE_Reg_Read(p8_TIMERMK_Reg_Mapping,1,&u8_reg_data);
	AFE_Reg_Write(p8_TIMERMK_Reg_Mapping,u8_reg_data |u8_TIMERMK_Data_Mapping[E_TIMER_B_IR]);	
	AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_B_IR]);
}

/*******************************************************************************
* Function Name: AFE_TimerB_LOCO1secStart
* Description  : Initialize and start 1sec timer by using AFE Timer B form LOCO.
* Arguments    : void
* Return Value : void
*******************************************************************************/
U8 AFE_TimerB_Control(U8 u8_con)
{
	if(u8_con > ON)
	{
		return FALSE;
	}
	if((f_AFE_TIMERB_Run == ON) &&(u8_con == ON))
	{
		return FALSE;
	}

	if(u8_con >= ON)
	{
		AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_B_IR]);
		AFE_Reg_Write(p8_ATMBCR_Reg_Mapping,u8_AFETRB_Data_Mapping[ON]);
	}else
	{
		AFE_Reg_Write(p8_ATMBCR_Reg_Mapping,u8_AFETRB_Data_Mapping[OFF]);
		AFE_Reg_Write(p8_TIMERIF_Reg_Mapping,~u8_TIMERIR_data_Mapping[E_TIMER_B_IR]);
	}
	
	return TRUE;
}
void afe_TimerB_Overflow_Chk(void)
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_TIMERIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_TIMERIR_data_Mapping[E_TIMER_B_IR])
	{
		f_AFE_TIMERB_Int_OVF = ON;
	}
}
void afe_TimerA_Overflow_Chk(void)
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_TIMERIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_TIMERIR_data_Mapping[E_TIMER_A_IR])
	{
		f_AFE_TIMERA_Int_OVF = ON;
	}
}
