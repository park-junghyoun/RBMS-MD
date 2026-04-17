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

typedef enum {
	E_AFE_PD_NOT_ACT = 0,
	E_AFE_PD_NOT_READY,
	E_AFE_PD_READY
} E_AFE_PD_READY_ITEM;


typedef enum {
	E_AFE_OK = 0,
	E_AFE_ALREADY_DONE,
	E_AFE_HW_FAIL,
	E_AFE_NOT_INIT, 
	E_AFE_PARAM_ERROR
} E_AFE_RESULT;

typedef enum{
	E_AFE_CI_SHORT_DISABLE = 0,
	E_AFE_CI_SHORT_ENABLE,
	E_AFE_CI_SHORT_NUM
} E_AFE_CI_SHORT_ITEM;

typedef enum{
	E_AFE_HVIO_HVP0 = 0,
	E_AFE_HVIO_HVP1,
	E_AFE_HVIO_HVP2,
	E_AFE_HVIO_NUM
} E_AFE_HVIO_ITEM;

typedef enum{
	E_AFE_HVP_MODE_INPUT = 0,
	E_AFE_HVP_MODE_OUTPUT_PCH,
	E_AFE_HVP_MODE_OUTPUT_NCH,
	E_AFE_HVP_MODE_NUM
} E_AFE_HVP_MODE_ITEM;

typedef enum {
	E_SYS_ERROR_HWOVERFLOW = 0,
	E_SYS_RRROR_PSW_UNMACTH,
	E_SYS_ERROR_NUM
}E_AFE_SYS_ERROR_ITEM;

typedef enum {
	E_AFE_WINDOW0 = 0,
	E_AFE_WINDOW1,
	E_AFE_WINDOW2,
	E_AFE_WINDW_NUM
}E_AFE_WINDOW_ITEM;

typedef enum {
	E_AFE_WDT_OFF = 0,
	E_AFE_WDT_8S_RESET_DIS,
	E_AFE_WDT_8S_RESET_EN,
	E_AFE_WDT_SETTING_NUM
}E_AFE_WDT_SETTING_ITEM;

typedef enum {
	E_AFE_MODE_NORMAL = 0,
	E_AFE_MODE_LOWPOWER,
	E_AFE_MODE_NUM
}E_AFE_MODE_ITEM;

typedef enum {
	E_AFE_OC_DISABLE= 0,
	E_AFE_OC_FET_CTRL_DISABLE,
	E_AFE_OC_FET_CTRL_ENABLE,
	E_AFE_OC_SETTING_NUM
}E_AFE_OC_SETTING_ITEM;

typedef enum {
	E_AFE_WKUP_FET_CTRL_DISABLE =0,
	E_AFE_WKUP_FET_CTRL_ENABLE,
	E_AFE_WKUP_SETTING_NUM
}E_AFE_WKUP_SETTING_ITEM;

typedef enum{
	E_AFE_WKUP_GAIN_2 = 0,
	E_AFE_WKUP_GAIN_5,
	E_AFE_WKUP_GAIN_10,
	E_AFE_WKUP_GAIN_20,
	E_WKUP_GAIN_ITEM_NUM
} E_AFE_WKUP_GAIN_ITEM;

typedef enum{
	E_AFE_CI_RANGE_200 = 0,
	E_AFE_CI_RANGE_100,
	E_AFE_CI_RANGE_50,
	E_AFE_CI_RANGE_20,
	E_AFE_CI_RANGE_NUM
} E_AFE_CI_RANGE_ITEM;

typedef enum{
	E_AFE_EVENT_CC = 0,
	E_AFE_EVENT_AD,
	E_AFE_EVENT_SC,
	E_AFE_EVENT_DOC,
	E_AFE_EVENT_COC,
	E_AFE_EVENT_TIMERA,
	E_AFE_EVENT_TIMERB,
	E_AFE_EVENT_WDT,
	E_AFE_EVENT_DWU,
	E_AFE_EVENT_CWU,
	E_AFE_EVENT_PON,
	E_AFE_EVENT_ERROR,
	E_AFE_EVENT_NUM
} E_AFE_EVENT_ITEM;

typedef enum{
	E_AFE_DEV_RAJ240100 = 0,
	E_AFE_DEV_RAJ240090,
	E_AFE_DEV_RAJ240095,
	E_AFE_DEV_RAJ240094,
	E_AFE_DEV_RAJ240055,
	E_AFE_DEV_RAJ240057
} E_AFE_DEVICE_ITEM;

typedef struct{
	E_AFE_EVENT_ITEM e_event;
	void      * p_context; 
} st_afe_callback_args_t;

typedef void (*afe_callback_t)(st_afe_callback_args_t * p_args);

#define U16_AFE_SYS_ER_HWOVF_BIT			((U16)1<<E_SYS_ERROR_HWOVERFLOW)
#define U16_AFE_SYS_ER_PSW_BIT			((U16)1<<E_SYS_RRROR_PSW_UNMACTH)


#define U16_AFE_INT_CC_BIT				((U16)1<<E_AFE_EVENT_CC)
#define U16_AFE_INT_AD_BIT				((U16)1<<E_AFE_EVENT_AD)
#define U16_AFE_INT_SC_BIT				((U16)1<<E_AFE_EVENT_SC)
#define U16_AFE_INT_DOC_BIT				((U16)1<<E_AFE_EVENT_DOC)
#define U16_AFE_INT_COC_BIT				((U16)1<<E_AFE_EVENT_COC)
#define U16_AFE_INT_TA_BIT				((U16)1<<E_AFE_EVENT_TIMERA)
#define U16_AFE_INT_TB_BIT				((U16)1<<E_AFE_EVENT_TIMERB)
#define U16_AFE_INT_WDT_BIT				((U16)1<<E_AFE_EVENT_WDT)
#define U16_AFE_INT_DWU_BIT				((U16)1<<E_AFE_EVENT_DWU)
#define U16_AFE_INT_CWU_BIT				((U16)1<<E_AFE_EVENT_CWU)
#define U16_AFE_INT_PON_BIT				((U16)1<<E_AFE_EVENT_PON)
#define U16_AFE_INT_ERROR_BIT			((U16)1<<E_AFE_EVENT_ERROR)

