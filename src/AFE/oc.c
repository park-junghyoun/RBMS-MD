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
* File Name		: oc.c
* Contents		: RAA241xxx Overcurrent Detection Circuit control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _OC_C

#include "define.h"
#include "afe.h"
#include "oc_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------
#pragma interrupt _int_AbnormalDtct(vect=U16_ANL_VECTOR_MAPPING)		// ANL interrupt
static void afe_DOC_Cailbration(void);
static void afe_COC_Cailbration(void);
static void afe_OC_WDT_Init(void);
static void afe_OC_SCC_Setting(U8 u8_scc_enable, U8 u8_sccmpv, U8 u8_scc_time );
static void afe_OC_DOC_Setting(U8 u8_doc_enable, U8 u8_docmpv, U16 u16_doc_time );
static void afe_OC_COC_Setting(U8 u8_coc_enable, U8 u8_cocmpv, U8 u8_coc_time );
static void afe_OC_Interrupt(U8 u8_onoff);
static void afe_SC_Overflow_Chk(void);
static void afe_DOC_Overflow_Chk(void);
static void afe_COC_Overflow_Chk(void);
static void afe_WDT_Overflow_Chk(void);
// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
void AFE_OC_Init(st_afe_hw1_config_t config)
{
	afe_OC_Interrupt(OFF);
	afe_OC_WDT_Init();
	afe_COC_Cailbration();
	afe_DOC_Cailbration();
	afe_OC_SCC_Setting(config.u8_sc_enable,config.st_thr.u8_sc_th,(U8)config.st_time.u16_sc_time);
	afe_OC_DOC_Setting(config.u8_doc_enable,config.st_thr.u8_sc_th,config.st_time.u16_doc_time);
	afe_OC_COC_Setting(config.u8_occ_enable,config.st_thr.u8_sc_th,(U8)config.st_time.u16_occ_time);
	afe_OC_Interrupt(ON);
}
void afe_OC_WDT_Init( void )
{
	AFE_Reg_Write(&AFE_AWDTCON,	( WDT_8S				// 8sec
								| WDT_MTRSEL_EN));		// MCU reset output enable
}
/*******************************************************************************
* Function Name: _int_CircuitShortCurrDtct
* Description  : Circuit short current detection
* Arguments    : void
* Return Value : void
*******************************************************************************/
void _int_AbnormalDtct( void )
{
	U8 u8_reg_data;
	
	f_AFE_Int_Opr = ON;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if( u8_reg_data & u8_ABIR_Data_Mapping[E_OC_SCD_IR])								//SDC interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_OC_SCD_IR]);
		f_AFE_SC_Int = ON;							// Set SC interrupt flag
		_INT_AFE_SC_Callback(u32_AFE_Int_Flg,u32_AFE_IntErr_Flg);
		afe_SC_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_ABIR_Data_Mapping[E_OC_DOC_IR])								// DOC interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_OC_DOC_IR]);
		f_AFE_DOC_Int = ON;							// Set DOC interrupt flag
		_INT_AFE_DOC_Callback(u32_AFE_Int_Flg,u32_AFE_IntErr_Flg);
		afe_DOC_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_ABIR_Data_Mapping[E_OC_COC_IR])								// COC interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_OC_COC_IR]);
		f_AFE_COC_Int = ON;							// Set DOC interrupt flag
		_INT_AFE_COC_Callback(u32_AFE_Int_Flg,u32_AFE_IntErr_Flg);
		afe_COC_Overflow_Chk();
	}

	if( u8_reg_data & u8_ABIR_Data_Mapping[E_OC_WDT_IR])							// WDT interrupt request
	{
		AFE_Reg_Write(p8_ABIF_Reg_Mapping,~u8_ABIR_Data_Mapping[E_OC_WDT_IR]);
		f_AFE_WDT_Int = ON; 						// Set DOC interrupt flag
		_INT_AFE_WDT_Callback(u32_AFE_Int_Flg,u32_AFE_IntErr_Flg);
		afe_WDT_Overflow_Chk();
	}
	
	f_AFE_Int_Opr = OFF;

}
void afe_OC_SCC_Setting(U8 u8_scc_enable, U8 u8_sccmpv, U8 u8_scc_time )
{
	U8 u8_sccmpv_data;
	U8 u8_scctime_data;

	if(u8_scc_enable > ON)
	{
		return;
	}
	
	if(u8_scc_time > U8_OC_SCCTIME_MAX)
	{
		u8_scctime_data = U8_OC_SCCTIME_MAX;
	}else if(u8_scc_time <= U8_OC_SCCTIME_MIN)
	{
		u8_scctime_data = U8_OC_SCCTIME_MIN;
	}else
	{
		u8_scctime_data = u8_scc_time;
	}

	if(u8_sccmpv > U8_OC_SCCMPV_MAX)
	{
		u8_sccmpv_data = U8_OC_SCCMPV_MAX;
	}else if(u8_sccmpv <= U8_OC_SCCMPV_MIN)
	{
		u8_sccmpv_data = U8_OC_SCCMPV_MIN;
	}else
	{
		u8_sccmpv_data = u8_sccmpv;
	}

	AFE_Reg_Write(p8_SCCTIME_Reg_Mapping,u8_scctime_data);

	AFE_Reg_Write(p8_SCCCON_Reg_Mapping,u8_SCCCON_Data_Mapping[u8_scc_enable]|u8_sccmpv_data);
}
void afe_OC_DOC_Setting(U8 u8_doc_enable, U8 u8_docmpv, U16 u16_doc_time )
{
	U8 u8_docmpv_data;
	U16 u16_doctime_data;

	if(u8_doc_enable > ON)
	{
		return;
	}
	
	if(u16_doc_time > U16_OC_DOCTIME_MAX)
	{
		u16_doctime_data = U16_OC_DOCTIME_MAX;
	}else if(u16_doc_time <= U16_OC_DOCTIME_MIN)
	{
		u16_doctime_data = U16_OC_DOCTIME_MIN;
	}else
	{
		u16_doctime_data = u16_doc_time;
	}

	if(u8_docmpv > U8_OC_DOCMPV_MAX)
	{
		u8_docmpv_data = U8_OC_DOCMPV_MAX;
	}else if(u8_docmpv <= U8_OC_DOCMPV_MIN)
	{
		u8_docmpv_data = U8_OC_DOCMPV_MIN;
	}else
	{
		u8_docmpv_data = u8_docmpv;
	}

	AFE_Reg_Write(p8_DOCTIME1_Reg_Mapping,(U8)(u16_doctime_data&0xFF));
	AFE_Reg_Write(p8_DOCTIME2_Reg_Mapping,(U8)(u16_doctime_data>>8));

	AFE_Reg_Write(p8_DOCCON_Reg_Mapping,u8_DOCCON_Data_Mapping[u8_doc_enable]|u8_docmpv_data);
}
void afe_OC_COC_Setting(U8 u8_coc_enable, U8 u8_cocmpv, U8 u8_coc_time )
{
	U8 u8_cocmpv_data;
	U8 u8_coctime_data;

	if(u8_coc_enable > ON)
	{
		return;
	}
	
	if(u8_coc_time > U8_OC_COCTIME_MAX)
	{
		u8_coctime_data = U8_OC_COCTIME_MAX;
	}else if(u8_coc_time <= U8_OC_COCTIME_MIN)
	{
		u8_coctime_data = U8_OC_COCTIME_MIN;
	}else
	{
		u8_coctime_data = u8_coc_time;
	}

	if(u8_cocmpv > U8_OC_DOCMPV_MAX)
	{
		u8_cocmpv_data = U8_OC_DOCMPV_MAX;
	}else if(u8_cocmpv <= U8_OC_DOCMPV_MIN)
	{
		u8_cocmpv_data = U8_OC_DOCMPV_MIN;
	}else
	{
		u8_cocmpv_data = u8_cocmpv;
	}

	AFE_Reg_Write(p8_COCTIME_Reg_Mapping,u8_coctime_data);

	AFE_Reg_Write(p8_COCCON_Reg_Mapping,u8_COCCON_Data_Mapping[u8_coc_enable]|u8_cocmpv_data);
}
void afe_DOC_Cailbration(void)
{
	U8 u8_docsts = 0;												// OCDSTS register read
	U8 u8_doccal_val = u8_DOCCAL_InitVal_Mapping;						// work for calibration value
	
	AFE_WindowTo(WINDOW1);						// AFE Window 1
	AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,u8_DOCCAL_Data_Mapping[ON] | u8_doccal_val);					// DOC calibration enabled
	AFE_WindowTo(WINDOW0);						// AFE Window 0
	AFE_Reg_Write(p8_DOCTIME1_Reg_Mapping,(U8)U16_OC_DOCTIME_MIN&0xFF);							// detectiom time 488[us] * 1 = 488[us]
	AFE_Reg_Write(p8_DOCTIME2_Reg_Mapping,(U8)U16_OC_DOCTIME_MIN>>8);
	AFE_Reg_Write(p8_DOCCON_Reg_Mapping,u8_DOCCON_Data_Mapping[ON]);						// DOC1 detection curcuit enabled

	MCU_TM03_100usWaitTime();
	
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
				AFE_WindowTo(WINDOW1);			// AFE Window 1
				AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,p8_DOCCAL_Reg_Mapping[OFF] | u8_doccal_val);					// DOCCAL calibration value setting & DOC calibration disabled
				AFE_WindowTo(WINDOW0);			// AFE Window 0
				break;

			}
		}else
		{
			AFE_WindowTo(WINDOW1);				// AFE Window 1
			AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,p8_DOCCAL_Reg_Mapping[OFF] | u8_doccal_val);			// Set DOC calibration value
			AFE_WindowTo(WINDOW0);				// AFE Window 0
			break;
		}
		AFE_WindowTo(WINDOW1);					// AFE Window 1
		AFE_Reg_Write(p8_DOCCAL_Reg_Mapping,u8_DOCCAL_Data_Mapping[ON] | u8_doccal_val);				// DOC calibration enabled & calibration value
		AFE_WindowTo(WINDOW0);					// AFE Window 0
		AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_DOC_Mapping);					// Discharge detection flag clear
		AFE_TimerB_Con(ON);
		while(f_AFE_TIMERB_Int == OFF);
		AFE_TimerB_Con(OFF);
		f_AFE_TIMERB_Int = OFF;	
	
	}while(1);	
	AFE_Reg_Write(p8_DOCCON_Reg_Mapping,u8_DOCCON_Data_Mapping[OFF]);						// DOC1 detection curcuit disabled
	AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_DOC_Mapping);						// DOC1 detection flag clear

}
void afe_COC_Cailbration(void)
{
	U8 u8_cocsts = 0;												// OCDSTS register read
	U8 u8_coccal_val = u8_COCCAL_InitVal_Mapping;						// work for calibration value
	
	AFE_WindowTo(WINDOW1);						// AFE Window 1
	AFE_Reg_Write(p8_COCCAL_Reg_Mapping,u8_COCCAL_Data_Mapping[ON] | u8_coccal_val);					// DOC calibration enabled
	AFE_WindowTo(WINDOW0);						// AFE Window 0
	AFE_Reg_Write(p8_COCTIME_Reg_Mapping,U8_OC_COCTIME_MIN);
	AFE_Reg_Write(p8_COCCON_Reg_Mapping,u8_COCCON_Data_Mapping[ON]);						// DOC1 detection curcuit enabled
	
	AFE_TimerB_Con(ON);
	while(f_AFE_TIMERB_Int == OFF);
	AFE_TimerB_Con(OFF);
	f_AFE_TIMERB_Int= OFF;
	
	do{	
		if(u8_coccal_val != 0x00)
		{
			AFE_Reg_Read(p8_OCDSTS_Reg_Mapping,1,&u8_cocsts);			
			if(u8_cocsts & u8_OCDRSTS_DOC_Mapping)
			{
				u8_coccal_val--;
			}else
			{
				u8_coccal_val++;
				AFE_WindowTo(WINDOW1);			// AFE Window 1
				AFE_Reg_Write(p8_COCCAL_Reg_Mapping,p8_COCCAL_Reg_Mapping[OFF] | u8_coccal_val);					// DOCCAL calibration value setting & DOC calibration disabled
				AFE_WindowTo(WINDOW0);			// AFE Window 0
				break;

			}
		}else
		{
			AFE_WindowTo(WINDOW1);				// AFE Window 1
			AFE_Reg_Write(p8_COCCAL_Reg_Mapping,p8_COCCAL_Reg_Mapping[OFF] | u8_coccal_val);			// Set DOC calibration value
			AFE_WindowTo(WINDOW0);				// AFE Window 0
			break;
		}
		AFE_WindowTo(WINDOW1);					// AFE Window 1
		AFE_Reg_Write(p8_COCCAL_Reg_Mapping,p8_COCCAL_Reg_Mapping[ON] | u8_coccal_val);				// DOC calibration enabled & calibration value
		AFE_WindowTo(WINDOW0);					// AFE Window 0
		AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_COC_Mapping);					// Discharge detection flag clear
		AFE_TimerB_Con(ON);
		while(f_AFE_TIMERB_Int == OFF);
		AFE_TimerB_Con(OFF);
		f_AFE_TIMERB_Int = OFF;
	
	}while(1);	
	AFE_Reg_Write(p8_COCCON_Reg_Mapping,u8_COCCON_Data_Mapping[OFF]);						// DOC1 detection curcuit disabled
	AFE_Reg_Write(p8_OCORSTS_Reg_Mapping,u8_OCDRSTS_COC_Mapping);						// DOC1 detection flag clear

}

void afe_OC_Interrupt(U8 u8_onoff)
{
	U8 u8_reg_data;
	
	AFE_Reg_Write(p8_ABIF_Reg_Mapping,~( p8_ABIF_Reg_Mapping[E_OC_SCD_IR] | p8_ABIF_Reg_Mapping[E_OC_DOC_IR] | p8_ABIF_Reg_Mapping[E_OC_COC_IR] | p8_ABIF_Reg_Mapping[E_OC_WDT_IR]));

	AFE_Reg_Read(p8_ABIRMK_Reg_Mapping,1,&u8_reg_data);
	if(u8_onoff == ON)
	{
		u8_reg_data |= (u8_ABIRMK_Data_Mapping[E_OC_SCD_IR] | u8_ABIRMK_Data_Mapping[E_OC_DOC_IR] | u8_ABIRMK_Data_Mapping[E_OC_COC_IR] | u8_ABIRMK_Data_Mapping[E_OC_WDT_IR]);
	}else
	{
		u8_reg_data &= ~(u8_ABIRMK_Data_Mapping[E_OC_SCD_IR] | u8_ABIRMK_Data_Mapping[E_OC_DOC_IR] | u8_ABIRMK_Data_Mapping[E_OC_COC_IR] | u8_ABIRMK_Data_Mapping[E_OC_WDT_IR]);
	}
	AFE_Reg_Write(p8_ABIRMK_Reg_Mapping,u8_reg_data);
}
void afe_SC_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_OC_SCD_IR])
	{
		f_AFE_SC_Int = ON;
	}
}
void afe_COC_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_OC_COC_IR])
	{
		f_AFE_COC_Int = ON;
	}
}
void afe_DOC_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_OC_DOC_IR])
	{
		f_AFE_DOC_Int = ON;
	}
}
void afe_WDT_Overflow_Chk(void)
{
	U8 u8_reg_data;
	
	AFE_Reg_Read(p8_ABIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ABIR_Data_Mapping[E_OC_WDT_IR])
	{
		f_AFE_WDT_Int = ON;
	}
}