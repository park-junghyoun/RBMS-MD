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
* File Name		: r_bms_measurement.h
* Contents		: Public Measurement Types Module
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

#include "define.h"
#include "r_bms_api_limits.h"

typedef struct {
	U8 u8_ad_forced_zero;
	U8 u8_cc_forced_zero;
} st_bms_measure_forced_zero_state_t;

typedef enum {
	E_BMS_THERMISTOR_AN0 = 0u,
	E_BMS_THERMISTOR_AN1,
	E_BMS_THERMISTOR_AN2,
	E_BMS_THERMISTOR_AN3,
	E_BMS_THERMISTOR_AN4,
	E_BMS_THERMISTOR_COUNT
} E_BMS_THERMISTOR_ITEM;

typedef enum {
	E_BMS_CELL_1 = 0u,
	E_BMS_CELL_2,
	E_BMS_CELL_3,
	E_BMS_CELL_4,
	E_BMS_CELL_5,
	E_BMS_CELL_6,
	E_BMS_CELL_7,
	E_BMS_CELL_8,
	E_BMS_CELL_9,
	E_BMS_CELL_10,
	E_BMS_CELL_COUNT
} E_BMS_CELL_ITEM;

/*
 * User-configurable AD channel mask DTO.
 *
 * Only mutable mask domains are exposed here to prevent accidental modification of
 * mandatory sensing channels (VIN/AN/VREG_AN and HV PACK1).
 * u8_hv_mask_bit accepts only PACK2/BATT bits.
 */
typedef struct {
	U8 u8_hv_mask_bit;
	U8 u8_functional_mask_bit;
} st_bms_ad_user_mask_t;

/* Bit macros for each device for [u8_hv_mask_bit] */
#define U8_DEV100_AD_HVMASK_PON_BIT			(1U<<1)
#define U8_DEV100_AD_HVMASK_TOTAL_BIT		(1U<<2)

#define U8_DEV95_AD_HVMASK_CHMON_BIT		(1U<<1)
#define U8_DEV95_AD_HVMASK_TOTAL_BIT		(1U<<2)

#define U8_DEV55_AD_HVMASK_AN3_BIT			(1U<<2)
#define U8_DEV55_AD_HVMASK_TOTAL_BIT		(1U<<0)

/* Bit macros for each device for [u8_functional_mask_bit] */
#define U8_DEVCOM_AD_FUNCMASK_SIMPLET_BIT	(1U<<0)
#define U8_DEVCOM_AD_FUNCMASK_REG2_BIT		(1U<<1)
#define U8_DEV95_AD_FUNCMASK_ANM_BIT		(1U<<2)

/*
 * Host-facing AD-completion converted measurement snapshot.
 * Voltage and temperature values are grouped by AD completion timing so callers can
 * consume one coherent sample after E_ALARM_AD_COMP.
 */
typedef struct {
	U16 u16_pack_voltage_mV;
	U16 au16_cell_voltage_mV[R_BMS_USER_API_CELL_COUNT];
	S16 as16_cell_temperature_0p1dC[R_BMS_USER_API_NTC_COUNT];
} st_bms_ad_snapshot_t;

/*
 * Host-facing CC-completion converted measurement snapshot.
 * Pack current is published separately because it becomes valid on E_ALARM_CC_COMP.
 */
typedef struct {
	S32 s32_pack_current_mA;
} st_bms_cc_snapshot_t;

/*
 * Host-facing AD-completion raw measurement snapshot.
 * Raw ADC buffers are exposed by completion timing so advanced users can match acquisition data to
 * the corresponding completion event without mixing AD and CC timelines.
 */
typedef struct {
	U16 au16_vin[R_BMS_USER_API_CELL_COUNT];
	U16 au16_hv[R_BMS_USER_API_HV_ADC_COUNT];
	U16 au16_an[R_BMS_USER_API_NTC_COUNT];
	U16 au16_vreg_an[R_BMS_USER_API_NTC_COUNT];
	U16 au16_functional[R_BMS_USER_API_FUNC_ADC_COUNT];
} st_bms_ad_raw_snapshot_t;

/*
 * Host-facing CC-completion raw snapshot.
 * The coulomb-counter raw code is retrieved independently from the AD raw snapshot.
 */
typedef struct {
	U32 u32_cc_ad_raw;
} st_bms_cc_raw_snapshot_t;
