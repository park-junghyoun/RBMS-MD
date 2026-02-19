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

static volatile U16 u16_Pending_bitmap = 0;
static volatile U8  au8_Pending_count[E_AFE_EVENT_NUM] = {0};

static volatile U8 u8_Sw_Ovf = 0;
void Stop_Mode(void);

/* ===== ISR-safe Callback ===== */
void R_BMS_afe_callback(st_afe_callback_args_t *p_args)
{
	MCU_PSW_PUSH();
	if (p_args->e_event < E_AFE_EVENT_NUM)
	{
		if (au8_Pending_count[p_args->e_event] < 0xFFu)
		{
			au8_Pending_count[p_args->e_event]++;
			u16_Pending_bitmap |= ((U32)1u << p_args->e_event);
		}
		else
		{
			u8_Sw_Ovf = ON;
			//TODO: Software OverFlow (per-event queue overflow)
		}
	}else
	{
		u8_Sw_Ovf = ON;
		//TODO: Software OverFlow (per-event queue overflow)

	}
	MCU_PSW_POP();
}
void R_BMS_afe_event_hw_overflow(U32 ovf_flg)
{
	if (ovf_flg & U16_AFE_INT_CC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_CC_BIT);
	}
	if (ovf_flg & U16_AFE_INT_AD_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_AD_BIT);
	}
	if (ovf_flg & U16_AFE_INT_SC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_SC_BIT);
	}
	if (ovf_flg & U16_AFE_INT_DOC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_DOC_BIT);
	}
	if (ovf_flg & U16_AFE_INT_COC_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_COC_BIT);
	}
	if (ovf_flg & U16_AFE_INT_TA_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_TA_BIT);
	}
	if (ovf_flg & U16_AFE_INT_TB_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_TB_BIT);
	}
	if (ovf_flg & U16_AFE_INT_WDT_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_WDT_BIT);
	}
	if (ovf_flg & U16_AFE_INT_DWU_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_DWU_BIT);
	}
	if (ovf_flg & U16_AFE_INT_CWU_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_CWU_BIT);
	}
	if (ovf_flg & U16_AFE_INT_PON_BIT)
	{
		//TODO : Over Flow Error
		AFE_Int_HwOvf_Clear(U16_AFE_INT_PON_BIT);
	}

}
U32 u32_ad;
U16 u16_ad;
U16 u16_error;
static void R_BMS_afe_process_event_count(E_AFE_EVENT_ITEM e_event, U8 u8_count)
{
	while (u8_count)
	{
		switch (e_event)
		{
			case E_AFE_EVENT_CC:
			{
				u32_ad = AFE_CI_Get_AdData();
				AFE_AD_Start_SW_Trigger();
				break;
			}
			case E_AFE_EVENT_AD:
			{
				u16_ad = AFE_AD_Get_AdData(E_AFE_MEA_CELL1);
				break;
			}
			case E_AFE_EVENT_SC:
				break;
			case E_AFE_EVENT_DOC:
				break;
			case E_AFE_EVENT_COC:
				break;
			case E_AFE_EVENT_TIMERA:
				break;
			case E_AFE_EVENT_TIMERB:
				break;
			case E_AFE_EVENT_WDT:
				break;
			case E_AFE_EVENT_DWU:
				break;
			case E_AFE_EVENT_CWU:
				break;
			case E_AFE_EVENT_PON:
				break;
			case E_AFE_EVENT_ERROR:
				u16_error = AFE_System_Get_Error();
				break;
			default:
				/* TODO: add event-specific handling */
				break;
		}
		u8_count--;
	}
}
static void R_BMS_afe_take_pending_snapshot(U8 *au8_snapshot, U16 *pu16_bitmap)
{
	U8 u8_idx;

	MCU_PSW_PUSH();
	*pu16_bitmap = u16_Pending_bitmap;
	u16_Pending_bitmap = 0;

	for (u8_idx = 0; u8_idx < E_AFE_EVENT_NUM; u8_idx++)
	{
		au8_snapshot[u8_idx] = au8_Pending_count[u8_idx];
		au8_Pending_count[u8_idx] = 0;
	}
	MCU_PSW_POP();
}

void R_BMS_afe_event_process(void)
{
	U8 au8_snapshot[E_AFE_EVENT_NUM] = {0};
	U16 u16_snapshot_bitmap = 0;
	U8 u8_event;

	/*
	 * Snapshot-and-clear quickly in a critical section,
	 * then process outside ISR lock to reduce latency.
	 */
	R_BMS_afe_take_pending_snapshot(au8_snapshot, &u16_snapshot_bitmap);

	for (u8_event = 0; u8_event < E_AFE_EVENT_NUM; u8_event++)
	{
		if (u16_snapshot_bitmap & ((U16)1u << u8_event))
		{
			R_BMS_afe_process_event_count((E_AFE_EVENT_ITEM)u8_event, au8_snapshot[u8_event]);
		}
	}

}

/* ===== Main Loop Event Handler ===== */
void R_BMS_afe_event_handler(void)
{

	if(u16_Pending_bitmap)
	{
		R_BMS_afe_event_process();
	}
	
}

void R_BMS_afe_load_config(st_afe_config_t *cfg)
{
	cfg->e_afe_clock = E_AFE_CLOCK_NORMAL;
	cfg->e_afe_wdt_config = E_AFE_WDT_OFF;
	cfg->st_afe_hw1_config.st_sc_config.e_setting= E_AFE_OC_DISABLE;
	cfg->st_afe_hw1_config.st_odc_config.e_setting= E_AFE_OC_DISABLE;
	cfg->st_afe_hw1_config.st_occ_config.e_setting= E_AFE_OC_DISABLE;
	cfg->st_afe_adc_config.u64_adc_enable = U64_AD_CV1|U64_AD_CV2|U64_AD_CV3|U64_AD_CV4|U64_AD_CV5|U64_AD_CV10;
	cfg->st_afe_adc_config.u8_adc_time = 0x07;
	cfg->st_afe_adc_config.u8_adc_settime = 0x0A;


}

U8 R_BMS_afe_init(void)
{
	st_afe_driver_info_t u8_init_result= {0,};
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
	u8_afe_init = R_BMS_afe_init();

	if(u8_afe_init == TRUE)
	{
		AFE_AD_Start_SW_Trigger();
		AFE_CI_Start();
		AFE_FET_Set(ON, ON);
		AFE_TimerA_Control(ON);
		AFE_TimerB_Control(ON);
	}
	while (1)
	{

		//AFE_Reg_Read(&AFE_AFIF3,1,&u8_reg_data);
		R_BMS_afe_event_handler();
		Stop_Mode();
	}
}

void Stop_Mode(void)
{
	if(u16_Pending_bitmap) return;
	
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


