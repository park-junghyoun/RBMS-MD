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
* File Name		: r_bms_app.c
* Contents		: RBMS Modifiable Application
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _APP
#include "r_bms_app.h"


U8 APP_BMS_Core_Init(void)
{
	E_BMS_RESULT_ITEM e_ret;

	e_ret = BMS_Core_Initialize(&st_fixed_data.st_bms_init_config);
	return APP_ReportBMSCoreResult(e_ret);

}
U8 APP_ReportBMSCoreResult(E_BMS_RESULT_ITEM e_ret)
{
	if( e_ret != E_BMS_OK)
	{
		switch(e_ret)
		{
			case E_BMS_ERR_HW:
				f_init_hw_error = ON;
				break;
			case E_BMS_ERR_INVALID_PARAM:
				f_init_config_error = ON;
				break;
			case E_BMS_ERR_NOT_INIT:
			case E_BMS_ERR_NOT_READY:
			default:
				break;
		}
		return FALSE;
	}
	return TRUE;
}
/*******************************************************************************
* Function Name: app_refresh_ad_measurement_snapshot
* Description  : Executes app_refresh_ad_measurement_snapshot routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void APP_Get_AD_measurement_snapshot(void)
{
	st_bms_ad_snapshot_t st_ad_snapshot = {0};

	if(BMS_Measure_GetAdSnapshot(&st_ad_snapshot) != E_BMS_OK)
	{
		return;
	}

	st_flexible_data_ram.st_measurement.ad = st_ad_snapshot;
}

/*******************************************************************************
* Function Name: app_refresh_cc_measurement_snapshot
* Description  : Executes app_refresh_cc_measurement_snapshot routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void APP_Get_CC_measurement_snapshot(void)
{
	st_bms_cc_snapshot_t st_cc_snapshot = {0};

	if(BMS_Measure_GetCcSnapshot(&st_flexible_data_ram.st_measurement.cc) != E_BMS_OK)
	{
		return;
	}
	
	st_flexible_data_ram.st_measurement.cc = st_cc_snapshot;
}

/*******************************************************************************
* Function Name: app_poll_cc_raw_signal
* Description  : Executes app_poll_cc_raw_signal routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void APP_Get_CC_RAW_measurement_snapshot(void)
{
	st_bms_cc_raw_snapshot_t st_cc_raw_snapshot = {0};

	if(BMS_Measure_GetCcRawSnapshot(&st_cc_raw_snapshot) != E_BMS_OK)
	{
		return;
	}
}

/*******************************************************************************
* Function Name: app_poll_ad_raw_signal
* Description  : Executes app_poll_ad_raw_signal routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void APP_Get_AD_RAW_measurement_snapshotl(void)
{
	st_bms_ad_raw_snapshot_t st_ad_raw_snapshot = {0};

	if(BMS_Measure_GetAdRawSnapshot(&st_ad_raw_snapshot) != E_BMS_OK)
	{
		return;
	}
}

/*******************************************************************************
* Function Name: app_refresh_fet_status
* Description  : Executes app_refresh_fet_status routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void APP_Get_FET_status(void)
{
	st_bms_fet_state_t st_policy_state;
	st_bms_fet_state_t st_hw_state;

	if(BMS_Fet_GetPolicyState(&st_policy_state) != E_BMS_OK)
	{
		return;
	}
	if(BMS_Fet_GetState(&st_hw_state) != E_BMS_OK)
	{
		return;
	}
	
	f_cfet = st_hw_state.u8_chg_fet_state;
	f_dfet = st_hw_state.u8_dsg_fet_state;
}