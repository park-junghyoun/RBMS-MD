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
* System Name	: RAJ240xxx RBMS Core for renesas
* File Name		: r_bms_callbacks_types.h
* Contents		: Callback Module
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

/*
 * Callback interface exposed to the application layer.
 *
 * The BMS core invokes these hooks to notify user firmware about alarms and mode changes
 * without introducing a reverse dependency from the core into board-specific code.
 */
#include "define.h"
#include "r_bms_protection_types.h"

/* Alarm events delivered through BMS_OnAlarmEvent callback. */
typedef enum {
	E_ALARM_CC_COMP = 0,	/* Coulomb-counter conversion complete */
	E_ALARM_AD_COMP,		/* ADC/measurement conversion complete */
	E_ALARM_125MS,			/* 125 ms scheduler tick */
	E_ALARM_5MS,			/* 5 ms fast scheduler tick */
	E_ALARM_CHG,			/* Charger/wakeup CHG signal event */
	E_ALARM_DSG,			/* Discharge/wakeup DSG signal event */
	E_ALARM_PIN_EDGE,		/* External wakeup pin edge event */
	E_ALARM_COUNT			/* Number of alarm event items */
} E_BMS_ALARM_ITEM;

typedef void (*BMS_OnProtectionActiveEvent)(E_BMS_ACTIVE_PROTECTION_ITEM e_protection, U8 u8_entered);
typedef void (*BMS_OnProtectionLatchedEvent)(E_BMS_LATCHED_PROTECTION_ITEM e_protection, U8 u8_entered);
typedef void (*BMS_OnAlarmEvent)(E_BMS_ALARM_ITEM e_alarm);
typedef struct {
	/* Split callback: auto-clear(active) protection enter/exit only. */
	BMS_OnProtectionActiveEvent on_protection_active_event;		/* Callback for active-protection enter/exit transitions */
	/* Split callback: latched-protection state change (u8_entered indicates enter/clear). */
	BMS_OnProtectionLatchedEvent on_protection_latched_event;	/* Callback for latched-protection state changes */
	BMS_OnAlarmEvent on_alarm;									/* Callback for periodic and hardware alarm events */
} BmsCoreCallbacks;
