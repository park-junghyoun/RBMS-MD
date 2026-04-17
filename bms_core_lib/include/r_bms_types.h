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
* File Name		: r_bms_types.h
* Contents		: Public Types Module
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#pragma once

#include "define.h"
#include "afe_types.h"
#include "r_bms_measurement.h"
#include "r_bms_api_limits.h"
#include "r_bms_version.h"
#include "r_bms_protection.h"

/*
 * Public BMS enums and data transfer types.
 *
 * This header defines the stable vocabulary shared across the library boundary: result
 * codes, modes, alarms, balancing control, and host-facing measurement DTOs.
 */
typedef enum {
	E_BMS_OK = 0,				/* API completed successfully */
	E_BMS_ERR_HW,				/* Hardware/driver reported a fault */
	E_BMS_ERR_INVALID_PARAM,	/* Input parameter is out of supported range */
	E_BMS_ERR_NOT_INIT,			/* API was called before BMS initialization */
	E_BMS_ERR_NOT_READY			/* API/data path is not ready yet */
} E_BMS_RESULT_ITEM;

/* Internal-status bitmap (runtime diagnostics folded into U16_LPROT_IR_BIT). */
typedef enum {
	E_BMS_ISTAT_EVENT_COALESCED = 0,	/* Multiple internal events merged into one processing slot */
	E_BMS_ISTAT_AD_START_WHILE_BUSY,	/* AD conversion start requested while AD was busy */
	E_BMS_ISTAT_CC_START_WHILE_BUSY,	/* Coulomb counter start requested while CC was busy */
	E_BMS_ISTAT_AFE_SYS_HW_OVERFLOW,	/* AFE system status reported hardware overflow */
	E_BMS_ISTAT_AFE_SYS_PSW,			/* AFE system status reported PSW event */
	E_BMS_ISTAT_AFE_ALREADY_DONE,		/* AFE operation request was already completed */
	E_BMS_ISTAT_AFE_HW_FAIL,			/* AFE layer returned hardware failure */
	E_BMS_ISTAT_AFE_NOT_INIT,			/* AFE layer not initialized */
	E_BMS_ISTAT_AFE_PARAM_ERROR,		/* AFE layer parameter error */
	E_BMS_ISTAT_BMS_ERR_HW,				/* BMS API returned E_BMS_ERR_HW */
	E_BMS_ISTAT_BMS_ERR_INVALID_PARAM,	/* BMS API returned E_BMS_ERR_INVALID_PARAM */
	E_BMS_ISTAT_BMS_ERR_NOT_INIT,		/* BMS API returned E_BMS_ERR_NOT_INIT */
	E_BMS_ISTAT_BMS_ERR_NOT_READY,		/* BMS API returned E_BMS_ERR_NOT_READY */
	E_BMS_ISTAT_COUNT					/* Number of internal-status bitmap items */
} E_BMS_INTERNAL_STATUS_ITEM;

typedef enum {
	E_BMS_MODE_INIT,		/* Initial state after reset/initialization */
	E_BMS_MODE_NORMAL,		/* Normal measurement/protection operation */
	E_BMS_MODE_SLEEP,		/* Low-power sleep mode */
	E_BMS_MODE_SLEEP2,		/* Deeper low-power sleep mode */
	E_BMS_MODE_SHIP,		/* Ship/storage mode with minimum power */
	E_BMS_MODE_COUNT		/* Number of BMS operating modes */
} E_BMS_MODE_ITEM;

typedef enum {
	E_WAKEUP_CHG = 0,		/* Wakeup source: charger detection */
	E_WAKEUP_DSG,			/* Wakeup source: discharge/load detection */
	E_WAKEUP_PIN,			/* Wakeup source: external wakeup pin edge */
	E_WAKEUP_COUNT			/* Number of wakeup policy bits */
} E_BMS_WAKEUP_ITEM;

#define U8_WAKEUP_BIT_ALLOFF	((U8)0u)								/* Wakeup policy: disable all wakeup sources */
#define U8_WAKEUP_BIT_CHG		((U8)(1u << (U8)E_WAKEUP_CHG))		/* Wakeup policy bit for charger wakeup */
#define U8_WAKEUP_BIT_DSG		((U8)(1u << (U8)E_WAKEUP_DSG))		/* Wakeup policy bit for discharge wakeup */
#define U8_WAKEUP_BIT_PIN		((U8)(1u << (U8)E_WAKEUP_PIN))		/* Wakeup policy bit for external-pin wakeup */
#define U8_WAKEUP_VALID_MASK	((U8)((1u << (U8)E_WAKEUP_COUNT) - 1u))	/* Mask of all valid wakeup policy bits */

typedef enum {
	E_FET_CHG = 0,			/* Charge-path FET control bit index */
	E_FET_DSG,				/* Discharge-path FET control bit index */
	E_FET_COUNT				/* Number of FET policy bits */
} E_BMS_FET_ITEM;

/* NOTE: E_BMS_FET_ITEM remains public because mode profile config (r_bms_config.h) uses E_FET_COUNT. */
#define U8_FET_BIT_ALLOFF	((U8)0u)								/* FET policy: all FET bits OFF */
#define U8_FET_BIT_CHG		((U8)(1u << (U8)E_FET_CHG))			/* FET policy bit for CHG FET */
#define U8_FET_BIT_DSG		((U8)(1u << (U8)E_FET_DSG))			/* FET policy bit for DSG FET */
#define U8_FET_VALID_MASK	((U8)((1u << (U8)E_FET_COUNT) - 1u))	/* Mask of all valid FET policy bits */

/*
 * Request DTO for user FET override control API.
 * - u8_chg_override_off: ON  -> force CHG FET OFF.
 *                        OFF -> CHG FET follows BMS core policy.
 * - u8_dsg_override_off: ON  -> force DSG FET OFF.
 *                        OFF -> DSG FET follows BMS core policy.
 */
typedef struct
{
	U8 u8_chg_override_off;		/* ON: force CHG FET OFF, OFF: follow core policy */
	U8 u8_dsg_override_off;		/* ON: force DSG FET OFF, OFF: follow core policy */
} st_bms_fet_override_req_t;

/*
 * Read DTO for user FET state query APIs.
 * - u8_chg_fet_state: CHG FET ON/OFF state.
 * - u8_dsg_fet_state: DSG FET ON/OFF state.
 */
typedef struct
{
	U8 u8_chg_fet_state;			/* Current CHG FET state (ON/OFF) */
	U8 u8_dsg_fet_state;			/* Current DSG FET state (ON/OFF) */
} st_bms_fet_state_t;

typedef enum
{
	E_BAL_CTRL_AUTO = 0,   /* Default: automatic balancing control */
	E_BAL_CTRL_FORCE_ON,   /* Force balancing ON with user mask */
	E_BAL_CTRL_FORCE_OFF   /* Force balancing OFF */
} E_BAL_USER_CTRL_MODE;

/*
 * Request DTO for user balancing control API.
 * - e_mode  : AUTO/FORCE_ON/FORCE_OFF policy selection.
 * - u16_mask: Cell mask used when e_mode == E_BAL_CTRL_FORCE_ON.
 */
typedef struct
{
	E_BAL_USER_CTRL_MODE e_mode;	/* Balancing user control policy */
	U16 u16_mask;					/* Cell bitmask used when FORCE_ON is selected */
} st_bms_bal_user_ctrl_req_t;

typedef struct
{
	E_BAL_USER_CTRL_MODE e_mode;  	 /* User control mode */
	U16 u16_mask;						 /* Cell bitmask used when mode is FORCE_ON */
} st_bms_bal_user_ctrl_t;
