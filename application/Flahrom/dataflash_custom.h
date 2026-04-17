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

/*""FILE COMMENT""*******************************************************
* System Name	: RAJ240xxx Smart Battery Standard firmware
* File Name		: dataflash_custom.h
* Version		: 0.01
* Contents		: Data Flash access function (custom) header file
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx Standard firmware
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* Note			: 
************************************************************************
* Copyright,2020 (2012-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2020.12.01 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#ifndef _DATAFLASH_CUSTOM_H
#define _DATAFLASH_CUSTOM_H

#ifdef	_DATAFLASH_CUSTOM
#define		GLOBAL
#else	// _DATAFLASH_CUSTOM
#define		GLOBAL	extern
#endif	// _DATAFLASH_CUSTOM

#include "define.h"

// - Function declaration -

// - Grobal variable -


// - Define definition -
// Flexible data configuration

#define FLEX_INDEX_SIZE		0x10					// Size of Flexible data index
#define FLEX_AREA_NUM		7						// Number of Flexible data area
#define FLEX_AREA_SIZE		0x90					// Size of a Flexible data area

// Reason of Flexible data update
enum {
	FLEXUP_DUMMY,									// Dummy
	FLEXUP_MODE,									// By mode changing
	FLEXUP_RC,										// By RSOC
	FLEXUP_FLASH,									// By Flash update
	FLEXUP_SMB,										// By SMBus command
	FLEXUP_WDT,										// By AFE WDT
};

typedef struct
{
	U32 u32_fcc;
	U32 u32_rc;
	U16 u16_rsoc;
	U16 u16_soh;
	U32 u32_cycle_count;
	U32 u32_total_quse;
} st_capacity_t;

typedef struct
{
	U16 u16_charging_voltage;
	S32 s32_charging_current;
} st_charger_t;

typedef struct {
	st_bms_ad_snapshot_t ad;		// [32byte] ad data
	st_bms_cc_snapshot_t cc;		// [4byte] cc data
} st_measurement_t;

typedef struct
{
	U32 u32_day;
	U8 u8_hour;
	U8 u8_min;
	U8 u8_sec;
	U8 u8_rsv;
} st_runtime_t;

typedef struct
{
	U16 u16_safety_bit;
	U16 u16_permanent_bit;
	U16 u16_capacity_bit;
	U16 u16_battery_status_bit;
	U16 u16_oper_status_bit;
	U16 u16_pack_status_bit;
	U16 u16_balancing_bit;
	U16 u16_slef_discharge_bit;
	U32 u32_internal_bit;
} st_status_bit_t;

typedef struct
{
	U8 u8_pd_reason;
	U8 u8_update_reason;
} st_reason_t;

// - Flexible data -
typedef struct										// Flexible data structure 
{
	st_capacity_t		st_capacity;					// [20byte] capacity data
	st_charger_t		st_charger;					// [6byte] charger data
	st_measurement_t	st_measurement;				// [36byte] measurement data
	st_status_bit_t		st_status;						// [20byte] status data
	st_reason_t		st_reason;					// [2byte] reason data
	st_runtime_t		st_runtime;					// [8byte] runtime data
	U16 u16_manufacture_date;						// [2byte] manufacture data
} st_flexible_data_t;

#define FLEX_SIZE	sizeof(st_flexible_data_t)			// Size of Flexible data (94byte)

GLOBAL st_flexible_data_t	st_flexible_data_ram;						// Flexible data

#define f_dfet			DEFS_BIT0(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// DFET	1=ON, 0=OFF
#define f_cfet			DEFS_BIT1(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// CFET	1=ON, 0=OFF
#define f_pf			DEFS_BIT2(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// PF	1=PF, 0=Other
#define f_ss			DEFS_BIT3(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// SS	1=unseal, 0=Seal
#define f_calemp		DEFS_BIT4(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// Calib value empty
#define f_fixedemp		DEFS_BIT5(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// fixed value empty
#define f_pinst			DEFS_BIT6(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// pin status
#define f_wdt			DEFS_BIT7(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// wdt status

#define f_rl			DEFS_BIT0(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// RL	1=relearning, 0=no rel.
#define f_cp_h		DEFS_BIT1(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// CPH	1=detect, 0=not detect
#define f_cp_l			DEFS_BIT2(&st_flexible_data_ram.st_status.u16_packstatus_bit)		// CPL	1=detect, 0=not detect

#define s16_SMB08_temp		st_flexible_data_ram.st_measurement.ad.as16_cell_temperature_0p1dC[0]
#define s32_SMB0A_curr		st_flexible_data_ram.st_measurement.cc.s32_pack_current_mA
#define u16_SMB0D_rsoc		st_flexible_data_ram.st_capacity.u16_rsoc
#define u32_SMB0F_rc			st_flexible_data_ram.st_capacity.u32_rc
#define u32_SBM10_fcc			st_flexible_data_ram.st_capacity.u32_fcc
#define s32_SMB14_chg_curr		st_flexible_data_ram.st_charger.s32_charging_current
#define u16_SMB15_chg_volt		st_flexible_data_ram.st_charger.u16_charging_voltage
#define u16_SMB16_batt_status	st_flexible_data_ram.st_status.u16_battery_status_bit
#define u32_SMB17_cycle_cnt	st_flexible_data_ram.st_capacity.u32_cycle_count
#define u16_SMB1B_mfg_date	st_flexible_data_ram.u16_manufacture_date
#define u16_SMB38_safety_status	st_flexible_data_ram.st_status.u16_safety_bit
#define u16_SMB41_oper_status	st_flexible_data_ram.st_status.u16_oper_status_bit
#define u16_SMB43_pack_status	st_flexible_data_ram.st_status.u16_pack_status_bit
#define u16_SMB45_sd_status	st_flexible_data_ram.st_status.u16_slef_discharge_bit
#define u16_SMB46_cb_status	st_flexible_data_ram.st_status.u16_balancing_bit
#define u16_SMB47_pack_volt	st_flexible_data_ram.st_measurement.ad.u16_pack_voltage_mV
#define u16_SMB48_soh			st_flexible_data_ram.st_capacity.u16_soh
#define u16_SMB60_volt		st_flexible_data_ram.st_measurement.ad.au16_cell_voltage_mV
#define u16_SMB6A_temp		st_flexible_data_ram.st_measurement.ad.as16_cell_temperature_0p1dC

// - Own data -
typedef struct
{
	st_bms_cal_voltage_points_t	ast_cal_cell[R_BMS_USER_API_CELL_COUNT];	// [20byte] Low voltage side of V
	st_bms_cal_voltage_points_t st_cal_pack;
	st_bms_cal_current_points_t	st_cal_curr;
} st_cal_data_t;

#pragma address st_cal_data_dataflash = 0x0F1800
GLOBAL st_cal_data_t	st_cal_data_dataflash;

#undef 		GLOBAL

#endif	// _DATAFLASH_CUSTOM_H



