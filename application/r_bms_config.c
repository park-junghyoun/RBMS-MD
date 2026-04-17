#define _CONFIG
#include "r_bms_api.h"
#include "r_bms_config.h"

/*******************************************************************************
* Function Name: app_configure_callbacks
* Description  : Registers application-level alarm and protection callbacks to
*                the BMS Core callback table.
* Arguments    : None
* Return Value : None
* Notes        : This routine can be called after BMS_Core_Initialize() to
*                activate user event handling hooks.
*******************************************************************************/
U8 APP_CFG_Callbacks(void)
{
	E_BMS_RESULT_ITEM e_ret = E_BMS_OK;
	BmsCoreCallbacks st_callbacks = {0};
	
	st_callbacks.on_alarm = APP_Alarm_Event;
	st_callbacks.on_protection_active_event = APP_Protection_Active_Event;
	st_callbacks.on_protection_latched_event = APP_Protection_Latched_Event;
	if(BMS_Core_RegisterCallbacks(&st_callbacks) != E_BMS_OK)
	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************
* Function Name: app_configure_mode_profile
* Description  : Loads and updates the SLEEP mode operating profile for the
*                user firmware example.
* Arguments    : None
* Return Value : None
* Notes        : The routine reads the current profile, updates timing/FET
*                defaults, and writes the profile back to the core.
*******************************************************************************/
U8 APP_CFG_Set_Mode_profile(void)
{
	if(BMS_Mode_SetProfile(E_BMS_MODE_NORMAL, st_fixed_data.st_bms_normal_config) != E_BMS_OK)
	{
		return FALSE;
	}
	if(BMS_Mode_SetProfile(E_BMS_MODE_SLEEP, st_fixed_data.st_bms_sleep_config) != E_BMS_OK)
	{
		return FALSE;
	}
	if(BMS_Mode_SetProfile(E_BMS_MODE_SLEEP2, st_fixed_data.st_bms_sleep2_config) != E_BMS_OK)
	{
		return FALSE;
	}
	if(BMS_Mode_SetProfile(E_BMS_MODE_SHIP, st_fixed_data.st_bms_ship_config) != E_BMS_OK)
	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************
* Function Name: APP_CFG_Set_Protection_profile
* Description  : Updates software protection thresholds from the default
*                profile for product-level policy tuning.
* Arguments    : None
* Return Value : None
* Notes        : Current runtime config is used as the base and then partially
*                overridden before applying it at runtime.
*******************************************************************************/
U8 APP_CFG_Set_Protection_profile(void)
{
	if(BMS_Protection_SetConfig(st_fixed_data.st_bms_prot_config) != E_BMS_OK)
	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************
* Function Name: app_configure_hw_protection_path
* Description  : Reads, modifies, and reapplies HW1/HW2 AFE hardware
*                protection and wakeup settings.
* Arguments    : None
* Return Value : None
* Notes        : This function demonstrates board-specific tuning for
*                DOC/COC and wakeup behavior through BMS Config APIs.
*******************************************************************************/
U8 APP_CFG_Set_HW_profile(void)
{
	if(BMS_Config_SetHw1(st_fixed_data.st_hw1_config) != E_BMS_OK)
	{
		return FALSE;
	}
	if(BMS_Config_SetHw2(st_fixed_data.st_hw2_config) != E_BMS_OK)
	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************
* Function Name: app_configure_thermistor_tables
* Description  : Creates a runtime thermistor table from default values and
*                applies it to the selected NTC channel.
* Arguments    : None
* Return Value : None
* Notes        : The example applies a +1 offset to all table entries to show
*                how per-product compensation can be injected.
*******************************************************************************/
U8 APP_CFG_Set_Thermistor_tables(void)
{
	if(BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN0, st_fixed_data.st_thermister1_table) != E_BMS_OK)
	{
		return FALSE;
	}
	
	if(BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN1, st_fixed_data.st_thermister2_table) != E_BMS_OK)
	{
		return FALSE;
	}
	
	if(BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN2, st_fixed_data.st_thermister3_table) != E_BMS_OK)
	{
		return FALSE;
	}
	
	if(BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN3, st_fixed_data.st_thermister4_table) != E_BMS_OK)
	{
		return FALSE;
	}
	
	if(BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN4, st_fixed_data.st_thermister5_table) != E_BMS_OK)
	{
		return FALSE;
	}
	return TRUE;	
}
/*******************************************************************************
* Function Name: app_service_balancing_control
* Description  : Evaluates cell-voltage spread and updates balancing user
*                control mode accordingly.
* Arguments    : None
* Return Value : None
* Notes        : Balancing is forced only when delta/absolute conditions are
*                met; otherwise control returns to automatic mode.
*******************************************************************************/
void APP_CFG_Set_Bal_profile(void)
{
	if(BMS_Balancing_SetBalConfig(st_fixed_data.st_bal_config) != E_BMS_OK)
	{
		return FALSE;
	}
	if(BMS_Balancing_SetSelfDischargeConfig(st_fixed_data.st_self_dsg_config) != E_BMS_OK)
	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************
* Function Name: app_apply_calibration_profiles
* Description  : Builds and applies cell, pack, and current calibration
*                coefficients using production reference points.
* Arguments    : None
* Return Value : None
* Notes        : Computed calibration coefficients are applied immediately.
*******************************************************************************/
U8 APP_Apply_Calibration_Profiles(void)
{
	st_bms_cal_voltage_coeff_t st_cell_coeff = {0};
	st_bms_cal_pack_coeff_t st_pack_coeff = {0};
	st_bms_cal_current_coeff_t st_current_coeff = {0};
	U8 u8_index = 0;
	
	for(u8_index = 0; u8_index<R_BMS_USER_API_CELL_COUNT; u8_index++)
	{
		if(BMS_Calib_ComputeCellCoeff((E_BMS_CELL_ITEM)u8_index, &st_cal_data_dataflash.ast_cal_cell[u8_index], &st_cell_coeff) == E_BMS_OK)
		{
			if(BMS_Calib_ApplyCellCoeff((E_BMS_CELL_ITEM)u8_index, &st_cell_coeff) != E_BMS_OK)
			{
				return FALSE;
			}
		}else
		{
			return FALSE;
		}
	}
	
	if(BMS_Calib_ComputePackCoeff(&st_cal_data_dataflash.st_cal_pack, &st_pack_coeff) == E_BMS_OK)
	{
		if(BMS_Calib_ApplyPackCoeff(&st_pack_coeff) != E_BMS_OK)
		{
			return FALSE;
		}
	}else
	{
		return FALSE;
	}

	if(BMS_Calib_ComputeCurrentCoeff(&st_cal_data_dataflash.ast_cal_curr, &st_current_coeff) == E_BMS_OK)
	{
		if(BMS_Calib_ApplyCurrentCoeff(&st_current_coeff) != E_BMS_OK)
		{
			return FALSE;
		}
	}else
	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************
* Function Name: app_on_alarm
* Description  : Callback handler invoked on alarm events to update counters
*                and drive example status LEDs.
* Arguments    : alarm
*                  Alarm item notified by the BMS Core.
* Return Value : None
* Notes        : Registered through app_configure_callbacks().
*******************************************************************************/
void APP_Alarm_Event(E_BMS_ALARM_ITEM e_alarm)
{
	switch(e_alarm)
	{
		case E_ALARM_CC_COMP:
			app_process_cc_measurement_api();
			app_poll_cc_raw_signal();
			break;
		case E_ALARM_AD_COMP:
			LED4 = ~LED4;
			app_process_ad_measurement_api();
			app_poll_ad_raw_signal();
			break;
		case E_ALARM_125MS:
			APP_Get_FET_status();
			app_service_mode_manager();
			//app_service_balancing_control();
			//app_service_fet_override();
			//app_service_latched_protection();
			break;
		case E_ALARM_5MS:
			break;
		case E_ALARM_CHG:
		case E_ALARM_DSG:
		case E_ALARM_PIN_EDGE:
			BMS_Mode_Set(E_BMS_MODE_NORMAL);
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name: APP_Protection_Active_Event
* Description  : 
* Arguments    : 
* Return Value : 
* Notes        : 
*******************************************************************************/
void APP_Protection_Active_Event(E_BMS_ACTIVE_PROTECTION_ITEM e_prot, U8 u8_entered)
{
	BMS_Protection_GetActiveMask(&st_flexible_data_ram.st_status.u16_safety_bit);
	
	switch(e_prot)
	{
		case E_APROT_CUT:
		case E_APROT_DUT:
		case E_APROT_COT:
		case E_APROT_DOT:
		case E_APROT_HCOC:
		case E_APROT_HDOC:
		case E_APROT_HSC:
		case E_APROT_COC1:
		case E_APROT_COC2:
		case E_APROT_COC3:
		case E_APROT_DOC1:
		case E_APROT_DOC2:
		case E_APROT_DOC3:
		case E_APROT_OV:
		case E_APROT_UV:
		case E_APROT_POC:
		default:
			break;
	}
}

/*******************************************************************************
* Function Name: APP_Protection_Latched_Event
* Description  : 
* Arguments    : 
* Return Value : None
* Notes        : 
*******************************************************************************/
void APP_Protection_Latched_Event(E_BMS_LATCHED_PROTECTION_ITEM e_prot, U8 u8_entered)
{
	BMS_Protection_GetLatchedMask(&st_flexible_data_ram.st_status.u16_permanent_bit);
	
	switch(e_prot)
	{
		case E_LPROT_IR:
			BMS_InternalStatus_Get(st_flexible_data_ram.st_status.u32_internal_bit);
			break;
		case E_LPROT_COW:
		case E_LPROT_TOW:
		case E_LPROT_CTOT:
		case E_LPROT_CTOV:
		case E_LPROT_CIMB:
		case E_LPROT_DFF:
		case E_LPROT_CFF:
		default:
			break;
	}

}
