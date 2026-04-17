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
U8 APP_Callbacks_Register(void)
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
