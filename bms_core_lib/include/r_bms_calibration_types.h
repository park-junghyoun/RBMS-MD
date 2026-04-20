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
* File Name		: r_bms_calibration_types.h
* Contents		: Public Calibration Types Module
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

#include "define.h"

/*
 * Public BMS calibration enums and DTOs.
 *
 * This header isolates the calibration model interface from the broader public
 * type catalog so calibration-related APIs can include only what they need.
 */
typedef enum {
	E_BMS_CAL_STATE_DEFAULT = 0,
	E_BMS_CAL_STATE_OFFSET_ONLY,
	E_BMS_CAL_STATE_GAIN_OFFSET,
	E_BMS_CAL_STATE_COUNT
} E_BMS_CAL_STATE_ITEM;

typedef enum {
	E_BMS_CAL_POINT_SINGLE = 0u,
	E_BMS_CAL_POINT_DUAL
} E_BMS_CAL_POINT_ITEM;

typedef struct {
	E_BMS_CAL_POINT_ITEM e_point;
	U16 u16_adc_low;
	U16 u16_adc_high;
	U16 u16_ref_low_mV;
	U16 u16_ref_high_mV;
} st_bms_cal_voltage_points_t;

typedef struct {
	S32 u32_gain_q16;
	S32 u32_offset_q16;
	E_BMS_CAL_STATE_ITEM e_state;
} st_bms_cal_voltage_coeff_t;

typedef struct {
	S32 u32_gain_q16;
	S32 u32_offset_q16;
	E_BMS_CAL_STATE_ITEM e_state;
} st_bms_cal_pack_coeff_t;

typedef struct {
	E_BMS_CAL_POINT_ITEM e_point;
	U32 u32_adc_zero;
	U32 u32_adc_load;
	S32 s32_ref_load_mA;
} st_bms_cal_current_points_t;

typedef struct {
	U32 u32_offset_adc;
	U32 u32_k_q20;
	E_BMS_CAL_STATE_ITEM e_state;
} st_bms_cal_current_coeff_t;
