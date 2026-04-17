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
* File Name		: ram.h
* Version		: 0.01
* Contents		: Global RAM data definition header file
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
* History		: 2020.10.01 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#ifndef _RAM_H
#define _RAM_H

#ifdef	_RAM
#define		GLOBAL
#else	// _RAM
#define		GLOBAL	extern
#endif	// _RAM


GLOBAL u16_byte_t u16_charging_current;
GLOBAL u16_byte_t u16_charging_voltage;

GLOBAL U16 u16_init_status;				 //Initialization Status Bit
#define f_init_hw_error			DEF16_BIT0(&u16_init_status)	// Initialization hw error
#define f_init_fixed_error		DEF16_BIT1(&u16_init_status)	// Initialization config error
#define f_init_cal_error			DEF16_BIT2(&u16_init_status)	// fixed data none	
#define f_init_cal_none			DEF16_BIT3(&u16_init_status)	// calibration data none
#define f_init_fixed_none		DEF16_BIT4(&u16_init_status)	// fixed data none
	
#undef		GLOBAL

#endif	// _RAM_H



