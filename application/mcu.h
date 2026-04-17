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
* File Name		: mcu.h
* Version		: 0.01
* Contents		: MCU function header file
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
#ifndef _MCU_H
#define _MCU_H



// - Function declaration -
void Init_TM01_1msTimer(void);					// Initialize TM01(1ms)
void Init_IT_125msTimer(void);					// Initialize 12Bit int.timer
												// (125ms)
void WaitTimer(U8 atime);						// Wait timer
void Start_TM03(void);							// Start TM03
void Stop_TM03(void);							// Stop TM03

// - Define definition -

// MCU register setting (by 8MHz)
#define TPS_CKm0_mask		0xFFF0				// TPS: masking CKm0
#define TPS_CKm1_mask		0xFF0F				//      masking CKm1
#define TPS_CKm3_mask		0x0FFF				//      masking CKm3
#define TPS_CKm0_7KHz		0x000A				// TPS: CKm0 = 7.8125KHz
#define TPS_CKm1_1MHz		0x0030				// TPS: CKm1 = 1MHz
#define TPS_CKm3_7KHz		0x1000				//    : CKm3 = 7.8125KHz
#define TMR_CKm0_16Bit		0x0000				// TMR: Select CKm0,16Bit
#define TMR_CKm1_16Bit		0x8000				//      Select CKm1,16Bit
#define TMR_CKm3_8Bit		0xC800				//    : Select CKm3, 8Bit
#define TMR_CKm3_16Bit		0xC000				//    : Select CKm3,16Bit
#define IT_START			0x8000				// ITMC: Start counting
#define IT_STOP				0x7FFF				// ITMC: Stop counting
#define OSMC_LOCO			0x10				// OSMC: Low-speed OCO


// Wait time of WaitTimer()
#define WAIT_1MS			8					// 128us x 8 = 1ms (1.024ms)
#define WAIT_9MS			70					// 128us x 70 = 9ms (8.96ms)
#define WAIT_128US			1					// 128us x 1 = 128us
#define WAIT_256US			2					// 128us x 2 = 256us

// Trimming data for MCU
#define B_TH25_AN0_REG		*(U16*)0x0DC40		// AN0 Pullup res 25degC
#define B_TH25_AN1_REG		*(U16*)0x0DC42		// AN1 Pullup res 25degC
#define B_TH25_AN2_REG		*(U16*)0x0DC44		// AN2 Pullup res 25degC



#endif	// _MCU_H



