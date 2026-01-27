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
* System Name	: RAA241xxx RBMS-P Firmware for Renesas
* File Name		: afe.h
* Contents		: AFE header file
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

typedef struct {
	U8 u8_wkup_en;
	U8 u8_wkup_mpv;
	U8 u8_gain;
	U8 u8_fet;
} st_afe_wkup_setting_t;

typedef struct {
	U8 u8_pon_en;
	st_afe_wkup_setting_t	st_dsg_wkup;
	st_afe_wkup_setting_t	st_chg_wkup;
	U8 u8_wkup_time;
} st_afe_hw2_config_t;

typedef struct {
    U16 u16_sc_time;
    U16 u16_doc_time;
    U16 u16_occ_time;
} st_afe_time_t;

typedef struct {
    U8 u8_sc_th;
    U8 u8_doc_th;
    U8 u8_occ_th;
} st_afe_thresholds_t;

typedef struct {
    U8 u8_sc_enable;
    U8 u8_doc_enable;	
    U8 u8_occ_enable;
    st_afe_thresholds_t   st_thr;
    st_afe_time_t  st_time;
} st_afe_hw1_config_t;

typedef struct {
	U64 u64_ad_enable;
	U8 u8_ad_settime;
	U8 u8_ad_time;
} st_afe_ad_config_t;

typedef struct {
	U8 u8_afe_clock;
	st_afe_hw1_config_t st_afe_hw1_config;
	st_afe_hw2_config_t st_afe_hw2_config;
	st_afe_ad_config_t st_afe_ad_config;
} st_afe_config_t;

typedef enum {
	E_AFE_WINDOW0 = 0,
	E_AFE_WINDOW1,
	E_AFE_WINDOW2
}E_AFE_WINDOW_ITEM;

typedef enum {
	E_AFE_NORMAL = 0,
	E_AFE_LOWPOWER
}E_AFE_CLOCK_ITEM;

// - Global function -----------------------------------------------------------
/***********************************************************************
AFE  PROFILE
***********************************************************************/
//User ADC	PROFILE
void AFE_Init( st_afe_config_t st_afe_config );
void AFE_Reg_Read( volatile  U8 __far *p_reg, U8 u8_size, U8 *p_data );
void AFE_Reg_Write( volatile U8 __far *p_reg, U8 u8_data );
void PSW_PUSH( void );
void PSW_POP( void );
void AFE_WindowTo( U8 u8_window );
U8 AFE_Get_Window( void );
void AFE_Interrupt_Clear( U32 u32_int_flg );

/***********************************************************************
ADC  PROFILE
***********************************************************************/
void AFE_AD_Init( st_afe_ad_config_t config );
void AFE_AD_Setting( st_afe_ad_config_t config );
void AFE_AD_Start_SW_Trigger( void );
void AFE_AD_Stop_SW_Trigger( void );
//User ADC  PROFILE
U16 AFE_AD_Get_AdData( U8 u8_ad_num );
/***********************************************************************
TIMER  PROFILE
***********************************************************************/
void AFE_Timer_Init( void );
//User TIMER  PROFILE
void AFE_TimerA_Con(U8 u8_con);
void AFE_TimerB_Con( U8 u8_con );

/***********************************************************************
PWR DEVICE PROFILE
***********************************************************************/
//User PWR	PROFILE
void AFE_PWR_Control(U8 u8_pwr_con);
U8 AFE_PWR_Get_State(void);
void AFE_PWR_PowerDown( void );
void AFE_PWR_Reset( void );
/***********************************************************************
CC SETTING DEVICE PROFILE
***********************************************************************/
void AFE_CI_Init( void );
//User CC	PROFILE
void AFE_CI_StartCC( void );
void AFE_CI_StopCC( void );
U32 AFE_CI_GetADC( void );
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
void AFE_HVP_Control( U8 u8_hvp_onoff );
/***********************************************************************
OC SETTING DEVICE PROFILE
***********************************************************************/
void AFE_OC_Init( st_afe_hw1_config_t config );
/***********************************************************************
Trimming SETTING DEVICE PROFILE
***********************************************************************/
void AFE_Trimming_Setting( void );
/***********************************************************************
Cell balancing SETTING DEVICE PROFILE
***********************************************************************/
//User CB	PROFILE
void AFE_CB_Stop( void );
void AFE_CB_Start( void );
void AFE_CB_Con( U16 u16_balancing );
/***********************************************************************
Wakeup SETTING DEVICE PROFILE
***********************************************************************/
void AFE_WKUP_Init( st_afe_hw2_config_t st_afe_wakeup_config );
//User CB	PROFILE
void AFE_WKUP_Dsg_ReStart( void );
void AFE_WKUP_Chg_ReStart( void );
void AFE_WKUP_Chg_En( U8 u8_onoff );
void AFE_WKUP_Dsg_En( U8 u8_onoff );

void MCU_100us_WaitTime(U8 u8_n00us_wait);
/***********************************************************************
Callback PROFILE
***********************************************************************/
extern void _INT_AFE_AD_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_TimerA_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_TimerB_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_CI_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_SC_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_COC_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_DOC_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_WDT_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_PON_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_DWU_Callback( U32 u32_int_flg, U32 u32_int_errflg );
extern void _INT_AFE_CWU_Callback( U32 u32_int_flg, U32 u32_int_errflg );

// - Global constant -----------------------------------------------------------


// - Global variable -----------------------------------------------------------
GLOBAL U32	u32_AFE_Int_Flg;											// AFE interrupt flag
#define f_AFE_CC_Int				DEF32_BIT0(&u32_AFE_Int_Flg)			// Current Integration
#define f_AFE_AD_Int				DEF32_BIT1(&u32_AFE_Int_Flg)			// Software Trigger A/D Convert
#define f_AFE_SC_Int				DEF32_BIT2(&u32_AFE_Int_Flg)			// Discharge Short current
#define f_AFE_DOC_Int				DEF32_BIT3(&u32_AFE_Int_Flg)			// Discharge Overcurrent
#define f_AFE_COC_Int				DEF32_BIT4(&u32_AFE_Int_Flg)			// Charge Overcurrent
#define f_AFE_OV_Int				DEF32_BIT7(&u32_AFE_Int_Flg)			// Over Voltage
#define f_AFE_UV_Int				DEF32_BIT8(&u32_AFE_Int_Flg)			// Under Voltage
#define f_AFE_TIMERA_Int			DEF32_BIT9(&u32_AFE_Int_Flg)			// Timer A
#define f_AFE_TIMERB_Int			DEF32_BIT10(&u32_AFE_Int_Flg)			// Timer B
#define f_AFE_WDT_Int				DEF32_BIT11(&u32_AFE_Int_Flg)			// mcu wdt
#define f_AFE_FETBEK_Int			DEF32_BIT12(&u32_AFE_Int_Flg)			// FET breakdown
#define f_AFE_DWU_Int				DEF32_BIT13(&u32_AFE_Int_Flg)			// Discharge WakeUp
#define f_AFE_CWU_Int				DEF32_BIT14(&u32_AFE_Int_Flg)			// Charge WakeUp
#define f_AFE_PON_Int				DEF32_BIT15(&u32_AFE_Int_Flg)			// PON wakeup

GLOBAL U32	u32_AFE_IntErr_Flg;										// AFE interrupt flag
#define f_AFE_CC_Int_OVF			DEF32_BIT0(&u32_AFE_IntErr_Flg)		// Current Integration
#define f_AFE_AD_Int_OVF			DEF32_BIT1(&u32_AFE_IntErr_Flg)		// Software Trigger A/D Convert
#define f_AFE_SC_Int_OVF			DEF32_BIT2(&u32_AFE_IntErr_Flg)		// Discharge Short current
#define f_AFE_DOC_Int_OVF			DEF32_BIT3(&u32_AFE_IntErr_Flg)		// Discharge Overcurrent
#define f_AFE_COC_Int_OVF			DEF32_BIT4(&u32_AFE_IntErr_Flg)		// Charge Overcurrent
#define f_AFE_OV_Int_OVF			DEF32_BIT7(&u32_AFE_IntErr_Flg)		// Over Voltage
#define f_AFE_UV_Int_OVF			DEF32_BIT8(&u32_AFE_IntErr_Flg)		// Under Voltage
#define f_AFE_TIMERA_Int_OVF		DEF32_BIT9(&u32_AFE_IntErr_Flg)		// Timer A
#define f_AFE_TIMERB_Int_OVF		DEF32_BIT10(&u32_AFE_IntErr_Flg)		// Timer B
#define f_AFE_WDT_Int_OVF			DEF32_BIT11(&u32_AFE_IntErr_Flg)		// mcu wdt
#define f_AFE_FETBEK_Int_OVF		DEF32_BIT12(&u32_AFE_IntErr_Flg)		// FET breakdown
#define f_AFE_DWU_Int_OVF			DEF32_BIT13(&u32_AFE_IntErr_Flg)		// Discharge WakeUp
#define f_AFE_CWU_Int_OVF			DEF32_BIT14(&u32_AFE_IntErr_Flg)		// Charge WakeUp
#define f_AFE_PON_Int_OVF			DEF32_BIT15(&u32_AFE_IntErr_Flg)		// PON wakeup

GLOBAL U32	u32_AFE_Sytem_Flg;										// AFE interrupt flag
#define f_AFE_Int_Opr				DEF32_BIT0(&u32_AFE_Sytem_Flg)		// operatiing AFE interrupt 
#define f_AFE_PON_Status			DEF32_BIT4(&u32_AFE_Sytem_Flg)

GLOBAL U32	u32_AFE_Run_Flg;											// AFE interrupt flag
#define f_AFE_CC_Run				DEF32_BIT0(&u32_AFE_Run_Flg)			// Current Integration
#define f_AFE_AD_Run				DEF32_BIT1(&u32_AFE_Run_Flg)			// Software Trigger A/D Convert
#define f_AFE_SC_Run				DEF32_BIT2(&u32_AFE_Run_Flg)			// Discharge Short current
#define f_AFE_DOC_Run				DEF32_BIT3(&u32_AFE_Run_Flg)			// Discharge Overcurrent
#define f_AFE_COC_Run				DEF32_BIT4(&u32_AFE_Run_Flg)			// Charge Overcurrent
#define f_AFE_DWU_Run			DEF32_BIT5(&u32_AFE_Run_Flg)			// Discharge WakeUp
#define f_AFE_CWU_Run			DEF32_BIT6(&u32_AFE_Run_Flg)			// Charge WakeUp
#define f_AFE_OV_Run				DEF32_BIT7(&u32_AFE_Run_Flg)			// Over Voltage
#define f_AFE_UV_Run				DEF32_BIT8(&u32_AFE_Run_Flg)			// Under Voltage
#define f_AFE_TIMERA_Run			DEF32_BIT9(&u32_AFE_Run_Flg)			// Timer A
#define f_AFE_TIMERB_Run			DEF32_BIT10(&u32_AFE_Run_Flg)			// Timer B
#define f_AFE_WDT_Run			DEF32_BIT11(&u32_AFE_Run_Flg)			// mcu wdt
#define f_AFE_FETBEK_Run			DEF32_BIT12(&u32_AFE_Run_Flg)			// FET breakdown
#define f_AFE_DSGWKUP_Run		DEF32_BIT13(&u32_AFE_Run_Flg)			// discharge wakeup
#define f_AFE_CHGWKUP_Run		DEF32_BIT14(&u32_AFE_Run_Flg)			// charge wakeup
#define f_AFE_PONWKUP_Run		DEF32_BIT15(&u32_AFE_Run_Flg)			// PON wakeup

#undef		GLOBAL

#endif
