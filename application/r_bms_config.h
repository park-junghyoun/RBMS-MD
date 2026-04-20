#ifndef _R_BMS_CONFIG_H
#define _R_BMS_CONFIG_H

#include "define.h"
#include "r_bms_api.h"

void APP_CFG_Set_Fixed_Profile(void);
U8 app_CFG_Set_Mode_profile(void);
U8 app_CFG_Set_Protection_profile(void);
U8 app_CFG_Set_HW_profile(void);
U8 app_CFG_Set_Thermistor_tables(void);
U8 app_CFG_Set_Bal_profile(void);
U8 APP_CFG_Apply_Calibration_Profiles(void);

#endif	// _R_BMS_CONFIG_H
