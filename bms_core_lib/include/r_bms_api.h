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
* File Name		: r_bms_api.h
* Contents		: RBMS Core API
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

#include "afe_config.h"
#include "afe_types.h"
#include "r_bms_types.h"
#include "r_bms_calibration.h"
#include "r_bms_protection.h"
#include "r_bms_config.h"
#include "r_bms_callbacks.h"
#include "r_bms_version.h"

/*
 * Public BMS core API surface.
 *
 * Application code should interact with the library through these functions rather than
 * reading or mutating internal RAM directly. The API groups cover initialization,
 * mode/profile control, hardware setting handoff, balancing requests, events, and
 * measurement readout.
 *
 * User-facing consistency rules used by this header:
 * - "Set" APIs consume input-only arguments.
 * - "Get" APIs write to caller-provided output buffers.
 * - Canonical naming for new APIs is: BMS_<Domain>_<Action><Target>
 *   (example: BMS_Calib_ComputeCellCoeff).
 */

E_BMS_RESULT_ITEM BMS_Core_Initialize(const st_sys_config_t* pst_sys_config);
E_BMS_RESULT_ITEM BMS_Core_RegisterCallbacks(const BmsCoreCallbacks* p_callbacks);
E_BMS_RESULT_ITEM BMS_Core_GetDriverInfo(st_bms_driver_info_t* pst_info);
E_BMS_RESULT_ITEM BMS_Core_PowerDown(void);

E_BMS_RESULT_ITEM BMS_Mode_SetProfile(E_BMS_MODE_ITEM e_state, const st_operating_profile_t* pst_profile);
E_BMS_RESULT_ITEM BMS_Mode_GetProfile(E_BMS_MODE_ITEM e_state, st_operating_profile_t* pst_profile);
E_BMS_RESULT_ITEM BMS_Mode_Set(E_BMS_MODE_ITEM e_state);
E_BMS_RESULT_ITEM BMS_Mode_Get(E_BMS_MODE_ITEM* p8_mode);

E_BMS_RESULT_ITEM BMS_Config_SetHw1(st_afe_hw1_config_t st_config);
E_BMS_RESULT_ITEM BMS_Config_GetHw1(st_afe_hw1_config_t *pst_config);
E_BMS_RESULT_ITEM BMS_Config_SetHw2(st_afe_hw2_config_t st_config);
E_BMS_RESULT_ITEM BMS_Config_GetHw2(st_afe_hw2_config_t *pst_config);
E_BMS_RESULT_ITEM BMS_Config_SetAfeTimerB(U8 u8_enable);

E_BMS_RESULT_ITEM BMS_Balancing_SetBalConfig(const st_bal_config_t* pst_config);
E_BMS_RESULT_ITEM BMS_Balancing_GetBalConfig(st_bal_config_t* pst_config);
E_BMS_RESULT_ITEM BMS_Balancing_SetSelfDischargeConfig(const st_bal_self_dsg_config_t* pst_config);
E_BMS_RESULT_ITEM BMS_Balancing_GetSelfDischargeConfig(st_bal_self_dsg_config_t* pst_config);
E_BMS_RESULT_ITEM BMS_Balancing_SetUserControlReq(const st_bms_bal_user_ctrl_req_t *pst_req);


E_BMS_RESULT_ITEM BMS_Protection_SetConfig(const st_protection_config_t* pst_config);
E_BMS_RESULT_ITEM BMS_Protection_GetConfig(st_protection_config_t* pst_config);


void BMS_Event_Process(void);
U8 BMS_Event_HasPending(void);

U32 BMS_InternalStatus_Get(void);
void BMS_InternalStatus_Clear(U32 u32_clear_mask);

E_BMS_RESULT_ITEM BMS_Measure_GetAdSnapshot(st_bms_ad_snapshot_t *pst_snapshot);
E_BMS_RESULT_ITEM BMS_Measure_GetCcSnapshot(st_bms_cc_snapshot_t *pst_snapshot);
E_BMS_RESULT_ITEM BMS_Measure_GetAdRawSnapshot(st_bms_ad_raw_snapshot_t *pst_snapshot);
E_BMS_RESULT_ITEM BMS_Measure_GetCcRawSnapshot(st_bms_cc_raw_snapshot_t *pst_snapshot);
E_BMS_RESULT_ITEM BMS_Measure_GetForcedZeroState(st_bms_measure_forced_zero_state_t *pst_state);
E_BMS_RESULT_ITEM BMS_Measure_SetAdUserMask(const st_bms_ad_user_mask_t* pst_mask);
E_BMS_RESULT_ITEM BMS_Measure_GetAdUserMask(st_bms_ad_user_mask_t* pst_mask);

E_BMS_RESULT_ITEM BMS_Calib_GetThermistorTable(E_BMS_THERMISTOR_ITEM e_thermistor, U32 *pa32_table);
E_BMS_RESULT_ITEM BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_ITEM e_thermistor, const U32 *pa32_table);
E_BMS_RESULT_ITEM BMS_Calib_GetThermistorResistance(E_BMS_THERMISTOR_ITEM e_thermistor, U32 *p32_resistance_ohm);

E_BMS_RESULT_ITEM BMS_Calib_ComputeCellCoeff(E_BMS_CELL_ITEM e_cell_idx, const st_bms_cal_voltage_points_t *pst_points, st_bms_cal_voltage_coeff_t *pst_out_coeff);
E_BMS_RESULT_ITEM BMS_Calib_ApplyCellCoeff(E_BMS_CELL_ITEM e_cell_idx, const st_bms_cal_voltage_coeff_t *pst_coeff);
E_BMS_RESULT_ITEM BMS_Calib_GetCellCoeff(E_BMS_CELL_ITEM e_cell_idx, st_bms_cal_voltage_coeff_t *pst_coeff);
E_BMS_RESULT_ITEM BMS_Calib_ComputePackCoeff(const st_bms_cal_voltage_points_t *pst_points, st_bms_cal_pack_coeff_t *pst_out_coeff);
E_BMS_RESULT_ITEM BMS_Calib_ApplyPackCoeff(const st_bms_cal_pack_coeff_t *pst_coeff);
E_BMS_RESULT_ITEM BMS_Calib_GetPackCoeff(st_bms_cal_pack_coeff_t *pst_coeff);

E_BMS_RESULT_ITEM BMS_Calib_ComputeCurrentCoeff(const st_bms_cal_current_points_t *pst_points, st_bms_cal_current_coeff_t *pst_out_coeff);
E_BMS_RESULT_ITEM BMS_Calib_ApplyCurrentCoeff(const st_bms_cal_current_coeff_t *pst_coeff);
E_BMS_RESULT_ITEM BMS_Calib_GetCurrentCoeff(st_bms_cal_current_coeff_t *pst_coeff);

E_BMS_RESULT_ITEM BMS_Fet_GetPolicyState(st_bms_fet_state_t *pst_state);
E_BMS_RESULT_ITEM BMS_Fet_GetState(st_bms_fet_state_t *pst_state);
E_BMS_RESULT_ITEM BMS_Fet_SetUserOverrideReq(const st_bms_fet_override_req_t *pst_req);

E_BMS_RESULT_ITEM BMS_Protection_GetActiveMask(U16 *p16_mask);
E_BMS_RESULT_ITEM BMS_Protection_GetLatchedMask(U16 *p16_mask);
E_BMS_RESULT_ITEM BMS_Protection_ForceReleaseLatched(U16 u16_release_mask);
