#ifndef _R_BMS_EVENT_H
#define _R_BMS_EVENT_H

#include "define.h"
#include "r_bms_api.h"

U8 APP_Callbacks_Register(void);
void APP_Alarm_Event(E_BMS_ALARM_ITEM e_alarm);
void APP_Protection_Active_Event(E_BMS_ACTIVE_PROTECTION_ITEM e_prot, U8 u8_entered);
void APP_Protection_Latched_Event(E_BMS_LATCHED_PROTECTION_ITEM e_prot, U8 u8_entered);
void app_Charger_Timer(void);
void app_Sleep_Timer(void);
void app_SMBus_Timer(void);

#endif	// _R_BMS_EVENT_H
