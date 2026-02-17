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
* File Name		: wkup.c
* Contents		: RAA241xxx Wakeup Current Detection Circuit control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _WKUP_C

#include "define.h"
#include "afe.h"
#include "wkup_mapping.h"
#include "device_register.h"



// - Declare Internal function -------------------------------------------------
#pragma interrupt _int_WakeUpDtct(vect=U16_WKUP_VECTOR_MAPPING)							// Wakeup
static U8 afe_WKUP_Setting(st_afe_wkup_config_t st_wkup_chg_setting, st_afe_wkup_config_t st_wkup_dsg_setting, U8 u8_wkup_time);
static U8 afe_WKUP_Interrupt(U8 u8_onoff);
static void afe_WKUP_Chg_ReStart(void);
static void afe_WKUP_Dsg_ReStart(void);
static void afe_WKUP_Get(void);
static void afe_PON_Overflow_Chk(void);
static void afe_DWU_Overflow_Chk(void);
static void afe_CWU_Overflow_Chk(void);
static U8 afe_WKUP_Pon_Setting(U8 u8_pon_en);

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
U8 AFE_WKUP_Init(st_afe_hw2_config_t st_afe_wakeup_config)
{
	U8 init_seq = TRUE;

	init_seq = afe_WKUP_Interrupt(OFF);
	if(init_seq == FALSE)
	{
		return init_seq;
	}

	init_seq = afe_WKUP_Setting(st_afe_wakeup_config.st_chg_wkup_config,st_afe_wakeup_config.st_dsg_wkup_config, st_afe_wakeup_config.u8_dsgchg_wkup_time);
	if(init_seq == FALSE)
	{
		return init_seq;
	}
	init_seq = afe_WKUP_Pon_Setting(st_afe_wakeup_config.u8_pon_wkup_config);
	if(init_seq == FALSE)
	{
		return init_seq;
	}
	init_seq = afe_WKUP_Interrupt(ON);
	if(init_seq == FALSE)
	{
		return init_seq;
	}

	return init_seq;
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
U8 afe_WKUP_Setting(st_afe_wkup_config_t st_wkup_chg_setting, st_afe_wkup_config_t st_wkup_dsg_setting, U8 u8_wkup_time)
{
	U8	u8_wkup_limittime = 0;
	U8	u8_wkup_limitcmpv = 0;
	U8	u8_wkup_limitdmpv = 0;
	U8	u8_wkup_limitcgain = 0;
	U8	u8_wkup_limitdgain = 0;
	U8	u8_wkup_limitcfet = 0;
	U8	u8_wkup_limitdfet = 0;
	
	// Setting Wakeup Time
	if(u8_wkup_time <= U8_WKUP_TIME_MIN)
	{
		u8_wkup_limittime = U8_WKUP_TIME_MIN;
	}else if(u8_wkup_time > U8_WKUP_TIME_MAX)
	{
		u8_wkup_limittime = U8_WKUP_TIME_MAX;
	}else
	{
		u8_wkup_limittime = u8_wkup_time;
	}
	AFE_Reg_Write(p8_WKUPTIME_Reg_Mapping, u8_wkup_limittime);						// Set Wakeup det.time
	// Setting Charge Wakeup
	AFE_WKUP_Chg_Control(OFF);
	if( st_wkup_chg_setting.e_setting > E_AFE_WKUP_ENABLE_FET)
	{
		return FALSE;
	}
	if( st_wkup_chg_setting.e_setting == E_AFE_WKUP_DISABLE)
	{
		// Not Thing
	}else
	{
		if(st_wkup_chg_setting.u8_thresholds<= U8_WKUP_CHG_MIN)
		{
			u8_wkup_limitcmpv = U8_WKUP_CHG_MIN;
		}else if(st_wkup_chg_setting.u8_thresholds >= U8_WKUP_CHG_MAX)
		{
			u8_wkup_limitcmpv = U8_WKUP_CHG_MAX;
		}else
		{
			u8_wkup_limitcmpv = st_wkup_chg_setting.u8_thresholds;
		}
		if(st_wkup_chg_setting.e_gain >= E_WKUP_GAIN_ITEM_NUM)
		{
			return FALSE;
		}
		
		if(st_wkup_chg_setting.e_setting == E_AFE_WKUP_ENABLE_FET)
		{
			u8_wkup_limitcfet = ON;
		}else
		{
			u8_wkup_limitcfet = OFF;
		}
		AFE_Reg_Write(p8_WKUPCMPV_Reg_Mapping, u8_wkup_limitcmpv);
		AFE_Reg_Write(p8_WKUPCCON_Reg_Mapping, u8_WKUPCCON_Data_Mapping[u8_wkup_limitcgain][u8_wkup_limitcfet]);
	}

	// Setting Discharge Wakeup
	AFE_WKUP_Dsg_Control(OFF);
	if( st_wkup_dsg_setting.e_setting > E_AFE_WKUP_ENABLE_FET)
	{
		return FALSE;
	}
	if( st_wkup_dsg_setting.e_setting == E_AFE_WKUP_DISABLE)
	{
		// Not Thing
	}else
	{
		if(st_wkup_dsg_setting.u8_thresholds<= U8_WKUP_DSG_MIN)
		{
			u8_wkup_limitcmpv = U8_WKUP_DSG_MIN;
		}else if(st_wkup_dsg_setting.u8_thresholds >= U8_WKUP_DSG_MAX)
		{
			u8_wkup_limitdmpv = U8_WKUP_DSG_MAX;
		}else
		{
			u8_wkup_limitdmpv = st_wkup_dsg_setting.u8_thresholds;
		}
		if(st_wkup_dsg_setting.e_gain >= E_WKUP_GAIN_ITEM_NUM)
		{
			return FALSE;
		}
		
		if(st_wkup_dsg_setting.e_setting == E_AFE_WKUP_ENABLE_FET)
		{
			u8_wkup_limitdfet = ON;
		}else
		{
			u8_wkup_limitdfet = OFF;
		}

		AFE_Reg_Write(p8_WKUPDMPV_Reg_Mapping, u8_wkup_limitdmpv);
		AFE_Reg_Write(p8_WKUPDCON_Reg_Mapping, u8_WKUPDCON_Data_Mapping[u8_wkup_limitdgain][u8_wkup_limitdfet]);
	}

	return TRUE;
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/

U8 AFE_WKUP_Dsg_Control(U8 u8_con)
{
	U8 u8_seq_check  = TRUE;
	U8 u8_reg_data = 0;

	if( u8_con > ON)
	{
		u8_seq_check = FALSE;
		return u8_seq_check;
	}

	AFE_Reg_Read(p8_WKUPDCON_Reg_Mapping,1,&u8_reg_data);
	if(u8_con == ON)
	{
		f_AFE_DSGWKUP_Run = ON;
		u8_reg_data |= u8_WKUPDCON_EN_Data_Mapping;
	}else
	{
		f_AFE_DSGWKUP_Run = OFF;
		u8_reg_data &= ~u8_WKUPDCON_EN_Data_Mapping;
	}
	AFE_Reg_Write(p8_WKUPDCON_Reg_Mapping, u8_reg_data);	
	afe_WKUP_Dsg_ReStart();

	return u8_seq_check;
}
U8 AFE_WKUP_Chg_Control(U8 u8_con)
{
	U8 u8_seq_check  = TRUE;
	U8 u8_reg_data = 0;

	if( u8_con > ON)
	{
		u8_seq_check = FALSE;
		return u8_seq_check;
	}
	AFE_Reg_Read(p8_WKUPCCON_Reg_Mapping,1,&u8_reg_data);
	if(u8_con == ON)
	{
		f_AFE_CHGWKUP_Run = ON;
		u8_reg_data |= u8_WKUPDCON_EN_Data_Mapping;
	}else
	{
		f_AFE_CHGWKUP_Run = OFF;
		u8_reg_data &= ~u8_WKUPDCON_EN_Data_Mapping;
	}
	AFE_Reg_Write(p8_WKUPDCON_Reg_Mapping, u8_reg_data);	
	afe_WKUP_Chg_ReStart();
	
	return u8_seq_check;
}
void afe_WKUP_Chg_ReStart(void)
{
	AFE_Reg_Write(p8_WKUPRESTART_Reg_Mapping, u8_WKUPCRESTART_Data_Mapping);
}
void afe_WKUP_Dsg_ReStart(void)
{
	AFE_Reg_Write(p8_WKUPRESTART_Reg_Mapping, u8_WKUPDRESTART_Data_Mapping);
}

/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
U8 afe_WKUP_Interrupt(U8 u8_onoff)
{
	U8 u8_seq_check = TRUE;
	U8 u8_reg_data = 0;
	U8 u8_reg_data2 = 0;
	
	if(u8_onoff > ON)
	{
		u8_seq_check = FALSE;
		return u8_seq_check;
	}
	
	AFE_Reg_Read(p8_WKUPIRMK_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_onoff == ON)
	{
		u8_reg_data |= (p8_WKUPIRMK_Reg_Mapping[E_WKUP_PON_IR] | p8_WKUPIRMK_Reg_Mapping[E_WKUP_CWU_IR] | p8_WKUPIRMK_Reg_Mapping[E_WKUP_DWU_IR]);
		u8_reg_data2 |= (p8_WKUPIRMK_Reg_Mapping[E_WKUP_PON_IR] | p8_WKUPIRMK_Reg_Mapping[E_WKUP_CWU_IR] | p8_WKUPIRMK_Reg_Mapping[E_WKUP_DWU_IR]);
	}else
	{
		u8_reg_data &= ~(p8_WKUPIRMK_Reg_Mapping[E_WKUP_PON_IR] | p8_WKUPIRMK_Reg_Mapping[E_WKUP_CWU_IR] | p8_WKUPIRMK_Reg_Mapping[E_WKUP_DWU_IR]);
	}
	u8_seq_check = AFE_WindowTo(E_AFE_WINDOW1);
	if(u8_seq_check == FALSE)
	{
		return u8_seq_check;
	}
	AFE_Reg_Write(p8_WKUPDICON_Reg_Mapping,	u8_WKUPDICON_Data_Mapping[E_WKUP_CWU_IR] | u8_WKUPDICON_Data_Mapping[E_WKUP_DWU_IR]);
	u8_seq_check = AFE_WindowTo(E_AFE_WINDOW0);
	if(u8_seq_check == FALSE)
	{
		return u8_seq_check;
	}
	AFE_Reg_Write(p8_WKUPIRMK_Reg_Mapping,u8_reg_data);

	u8_reg_data = ~( u8_WKUPIR_Data_Mapping[E_WKUP_PON_IR] | u8_WKUPIR_Data_Mapping[E_WKUP_CWU_IR] | u8_WKUPIR_Data_Mapping[E_WKUP_DWU_IR]);
	AFE_Reg_Write(p8_WKUPIF_Reg_Mapping,u8_reg_data);

	return u8_seq_check;

}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
U8 afe_WKUP_Pon_Setting(U8 u8_pon_en)
{
	U8 u8_seq_check = TRUE;
	U8 u8_reg_data = 0;

	if( u8_pon_en > ON)
	{
		u8_seq_check = FALSE;
		return u8_seq_check;
	}
	if(u8_pon_en == ON)
	{
		f_AFE_PON_Run = ON;
		u8_reg_data = ON;
	}else
	{
		f_AFE_PON_Run = OFF;
		u8_reg_data = OFF;
	}
	u8_seq_check = AFE_WindowTo(E_AFE_WINDOW1);	// Window = 1
	if(u8_seq_check == FALSE)
	{
		f_AFE_PON_Run = OFF;
		return u8_seq_check;
	}
	AFE_Reg_Write(p8_PONEG_Reg_Mapping,		u8_PONEG_Data_Mapping[u8_reg_data]);		// CHMON = Both edge
	u8_seq_check = AFE_WindowTo(E_AFE_WINDOW0);	// Window = 0
	if(u8_seq_check == FALSE)
	{
		f_AFE_PON_Run = OFF;
		return u8_seq_check;
	}
	return u8_seq_check;
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
void afe_WKUP_Get(void)
{
	U8 u8_Ret = 0;
	
	AFE_WindowTo(E_AFE_WINDOW1);	// Window = 1
	AFE_Reg_Read(p8_PONMON_Reg_Mapping, 1, &u8_Ret);				// Read HVMON
	AFE_WindowTo(E_AFE_WINDOW0);	// Window = 0
	if( u8_Ret == 0 )																	// VCHG pin == High( NOT Connected ) ?
	{
		f_AFE_PON_Status = ON;														// return value = High
	}
	else																				// VCHG pin == Low
	{
		f_AFE_PON_Status =  OFF;														// return value = Low
	}
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
void _int_WakeUpDtct(void)
{
	U8	u8_reg_data = 0;
	
	f_AFE_Int_Opr = ON;
	AFE_Reg_Read(p8_WKUPIF_Reg_Mapping, 1, &u8_reg_data);								// Read interrupt request reg.

	if( u8_reg_data & u8_WKUPIR_Data_Mapping[E_WKUP_PON_IR] )						// CHMON pin detect ?
	{
		AFE_Reg_Write(p8_WKUPIF_Reg_Mapping, ~u8_WKUPIR_Data_Mapping[E_WKUP_PON_IR]);// Clear interrupt request
		afe_WKUP_Get();
		AFE_DispatchFrom_ISR(E_AFE_EVENT_PON);
		afe_PON_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_WKUPIR_Data_Mapping[E_WKUP_DWU_IR]  )						// Discharge Wakeup detect ?
	{
		AFE_Reg_Write(p8_WKUPIF_Reg_Mapping, ~u8_WKUPIR_Data_Mapping[E_WKUP_DWU_IR]);// Clear interrupt request
		AFE_DispatchFrom_ISR(E_AFE_EVENT_DWU);
		f_AFE_DSGWKUP_Run = OFF;
		afe_DWU_Overflow_Chk();
	}
	
	if( u8_reg_data & u8_WKUPIR_Data_Mapping[E_WKUP_CWU_IR] )						// Charge Wakeup detect ?
	{
		AFE_Reg_Write(p8_WKUPIF_Reg_Mapping, ~u8_WKUPIR_Data_Mapping[E_WKUP_CWU_IR]);	// Clear interrupt request
		AFE_DispatchFrom_ISR(E_AFE_EVENT_CWU);
		f_AFE_CHGWKUP_Run = OFF;
		afe_CWU_Overflow_Chk();
	}
	
	f_AFE_Int_Opr = OFF;
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
void afe_PON_Overflow_Chk(void)
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_WKUPIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_WKUPIR_Data_Mapping[E_WKUP_PON_IR])
	{
		f_AFE_PON_Int_OVF = ON;
	}
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
void afe_DWU_Overflow_Chk(void)
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_WKUPIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_WKUPIR_Data_Mapping[E_WKUP_DWU_IR])
	{
		f_AFE_DWU_Int_OVF = ON;
	}
}
/*******************************************************************************
* Function Name: AFE_GetFETstatus
* Description  : Get VCHG pin status
* Arguments    : void
* Return Value : U8 : 1:High(NOT Connected), 0:Low(Connected)
*******************************************************************************/
void afe_CWU_Overflow_Chk(void)
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_WKUPIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_WKUPIR_Data_Mapping[E_WKUP_CWU_IR])
	{
		f_AFE_CWU_Int_OVF = ON;
	}
}


