#ifndef _R_BMS_APP_H
#define _R_BMS_APP_H

#include "define.h"
#include "r_bms_api.h"

void APP_BMS_Core_Init(void);
void APP_RunFail_Handler(void);
void APP_Check_FlashData(void);
U8 APP_ReportBMSCoreResult_Fixed(E_BMS_RESULT_ITEM e_ret);
U8 APP_ReportBMSCoreResult_Calib(E_BMS_RESULT_ITEM e_ret);

void APP_Get_AD_measurement_snapshot(void);
void APP_Get_CC_measurement_snapshot(void);
void APP_Get_CC_RAW_measurement_snapshot(void);
void APP_Get_AD_RAW_measurement_snapshot(void);
void APP_Get_FETStatus(void);
void APP_Get_ModeStatus(void);
void APP_Calc_TotalVolt(void);

void APP_Sleep_Check(void);
void APP_EntryBoot(void);
void APP_EntryPowerDown(void);
void APP_Seq_PowerDown(void);

void Stop_Mode(void);

#endif	// _R_BMS_APP_H
