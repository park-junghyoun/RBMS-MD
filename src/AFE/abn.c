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
* File Name		: abn.c
* Contents		: abnormal detection (SC/DOC/COC/WDT) initialization and ISR handling
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _ABN_C

#include "define.h"
#include "afe.h"
#include "abn_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------
#pragma interrupt _int_AbnormalDtct(vect=U16_ANL_VECTOR_MAPPING)		// ANL interrupt
static U8 afe_Abn_DOC_Calibration(void);
static U8 afe_Abn_COC_Calibration(void);
static U8 afe_Abn_SCC_Setting( st_afe_oc_config_t st_oc_config );
static U8 afe_Abn_DOC_Setting( st_afe_oc_config_t st_oc_config );
static U8 afe_Abn_COC_Setting( st_afe_oc_config_t st_oc_config );
static void afe_Abn_Interrupt(U8 u8_onoff);
static void afe_Abn_SC_Overflow_Chk(void);
static void afe_Abn_DOC_Overflow_Chk(void);
static void afe_Abn_COC_Overflow_Chk(void);
static void afe_Abn_WDT_Overflow_Chk(void);
// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: AFE_Abn_OC_Init
* Description  : Initialize abnormal over-current blocks (SC/DOC/COC).
* Arguments    : config : HW1 OC configuration
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 AFE_Abn_OC_Init(st_afe_hw1_config_t config)
{
	U8 init_seq = TRUE;
	
	/* Keep ABN IRQs masked while calibration/configuration is in progress. */
	afe_Abn_Interrupt(OFF);
	init_seq = afe_Abn_COC_Calibration();
	if(init_seq == FALSE) 
	{
		return init_seq;
	}
	
	init_seq = afe_Abn_DOC_Calibration();
	if(init_seq == FALSE) 
	{
		return init_seq;
	}
	
	init_seq = afe_Abn_SCC_Setting(config.st_sc_config);
	if(init_seq == FALSE) 
	{
		return init_seq;
	}
	
	init_seq = afe_Abn_DOC_Setting(config.st_odc_config);
	if(init_seq == FALSE) 
	{
		return init_seq;
	}
	
	init_seq = afe_Abn_COC_Setting(config.st_occ_config);
	if(init_seq == FALSE) 
	{
		return init_seq;
	}
	
	/* Re-enable ABN IRQ delivery after all blocks are configured. */
	afe_Abn_Interrupt(ON);
	
	return init_seq;
}
/*******************************************************************************
* Function Name: AFE_Abn_WDT_Init
* Description  : Configure abnormal watchdog detection behavior.
* Arguments    : u8_wdt_config : watchdog mode
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 AFE_Abn_WDT_Init(U8 u8_wdt_config)
{
	/* Valid table index range is 0..2. */
	if(u8_wdt_config >= 3)
	{
		return FALSE;
	}
	/* Program watchdog behavior from predefined mapping table. */
	AFE_Reg_Write(p8_AWDTCON_Reg_Mapping,	u8_AWDTCON_DATA_Mapping[u8_wdt_config]);	

	/* Clear/refresh AWDT request flags after configuration. */
	AFE_Reg_Write(p8_AWDTRF_Reg_Mapping, 0xFF);
	
	return TRUE; 
}
/*******************************************************************************
* Function Name: _int_AbnormalDtct
* Description  : ABN interrupt service routine for SC/DOC/COC/WDT sources.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void _int_AbnormalDtct( void )
{
	/* Snapshot ABN interrupt flags once and service each asserted source. */
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if( u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_SCD_IR])								//SDC interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_ABN_SCD_IR]);
		AFE_DispatchFrom_ISR(E_AFE_EVENT_SC);
		afe_Abn_SC_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_DOC_IR])								// DOC interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_ABN_DOC_IR]);
		AFE_DispatchFrom_ISR(E_AFE_EVENT_DOC);
		afe_Abn_DOC_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_COC_IR])								// COC interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_ABN_COC_IR]);
		AFE_DispatchFrom_ISR(E_AFE_EVENT_COC);
		afe_Abn_COC_Overflow_Chk();
	}

	if( u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_WDT_IR])							// WDT interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_ABN_WDT_IR]);
		AFE_DispatchFrom_ISR(E_AFE_EVENT_WDT);
		afe_Abn_WDT_Overflow_Chk();
	}

}
/*******************************************************************************
* Function Name: afe_Abn_SCC_Setting
* Description  : Validate/clamp and apply SC detection threshold/time settings.
* Arguments    : st_oc_config : SC over-current configuration
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 afe_Abn_SCC_Setting( st_afe_oc_config_t st_oc_config )
{
	U8 u8_sccmpv_data;
	U8 u8_scctime_data;

	if(st_oc_config.e_setting > E_AFE_OC_ENABLE_FET)
	{
		return FALSE;
	}
	
	if(st_oc_config.u16_time > U8_ABN_SCCTIME_MAX)
	{
		u8_scctime_data = U8_ABN_SCCTIME_MAX;
	}else if(st_oc_config.u16_time <= U8_ABN_SCCTIME_MIN)
	{
		u8_scctime_data = U8_ABN_SCCTIME_MIN;
	}else
	{
		u8_scctime_data = st_oc_config.u16_time;
	}

	if(st_oc_config.u8_thresholds > U8_ABN_SCCMPV_MAX)
	{
		u8_sccmpv_data = U8_ABN_SCCMPV_MAX;
	}else if(st_oc_config.u8_thresholds <= U8_ABN_SCCMPV_MIN)
	{
		u8_sccmpv_data = U8_ABN_SCCMPV_MIN;
	}else
	{
		u8_sccmpv_data = st_oc_config.u8_thresholds;
	}

	AFE_Reg_Write(p8_SCCTIME_Reg_Mapping,u8_scctime_data);

	AFE_Reg_Write(p8_SCCCON_Reg_Mapping,u8_SCCCON_Data_Mapping[st_oc_config.e_setting]|u8_sccmpv_data);

	return TRUE;
}
/*******************************************************************************
* Function Name: afe_Abn_DOC_Setting
* Description  : Validate/clamp and apply DOC detection threshold/time settings.
* Arguments    : st_oc_config : DOC over-current configuration
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 afe_Abn_DOC_Setting( st_afe_oc_config_t st_oc_config )
{
	U8 u8_odcmpv_data;
	U16 u16_odctime_data;

	if(st_oc_config.e_setting > E_AFE_OC_ENABLE_FET)
	{
		return FALSE;
	}
	
	if(st_oc_config.u16_time > U16_ABN_DOCTIME_MAX)
	{
		u16_odctime_data = U16_ABN_DOCTIME_MAX;
	}else if(st_oc_config.u16_time <= U16_ABN_DOCTIME_MIN)
	{
		u16_odctime_data = U16_ABN_DOCTIME_MIN;
	}else
	{
		u16_odctime_data = st_oc_config.u16_time;
	}

	/* Clamp DOC threshold to DOC-specific HW range. */
	if(st_oc_config.u8_thresholds > U8_ABN_DOCMPV_MAX)
	{
		u8_odcmpv_data = U8_ABN_DOCMPV_MAX;
	}else if(st_oc_config.u8_thresholds <= U8_ABN_DOCMPV_MIN)
	{
		u8_odcmpv_data = U8_ABN_DOCMPV_MIN;
	}else
	{
		u8_odcmpv_data = st_oc_config.u8_thresholds;
	}

	AFE_Reg_Write(p8_DOCTIME1_Reg_Mapping,(U8)(u16_odctime_data&0xFF));
	AFE_Reg_Write(p8_DOCTIME2_Reg_Mapping,(U8)(u16_odctime_data>>8));

	AFE_Reg_Write(p8_DOCCON_Reg_Mapping,u8_DOCCON_Data_Mapping[st_oc_config.e_setting]|u8_odcmpv_data);

	return TRUE;
}
/*******************************************************************************
* Function Name: afe_Abn_COC_Setting
* Description  : Validate/clamp and apply COC detection threshold/time settings.
* Arguments    : st_oc_config : COC over-current configuration
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 afe_Abn_COC_Setting( st_afe_oc_config_t st_oc_config )
{
	U8 u8_cocmpv_data;
	U8 u8_coctime_data;

	if(st_oc_config.e_setting > E_AFE_OC_ENABLE_FET)
	{
		return FALSE;
	}
	
	if(st_oc_config.u16_time > U8_ABN_COCTIME_MAX)
	{
		u8_coctime_data = U8_ABN_COCTIME_MAX;
	}else if(st_oc_config.u16_time <= U8_ABN_COCTIME_MIN)
	{
		u8_coctime_data = U8_ABN_COCTIME_MIN;
	}else
	{
		u8_coctime_data = st_oc_config.u16_time;
	}

	/* Clamp COC threshold to COC-specific HW range. */
	if(st_oc_config.u8_thresholds > U8_ABN_COCMPV_MAX)
	{
		u8_cocmpv_data = U8_ABN_COCMPV_MAX;
	}else if(st_oc_config.u8_thresholds <= U8_ABN_COCMPV_MIN)
	{
		u8_cocmpv_data = U8_ABN_COCMPV_MIN;
	}else
	{
		u8_cocmpv_data = st_oc_config.u8_thresholds;
	}

	AFE_Reg_Write(p8_COCTIME_Reg_Mapping,u8_coctime_data);

	AFE_Reg_Write(p8_COCCON_Reg_Mapping,u8_COCCON_Data_Mapping[st_oc_config.e_setting]|u8_cocmpv_data);

	return TRUE;
}
/*******************************************************************************
* Function Name: afe_Abn_DOC_Calibration
* Description  : Execute DOC comparator offset calibration sequence.
* Arguments    : void
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 afe_Abn_DOC_Calibration(void)
{
	U8 u8_docsts = 0;												// OCDSTS register read
	U8 u8_doccal_val = u8_DOCCAL_InitVal_Mapping;						// work for calibration value
	U8 u8_reg_check = TRUE;
	
	AFE_WindowTo(E_AFE_WINDOW1);						// AFE Window 1
	AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,u8_DOCCAL_Data_Mapping[ON] | u8_doccal_val);					// DOC calibration enabled
	AFE_WindowTo(E_AFE_WINDOW0);						// AFE Window 0
	AFE_Reg_Write(p8_DOCTIME1_Reg_Mapping,(U8)U16_ABN_DOCTIME_MIN&0xFF);							// detectiom time 488[us] * 1 = 488[us]
	AFE_Reg_Write(p8_DOCTIME2_Reg_Mapping,(U8)U16_ABN_DOCTIME_MIN>>8);
	AFE_Reg_Write(p8_DOCCON_Reg_Mapping,u8_DOCCON_Data_Mapping[ON]);						// DOC1 detection curcuit enabled

	MCU_100us_WaitTime(10);
	
	/* Sweep calibration code until DOC status toggles, then back off one step. */
	do{	
		if(u8_doccal_val != 0x00)
		{
			AFE_Reg_Read(p8_OCDSTS_Reg_Mapping,1,&u8_docsts);			
			if(u8_docsts & u8_OCDRSTS_DOC_Mapping)
			{
				u8_doccal_val--;
			}else
			{
				u8_doccal_val++;
				AFE_WindowTo(E_AFE_WINDOW1);			// AFE Window 1
				AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,u8_DOCCAL_Data_Mapping[OFF] | u8_doccal_val);					// DOCCAL calibration value setting & DOC calibration disabled
				AFE_WindowTo(E_AFE_WINDOW0);			// AFE Window 0
				break;

			}
		}else
		{
			AFE_WindowTo(E_AFE_WINDOW1);				// AFE Window 1
			AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,u8_DOCCAL_Data_Mapping[OFF] | u8_doccal_val);			// Set DOC calibration value
			AFE_WindowTo(E_AFE_WINDOW0);				// AFE Window 0
			u8_reg_check = FALSE;
			break;
		}
		AFE_WindowTo(E_AFE_WINDOW1);					// AFE Window 1
		AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,u8_DOCCAL_Data_Mapping[ON] | u8_doccal_val);				// DOC calibration enabled & calibration value
		AFE_WindowTo(E_AFE_WINDOW0);					// AFE Window 0
		AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_DOC_Mapping);					// Discharge detection flag clear
		MCU_100us_WaitTime(10);	
	
	}while(1);	
	AFE_Reg_Write(p8_DOCCON_Reg_Mapping,u8_DOCCON_Data_Mapping[OFF]);						// DOC1 detection curcuit disabled
	AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_DOC_Mapping);						// DOC1 detection flag clear

	return u8_reg_check;

}
/*******************************************************************************
* Function Name: afe_Abn_COC_Calibration
* Description  : Execute COC comparator offset calibration sequence.
* Arguments    : void
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 afe_Abn_COC_Calibration(void)
{
	U8 u8_cocsts = 0;												// OCDSTS register read
	U8 u8_coccal_val = u8_COCCAL_InitVal_Mapping;						// work for calibration value
	U8 u8_reg_check = TRUE;
	
	AFE_WindowTo(E_AFE_WINDOW1);						// AFE Window 1
	AFE_Reg_Write(p8_COCCAL_Reg_Mapping,u8_COCCAL_Data_Mapping[ON] | u8_coccal_val);					// DOC calibration enabled
	AFE_WindowTo(E_AFE_WINDOW0);						// AFE Window 0
	AFE_Reg_Write(p8_COCTIME_Reg_Mapping,U8_ABN_COCTIME_MIN);
	AFE_Reg_Write(p8_COCCON_Reg_Mapping,u8_COCCON_Data_Mapping[ON]);						// DOC1 detection curcuit enabled
	
	MCU_100us_WaitTime(10);
	
	/* Sweep calibration code until COC status toggles, then back off one step. */
	do{	
		if(u8_coccal_val != 0x00)
		{
			AFE_Reg_Read(p8_OCDSTS_Reg_Mapping,1,&u8_cocsts);			
			/* Evaluate COC status flag while calibrating COC comparator. */
			if(u8_cocsts & u8_OCDSTS_COC_Mapping)
			{
				u8_coccal_val--;
			}else
			{
				u8_coccal_val++;
				AFE_WindowTo(E_AFE_WINDOW1);			// AFE Window 1
				AFE_Reg_Write(p8_COCCAL_Reg_Mapping,u8_COCCAL_Data_Mapping[OFF] | u8_coccal_val);					// DOCCAL calibration value setting & DOC calibration disabled
				AFE_WindowTo(E_AFE_WINDOW0);			// AFE Window 0
				break;

			}
		}else
		{
			AFE_WindowTo(E_AFE_WINDOW1);				// AFE Window 1
			AFE_Reg_Write(p8_COCCAL_Reg_Mapping,u8_COCCAL_Data_Mapping[OFF] | u8_coccal_val);			// Set DOC calibration value
			AFE_WindowTo(E_AFE_WINDOW0);				// AFE Window 0
			u8_reg_check = FALSE;
			break;
		}
		AFE_WindowTo(E_AFE_WINDOW1);					// AFE Window 1
		AFE_Reg_Write(p8_COCCAL_Reg_Mapping,u8_COCCAL_Data_Mapping[ON] | u8_coccal_val);				// DOC calibration enabled & calibration value
		AFE_WindowTo(E_AFE_WINDOW0);					// AFE Window 0
		AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_COC_Mapping);					// Discharge detection flag clear
		MCU_100us_WaitTime(10);
	
	}while(1);	
	AFE_Reg_Write(p8_COCCON_Reg_Mapping,u8_COCCON_Data_Mapping[OFF]);						// DOC1 detection curcuit disabled
	AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_COC_Mapping);						// DOC1 detection flag clear

	return u8_reg_check;

}
/*******************************************************************************
* Function Name: afe_Abn_Interrupt
* Description  : Enable/disable ABN interrupt masks for all ABN sources.
* Arguments    : u8_onoff : ON to mask, OFF to unmask
* Return Value : void
*******************************************************************************/
void afe_Abn_Interrupt(U8 u8_onoff)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIRMK_Reg_Mapping,1,&u8_reg_data);
	/* Mask-register polarity: set bits to mask, clear bits to unmask. */
	if(u8_onoff == ON)
	{
		u8_reg_data |= (u8_ABIRMK_Data_Mapping[E_ABN_SCD_IR] | u8_ABIRMK_Data_Mapping[E_ABN_DOC_IR] | u8_ABIRMK_Data_Mapping[E_ABN_COC_IR] | u8_ABIRMK_Data_Mapping[E_ABN_WDT_IR]);
	}else
	{
		u8_reg_data &= ~(u8_ABIRMK_Data_Mapping[E_ABN_SCD_IR] | u8_ABIRMK_Data_Mapping[E_ABN_DOC_IR] | u8_ABIRMK_Data_Mapping[E_ABN_COC_IR] | u8_ABIRMK_Data_Mapping[E_ABN_WDT_IR]);
	}
	AFE_Reg_Write(p8_ABIRMK_Reg_Mapping,u8_reg_data);

	AFE_Reg_Write(p8_ABIF_Reg_Mapping,~( u8_ABIR_Data_Mapping[E_ABN_SCD_IR] | u8_ABIR_Data_Mapping[E_ABN_DOC_IR] | u8_ABIR_Data_Mapping[E_ABN_COC_IR] | u8_ABIR_Data_Mapping[E_ABN_WDT_IR]));
}
/*******************************************************************************
* Function Name: afe_Abn_SC_Overflow_Chk
* Description  : Detect SC interrupt re-assertion while ISR is servicing current event.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void afe_Abn_SC_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_SCD_IR])
	{
		AFE_Int_HwOvf_Set(E_AFE_EVENT_SC);
	}
}
/*******************************************************************************
* Function Name: afe_Abn_COC_Overflow_Chk
* Description  : Detect COC interrupt re-assertion while ISR is servicing current event.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void afe_Abn_COC_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_COC_IR])
	{
		AFE_Int_HwOvf_Set(E_AFE_EVENT_COC);
	}
}
/*******************************************************************************
* Function Name: afe_Abn_DOC_Overflow_Chk
* Description  : Detect DOC interrupt re-assertion while ISR is servicing current event.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void afe_Abn_DOC_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_DOC_IR])
	{
		AFE_Int_HwOvf_Set(E_AFE_EVENT_DOC);
	}
}
/*******************************************************************************
* Function Name: afe_Abn_WDT_Overflow_Chk
* Description  : Detect WDT interrupt re-assertion while ISR is servicing current event.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void afe_Abn_WDT_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_ABN_WDT_IR])
	{
		AFE_Int_HwOvf_Set(E_AFE_EVENT_WDT);
	}
}
