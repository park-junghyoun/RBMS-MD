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
* OS			: None
* Programmer	: Ryoji Kato
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
#pragma interrupt _int_TM03(vect=INTTM03)			// Timer for AD convert
#pragma interrupt _int_IT_125ms(vect=INTIT)			// Timer for main 125msec cycle

#include "flashrom.h"
#include "ram.h"
#include "mcu.h"
#include "afe.h"
#include "smbus.h"
#include "mode.h"
#include "dataflash_custom.h"
#include "safety_custom.h"


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
void Init_TM01_1msTimer(void)
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
* module outline	: 12Bit interval timer initialize function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Init_IT_125msTimer(void)
*-------------------------------------------------------------------
* Function			: Initializing 12Bit interval timer (125ms timer).
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
void Init_IT_125msTimer(void)
{
	RTCEN = 1;									// 12bit interval timer
												//  supplies input clock

	ITMC = 0;									// Stop timer

	ITMK = 1;									// Disable INTIT interrupt
	ITIF = 0;									// Clear INTIT interrupt flag

	ITPR0 = 1;									// INTIT interrupt priority
	ITPR1 = 0;									//  Level 1

	OSMC = OSMC_LOCO;							// Select Low-speed OCO clock
												// (15kHz)

	ITMC = 1874;								// 15kHz * (1874+1) = 125msec

	ITIF = 0;									// Clear INTIT interrupt flag
	ITMK = 0;									// Enable INTIT interrupt
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Wait function by using timer
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void WaitTimer(U8 atime)
*-------------------------------------------------------------------
* Function			: Waiting specified time by using Timer UNIT0 Channel0.
*-------------------------------------------------------------------
* Argument			: U8 atime	: Wait time
*					: The time is "(atime+1)x 128us".
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
* History			: 2020.11.05 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void WaitTimer(U8 atime)
{
	TT0L.3 = 1;								// Stop TM03

	TPS0 &= TPS_CKm3_mask;
	TPS0 |= TPS_CKm3_7KHz;					// CKm3 : Clock=7.8125kHz

	TMMK03 = 1;								// Disable INTTM03 interrupt
	TMIF03 = 0;								// Clear INTTM03 interrupt flag

	TMPR003 = 1;							// TM03 interrupt priority
	TMPR103 = 0;							//  Level 1

	//TMR03 = TMR_CKm3_8Bit;				// Select CKm3, 8Bit
	TMR03 = TMR_CKm3_16Bit;					// Select CKm3, 16Bit
	TDR03 = atime;							// 7.8125kHz(128us) x ( atime + 1 )

	TS0L.3 = 1;								// Start TM03
	while( TMIF03 == 0 ) ;					// Wait for interrupt
	TMIF03 = 0;								// Clear INTTM03 interrupt flag

	TT0L.3 = 1;								// Stop TM03
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: TM03 start function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Start_TM03(void)
*-------------------------------------------------------------------
* Function			: Start Timer UNIT0 Channel3 for AD wait.
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
* History			: 2020.12.11 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Start_TM03(void)
{
	TT0L.3 = 1;									// Stop TM03

	TPS0 &= TPS_CKm3_mask;
	TPS0 |= TPS_CKm3_7KHz;						//	CKm3 :	Clock=7.8125kHz

	TMMK03 = 0;									// Enable INTTM03 interrupt
	TMIF03 = 0;									// Clear INTTM03 interrupt flag

	TMPR003 = 1;								// TM03 interrupt priority
	TMPR103 = 0;								//  Level 1

//	TMR03 = TMR_CKm3_8Bit;						// Select CKm3, 8Bit
//	TDR03 = 100;								// 128us * 100
	TMR03 = TMR_CKm3_16Bit;						// Select CKm3, 16Bit
	TDR03 = 599;								// 128us * 600(n+1) = 76.8ms
	// Note: Maximum time of AD conversion of Tasman is "8ms x 7items = 56ms".
	//       The timeout time is set with about 30% margin.

	TS0L.3 = 1;									// Start TM03
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: TM03 stop function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Stop_TM03(void)
*-------------------------------------------------------------------
* Function			: Stop Timer UNIT0 Channel3 for AD wait.
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
* History			: 2020.12.11 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Stop_TM03(void)
{
	TMIF03 = 0;									// Clear INTTM03 interrupt flag
	TT0L.3 = 1;									// Stop TM03
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

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: [TM03] AD convert timeout interrupt routine
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void _int_TM03(void)
*-------------------------------------------------------------------
* Function			: TM03 interrupt routine for AD wait.
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
* History			: 2020.12.11 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void _int_TM03(void)
{
	Stop_TM03();								// Stop TM03
	if( aad_sts == AFE_AD_WAIT )				// AD status = Wait ?
	{
		aad_sts = AFE_AD_FAIL;					// Set AD status = Failed
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: [IT] 125ms timer function for main cycle
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void _int_IT_125ms(void)
*-------------------------------------------------------------------
* Function			: 125ms timer for main cycle.
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
* History			: 2020.12.17 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void _int_IT_125ms(void)
{
	ITMC &= IT_STOP;							// Stop timer
	f_125ms_int = ON;							// Set 125ms interval flag
}

