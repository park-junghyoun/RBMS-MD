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
* File Name		: trim.h
* Contents		: RAA241xxx AFE Trimming data setup header
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#ifndef _AFE_TRIM_MAP_H
#define _AFE_TRIM_MAP_H

// - Include header file -------------------------------------------------------
#include "device_register.h"
#include "iodefine.h"

// - Global function -----------------------------------------------------------
#define P8_TRIM_ADDR_AOCOT0					AFEREG04							//(F0504)
#define P8_TRIM_ADDR_AOCOT1					AFEREG05							//(F0505)
#define P8_TRIM_ADDR_AOCOT2					AFEREG06							//(F0506)
#define P8_TRIM_ADDR_ALOCOT0				AFEREG07							//(F0507)
#define P8_TRIM_ADDR_ALOCOT1				AFEREG08							//(F0508)
#define P8_TRIM_ADDR_BT0						AFEREG0A							//(F050A)
#define P8_TRIM_ADDR_BT1						AFEREG0B							//(F050B)
#define P8_TRIM_ADDR_RT0						AFEREG0C							//(F050C)
#define P8_TRIM_ADDR_RT1						AFEREG0D							//(F050D)
#define P8_TRIM_ADDR_BUFT0					AFEREG0E							//(F050E)
#define P8_TRIM_ADDR_BUFT1					AFEREG0F							//(F050F)
#define P8_TRIM_ADDR_VREG2T					AFEREG10							//(F0510)
#define P8_TRIM_ADDR_FCPT0					AFEREG11							//(F0511)

// Trimming data for AFE
#define P8_TRIM_DATA_FCPT0					((const __far U8*)0x01C86D)			/* B_AFE_FET0 */
#define P8_TRIM_DATA_VREG2_5V				((const __far U8*)0x01C86C) 			/* AFE-VREG2(5.0V) */
#define P8_TRIM_DATA_VREG2_3V				((const __far U8*)0x01C86B) 			/* AFE-VREG2(3.3V) */
#define P8_TRIM_DATA_BUFT0					((const __far U8*)0x01C86A) 			/* AFE-IV TRIM1 */
#define P8_TRIM_DATA_BUFT1					((const __far U8*)0x01C869) 			/* AFE-IV TRIM0 */
#define P8_TRIM_DATA_RT0						((const __far U8*)0x01C867) 			/* AFE-VREGAD(RT0) */
#define P8_TRIM_DATA_RT1						((const __far U8*)0x01C868) 			/* AFE-VREGCC(RT1) */
#define P8_TRIM_DATA_BT0						((const __far U8*)0x01C865) 				/* AFE-BT0 */
#define P8_TRIM_DATA_BT1						((const __far U8*)0x01C866) 			/* AFE-BT1 */
#define P8_TRIM_DATA_LOCO1					((const __far U8*)0x01C864) 			/* AFE-LOCO1 */
#define P8_TRIM_DATA_LOCO0					((const __far U8*)0x01C863) 			/* AFE-LOCO0 */
#define P8_TRIM_DATA_OCO2					((const __far U8*)0x01C862) 			/* AFE-OCO2 */
#define P8_TRIM_DATA_OCO1					((const __far U8*)0x01C861) 			/* AFE-OCO1 */
#define P8_TRIM_DATA_OCO0					((const __far U8*)0x01C860) 			/* AFE-OCO0 */


#define U8_TRIM_SEQUENCE_NUMBER	13		
volatile U8 __near * const p8_Trim_Sequence_Reg_Mapping[U8_TRIM_SEQUENCE_NUMBER] =
{
	&P8_TRIM_ADDR_BT0,
	&P8_TRIM_ADDR_BT1,
	&P8_TRIM_ADDR_VREG2T,
	&P8_TRIM_ADDR_BUFT0,
	&P8_TRIM_ADDR_BUFT1,
	&P8_TRIM_ADDR_AOCOT0,
	&P8_TRIM_ADDR_AOCOT1,
	&P8_TRIM_ADDR_AOCOT2,
	&P8_TRIM_ADDR_ALOCOT0,
	&P8_TRIM_ADDR_ALOCOT1,
	&P8_TRIM_ADDR_RT0,
	&P8_TRIM_ADDR_RT1,
	&P8_TRIM_ADDR_FCPT0
};
const __far U8* const p8_Trim_Sequence_Data_Mapping[U8_TRIM_SEQUENCE_NUMBER] =
{
	P8_TRIM_DATA_BT0,
	P8_TRIM_DATA_BT1,
	P8_TRIM_DATA_VREG2_3V,
	P8_TRIM_DATA_BUFT0,
	P8_TRIM_DATA_BUFT1,
	P8_TRIM_DATA_OCO0,
	P8_TRIM_DATA_OCO1,
	P8_TRIM_DATA_OCO2,
	P8_TRIM_DATA_LOCO0,
	P8_TRIM_DATA_LOCO1,
	P8_TRIM_DATA_RT0,
	P8_TRIM_DATA_RT1,
	P8_TRIM_DATA_FCPT0
};

// - Global constant -----------------------------------------------------------

// - Global variable -----------------------------------------------------------

#endif		/* _TRIM_H  */
