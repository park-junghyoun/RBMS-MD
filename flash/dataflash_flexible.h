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

#ifndef _DATAFLASH_FLEXIBLE_H
#define _DATAFLASH_FLEXIBLE_H

#ifdef	_DATAFLASH_FLEXIBLE
#define		GLOBAL
#else	// _DATAFLASH_FLEXIBLE
#define		GLOBAL	extern
#endif	// _DATAFLASH_FLEXIBLE

#include "r_bms_api.h"
#include "r_bms_api_limits.h"
#include "define.h"

// - Function declaration -
void DataFlash_update_check(void);							// DataFlash updating
void FlexibleData_Read(void);								// Read Flexible data
U8 Write_FlexibleData(void);									// Write Flexible data
U8 FlexibleData_Write(void);									// Legacy alias
void Request_FlexibleData_update(void);						// Request Flexible data update


// - Define definition -
// Flexible data configuration
#define U8_FLEX_INDEX_SIZE		0x10						// Size of Flexible data index
#define U8_FLEX_AREA_NUM			0x07						// Number of Flexible data area
#define U8_FLEX_AREA_SIZE			0x90						// Size of a Flexible data area

// Reason of Flexible data update
enum {
	FLEXUP_DUMMY,										// Dummy
	FLEXUP_MODE,										// By mode changing
	FLEXUP_RC,											// By RSOC
	FLEXUP_FLASH,										// By Flash update
	FLEXUP_SMB,											// By SMBus command
	FLEXUP_WDT,											// By AFE WDT
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
	U16 u16_gaging_bit;
	U16 u16_oper_status_bit;
	U16 u16_pack_status_bit;
	U16 u16_balancing_bit;
	U16 u16_slef_discharge_bit;
	U16 u16_unseal_bit;
	U32 u32_internal_bit;
} st_status_bit_t;

typedef struct
{
	U8 u8_pd_reason;
	U8 u8_update_reason;
} st_reason_t;

// - Flexible data -
typedef struct
{
	st_capacity_t		st_capacity;					// [20byte] capacity data
	st_charger_t		st_charger;					// [6byte] charger data
	st_measurement_t	st_measurement;				// [36byte] measurement data
	st_status_bit_t		st_status;						// [20byte] status data
	st_reason_t		st_reason;					// [2byte] reason data
	st_runtime_t		st_runtime;					// [8byte] runtime data
	U16 u16_bms_core_mode;						// [2byte] bms core mode
	U16 u16_manufacture_date;						// [2byte] manufacture data
} st_flexible_data_t;

#define FLEX_SIZE	sizeof(st_flexible_data_t)			// Size of Flexible data (96byte)

GLOBAL st_flexible_data_t	st_flexible_data_ram;						// Flexible data

#define f_dfet			DEF16_BIT0(&st_flexible_data_ram.st_status.u16_pack_status_bit)		// DFET	1=ON, 0=OFF
#define f_cfet			DEF16_BIT1(&st_flexible_data_ram.st_status.u16_pack_status_bit)		// CFET	1=ON, 0=OFF
#define f_saf			DEF16_BIT3(&st_flexible_data_ram.st_status.u16_pack_status_bit)		// SAF	1=safety, 0=Not safety
#define f_pf			DEF16_BIT4(&st_flexible_data_ram.st_status.u16_pack_status_bit)		// PF	1=PF, 0=Not PF
#define f_pinst			DEF16_BIT5(&st_flexible_data_ram.st_status.u16_pack_status_bit)		// pin status

#define f_init			DEF16_BIT0(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// init complete
#define f_ss			DEF16_BIT1(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// SS	1=unseal, 0=Seal
#define f_calib			DEF16_BIT2(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// calibration mode
#define f_cal_emp		DEF16_BIT3(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// calibration data none
#define f_fixed_emp	DEF16_BIT4(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// fixed data none
#define f_fixed_error	DEF16_BIT5(&st_flexible_data_ram.st_status.u16_oper_status_bit)
#define f_cal_error		DEF16_BIT6(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// fixed data none	
#define f_hw_error		DEF16_BIT7(&st_flexible_data_ram.st_status.u16_oper_status_bit)		// Initialization hw error

#define f_rl			DEF16_BIT0(&st_flexible_data_ram.st_status.u16_gaging_bit)			// RL	1=relearning, 0=no rel.
#define f_cp_h		DEF16_BIT1(&st_flexible_data_ram.st_status.u16_gaging_bit)			// CPH	1=detect, 0=not detect
#define f_cp_l			DEF16_BIT2(&st_flexible_data_ram.st_status.u16_gaging_bit)			// CPL	1=detect, 0=not detect

#define s16_SMB08_temp		st_flexible_data_ram.st_measurement.ad.as16_cell_temperature_0p1dC[0]
#define s32_SMB0A_curr		st_flexible_data_ram.st_measurement.cc.s32_pack_current_mA
#define u16_SMB0D_rsoc		st_flexible_data_ram.st_capacity.u16_rsoc
#define u32_SMB0F_rc			st_flexible_data_ram.st_capacity.u32_rc
#define u32_SMB10_fcc			st_flexible_data_ram.st_capacity.u32_fcc
#define s32_SMB14_chg_curr		st_flexible_data_ram.st_charger.s32_charging_current
#define u16_SMB15_chg_volt		st_flexible_data_ram.st_charger.u16_charging_voltage
#define u16_SMB16_batt_status	st_flexible_data_ram.st_status.u16_pack_status_bit
#define u32_SMB17_cycle_cnt	st_flexible_data_ram.st_capacity.u32_cycle_count
#define u16_SMB1B_mfg_date	st_flexible_data_ram.u16_manufacture_date
#define u16_SMB38_safety_status	st_flexible_data_ram.st_status.u16_safety_bit
#define u16_SMB39_pf_status	st_flexible_data_ram.st_status.u16_permanent_bit
#define u16_SMB41_oper_status	st_flexible_data_ram.st_status.u16_oper_status_bit
#define u16_SMB42_pack_status	st_flexible_data_ram.st_status.u16_pack_status_bit
#define u16_SMB45_sd_status	st_flexible_data_ram.st_status.u16_slef_discharge_bit
#define u16_SMB46_cb_status	st_flexible_data_ram.st_status.u16_balancing_bit
#define u16_SMB47_pack_volt	st_flexible_data_ram.st_measurement.ad.u16_pack_voltage_mV
#define u16_SMB48_soh			st_flexible_data_ram.st_capacity.u16_soh
#define u16_SMB50_seal		st_flexible_data_ram.st_status.u16_unseal_bit
#define u16_SMB60_volt		st_flexible_data_ram.st_measurement.ad.au16_cell_voltage_mV
#define u16_SMB6A_temp		st_flexible_data_ram.st_measurement.ad.as16_cell_temperature_0p1dC

GLOBAL U16 u16_SMB09_total_v;

#undef 		GLOBAL

#endif	// _DATAFLASH_FLEXIBLE_H
