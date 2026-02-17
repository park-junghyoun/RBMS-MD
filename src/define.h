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
* File Name		: define.h
* Contents		: general define
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _DEFINE_H
#define _DEFINE_H


// - includes -
#include "iodefine.h"

/* Project-wide primitive types, boolean constants, and common compile-time macros. */

#define MAX2(a, b)  (( (a) > (b) ) ? (a) : (b))

#define DI      __DI
#define EI      __EI
#define HALT    __halt
#define NOP     __nop
#define STOP    __stop

// - define -
#define ON		1
#define OFF		0
#define MAINTAIN	0xFF
#define HI		1
#define LOW		0
#define OUTPUT	1
#define INPUT		0

#define PNULL (void*)0
#define NULL	0
#define TRUE	1
#define FALSE	0

typedef unsigned char	U8;
typedef signed char		S8;
typedef unsigned short	U16;
typedef signed short	S16;
typedef unsigned long	U32;
typedef signed long		S32;
typedef signed long long	S64;
typedef unsigned long long U64;


#define U8_MAX			       ( (U8)0xFFU )
#define U16_MAX			    ( (U16)0xFFFFU )
#define U32_MAX			( (U32)0xFFFFFFFFU )

#define S8_MAX			       ( (S8)0x7F )
#define S8_MIN			       ( (S8)0x80 )
#define S16_MAX			    ( (S16)0x7FFF )
#define S16_MIN			    ( (S16)0x8000 )
#define S32_MAX			( (S32)0x7FFFFFFF )
#define S32_MIN			( (S32)0x80000000 )

typedef struct
{
	unsigned char bit0			:1;	
	unsigned char bit1			:1;
	unsigned char bit2			:1;
	unsigned char bit3			:1;
	unsigned char bit4			:1;
	unsigned char bit5			:1;
	unsigned char bit6			:1;
	unsigned char bit7			:1;
}_ST8_BIT;

#define DEF8_BIT7(pdata)	((volatile _ST8_BIT*)(pdata))->bit7
#define DEF8_BIT6(pdata)	((volatile _ST8_BIT*)(pdata))->bit6
#define DEF8_BIT5(pdata)	((volatile _ST8_BIT*)(pdata))->bit5
#define DEF8_BIT4(pdata)	((volatile _ST8_BIT*)(pdata))->bit4
#define DEF8_BIT3(pdata)	((volatile _ST8_BIT*)(pdata))->bit3
#define DEF8_BIT2(pdata)	((volatile _ST8_BIT*)(pdata))->bit2
#define DEF8_BIT1(pdata)	((volatile _ST8_BIT*)(pdata))->bit1
#define DEF8_BIT0(pdata)	((volatile _ST8_BIT*)(pdata))->bit0
typedef struct
{
	unsigned char bit0			:1;	
	unsigned char bit1			:1;
	unsigned char bit2			:1;
	unsigned char bit3			:1;	
	unsigned char bit4			:1;
	unsigned char bit5			:1;
	unsigned char bit6			:1;
	unsigned char bit7			:1;
	unsigned char bit8			:1;
	unsigned char bit9			:1;
	unsigned char bit10			:1;
	unsigned char bit11			:1;
	unsigned char bit12			:1;
	unsigned char bit13			:1;
	unsigned char bit14			:1;
	unsigned char bit15			:1;
}_ST16_BIT;

#define DEF16_BIT15(pdata)	((_ST16_BIT*)(pdata))->bit15
#define DEF16_BIT14(pdata)	((_ST16_BIT*)(pdata))->bit14
#define DEF16_BIT13(pdata)	((_ST16_BIT*)(pdata))->bit13
#define DEF16_BIT12(pdata)	((_ST16_BIT*)(pdata))->bit12
#define DEF16_BIT11(pdata)	((_ST16_BIT*)(pdata))->bit11
#define DEF16_BIT10(pdata)	((_ST16_BIT*)(pdata))->bit10
#define DEF16_BIT9(pdata)	((_ST16_BIT*)(pdata))->bit9
#define DEF16_BIT8(pdata)	((_ST16_BIT*)(pdata))->bit8
#define DEF16_BIT7(pdata)	((_ST16_BIT*)(pdata))->bit7
#define DEF16_BIT6(pdata)	((_ST16_BIT*)(pdata))->bit6
#define DEF16_BIT5(pdata)	((_ST16_BIT*)(pdata))->bit5
#define DEF16_BIT4(pdata)	((_ST16_BIT*)(pdata))->bit4
#define DEF16_BIT3(pdata)	((_ST16_BIT*)(pdata))->bit3
#define DEF16_BIT2(pdata)	((_ST16_BIT*)(pdata))->bit2
#define DEF16_BIT1(pdata)	((_ST16_BIT*)(pdata))->bit1
#define DEF16_BIT0(pdata)	((_ST16_BIT*)(pdata))->bit0

typedef struct
{
	unsigned char bit0			:1;	
	unsigned char bit1			:1;
	unsigned char bit2			:1;
	unsigned char bit3			:1;	
	unsigned char bit4			:1;
	unsigned char bit5			:1;
	unsigned char bit6			:1;
	unsigned char bit7			:1;
	unsigned char bit8			:1;
	unsigned char bit9			:1;
	unsigned char bit10			:1;
	unsigned char bit11			:1;
	unsigned char bit12			:1;
	unsigned char bit13			:1;
	unsigned char bit14			:1;
	unsigned char bit15			:1;
	unsigned char bit16			:1;	
	unsigned char bit17			:1;
	unsigned char bit18			:1;
	unsigned char bit19			:1;	
	unsigned char bit20			:1;
	unsigned char bit21			:1;
	unsigned char bit22			:1;
	unsigned char bit23			:1;
	unsigned char bit24			:1;
	unsigned char bit25			:1;
	unsigned char bit26			:1;
	unsigned char bit27			:1;
	unsigned char bit28			:1;
	unsigned char bit29			:1;
	unsigned char bit30			:1;
	unsigned char bit31			:1;

}_ST32_BIT;

#define DEF32_BIT31(pdata)	((_ST32_BIT*)(pdata))->bit31
#define DEF32_BIT30(pdata)	((_ST32_BIT*)(pdata))->bit30
#define DEF32_BIT29(pdata)	((_ST32_BIT*)(pdata))->bit29
#define DEF32_BIT28(pdata)	((_ST32_BIT*)(pdata))->bit28
#define DEF32_BIT27(pdata)	((_ST32_BIT*)(pdata))->bit27
#define DEF32_BIT26(pdata)	((_ST32_BIT*)(pdata))->bit26
#define DEF32_BIT25(pdata)	((_ST32_BIT*)(pdata))->bit25
#define DEF32_BIT24(pdata)	((_ST32_BIT*)(pdata))->bit24
#define DEF32_BIT23(pdata)	((_ST32_BIT*)(pdata))->bit23
#define DEF32_BIT22(pdata)	((_ST32_BIT*)(pdata))->bit22
#define DEF32_BIT21(pdata)	((_ST32_BIT*)(pdata))->bit21
#define DEF32_BIT20(pdata)	((_ST32_BIT*)(pdata))->bit20
#define DEF32_BIT19(pdata)	((_ST32_BIT*)(pdata))->bit19
#define DEF32_BIT18(pdata)	((_ST32_BIT*)(pdata))->bit18
#define DEF32_BIT17(pdata)	((_ST32_BIT*)(pdata))->bit17
#define DEF32_BIT16(pdata)	((_ST32_BIT*)(pdata))->bit16
#define DEF32_BIT15(pdata)	((_ST32_BIT*)(pdata))->bit15
#define DEF32_BIT14(pdata)	((_ST32_BIT*)(pdata))->bit14
#define DEF32_BIT13(pdata)	((_ST32_BIT*)(pdata))->bit13
#define DEF32_BIT12(pdata)	((_ST32_BIT*)(pdata))->bit12
#define DEF32_BIT11(pdata)	((_ST32_BIT*)(pdata))->bit11
#define DEF32_BIT10(pdata)	((_ST32_BIT*)(pdata))->bit10
#define DEF32_BIT9(pdata)	((_ST32_BIT*)(pdata))->bit9
#define DEF32_BIT8(pdata)	((_ST32_BIT*)(pdata))->bit8
#define DEF32_BIT7(pdata)	((_ST32_BIT*)(pdata))->bit7
#define DEF32_BIT6(pdata)	((_ST32_BIT*)(pdata))->bit6
#define DEF32_BIT5(pdata)	((_ST32_BIT*)(pdata))->bit5
#define DEF32_BIT4(pdata)	((_ST32_BIT*)(pdata))->bit4
#define DEF32_BIT3(pdata)	((_ST32_BIT*)(pdata))->bit3
#define DEF32_BIT2(pdata)	((_ST32_BIT*)(pdata))->bit2
#define DEF32_BIT1(pdata)	((_ST32_BIT*)(pdata))->bit1
#define DEF32_BIT0(pdata)	((_ST32_BIT*)(pdata))->bit0

#endif
