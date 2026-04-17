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

#pragma once

/* Protection categories handled by the core engine. */
typedef enum {
	E_APROT_CUT = 0,	/* Charge under-temperature */
	E_APROT_DUT,		/* Discharge under-temperature */
	E_APROT_COT,		/* Charge over-temperature */
	E_APROT_DOT,		/* Discharge over-temperature */
	E_APROT_HCOC,		/* Hardware charge over-current */
	E_APROT_HDOC,		/* Hardware discharge over-current */
	E_APROT_HSC,		/* Hardware short-circuit */
	E_APROT_COC1,		/* Software charge over-current level 1 */
	E_APROT_COC2,		/* Software charge over-current level 2 */
	E_APROT_COC3,		/* Software charge over-current level 3 */
	E_APROT_DOC1,		/* Software discharge over-current level 1 */
	E_APROT_DOC2,		/* Software discharge over-current level 2 */
	E_APROT_DOC3,		/* Software discharge over-current level 3 */
	E_APROT_OV,			/* Cell over-voltage */
	E_APROT_UV,			/* Cell under-voltage */
	E_APROT_POC,		/* Precharge over-current */
	E_APROT_COUNT		/* Number of auto-clear(active) protection items */
} E_BMS_ACTIVE_PROTECTION_ITEM;

typedef enum {
	E_LPROT_COW = 0,	/* Cell open-wire diagnostic latch */
	E_LPROT_TOW,		/* Thermistor open-wire diagnostic latch */
	E_LPROT_CTOT,		/* Critical over-temperature latch */
	E_LPROT_CTOV,		/* Critical over-voltage latch */
	E_LPROT_CIMB,		/* Cell-imbalance latch */
	E_LPROT_DFF,		/* Discharge FET fault latch */
	E_LPROT_CFF,		/* Charge FET fault latch */
	E_LPROT_IR,			/* Internal-runtime diagnostic latch */
	E_LPROT_COUNT		/* Number of latched protection items */
} E_BMS_LATCHED_PROTECTION_ITEM;

#define U16_APROT_CUT_BIT	(1U << E_APROT_CUT)	/* Bit mask for CUT (charge under-temperature) */
#define U16_APROT_DUT_BIT	(1U << E_APROT_DUT)	/* Bit mask for DUT (discharge under-temperature) */
#define U16_APROT_COT_BIT	(1U << E_APROT_COT)	/* Bit mask for COT (charge over-temperature) */
#define U16_APROT_DOT_BIT	(1U << E_APROT_DOT)	/* Bit mask for DOT (discharge over-temperature) */

#define U16_APROT_HCOC_BIT	(1U << E_APROT_HCOC)	/* Bit mask for HCOC (HW charge over-current) */
#define U16_APROT_HDOC_BIT	(1U << E_APROT_HDOC)	/* Bit mask for HDOC (HW discharge over-current) */
#define U16_APROT_HSC_BIT	(1U << E_APROT_HSC)	/* Bit mask for HSC (HW short-circuit) */
#define U16_APROT_COC1_BIT	(1U << E_APROT_COC1)	/* Bit mask for COC1 (SW charge over-current level 1) */

#define U16_APROT_COC2_BIT	(1U << E_APROT_COC2)	/* Bit mask for COC2 (SW charge over-current level 2) */
#define U16_APROT_COC3_BIT	(1U << E_APROT_COC3)	/* Bit mask for COC3 (SW charge over-current level 3) */
#define U16_APROT_DOC1_BIT	(1U << E_APROT_DOC1)	/* Bit mask for DOC1 (SW discharge over-current level 1) */
#define U16_APROT_DOC2_BIT	(1U << E_APROT_DOC2)	/* Bit mask for DOC2 (SW discharge over-current level 2) */

#define U16_APROT_DOC3_BIT	(1U << E_APROT_DOC3)	/* Bit mask for DOC3 (SW discharge over-current level 3) */
#define U16_APROT_OV_BIT	(1U << E_APROT_OV)	/* Bit mask for OV (over-voltage) */
#define U16_APROT_UV_BIT	(1U << E_APROT_UV)	/* Bit mask for UV (under-voltage) */
#define U16_APROT_POC_BIT	(1U << E_APROT_POC)	/* Bit mask for POC (precharge over-current) */

#define U16_LPROT_COW_BIT	(1U << E_LPROT_COW)	/* Bit mask for COW (cell open-wire) */
#define U16_LPROT_TOW_BIT	(1U << E_LPROT_TOW)	/* Bit mask for TOW (thermistor open-wire) */
#define U16_LPROT_CTOT_BIT	(1U << E_LPROT_CTOT)	/* Bit mask for CTOT (critical over-temperature) */
#define U16_LPROT_CTOV_BIT	(1U << E_LPROT_CTOV)	/* Bit mask for CTOV (critical over-voltage) */
#define U16_LPROT_CIMB_BIT	(1U << E_LPROT_CIMB)	/* Bit mask for CIMB (cell imbalance) */
#define U16_LPROT_DFF_BIT	(1U << E_LPROT_DFF)	/* Bit mask for DFF (discharge FET fault) */
#define U16_LPROT_CFF_BIT	(1U << E_LPROT_CFF)	/* Bit mask for CFF (charge FET fault) */
#define U16_LPROT_IR_BIT	(1U << E_LPROT_IR)	/* Bit mask for IR (internal error) */

/*
 * Public bit masks and policy macros.
 *
 * Note: this header depends on enum values declared in r_bms_types.h and is
 * normally consumed through r_bms_types.h / r_bms_api.h.
 */

/* Internal-status bitmap (runtime diagnostics folded into U16_LPROT_IR_BIT). */
#define U32_BMS_ISTAT_EVENT_COALESCED_BIT        (1UL << E_BMS_ISTAT_EVENT_COALESCED)	/* Bit mask for coalesced internal events */
#define U32_BMS_ISTAT_AD_START_WHILE_BUSY_BIT    (1UL << E_BMS_ISTAT_AD_START_WHILE_BUSY)	/* Bit mask for AD-start while busy */
#define U32_BMS_ISTAT_CC_START_WHILE_BUSY_BIT    (1UL << E_BMS_ISTAT_CC_START_WHILE_BUSY)	/* Bit mask for CC-start while busy */
#define U32_BMS_ISTAT_AFE_SYS_HW_OVERFLOW_BIT    (1UL << E_BMS_ISTAT_AFE_SYS_HW_OVERFLOW)	/* Bit mask for AFE HW-overflow diagnostic */
#define U32_BMS_ISTAT_AFE_SYS_PSW_BIT            (1UL << E_BMS_ISTAT_AFE_SYS_PSW)		/* Bit mask for AFE PSW diagnostic */
#define U32_BMS_ISTAT_AFE_ALREADY_DONE_BIT       (1UL << E_BMS_ISTAT_AFE_ALREADY_DONE)	/* Bit mask for AFE already-done diagnostic */
#define U32_BMS_ISTAT_AFE_HW_FAIL_BIT            (1UL << E_BMS_ISTAT_AFE_HW_FAIL)		/* Bit mask for AFE hardware-failure diagnostic */
#define U32_BMS_ISTAT_AFE_NOT_INIT_BIT           (1UL << E_BMS_ISTAT_AFE_NOT_INIT)		/* Bit mask for AFE not-initialized diagnostic */
#define U32_BMS_ISTAT_AFE_PARAM_ERROR_BIT        (1UL << E_BMS_ISTAT_AFE_PARAM_ERROR)	/* Bit mask for AFE parameter-error diagnostic */
#define U32_BMS_ISTAT_BMS_ERR_HW_BIT             (1UL << E_BMS_ISTAT_BMS_ERR_HW)			/* Bit mask for BMS error: HW */
#define U32_BMS_ISTAT_BMS_ERR_INVALID_PARAM_BIT  (1UL << E_BMS_ISTAT_BMS_ERR_INVALID_PARAM)	/* Bit for BMS error code: invalid parameter */
#define U32_BMS_ISTAT_BMS_ERR_NOT_INIT_BIT       (1UL << E_BMS_ISTAT_BMS_ERR_NOT_INIT)		/* Bit for BMS error code: not initialized */
#define U32_BMS_ISTAT_BMS_ERR_NOT_READY_BIT      (1UL << E_BMS_ISTAT_BMS_ERR_NOT_READY)		/* Bit for BMS error code: not ready */
#define U32_BMS_ISTAT_ALL_BITS                   ((1UL << E_BMS_ISTAT_COUNT) - 1UL)			/* Mask of all defined internal-status bits */
