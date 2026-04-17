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
* System Name	: RAJ240xxx Smart Battery Standard firmware
* File Name		: mcu.c
* Version		: 0.01
* Contents		: MCU functions
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx Standard firmware
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* Note			: 
************************************************************************
* Copyright,2020 (2012-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2020.10.21 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/

#define _MCU

// - Include header file -
#include "define.h"									// Common definition
#pragma interrupt _int_TM01_SMBus1ms(vect=INTTM01)	// Timer for SMBus

#include "iodefine.h"
#include "mcu.h"
#include "smbus.h"
#include "r_bms_api.h"

void MCU_Init(void)
{
	mcu_LED_Init();
	mcu_TM01_1ms_Init();
	SMBus_initialize();										// SMBus initializing
}
/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: TM01 initialize function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Init_TM01_1msTimer(void)
*-------------------------------------------------------------------
* Function			: Initializing TM01 (1ms timer).
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.10.21 Ver 0.01
* 					: Replace overall
* 

*""FUNC COMMENT END""**********************************************/
void mcu_TM01_1ms_Init(void)
{
	TAU0EN = 1;									// Timer array unit0
												// Supplies input clock

	TT0L.1 = 1;									// Stop TM01

	TPS0 &= TPS_CKm1_mask;
	TPS0 |= TPS_CKm1_1MHz;						// CKm1 : Clock=1MHz

	TMMK01 = 1;									// Disable INTTM01 interrupt
	TMIF01 = 0;									// Clear INTTM01 interrupt flag

	TMPR001 = 1;									// TM01 interrupt priority
	TMPR101 = 0;									//  Level 1

	TMR01 = TMR_CKm1_16Bit;						// Select CKm1, 16Bit
	TDR01 = 999;									// 1MHz * 1000(n+1) = 1msec

	TMIF01 = 0;									// Clear INTTM01 interrupt flag
	TMMK01 = 0;									// Enable INTTM01 interrupt
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: [TM01] 1ms timer function for SMBus
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void _int_TM01_SMBus1ms(void)
*-------------------------------------------------------------------
* Function			: 1ms timer for counting SMBus timeout.
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void _int_TM01_SMBus1ms(void)
{
	if( f_mstto_req == ON )						// Checking Master timeout ?
	{
		u8_smbus_m_timeout_cnt++;							// Count the time
	}
	if( f_slvto_req == ON )						// Checking Slave timeout ?
	{
		u8_smbus_s_timeout_cnt++;							// Count the time
	}
	if( f_sclto_req == ON )						// Checking SCL timeout ?
	{
		u8_smbus_scl_timeout_cnt++;							// Count the time
	}
}
/*******************************************************************************
* Function Name: app_init_leds
* Description  : Executes app_init_leds routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void mcu_LED_Init(void)
{
	PM0 = PM0 & 0b11111100;
	PM1 =  PM1 & 0b10000110;
	/* initialize the LEDs to low. */
	LED1=1;
	LED2=1;
	LED3=1;
	LED4=1;
	LED5=1;
	LED6=1;
	LED7=1;
}
void Stop_Mode(void)
{
	DI();
	if(BMS_Event_HasPending())
	{
		EI();
		return;
	}
	WUP0 = 1;
	NOP();										// wait 3clock
	NOP();
	NOP();
	EI();									// Interrupt enable
	STOP();								// Stop mode
	NOP();							// wait 5clock
	NOP();
	NOP();
	NOP();
	NOP();
	WUP0 = 0;
}

