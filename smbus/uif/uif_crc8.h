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
* System Name	: RAJ240XXX F/W user interface library
* File Name		: uif_crc8.h
* Version			: 1.00
* Contents		: user interface function header file
************************************************************************
* Copyright(C) 2013 (2012-2013) RENESAS ELECTRONICS CORPORATION
*                AND RENESAS SOLUTIONS CORPORATION
************************************************************************
* History		: 2025.01.01
*""FILE COMMENT END""**************************************************/

#ifndef _UIF_CRC8_H
#define _UIF_CRC8_H

/***********************************************************************
	define
***********************************************************************/
#if defined (_AFE_TYP_100_90_H)
#define AU8_CRC8TBL ((volatile const __far U8 *)(0x1CD18uL))
#elif defined(_AFE_TYP_95_94_H) || defined(_AFE_TYP_55_57_H)
#pragma address au8_CRC8TBL = 0x1CDB0	// CRC Table
#endif

#endif //_UIF_CRC8_H