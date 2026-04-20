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
* File Name		: inline_asm.h
* Version		: 0.01
* Contents		: Inline assembler header file
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx Standard firmware
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* OS			: None
* Programmer	: Ryoji Kato
* Note			: 
************************************************************************
* Copyright,2020 (2018-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2020.12.16 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#ifndef _INLINE_ASM_H
#define _INLINE_ASM_H

#pragma inline_asm ASM_JUMP_BOOT
#pragma inline_asm ASM_SW_RESET

static void ASM_JUMP_BOOT(void)
{
#if defined(_AFE_TYP_95_94_H) || defined(_AFE_TYP_55_57_H)
	BR !!0x00DC80
#endif
#if defined(_AFE_TYP_100_90_H)
	BR !!0x01CC08
#endif
}

static void ASM_SW_RESET(void)
{
	.DB2 0x0FFFF
}
#endif	// _INLINE_ASM_H

