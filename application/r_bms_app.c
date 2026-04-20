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
#include "dataflash_calibration.h"
#include "dataflash_flexible.h"
#include "flashrom_fixed.h"
#include "smbus.h"
#include "r_bms_ram.h"
#include "inline_asm.h"


U8 APP_BMS_Core_Init(void)
{
	E_BMS_RESULT_ITEM e_ret;

	e_ret = BMS_Core_Initialize(&st_fixed_data.st_bms_init_config);
	return APP_ReportBMSCoreResult_Fixed(e_ret);

}

void APP_Check_FlashData(void)
{
	U8 u8_ret;

	u8_ret = FLASH_Check_FixedData();
	if(u8_ret == FALSE)
	{
		f_init_fixed_none = TRUE;
		while(1)
		{
			SMBus_timeout_check();							// SMBus timeout check
		}
	}
	u8_ret = FLASH_Check_CalibrationData();
	if(u8_ret == FALSE)
	{
		f_init_cal_none = TRUE;
	}

}

U8 APP_ReportBMSCoreResult_Fixed(E_BMS_RESULT_ITEM e_ret)
{
	if( e_ret != E_BMS_OK)
	{
		switch(e_ret)
		{
			case E_BMS_ERR_HW:
				f_hw_error = ON;
				break;
			case E_BMS_ERR_INVALID_PARAM:
				f_fixed_error = ON;
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
U8 APP_ReportBMSCoreResult_Calib(E_BMS_RESULT_ITEM e_ret)
{
	if( e_ret != E_BMS_OK)
	{
		switch(e_ret)
		{
			case E_BMS_ERR_HW:
				f_hw_error = ON;
				break;
			case E_BMS_ERR_INVALID_PARAM:
				f_cal_error = ON;
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
	if(BMS_Measure_GetAdSnapshot(&st_flexible_data_ram.st_measurement.ad) != E_BMS_OK)
	{
		return;
	}
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
	if(BMS_Measure_GetCcSnapshot(&st_flexible_data_ram.st_measurement.cc) != E_BMS_OK)
	{
		return;
	}
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
void APP_Get_AD_RAW_measurement_snapshot(void)
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
void APP_Get_FETstatus(void)
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
void APP_Sleep_Check(void)
{
	if((st_flexible_data_ram.st_measurement.cc.s32_pack_current_mA <= (S32)st_fixed_data.st_system_info.u16_sleep_current) &&
		(st_flexible_data_ram.st_measurement.cc.s32_pack_current_mA >= -(S32)st_fixed_data.st_system_info.u16_sleep_current) &&
		(f_nosmb == ON) &&
		(st_flexible_data_ram.st_status.u16_safety_bit == 0) &&
		(st_flexible_data_ram.st_status.u16_permanent_bit == 0))
	{
		BMS_Mode_Set(E_BMS_MODE_SLEEP);

	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Move to Flash update mode operation
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void MoveToFlashUpdate(void)
*-------------------------------------------------------------------
* Function			: Move to Flash update mode operation.
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
* History			: 2020.10.16 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void APP_MoveToBoot(void)
{

	st_flexible_data_ram.st_reason.u8_update_reason = FLEXUP_FLASH;			// Set Reason of Flex update
	Write_FlexibleData();					// Update Flexible data

	DI();										// Disable interrupt
	Stop_AFEWDT();								// Stop AFE WDT
	ASM_JUMP_BOOT_64();							// To Flash update mode
}
