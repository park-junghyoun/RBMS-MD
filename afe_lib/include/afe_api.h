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
#include "afe_types.h"
#include "afe_config.h"
// - Global function -----------------------------------------------------------
/***********************************************************************
AFE  PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_Init( st_afe_config_t st_afe_config );
E_AFE_RESULT AFE_Reg_Read( volatile __far U8 *p_reg, U8 u8_size, U8 __near *p_data );
E_AFE_RESULT AFE_Reg_Write( volatile __far U8 *p_reg, U8 u8_data );
void AFE_Int_Clear_HwOverFlow(U16 u16_bitmask);
U16 AFE_Int_Get_HwOverFlow( void );
E_AFE_RESULT AFE_Set_Window( E_AFE_WINDOW_ITEM e_window );
E_AFE_WINDOW_ITEM AFE_Get_Window( void );
U16 AFE_Get_InternalError(void);
st_afe_driver_info_t AFE_Get_DriverInfo(void);
/***********************************************************************
ADC  PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_AD_Set_Setting( st_afe_adc_config_t st_config );
E_AFE_RESULT AFE_AD_Get_Setting(st_afe_adc_config_t* pst_config);
E_AFE_RESULT AFE_AD_Start_Trigger( void );
E_AFE_RESULT AFE_AD_Stop_Trigger( void );
E_AFE_RESULT AFE_AD_Get_AdData( st_afe_adc_buffer_t* pst_afe_adc_buffer );
/***********************************************************************
TIMER  PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_TimerA_Control( U8 u8_con );
E_AFE_RESULT AFE_TimerB_Control( U8 u8_con );
/***********************************************************************
ABN DEVICE PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_ABN_OC_Set_Setting(st_afe_hw1_config_t st_config);
E_AFE_RESULT AFE_ABN_OC_Get_Setting(st_afe_hw1_config_t* pst_config);
E_AFE_RESULT AFE_ABN_WDT_Clear( void );
/***********************************************************************
PWR DEVICE PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_PWR_Control( E_AFE_MODE_ITEM e_pwr_con );
E_AFE_MODE_ITEM AFE_PWR_Get_Mode(void);
E_AFE_RESULT AFE_PWR_PowerDown( void );
E_AFE_RESULT AFE_PWR_Reset(void);

E_AFE_RESULT AFE_PowerDown_Prepare(void);
E_AFE_RESULT AFE_PowerDown_CheckReady(E_AFE_PD_READY_ITEM *p8_state);
E_AFE_RESULT AFE_PowerDown_Entry(void);
E_AFE_RESULT AFE_PowerDown_Cancel(void);


/***********************************************************************
Current Integration PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_CI_Start( void );
E_AFE_RESULT AFE_CI_Stop( void );
E_AFE_RESULT AFE_CI_Internal_Short_Control( E_AFE_CI_SHORT_ITEM e_short_con );
E_AFE_RESULT AFE_CI_Get_AdData(st_afe_cc_buffer_t* pst_afe_cc_buffer);
/***********************************************************************
FET Control PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_FET_Set_State(U8 u8_cfet, U8 u8_dfet);
E_AFE_RESULT AFE_FET_Get_State(U8* pu8_fet_state);
/***********************************************************************
High Voltage Pin  PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_HVP_Mode_Control(E_AFE_HVIO_ITEM e_hvio, E_AFE_HVP_MODE_ITEM e_mode);
E_AFE_RESULT AFE_HVP_Output_Control(E_AFE_HVIO_ITEM e_hvio, U8 u8_con);
E_AFE_RESULT AFE_HVP_Get_State(E_AFE_HVIO_ITEM e_hvio, U8* pu8_state);
/***********************************************************************
Cell balancing PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_CB_Stop( void );
E_AFE_RESULT AFE_CB_Get_State(U16* pu16_balancing_state);
E_AFE_RESULT AFE_CB_Control( U16 u16_balancing );
/***********************************************************************
Wakeup  PROFILE (Public API Profile)
***********************************************************************/
E_AFE_RESULT AFE_WKUP_Set_Setting(st_afe_hw2_config_t st_config);
E_AFE_RESULT AFE_WKUP_Get_Setting(st_afe_hw2_config_t* pst_config);
E_AFE_RESULT AFE_WKUP_Dsg_Control(U8 u8_con);
E_AFE_RESULT AFE_WKUP_Chg_Control(U8 u8_con);
E_AFE_RESULT AFE_WKUP_Chg_ReStart(void);
E_AFE_RESULT AFE_WKUP_Dsg_ReStart(void);
E_AFE_RESULT AFE_WKUP_PON_Get_State(U8* pu8_state);
E_AFE_RESULT AFE_WKUP_PON_Control(U8 u8_con);
/***********************************************************************
MCU PROFILE (Public API Profile)
***********************************************************************/
void MCU_100us_WaitTime(U8 u8_n00us_wait);
void MCU_PSW_PUSH( void );
void MCU_PSW_POP( void );
/***********************************************************************
Callback PROFILE (Public API Profile)
***********************************************************************/
void AFE_Callback_ISR( afe_callback_t st_cb, void * p_context );
