#include "r_bms_config.h"
#include "r_bms_app.h"
#include "flashrom_fixed.h"
#include "dataflash_calibration.h"

void APP_CFG_Set_Fixed_Profile(void)
{
	if(app_CFG_Set_Mode_profile() == FALSE) return;
	if(app_CFG_Set_Protection_profile() == FALSE) return;
	if(app_CFG_Set_HW_profile() == FALSE) return;
	if(app_CFG_Set_Thermistor_tables() == FALSE) return;
	if(app_CFG_Set_Bal_profile() == FALSE) return;
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
U8 app_CFG_Set_Mode_profile(void)
{
	E_BMS_RESULT_ITEM e_ret;
	
	e_ret = BMS_Mode_SetProfile(E_BMS_MODE_NORMAL, st_fixed_data.st_bms_normal_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	e_ret = BMS_Mode_SetProfile(E_BMS_MODE_SLEEP, st_fixed_data.st_bms_sleep_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	e_ret = BMS_Mode_SetProfile(E_BMS_MODE_SLEEP2, st_fixed_data.st_bms_sleep2_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	e_ret = BMS_Mode_SetProfile(E_BMS_MODE_SHIP, st_fixed_data.st_bms_ship_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
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
U8 app_CFG_Set_Protection_profile(void)
{
	E_BMS_RESULT_ITEM e_ret;
	
	e_ret = BMS_Protection_SetConfig(st_fixed_data.st_bms_prot_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
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
U8 app_CFG_Set_HW_profile(void)
{
	E_BMS_RESULT_ITEM e_ret;

	e_ret = BMS_Config_SetHw1(st_fixed_data.st_hw1_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	e_ret = BMS_Config_SetHw2(st_fixed_data.st_hw2_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
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
U8 app_CFG_Set_Thermistor_tables(void)
{
	E_BMS_RESULT_ITEM e_ret;
	
	e_ret = BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN0, st_fixed_data.st_thermister1_table);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	
	e_ret = BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN1, st_fixed_data.st_thermister2_table);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	
	e_ret = BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN2, st_fixed_data.st_thermister3_table);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	
	e_ret = BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN3, st_fixed_data.st_thermister4_table);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	
	e_ret = BMS_Calib_SetThermistorTable(E_BMS_THERMISTOR_AN4, st_fixed_data.st_thermister5_table);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
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
U8 app_CFG_Set_Bal_profile(void)
{
	E_BMS_RESULT_ITEM e_ret;
	
	e_ret = BMS_Balancing_SetBalConfig(st_fixed_data.st_bal_config);
	if(e_ret != E_BMS_OK)	
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
	}
	e_ret = BMS_Balancing_SetSelfDischargeConfig(st_fixed_data.st_self_dsg_config);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Fixed(e_ret);
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
U8 APP_CFG_Apply_Calibration_Profiles(void)
{
	E_BMS_RESULT_ITEM e_ret;
	U8 u8_index = 0;
	
	for(u8_index = 0; u8_index<R_BMS_USER_API_CELL_COUNT; u8_index++)
	{
		e_ret = BMS_Calib_ApplyCellCoeff((E_BMS_CELL_ITEM)u8_index, &st_cal_data_dataflash.ast_coeff_cell[u8_index]);
		if(e_ret != E_BMS_OK)
		{
			return APP_ReportBMSCoreResult_Calib(e_ret);
		}
	}

	e_ret = BMS_Calib_ApplyPackCoeff(st_cal_data_dataflash.st_coeff_pack);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Calib(e_ret);
	}


	e_ret = BMS_Calib_ApplyCurrentCoeff(st_cal_data_dataflash.st_coeff_curr);
	if(e_ret != E_BMS_OK)
	{
		return APP_ReportBMSCoreResult_Calib(e_ret);
	}

	return TRUE;
}

