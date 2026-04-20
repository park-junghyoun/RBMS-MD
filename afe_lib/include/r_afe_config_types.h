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
* System Name	: RBMS-M Series Driver for Renesas
* File Name		: afe.h
* Contents		: AFE Driver header file
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

// - Include header file -------------------------------------------------------
#include "define.h"
#include "r_afe_types.h"

#define AFE_API_CELL_COUNT      (10u)
#define AFE_API_HV_ADC_COUNT    (3u)
#define AFE_API_NTC_COUNT       (5u)
#define AFE_API_FUNC_ADC_COUNT    (3u)

typedef struct {
	U8 u8_init_result;
	U8 u8_max_cell_series;
	U8 u8_max_thermistor_series;
	E_AFE_DEVICE_ITEM e_target_device;
	U16 u16_driver_version; 

	U16  u16_reserved;
} st_afe_driver_info_t;

typedef struct {
	E_AFE_WKUP_SETTING_ITEM e_setting;
	E_AFE_WKUP_GAIN_ITEM e_gain;
	U8 u8_thresholds;
} st_afe_wkup_config_t;

typedef struct {
	st_afe_wkup_config_t	st_dsg_wkup_config;
	st_afe_wkup_config_t	st_chg_wkup_config;
	U8 u8_dsgchg_wkup_time;
} st_afe_hw2_config_t;

typedef struct {
	E_AFE_OC_SETTING_ITEM e_setting;
	U8 u8_thresholds;
	U16 u16_time;
} st_afe_oc_config_t;

typedef struct {
	st_afe_oc_config_t st_sc_config;
	st_afe_oc_config_t st_doc_config;
	st_afe_oc_config_t st_coc_config;
} st_afe_hw1_config_t;

typedef struct {
	U16 u16_vin_mask_bit;
	U8 u8_high_volt_mask_bit;
	U8 u8_an_mask_bit;
	U8 u8_vreg_an_mask_bit;
	U8 u8_functional_mask_bit;
} st_afe_adc_mask_t;

typedef struct {
	st_afe_adc_mask_t st_valid;
	U16 au16_vin[AFE_API_CELL_COUNT];
	U16 au16_hv[AFE_API_HV_ADC_COUNT];
	U16 au16_an[AFE_API_NTC_COUNT];
	U16 au16_vreg_an[AFE_API_NTC_COUNT];	
	U16 au16_functional[AFE_API_FUNC_ADC_COUNT];
} st_afe_adc_buffer_t;

typedef struct {
	U32 u32_cc;
} st_afe_cc_buffer_t;

typedef struct {
	st_afe_adc_mask_t st_adc_enable;
	U8 u8_adc_settime;
	U8 u8_adc_time;
} st_afe_adc_config_t;

typedef struct {
	E_AFE_MODE_ITEM e_afe_mode_config;
	E_AFE_WDT_SETTING_ITEM e_afe_wdt_config;
	st_afe_hw1_config_t st_afe_hw1_config;
	st_afe_hw2_config_t st_afe_hw2_config;
	st_afe_adc_config_t st_afe_adc_config;
	E_AFE_CI_RANGE_ITEM e_afe_ci_config;
} st_afe_config_t;

