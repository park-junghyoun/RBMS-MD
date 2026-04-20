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
* System Name	: RAJ240xxx RBMS Core for renesas
* File Name		: r_bms_config_types.c
* Contents		: Config Module
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

/*
 * Public configuration models for the BMS core.
 *
 * These structures describe system topology, mode operating profiles, balancing limits,
 * and per-protection settings that are provided at initialization time or adjusted by
 * the application after startup.
 */

#include "r_afe_types.h"
#include "r_bms_types.h"
#include "r_bms_protection_types.h"
/* -------- System config -------- */
typedef struct {
	U8  u8_cell_series_count;	/* Number of series cells used by measurement/diagnostics (<= MAX_CELLS) */
	U8  u8_ntc_count;			/* Number of NTC channels used by measurement (<= MAX_NTC) */
	U8  u8_ntc_prot_bitmask;	/* Bit mask of NTC channels enabled for protection diagnostics */
	U8  u8_shunt_R_0p1mOhm;	/* [0.1 mOhm] Board shunt resistance */
	U16 u16_mask_current_mA;	/* [mA] Current deadband treated as idle (charge/discharge mask current) */
} st_sys_config_t;


/* -------- Balancing config -------- */
typedef struct {
	U16 u16_cell_bal_start_volt_mV;	/* [mV] Minimum cell voltage delta required to start/continue balancing */
	U16 u16_cell_bal_stop_volt_mV;		/* [mV] Cell voltage delta below which balancing stops */
	U16 u16_cell_bal_enable_lovolt_mV;	/* [mV] Minimum cell absolute voltage that allows balancing */
} st_bal_config_t;

typedef struct {
	S16 s16_cell_self_start_temp_0p1dC;	/* [0.1 degC] Max-cell-temperature threshold to start self-discharge */
	S16 s16_cell_self_stop_temp_0p1dC;	/* [0.1 degC] Max-cell-temperature threshold to stop self-discharge */
	U16 u16_cell_self_start_volt_mV;		/* [mV] Per-cell voltage threshold to start self-discharge */
	U16 u16_cell_self_stop_volt_mV;		/* [mV] Per-cell voltage threshold to stop self-discharge */
} st_bal_self_dsg_config_t;

/* -------- Protection config -------- */
typedef struct {
	/* Auto-clear temperature protections: CUT/DUT/COT/DOT */
	S16 s16_cot_set_threshold_0p1dC;	/* [0.1 degC] Charge over-temperature threshold */
	S16 s16_dot_set_threshold_0p1dC;	/* [0.1 degC] Discharge over-temperature threshold */
	S16 s16_cut_set_threshold_0p1dC;	/* [0.1 degC] Charge under-temperature threshold */
	S16 s16_dut_set_threshold_0p1dC;	/* [0.1 degC] Discharge under-temperature threshold */
	U16 u16_common_time_125ms;			/* [125 ms tick] Debounce/qualification time for CUT/DUT/COT/DOT */
} st_prot_temp_window_t;

typedef struct {
	/* Auto-clear voltage protections: OV/UV */
	U16 u16_ov_set_threshold_mV;	/* [mV] Cell over-voltage threshold */
	U16 u16_uv_set_threshold_mV;	/* [mV] Cell under-voltage threshold */
	U16 u16_common_time_125ms;		/* [125 ms tick] Debounce/qualification time for OV/UV */
} st_prot_voltage_window_t;

typedef struct {
	S32 s32_set_threshold_mA;	/* [mA] Current threshold for one COC/DOC level */
	U16 u16_set_time_125ms;		/* [125 ms tick] Qualification time for this COC/DOC level */
} st_prot_current_window_t;

typedef struct {
	U16 u16_set_threshold_mA;	/* [mA] Precharge over-current threshold */
	U16 u16_set_time_125ms;		/* [125 ms tick] Qualification time for POC */
	U16 u16_set_threshold_mV;	/* [mV] Minimum-cell voltage threshold used to arm POC check */
} st_prot_precurrent_window_t;


typedef struct {
	/* Latched temperature protection: CTOT */
	S16 s16_ctot_set_threshold_0p1dC;	/* [0.1 degC] Critical over-temperature latch threshold */
	U16 u16_set_time_125ms;				/* [125 ms tick] Qualification time before CTOT latches */
} st_prot_temp_latched_t;

typedef struct {
	/* Latched voltage protection: CTOV */
	U16 u16_ctov_set_threshold_mV;	/* [mV] Critical over-voltage latch threshold */
	U16 u16_set_time_125ms;			/* [125 ms tick] Qualification time before CTOV latches */
} st_prot_voltage_latched_t;

typedef struct {
	/*
	 * Grouped protection configuration
	 * --------------------------------
	 * The flat field list was hard for users to initialize correctly.
	 * This grouped form keeps the public config manageable:
	 *   - temperature auto-clear + latched
	 *   - voltage auto-clear + latched
	 *   - current windows
	 *   - diagnostic settings (runtime latch behavior is defined by
	 *     active/latched protection enums and their contiguous bit domains)
	 *
	 * Initialization flow:
	 *   1) BMS_Core_Initialize copies an internal ROM default profile into runtime config.
	 *   2) The application may later read/modify/replace this runtime copy through
	 *      BMS_Protection_GetConfig() / BMS_Protection_SetConfig().
	 */

	struct {
		st_prot_temp_window_t  st_window;	/* Auto-clear temperature settings (CUT/DUT/COT/DOT) */
		st_prot_temp_latched_t st_latched;	/* Latched temperature settings (CTOT) */
	} st_temperature;

	struct {
		st_prot_voltage_window_t  st_window;	/* Auto-clear voltage settings (OV/UV) */
		st_prot_voltage_latched_t st_latched;	/* Latched voltage settings (CTOV) */
	} st_voltage;

	struct {
		st_prot_current_window_t    st_coc[3];	/* Charge over-current levels: COC1..COC3 */
		st_prot_current_window_t    st_doc[3];	/* Discharge over-current levels: DOC1..DOC3 */
		st_prot_precurrent_window_t st_poc;		/* Precharge over-current settings (POC) */
	} st_current;

	struct {
		U16 u16_cimb_set_threshold_mV;	/* [mV] Cell imbalance threshold (max cell - min cell) */
		U16 u16_cimb_set_time_125ms;	/* [125 ms tick] Qualification time for CIMB latch */
	} st_diagnostic;
} st_protection_config_t;

typedef struct {
	U16 u16_active_fet_policy_bitmask;		/* FET cut-off policy for active protections (bit index: E_APROT_*) */
	U16 u16_latched_fet_policy_bitmask;	/* FET cut-off policy for latched protections (bit index: E_LPROT_*) */
	U16 u16_active_fuseout_policy_bitmask;	/* Fuse-out policy for active protections (bit index: E_APROT_*) */
	U16 u16_latched_fuseout_policy_bitmask;	/* Fuse-out policy for latched protections (bit index: E_LPROT_*) */
} st_protection_policy_t;

typedef struct {
	/* Fixed scheduler base is 125ms */
	U8 u8_base_fet_policy_bitmask;	/* Default FET state policy (bit index: E_FET_*), can be overridden by protection */

	/* Measurement cadence controls */
	U8 u8_ad_period_125ms_n;	/* AD cadence: 125 ms x n (0 disables AD) */
	U8 u8_cc_period_250ms_n;	/* CC cadence: 250 ms x n (0 disables CC) */
	
	/* wakeup / external pin control (bit index: E_WAKEUP_*) */
	U8 u8_wakeup_policy_bitmask;	/* Wakeup source enable bitmask (bit index: E_WAKEUP_*) */

	/* mode-specific protection/FET policy */
	st_protection_policy_t st_prot_policy;	/* Protection response policy for this operating mode */
} st_operating_profile_t;
