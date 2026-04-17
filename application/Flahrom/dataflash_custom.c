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
* File Name		: dataflash_custom.c
* Version		: 0.01
* Contents		: Data flash controlling functions (custom)
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
* History		: 2020.12.01 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#define _DATAFLASH_CUSTOM

// - Include header file -
#include "define.h"								// Common definition
#include "flashrom.h"
#include "dataflash.h"
#include <string.h>
#include "dataflash_custom.h"
#include "ram.h"

const __near st_flexible_data_t st_flexible_default = {			// DataFlash default value
	0,										// 0x10:FullChargeCapacity() [mAh]
	0,										// 0x17:CycleCount()
	0,										// Mode number, Failure reason
	0,										// RemainingCapacity correct work [mA250ms]
	0,										// reserved 1
	0,										// CycleCount work count
	0,										// Degradation counter
	0,										// BatteryFlags
	0,										// reserved 2
	0,										// Total storage time
	0,										// Storage time of V >= 4.2V
	0,										// Storage time of T1 >= 45? c
	0,										// Storage time of V >= 4.2V & T1 >= 45? c
	0,										// Total charged capacity
	0,										// Experience of MaxV
	65535,									// Experience of MinV
	0,										// Experience of MaxChargeC
	0,										// Experience of MaxDischargeC
	0,										// Experience of MaxTimp1.
	127,									// Experience of MinTimp1.
	0x0000,									// PackStatus
	0x0000,									// BatteryStatus 
	0,										// 0x08:Temperature1()
	0,										// 0x09:Voltage()
	0,										// 0x0A:Current()
	65535,									// Minimum cell voltage
	0,										// Maximum cell voltage
	0,										// Reason of Flexible data updating
	0,										// Reserved
	0,										// 0x44:FETTemp()
	0,										// MF date
	0,										// Serial number
	0x0000,									// SafetyStatus
	0x0000,									// PFStatus
	0,										// MCU Runaway Counter
};

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Flexible data default data setting function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void __Set_default_FlexibleData(void)
*-------------------------------------------------------------------
* Function			: Set default data of Flexible data.
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
* History			: 2020.12.01 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void FlexibleData_SetDefault(void)
{
	memcpy((U8*)&st_flexible_data_ram, (U8*)&st_flexible_default, sizeof(st_flexible_data_t));
}
