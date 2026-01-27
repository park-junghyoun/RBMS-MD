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
* File Name		: fet.h
* Contents		: RAA241xxx Charge/Discharge MOSFET control header
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#ifndef _MCU_MAP_H
#define _MCU_MAP_H

#include "iodefine.h"

#define MCU_SEQUENCE_NUMBER	9		
volatile U8 __near * const p8_MCU_Pin_Sequence_Reg_Mapping[MCU_SEQUENCE_NUMBER] =
{
	&PIOR0,
	&PM0,
	&PM1,
	&PM2,
	&PM6,
	&PM7,
	&CMC,
	&PER2,
	&C2CCNT
};

U8 const u8_MCU_Pin_Sequence_Data_Mapping[MCU_SEQUENCE_NUMBER] =
{
//PIOR0
	0b00000010,
//	    |||||||+- PIOR00 : 0
//	    ||||||+-- PIOR01 : 1
//	    |||||+--- PIOR02 : 0
//	    ||||+---- PIOR03 : 0
//	    |||+----- PIOR04 : 0
//	    ||+------ PIOR05 : 0
//	    |+------- Reserved bit : 0
//	   +-------- Reserved bit : 0
// PM0
	0b00011000,
//	    |||||||+--- P00 : 0 OUTPUT
//	    ||||||+---- P01 : 0 OUTPUT
//	    |||||+----- P02 : 0 OUTPUT
//	    ||||+------ P03 : 1 INPUT(No function)
//	    |||+------- P04 : 1 INPUT(No function)
//	    ||+-------- P05 : 0 OUTPUT
//	    |+--------- P06 : 0 OUTPUT
//	    +---------- P07 : 0 OUTPUT
// PM1
	0b10000000,
//	    |||||||+--- P10 : 0 OUTPUT
//	    ||||||+---- P11 : 0 OUTPUT
//	    |||||+----- P12 : 0 OUTPUT
//	    ||||+------ P13 : 0 OUTPUT
//	    |||+------- P14 : 0 OUTPUT
//	    ||+-------- P15 : 0 OUTPUT
//	    |+--------- P16 : 0 OUTPUT
//	    +---------- P17 : 1 INPUT
// PM2
	0b11111100,
//	    |||||||+--- P20 : 0 OUTPUT
//	    ||||||+---- P21 : 0 OUTPUT
//	    |||||+----- P22 : 1 INPUT(No function)
//	    ||||+------ P23 : 1 INPUT(No function)
//	    |||+------- P24 : 1 INPUT(No function)
//	    ||+-------- P25 : 1 INPUT(No function)
//	    |+--------- P26 : 1 INPUT(No function)
//	    +---------- P27 : 1 INPUT
// PM6
	0b11110011,
//	    |||||||+--- P60 : 1 INPUT
//	    ||||||+---- P61 : 1 INPUT
//	    |||||+----- P62 : 0 OUTPUT(No function)
//	    ||||+------ P63 : 0 OUTPUT(No function)
//	    |||+------- P64 : 1 INPUT(No function)
//	    ||+-------- P65 : 1 INPUT(No function)
// 	    |+--------- P66 : 1 INPUT(No function)
// 	   +---------- P67 : 1 INPUT
// PM7
	0b11111011,
//	    |||||||+--- P70 : 1 INPUT
//	    ||||||+---- P71 : 1 INPUT
//	    |||||+----- P72 : 0 OUTPUT(CS)
//	    ||||+------ P73 : 1 INPUT(No function)
//	    |||+------- P74 : 1 INPUT(No function)
//	    ||+-------- P75 : 1 INPUT(No function)
//	    |+--------- P76 : 1 INPUT(No function)
//	    +---------- P77 : 1 INPUT
//CMC
	0b00000000,
// Clock opration mode (Input mode)
//PER2
	0b10000000,
// SFR used by C2C can be read and written.
// C2CCNT
	0b10000001
//4bit Parallel communicatio
//C2C communication permission
};

#define AFE_SEQUENCE_NUMBER	10		
volatile U8 __near * const p8_AFE_Pin_Sequence_Reg_Mapping[AFE_SEQUENCE_NUMBER] =
{
	&EGP1,
	&EGN1,
	&PR02H,
	&PR12H,
	&PR02L,
	&PR12L,
	&IF2H,
	&IF2L,
	&MK2H,
	&MK2L
};

U8 const u8_AFE_Pin_Sequence_Data_Mapping[AFE_SEQUENCE_NUMBER] =
{
//EGP1
	0b00000000,
//EGN1
	0b00111011,
	// |||||||+--- INTP8		: Falling edge
	// ||||||+---- INTP9		: Falling edge
	// |||||+----- INTP10	: Disable
	// ||||+------ INTP11	: Falling edge
	// |||+------- INTP12	: Falling edge
	// ||+-------- INTP13	: Falling edge
	// |+---------			: Disable
	// +----------			: Disable

// PR02H
	0b11110111,
// PR12H
	0b11100111,
	// |||||||+--- INTP11	: Interrupt priority Level 3 (AFE wakeup interrupt)
	// ||||||+---- TRDPR		: Interrupt priority Level 3 (Disable)
	// |||||+-----			: Interrupt priority Level 3 (Disable)
	// ||||+------ INTP12	: Interrupt priority Level 0 (AFE abnormal	interrupt)
	// |||+------- INTP13	: Interrupt priority Level 1 (AFE timer interrupt)
	// ||+--------			: Interrupt priority Level 3 (Disable)
	// |+---------			: Interrupt priority Level 3 (Disable)
	// +---------- FLPR 		: Interrupt priority Level 3 (Disable)

// PR02L
	0b10011111,
// PR12L
	0b11111111,
	// |||||||+--- CAN0TRM	: Interrupt priority Level 3 (Disable)
	// ||||||+---- CANGRFR	: Interrupt priority Level 3 (Disable)
	// |||||+----- CANGER	: Interrupt priority Level 3 (Disable)
	// ||||+------ INTP6		: Interrupt priority Level 3 (Disable)
	// |||+------- INTP7		: Interrupt priority Level 3 (Disable)
	// ||+-------- INTP8		: Interrupt priority Level 2 (CC interrupt)
	// |+--------- INTP9		: Interrupt priority Level 2 (AD interrupt)
	// +---------- INTP10	: Interrupt priority Level 3 (Disable)

// IF2H
	0b00000000,
	// |||||||+--- INTP11	: Clear Interrupt flag (AFE wakeup interrupt)
	// ||||||+---- TRDPR		: Clear Interrupt flag (Disable)
	// |||||+-----			: Clear Interrupt flag (Disable)
	// ||||+------ INTP12	: Clear Interrupt flag (AFE abnormal  interrupt)
	// |||+------- INTP13	: Clear Interrupt flag (AFE timer interrupt)
	// ||+--------			: Clear Interrupt flag (Disable)
	// |+---------			: Clear Interrupt flag (Disable)
	// +---------- FLIF 	: Clear Interrupt flag (Disable)

//IF2L
	0b00000000,
	// |||||||+--- CAN0TRM	: Clear Interrupt flag (Disable)
	// ||||||+---- CANGRFR	: Clear Interrupt flag (Disable)
	// |||||+----- CANGER	: Clear Interrupt flag (Disable)
	// ||||+------ INTP6		: Clear Interrupt flag (Disable)
	// |||+------- INTP7		: Clear Interrupt flag (Disable)
	// ||+-------- INTP8		: Clear Interrupt flag (CC interrupt)
	// |+--------- INTP9		: Clear Interrupt flag (AD interrupt)
	// +---------- INTP10	: Clear Interrupt flag (Disable)

//MK2H
	0b11100110,
	// |||||||+--- INTP11	: Interrupt enable (AFE wakeup interrupt)
	// ||||||+---- TRDPR		: Interrupt disable (Disable)
	// |||||+-----			: Interrupt disable (Disable)
	// ||||+------ INTP12	: Interrupt enable (AFE abnormal  interrupt)
	// |||+------- INTP13	: Interrupt enable (AFE timer interrupt)
	// ||+--------			: Interrupt disable (Disable)
	// |+---------			: Interrupt disable (Disable)
	// +---------- FLIF 		: Interrupt disable (Disable)

// MK2L
	0b10011111
	// |||||||+--- CAN0TRM	: Interrupt disable (Disable)
	// ||||||+---- CANGRFR	: Interrupt disable (Disable)
	// |||||+----- CANGER	: Interrupt disable (Disable)
	// ||||+------ INTP6		: Interrupt disable (Disable)
	// |||+------- INTP7		: Interrupt disable (Disable)
	// ||+-------- INTP8		: Interrupt enable (CC interrupt)
	// |+--------- INTP9		: Interrupt enable (AD interrupt)
	// +---------- INTP10	: Interrupt disable (Disable)
};
/*
EGP1 = 0b00000000;
EGN1 = 0b00111011;
	// |||||||+--- INTP8		: Falling edge
	// ||||||+---- INTP9		: Falling edge
	// |||||+----- INTP10	: Disable
	// ||||+------ INTP11	: Falling edge
	// |||+------- INTP12	: Falling edge
	// ||+-------- INTP13	: Falling edge
	// |+---------			: Disable
	// +----------			: Disable
PR02H = 0b11110111;
PR12H = 0b11100111;
	// |||||||+--- INTP11	: Interrupt priority Level 3 (AFE wakeup interrupt)
	// ||||||+---- TRDPR		: Interrupt priority Level 3 (Disable)
	// |||||+-----			: Interrupt priority Level 3 (Disable)
	// ||||+------ INTP12	: Interrupt priority Level 0 (AFE abnormal	interrupt)
	// |||+------- INTP13	: Interrupt priority Level 1 (AFE timer interrupt)
	// ||+--------			: Interrupt priority Level 3 (Disable)
	// |+---------			: Interrupt priority Level 3 (Disable)
	// +---------- FLPR 	: Interrupt priority Level 3 (Disable)
PR02L = 0b10011111;
PR12L = 0b11111111;
	// |||||||+--- CAN0TRM	: Interrupt priority Level 3 (Disable)
	// ||||||+---- CANGRFR	: Interrupt priority Level 3 (Disable)
	// |||||+----- CANGER	: Interrupt priority Level 3 (Disable)
	// ||||+------ INTP6		: Interrupt priority Level 3 (Disable)
	// |||+------- INTP7		: Interrupt priority Level 3 (Disable)
	// ||+-------- INTP8		: Interrupt priority Level 2 (CC interrupt)
	// |+--------- INTP9		: Interrupt priority Level 2 (AD interrupt)
	// +---------- INTP10	: Interrupt priority Level 3 (Disable)
IF2H = 0b00000000;
	// |||||||+--- INTP11	: Clear Interrupt flag (AFE wakeup interrupt)
	// ||||||+---- TRDPR		: Clear Interrupt flag (Disable)
	// |||||+-----			: Clear Interrupt flag (Disable)
	// ||||+------ INTP12	: Clear Interrupt flag (AFE abnormal  interrupt)
	// |||+------- INTP13	: Clear Interrupt flag (AFE timer interrupt)
	// ||+--------			: Clear Interrupt flag (Disable)
	// |+---------			: Clear Interrupt flag (Disable)
	// +---------- FLIF 	: Clear Interrupt flag (Disable)
IF2L = 0b00000000;
	// |||||||+--- CAN0TRM	: Clear Interrupt flag (Disable)
	// ||||||+---- CANGRFR	: Clear Interrupt flag (Disable)
	// |||||+----- CANGER	: Clear Interrupt flag (Disable)
	// ||||+------ INTP6		: Clear Interrupt flag (Disable)
	// |||+------- INTP7		: Clear Interrupt flag (Disable)
	// ||+-------- INTP8		: Clear Interrupt flag (CC interrupt)
	// |+--------- INTP9		: Clear Interrupt flag (AD interrupt)
	// +---------- INTP10	: Clear Interrupt flag (Disable)
MK2H = 0b11100110;
	// |||||||+--- INTP11	: Interrupt enable (AFE wakeup interrupt)
	// ||||||+---- TRDPR		: Interrupt disable (Disable)
	// |||||+-----			: Interrupt disable (Disable)
	// ||||+------ INTP12	: Interrupt enable (AFE abnormal  interrupt)
	// |||+------- INTP13	: Interrupt enable (AFE timer interrupt)
	// ||+--------			: Interrupt disable (Disable)
	// |+---------			: Interrupt disable (Disable)
	// +---------- FLIF 		: Interrupt disable (Disable)
MK2L = 0b10011111;
	// |||||||+--- CAN0TRM	: Interrupt disable (Disable)
	// ||||||+---- CANGRFR	: Interrupt disable (Disable)
	// |||||+----- CANGER	: Interrupt disable (Disable)
	// ||||+------ INTP6		: Interrupt disable (Disable)
	// |||+------- INTP7		: Interrupt disable (Disable)
	// ||+-------- INTP8		: Interrupt enable (CC interrupt)
	// |+--------- INTP9		: Interrupt enable (AD interrupt)
	// +---------- INTP10	: Interrupt disable (Disable)

*/

typedef enum{
	E_MCU_CLOCK_32MHZ = 0,
	E_MCU_CLOCK_24MHZ,
	E_MCU_CLOCK_16MHZ,
	E_MCU_CLOCK_12MHZ,
	E_MCU_CLOCK_8MHZ,
	E_MCU_CLOCK_4MHZ,
	E_MCU_CLOCK_1MHZ,
	E_MCU_CLOCK_ITEM_NUM
} E_MCU_CLOCK_ITEM;

U8 const u8_MCU_CLOCK_Data_Mapping[E_MCU_CLOCK_ITEM_NUM] ={ 0x08,0x00,0x09,0x01,0x0A,0x0B,0x0D};
// 32Mhz,24Mhz,16Mhz,12Mhz,8Mhz,4Mhz,1Mhz

U8 const u8_MCU_TAU_TDR03_Data_Mapping[E_MCU_CLOCK_ITEM_NUM] ={12,9,6,4,3,1,0};
// 104us,106.667us,112us,106.667us,128us,128us,256us

#define U8_PER0_TAU0EN_MASK		0x01

#define P8_HOCO_CLOCK			(*(volatile __near U8 *)0xC4)

#define U8_HOCO_CLOCK_MASK          0x0F

#define U16_TAU_CKm3_MASK		0x0FFF				//      masking CKm3
#define U16_TAU_CKm3_FCLK_256	0x0000				//    : CKm3 = fCLK/2^8
#define U16_TAU_CKm3_16BIT		0xC000				//    : Select CKm3,16Bit


#endif		/* _FET_H  */
