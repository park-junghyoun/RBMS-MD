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
* File Name		: RBMS-MD.h
* Contents		: RBMS-M Driver Hher
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#include "afe.h"

static volatile U32 u32_Pending_bitmap = 0;
static volatile U8 u8_Sw_Ovf = 0;
void Stop_Mode(void);

/* ===== ISR-safe Callback ===== */
void R_BMS_afe_callback(st_afe_callback_args_t *p_args)
{
	/*
	 * In ISR context, queue events into the bitmap instead of processing immediately.
	 * If the same event arrives again before it is handled, mark software overflow.
	 */
	MCU_PSW_PUSH();
	if(u32_Pending_bitmap & (1u << p_args->event))
	{
		u8_Sw_Ovf = ON;
		u32_Pending_bitmap = 0;
		//TODO: Software OverWrite
	}else
	{
		u32_Pending_bitmap |= (1u << p_args->event);
	}
	MCU_PSW_POP();

	//TODO:Use events that require quick processing.
	/*
	switch(u32_Pending_bitmap)
	{
		case E_AFE_EVENT_CC:
		break:
	}
	*/
}
void R_BMS_afe_event_hw_overflow(U32 ovf_flg)
{
	/* Clear each hardware-reported interrupt overflow bit individually. */
	if (ovf_flg & U32_AFE_INT_CC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_CC_BIT);
	}
	if (ovf_flg & U32_AFE_INT_AD_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_AD_BIT);
	}
	if (ovf_flg & U32_AFE_INT_SC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_SC_BIT);
	}
	if (ovf_flg & U32_AFE_INT_DOC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_DOC_BIT);
	}
	if (ovf_flg & U32_AFE_INT_COC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_COC_BIT);
	}
	if (ovf_flg & U32_AFE_INT_OV_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_OV_BIT);
	}
	if (ovf_flg & U32_AFE_INT_UV_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_UV_BIT);
	}
	if (ovf_flg & U32_AFE_INT_TA_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_TA_BIT);
	}
	if (ovf_flg & U32_AFE_INT_TB_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_TB_BIT);
	}
	if (ovf_flg & U32_AFE_INT_WDT_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_WDT_BIT);
	}
	if (ovf_flg & U32_AFE_INT_DWU_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_DWU_BIT);
	}
	if (ovf_flg & U32_AFE_INT_CWU_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_CWU_BIT);
	}
	if (ovf_flg & U32_AFE_INT_PON_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U32_AFE_INT_PON_BIT);
	}

}
void R_BMS_afe_event_process(void)
{
	/* Drain and handle pending events in main-loop context. */
	if(u32_Pending_bitmap & U32_AFE_INT_CC_BIT)
	{
		U32 ad = AFE_CI_Get_AdData();
		(void)ad;
		u32_Pending_bitmap &= ~U32_AFE_INT_CC_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_AD_BIT)
	{
		U16 ad = AFE_AD_Get_AdData(U64_AD_CV4);
		(void)ad;
		u32_Pending_bitmap &= ~U32_AFE_INT_AD_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_SC_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_SC_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_DOC_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_DOC_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_COC_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_COC_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_OV_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_OV_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_UV_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_UV_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_TA_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_TA_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_TB_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_TB_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_WDT_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_WDT_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_DWU_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_DWU_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_CWU_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_CWU_BIT;
	}
	if(u32_Pending_bitmap & U32_AFE_INT_PON_BIT)
	{
		u32_Pending_bitmap &= ~U32_AFE_INT_PON_BIT;
	}


}

/* ===== Main Loop Event Handler ===== */
void R_BMS_afe_event_handler(void)
{
	U32 u32_ovf_flg = 0;

	if(u32_Pending_bitmap)
	{
		R_BMS_afe_event_process();
	}
	
	u32_ovf_flg = AFE_Int_HwOvf_Get();
	
	if(u32_ovf_flg)
	{
		R_BMS_afe_event_hw_overflow(u32_ovf_flg);
	}
	
}

void R_BMS_afe_load_config(st_afe_config_t *cfg)
{
	/* Default sample config: disable WDT/OC and enable representative CV ADC channels. */
	cfg->u8_afe_clock = E_AFE_CLOCK_NORMAL;
	cfg->u8_afe_wdt_config = E_AFE_WDT_OFF;
	cfg->st_afe_hw1_config.st_sc_config.e_setting= E_AFE_OC_DISABLE;
	cfg->st_afe_hw1_config.st_odc_config.e_setting= E_AFE_OC_DISABLE;
	cfg->st_afe_hw1_config.st_occ_config.e_setting= E_AFE_OC_DISABLE;
	cfg->st_afe_adc_config.u64_adc_enable = U64_AD_CV1|U64_AD_CV2|U64_AD_CV3|U64_AD_CV4|U64_AD_CV5|U64_AD_CV10;
	cfg->st_afe_adc_config.u8_adc_time = 0x07;
	cfg->st_afe_adc_config.u8_adc_settime = 0x0A;


}

U8 R_BMS_afe_init(void)
{
	st_afe_init_result_t u8_init_result= {0,};
	st_afe_config_t cfg;
	
	AFE_Callback_ISR(R_BMS_afe_callback, PNULL);

	R_BMS_afe_load_config(&cfg);
	u8_init_result = AFE_Init(cfg);
	return u8_init_result.u8_init_result;
}
static U8 u8_afe_init;

U8 u8_reg_data = 0;
void main(void)
{
	/* Start measurement/protection blocks only after successful AFE initialization. */
	u8_afe_init = R_BMS_afe_init();

	if(u8_afe_init == TRUE)
	{
		AFE_AD_Start_SW_Trigger();
		AFE_CI_StartCC();
		AFE_FET_Set(ON, ON);
		AFE_TimerA_Con(ON);
		AFE_TimerB_Con(ON);
	}
	while (1)
	{
		/*
		 * Handle queued events first, then enter STOP mode.
		 * The next interrupt wakes the MCU and processing resumes in this loop.
		 */
		R_BMS_afe_event_handler();
		Stop_Mode();
	}
}

void Stop_Mode(void)
{
	/* Do not enter low-power mode while events are pending. */
	if(u32_Pending_bitmap) return;
	
	DI();
	WUP0 = 1;
	NOP();											// wait 3clock
	NOP();
	NOP();
	EI();											// Interrupt enable
	STOP();											// Stop mode
	NOP();								// wait 5clock
	NOP();
	NOP();
	NOP();
	NOP();
	WUP0 = 0;	
}

