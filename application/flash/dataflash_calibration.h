/******************************************************************************
* DISCLAIMER                                                                    
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

#ifndef _DATAFLASH_CALIBRATION_H
#define _DATAFLASH_CALIBRATION_H

#ifdef	_DATAFLASH_CALIBRATION
#define		GLOBAL
#else	// _DATAFLASH_CALIBRATION
#define		GLOBAL	extern
#endif	// _DATAFLASH_CALIBRATION

#include "define.h"

// - Own data -
typedef struct
{
	st_bms_cal_voltage_coeff_t	ast_coeff_cell[R_BMS_USER_API_CELL_COUNT];	// [20byte] Low voltage side of V
	st_bms_cal_pack_coeff_t	st_coeff_pack;
	st_bms_cal_current_coeff_t	st_coeff_curr;
} st_cal_data_t;

#pragma address st_cal_data_dataflash = 0x0F1800
GLOBAL st_cal_data_t	st_cal_data_dataflash;

st_cal_data_t CalbirationData_Read(void);						// Read own data

#undef 		GLOBAL

#endif	// _DATAFLASH_CALIBRATION_H
