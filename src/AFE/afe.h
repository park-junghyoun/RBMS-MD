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

#ifndef _AFE_H
#define _AFE_H

// - Include header file -------------------------------------------------------
#include "define.h"
#include "device_register.h"

#ifdef	_AFE_C
#define		GLOBAL
#else
#define		GLOBAL	extern
#endif	/* _AFE_C */
typedef enum{
	E_AFE_HVP0 = 0,
	E_AFE_HVP1,
	E_AFE_HVP2,
	E_AFE_HVP_NUM
} E_AFE_HVIO_ITEM;

typedef enum{
	E_AFE_HVP_MODE_INPUT = 0,
	E_AFE_HVP_MODE_OUTPUT_PCH,
	E_AFE_HVP_MODE_OUTPUT_NCH,
	E_AFE_HVP_MODE_NUM
} E_AFE_HVP_MODE_ITEM;

typedef enum {
	E_AFE_WINDOW0 = 0,
	E_AFE_WINDOW1,
	E_AFE_WINDOW2
}E_AFE_WINDOW_ITEM;

typedef enum {
	E_AFE_WDT_OFF = 0,
	E_AFE_WDT_8S_RESET_DIS,
	E_AFE_WDT_8S_RESET_EN
}E_AFE_WDT_ITEM;

typedef enum {
	E_AFE_CLOCK_NORMAL = 0,
	E_AFE_CLOCK_LOWPOWER
}E_AFE_CLOCK_ITEM;

typedef enum {
	E_AFE_OC_DISABLE= 0,
	E_AFE_OC_ENABLE,
	E_AFE_OC_ENABLE_FET
}E_AFE_OC_SETTING_ITEM;

typedef enum {
	E_AFE_WKUP_DISABLE= 0,
	E_AFE_WKUP_ENABLE,
	E_AFE_WKUP_ENABLE_FET
}E_AFE_WKUP_SETTING_ITEM;

typedef enum{
	E_AFE_WKUP_GAIN_2 = 0,
	E_AFE_WKUP_GAIN_5,
	E_AFE_WKUP_GAIN_10,
	E_AFE_WKUP_GAIN_20,
	E_WKUP_GAIN_ITEM_NUM
} E_AFE_WKUP_GAIN_ITEM;

typedef enum {
/* ---- 1H: Battery cell measurement mode 1 ----*/
	E_AFE_MEA_CELL1 = 0,
	E_AFE_MEA_CELL2,
	E_AFE_MEA_CELL3,
	E_AFE_MEA_CELL4,
	E_AFE_MEA_CELL5,
	E_AFE_MEA_RSV1,
/* ---- 2H: Battery cell measurement mode 2 ----*/	
	E_AFE_MEA_CELL6,
	E_AFE_MEA_CELL7,
	E_AFE_MEA_CELL8,
	E_AFE_MEA_CELL9,
	E_AFE_MEA_CELL10,
	E_AFE_MEA_RSV2,
/* ---- 4H: High voltage pin measurement mode ----*/
	E_AFE_MEA_PACKV,
	E_AFE_MEA_PON,
	E_AFE_MEA_TOTALV,
	E_AFE_MEA_RSV3,
	E_AFE_MEA_RSV4,
	E_AFE_MEA_RSV5,
/* ---- 5H: Thermistor measurement mode ----*/
	E_AFE_MEA_AN0,
	E_AFE_MEA_AN1,
	E_AFE_MEA_AN2,
	E_AFE_MEA_VREG_AN0,
	E_AFE_MEA_VREG_AN1,
	E_AFE_MEA_VREG_AN2,
/* ---- 6H: Functional safety measurement mode ----*/
	E_AFE_MEA_ADREF,
	E_AFE_MEA_CCREF,
	E_AFE_MEA_ADCC,
	E_AFE_MEA_MCUREF,
	E_AFE_MEA_STEMP,
	E_AFE_MEA_VREG2,
	E_AFE_MEA_NUM/* 30 */
}E_AFE_MEA_MODE_ITEM;


typedef enum{
	E_AFE_EVENT_CC = 0,
	E_AFE_EVENT_AD,
	E_AFE_EVENT_SC,
	E_AFE_EVENT_DOC,
	E_AFE_EVENT_COC,
	E_AFE_EVENT_OV,
	E_AFE_EVENT_UV,
	E_AFE_EVENT_TIMERA,
	E_AFE_EVENT_TIMERB,
	E_AFE_EVENT_WDT,
	E_AFE_EVENT_DWU,
	E_AFE_EVENT_CWU,
	E_AFE_EVENT_PON
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
	E_AFE_EVENT_ITEM event;
	void      * p_context; 
} st_afe_callback_args_t;

typedef void (*afe_callback_t)(st_afe_callback_args_t * p_args);

typedef struct {
	U8 u8_init_result;
	U8 u8_max_cell_series;
	U8 u8_max_thermistor_series;
	E_AFE_DEVICE_ITEM e_target_deviece;
	U16 u16_driver_version; 

	U16  u16_reserved;
} st_afe_init_result_t;

typedef struct {
	E_AFE_WKUP_SETTING_ITEM e_setting;
	E_AFE_WKUP_GAIN_ITEM e_gain;
	U8 u8_thresholds;
} st_afe_wkup_config_t;

typedef struct {
	U8 u8_pon_wkup_config;
	st_afe_wkup_config_t	st_dsg_wkup_config;
	st_afe_wkup_config_t	st_chg_wkup_config;
	U8 u8_dsgchg_wkup_time;
} st_afe_hw2_config_t;

typedef struct {
	E_AFE_OC_SETTING_ITEM e_setting;
	U8 u8_thresholds;
	U8 u16_time;
} st_afe_oc_config_t;

typedef struct {
	st_afe_oc_config_t st_sc_config;
	st_afe_oc_config_t st_odc_config;
	st_afe_oc_config_t st_occ_config;
} st_afe_hw1_config_t;

typedef struct {
	U64 u64_adc_enable;
	U8 u8_adc_settime;
	U8 u8_adc_time;
} st_afe_adc_config_t;

typedef struct {
	E_AFE_CLOCK_ITEM e_afe_clock;
	E_AFE_WDT_ITEM e_afe_wdt_config;
	st_afe_hw1_config_t st_afe_hw1_config;
	st_afe_hw2_config_t st_afe_hw2_config;
	st_afe_adc_config_t st_afe_adc_config;
} st_afe_config_t;


// - Global function -----------------------------------------------------------
/***********************************************************************
AFE  PROFILE
***********************************************************************/
//User ADC	PROFILE
st_afe_init_result_t AFE_Init( st_afe_config_t st_afe_config );
void AFE_Reg_Read( volatile __far U8 *p_reg, U8 u8_size, U8 __near *p_data );
void AFE_Reg_Write( volatile __far U8 *p_reg, U8 u8_data );
void MCU_PSW_PUSH( void );
void MCU_PSW_POP( void );
U8 MCU_PSW_Get_Error(void);
U8 AFE_WindowTo( E_AFE_WINDOW_ITEM e_window );
U8 AFE_Get_Window( void );
void AFE_Interrupt_Clear( U32 u32_int_flg );

/***********************************************************************
ADC  PROFILE
***********************************************************************/
U8 AFE_AD_Init( st_afe_adc_config_t config );
U8 AFE_AD_Setting( st_afe_adc_config_t config );
//User ADC  PROFILE
U8 AFE_AD_Start_SW_Trigger( void );
void AFE_AD_Stop_SW_Trigger( void );
U16 AFE_AD_Get_AdData( E_AFE_MEA_MODE_ITEM u8_ad_num );
/***********************************************************************
TIMER  PROFILE
***********************************************************************/
void AFE_Timer_Init( void );
//User TIMER  PROFILE
U8 AFE_TimerA_Control(U8 u8_con);
U8 AFE_TimerB_Control( U8 u8_con );

/***********************************************************************
PWR DEVICE PROFILE
***********************************************************************/
//User PWR	PROFILE
U8 AFE_PWR_Control( E_AFE_CLOCK_ITEM e_pwr_con );
U8 AFE_PWR_Get_State(void);
U8 AFE_PWR_PowerDown( void );
U8 AFE_PWR_Reset(void);
/***********************************************************************
CC SETTING DEVICE PROFILE
***********************************************************************/
void AFE_CI_Init( void );
//User CC	PROFILE
U8 AFE_CI_Start( void );
void AFE_CI_Stop( void );
U32 AFE_CI_Get_AdData( void );
/***********************************************************************
FET DEVICE PROFILE
***********************************************************************/
void AFE_FET_Init( void );
//User FET	PROFILE
void AFE_FET_Set( U8 u8_cfet, U8 u8_dfet );
U8 AFE_FET_Get( void );
/***********************************************************************
HVP SETTING DEVICE PROFILE
***********************************************************************/
void AFE_HVP_Init( void );
//User HVP	PROFILE
U8 AFE_HVP_Mode_Control(E_AFE_HVIO_ITEM e_hvio, E_AFE_HVP_MODE_ITEM e_mode);
U8 AFE_HVP_Output_Control(E_AFE_HVIO_ITEM e_hvio, U8 u8_con);
U8 AFE_HVP_Get_State(E_AFE_HVIO_ITEM e_hvio);

/***********************************************************************
OC SETTING DEVICE PROFILE
***********************************************************************/
U8 AFE_Abn_OC_Init( st_afe_hw1_config_t config );
U8 AFE_Abn_WDT_Init(U8 u8_wdt_config);

/***********************************************************************
Trimming SETTING DEVICE PROFILE
***********************************************************************/
U8 AFE_Trimming_Setting( void );
/***********************************************************************
Cell balancing SETTING DEVICE PROFILE
***********************************************************************/
//User CB	PROFILE
void AFE_CB_Stop( void );
U16 AFE_CB_Get_State( void );
void AFE_CB_Control( U16 u16_balancing );
/***********************************************************************
Wakeup SETTING DEVICE PROFILE
***********************************************************************/
U8 AFE_WKUP_Init( st_afe_hw2_config_t st_afe_wakeup_config );
//User CB	PROFILE
U8 AFE_WKUP_Dsg_Control(U8 u8_con);
U8 AFE_WKUP_Chg_Control(U8 u8_con);

void MCU_100us_WaitTime(U8 u8_n00us_wait);
void MCU_Pin_Init(void);
void MCU_AFE_Pin_Init(void);
/***********************************************************************
Callback PROFILE
***********************************************************************/
void AFE_Callback_ISR(afe_callback_t st_cb, void * p_context);
void AFE_DispatchFrom_ISR(E_AFE_EVENT_ITEM e_ev);

U32 AFE_Int_HwOvf_Get(void);
void AFE_Int_HwOvf_Clear(U32 mask);

// - Global constant -----------------------------------------------------------


// - Global variable -----------------------------------------------------------
GLOBAL U32	u32_AFE_IntOVF_Flg;										// AFE interrupt flag
#define f_AFE_CC_Int_OVF			DEF32_BIT0(&u32_AFE_IntOVF_Flg)		// Current Integration
#define f_AFE_AD_Int_OVF			DEF32_BIT1(&u32_AFE_IntOVF_Flg)		// Software Trigger A/D Convert
#define f_AFE_SC_Int_OVF			DEF32_BIT2(&u32_AFE_IntOVF_Flg)		// Discharge Short current
#define f_AFE_DOC_Int_OVF			DEF32_BIT3(&u32_AFE_IntOVF_Flg)		// Discharge Overcurrent
#define f_AFE_COC_Int_OVF			DEF32_BIT4(&u32_AFE_IntOVF_Flg)		// Charge Overcurrent
#define f_AFE_OV_Int_OVF			DEF32_BIT5(&u32_AFE_IntOVF_Flg)		// Over Voltage
#define f_AFE_UV_Int_OVF			DEF32_BIT6(&u32_AFE_IntOVF_Flg)		// Under Voltage
#define f_AFE_TIMERA_Int_OVF		DEF32_BIT7(&u32_AFE_IntOVF_Flg)		// Timer A
#define f_AFE_TIMERB_Int_OVF		DEF32_BIT8(&u32_AFE_IntOVF_Flg)		// Timer B
#define f_AFE_WDT_Int_OVF			DEF32_BIT9(&u32_AFE_IntOVF_Flg)		// mcu wdt
#define f_AFE_DWU_Int_OVF			DEF32_BIT10(&u32_AFE_IntOVF_Flg)		// Discharge WakeUp
#define f_AFE_CWU_Int_OVF			DEF32_BIT11(&u32_AFE_IntOVF_Flg)		// Charge WakeUp
#define f_AFE_PON_Int_OVF			DEF32_BIT12(&u32_AFE_IntOVF_Flg)		// PON edge change

GLOBAL U32	u32_AFE_Sytem_Flg;										// AFE interrupt flag
#define f_AFE_Int_Opr				DEF32_BIT0(&u32_AFE_Sytem_Flg)		// operatiing AFE interrupt 
#define f_AFE_PON_Status			DEF32_BIT4(&u32_AFE_Sytem_Flg)

GLOBAL U32	u32_AFE_Run_Flg;											// AFE interrupt flag
#define f_AFE_CC_Run				DEF32_BIT0(&u32_AFE_Run_Flg)			// Current Integration
#define f_AFE_AD_Run				DEF32_BIT1(&u32_AFE_Run_Flg)			// Software Trigger A/D Convert
#define f_AFE_SC_Run				DEF32_BIT2(&u32_AFE_Run_Flg)			// Discharge Short current
#define f_AFE_DOC_Run				DEF32_BIT3(&u32_AFE_Run_Flg)			// Discharge Overcurrent
#define f_AFE_COC_Run				DEF32_BIT4(&u32_AFE_Run_Flg)			// Charge Overcurrent
#define f_AFE_OV_Run				DEF32_BIT5(&u32_AFE_Run_Flg)			// Over Voltage
#define f_AFE_UV_Run				DEF32_BIT6(&u32_AFE_Run_Flg)			// Under Voltage
#define f_AFE_TIMERA_Run			DEF32_BIT7(&u32_AFE_Run_Flg)			// Timer A
#define f_AFE_TIMERB_Run			DEF32_BIT8(&u32_AFE_Run_Flg)			// Timer B
#define f_AFE_WDT_Run			DEF32_BIT9(&u32_AFE_Run_Flg)			// mcu wdt
#define f_AFE_DSGWKUP_Run		DEF32_BIT10(&u32_AFE_Run_Flg)			// discharge wakeup
#define f_AFE_CHGWKUP_Run		DEF32_BIT11(&u32_AFE_Run_Flg)			// charge wakeup
#define f_AFE_PON_Run				DEF32_BIT12(&u32_AFE_Run_Flg)			// PON edge change

#define U32_AFE_INT_CC_BIT		((U32)1<<E_AFE_EVENT_CC)
#define U32_AFE_INT_AD_BIT		((U32)1<<E_AFE_EVENT_AD)
#define U32_AFE_INT_SC_BIT		((U32)1<<E_AFE_EVENT_SC)
#define U32_AFE_INT_DOC_BIT		((U32)1<<E_AFE_EVENT_DOC)
#define U32_AFE_INT_COC_BIT		((U32)1<<E_AFE_EVENT_COC)
#define U32_AFE_INT_OV_BIT		((U32)1<<E_AFE_EVENT_OV)
#define U32_AFE_INT_UV_BIT		((U32)1<<E_AFE_EVENT_UV)
#define U32_AFE_INT_TA_BIT		((U32)1<<E_AFE_EVENT_TIMERA)
#define U32_AFE_INT_TB_BIT		((U32)1<<E_AFE_EVENT_TIMERB)
#define U32_AFE_INT_WDT_BIT		((U32)1<<E_AFE_EVENT_WDT)
#define U32_AFE_INT_DWU_BIT		((U32)1<<E_AFE_EVENT_DWU)
#define U32_AFE_INT_CWU_BIT		((U32)1<<E_AFE_EVENT_CWU)
#define U32_AFE_INT_PON_BIT		((U32)1<<E_AFE_EVENT_PON)

#define U64_AD_CV1						((U64)1<<E_AFE_MEA_CELL1)
#define U64_AD_CV2						((U64)1<<E_AFE_MEA_CELL2)
#define U64_AD_CV3						((U64)1<<E_AFE_MEA_CELL3)
#define U64_AD_CV4						((U64)1<<E_AFE_MEA_CELL4)
#define U64_AD_CV5						((U64)1<<E_AFE_MEA_CELL5)
#define U64_AD_CV6						((U64)1<<E_AFE_MEA_CELL6)
#define U64_AD_CV7						((U64)1<<E_AFE_MEA_CELL7)
#define U64_AD_CV8						((U64)1<<E_AFE_MEA_CELL8)
#define U64_AD_CV9						((U64)1<<E_AFE_MEA_CELL9)
#define U64_AD_CV10						((U64)1<<E_AFE_MEA_CELL10)

#define U64_AD_PACKV						((U64)1<<E_AFE_MEA_PACKV)
#define U64_AD_PON						((U64)1<<E_AFE_MEA_PON)
#define U64_AD_TOTALV					((U64)1<<E_AFE_MEA_TOTALV)

#define U64_AD_AN0						((U64)1<<E_AFE_MEA_AN0)
#define U64_AD_AN1						((U64)1<<E_AFE_MEA_AN1)
#define U64_AD_AN2						((U64)1<<E_AFE_MEA_AN2)

#define U64_AD_AN0_VREG					((U64)1<<E_AFE_MEA_VREG_AN0)
#define U64_AD_AN1_VREG					((U64)1<<E_AFE_MEA_VREG_AN1)
#define U64_AD_AN2_VREG					((U64)1<<E_AFE_MEA_VREG_AN2)

#define U64_AD_ADREF						((U64)1<<E_AFE_MEA_ADREF)
#define U64_AD_CCREF						((U64)1<<E_AFE_MEA_CCREF)
#define U64_AD_ADCC						((U64)1<<E_AFE_MEA_ADCC)
#define U64_AD_MCUREF					((U64)1<<E_AFE_MEA_MCUREF)
#define U64_AD_STEMP						((U64)1<<E_AFE_MEA_STEMP)
#define U64_AD_VREG2						((U64)1<<E_AFE_MEA_VREG2)

#undef		GLOBAL

#endif
