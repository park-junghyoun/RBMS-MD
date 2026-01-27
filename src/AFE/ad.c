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
* File Name		: ad.c
* Contents		: RAA241xxx Sigma-delta A/D Converter control
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _AD_C

#include "define.h"
#include "afe.h"
#include "ad_mapping.h"
#include "device_register.h"


// - Declare Internal function -------------------------------------------------
#pragma interrupt _int_AD_Comple(vect=U16_INTAD_VECTOR_MAPPING)				// AFE interval timer interrupt

static void afe_ReadAD( void );
static void afe_SW_TriggerAD( void );
static void afe_AD_Overflow_Chk( void );

// - Internal constant ---------------------------------------------------------

// - Internal variable ---------------------------------------------------------
static U16 u16_get_adc[U8_TOTAL_ADC_COUNT];
static U8 u8_ad_enable_item[E_AD_ITEM_NUM];
static E_AFE_AD_ITEM e_ad_run_mode = E_AD_ITEM_NUM;

// - Define function -----------------------------------------------------------
void AFE_AD_Init( st_afe_ad_config_t config )
{
	U8 u8_reg_data = 0;

	AFE_AD_Setting(config);
	
	AFE_Reg_Read(p8_ADMK_Reg_Mapping,1,&u8_reg_data);
	AFE_Reg_Write(p8_ADMK_Reg_Mapping,u8_reg_data | u8_ADMK_Data_Mapping);
}
/*******************************************************************************
* Function Name: AD_Setting_ADEn
* Description  : Enable A/D conversion
* Caution      : Select and enable the AD to operate.
* Arguments    : u64_ad_enable : Bit table
*	              : E_AFE_AD_SETTINGTIME : AD setting time
*	              : E_AFE_AD_TIME : AD conversion time
* Return Value : void
*******************************************************************************/
void AFE_AD_Setting( st_afe_ad_config_t config )
{
	U64 u64_bit_mask = 0;
	U8 u8_index1 = 0;
	U8 u8_ad_limit_settime = 0;
	U8 u8_ad_limit_time = 0;

	
	AFE_AD_Stop_SW_Trigger();
	// admsel buffer setting
	for(u8_index1 = 0; u8_index1 <E_AD_ITEM_NUM; u8_index1++)
	{
		// Fleid mask
		u64_bit_mask = (1<<u8_Mode_Size[u8_index1]) - 1;
		// Fleid output
		u8_ad_enable_item[u8_index1] = (config.u64_ad_enable >> u8_Mode_Start_index[u8_index1]) & u64_bit_mask;
		
		AFE_Reg_Write(p8_ADMSEL_Reg_Mapping[u8_index1],u8_ad_enable_item[u8_index1]);
	}
	if(config.u8_ad_settime > U8_AD_SETTIME_MAX)
	{
		u8_ad_limit_settime = U8_AD_SETTIME_MAX;
	}
	else
	{
		u8_ad_limit_settime = config.u8_ad_settime;
	}
	if(config.u8_ad_time > U8_AD_TIME_MAX)
	{
		u8_ad_limit_time = U8_AD_TIME_MAX;
	}
	else
	{
		u8_ad_limit_time = config.u8_ad_time;
	}

	u8_ad_limit_time = (U8)((u8_ad_limit_settime<<4)|(u8_ad_limit_time));
	
	AFE_Reg_Write(p8_ADTIME_Reg_Mapping,u8_ad_limit_time);


}
/*******************************************************************************
* Function Name: AD_Start_SW_Trigger
* Description  : Start A/D conversion
* Caution      : Start AD to operate.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_AD_Start_SW_Trigger( void )
{
	e_ad_run_mode = E_AD_MODE1;
	AFE_Reg_Write(p8_ADCEN_Reg_Mapping, u8_ADCEN_Data_Mapping[ON]);
}
/*******************************************************************************
* Function Name: AD_Stop_SW_Trigger
* Description  : Stop A/D conversion
* Caution      : Stop AD to operate.
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_AD_Stop_SW_Trigger( void )
{
	AFE_Reg_Write(p8_ADCEN_Reg_Mapping, u8_ADCEN_Data_Mapping[OFF]);
}

/*******************************************************************************
* Function Name: AD_Get_AdData(U8 u8_ad_num, U16 u16_ad )
* Description  : Set Ad data
* Caution      : ad input ad buffer
* Arguments    : u8_ad_num : ad number
*	              : u16_ad : AD data
* Return Value : void
*******************************************************************************/
U16 AFE_AD_Get_AdData( U8 u8_ad_num )
{
	U16 u16_ad = 0;
	
	if(u8_ad_num >= U8_TOTAL_ADC_COUNT)
	{
		u16_ad = U16_MAX;
	}else
	{
		u16_ad = u16_get_adc[u8_ad_num];
	}
	
	
return u16_ad;
}
/*******************************************************************************
* Function Name: AD_ReadAD
* Description  : AD read Register Read
* Caution      : ad input ad buffer
* Arguments    : void
* Return Value : void
*******************************************************************************/
void afe_ReadAD( void )
{
	U8 u8_ad_index = 0;
	U8 u8_ad_item[U8_MAX_MODE_SIZE];

	if(e_ad_run_mode >= E_AD_ITEM_NUM)
	{
		return;
	}

	AFE_Reg_Read(p8_ADR_Reg_Mapping, u8_Mode_Size[e_ad_run_mode],u8_ad_item);

	for(u8_ad_index = 0; u8_ad_index < u8_Mode_Size[e_ad_run_mode]; u8_ad_index++)
	{
		u16_get_adc[u8_Mode_Start_index[e_ad_run_mode]+u8_ad_index] = u8_ad_item[u8_ad_index];
	}
}

void afe_SW_TriggerAD( void )
{
	U8 u8_item_index = 0;
	
	if(e_ad_run_mode >= E_AD_ITEM_NUM)
	{
		AFE_Reg_Write(p8_ADCEN_Reg_Mapping, u8_ADCEN_Data_Mapping[OFF]);
		f_AFE_AD_Int = ON;
		_INT_AFE_AD_Callback(u32_AFE_Int_Flg,u32_AFE_IntErr_Flg);
		return;
		
	}
	//find enable mode index 
	for(u8_item_index = 0; u8_item_index < E_AD_ITEM_NUM; u8_item_index++)
	{
		if(u8_ad_enable_item[e_ad_run_mode] == NULL)
		{
			e_ad_run_mode++;	
		}
	}

	AFE_Reg_Write(p8_ADMODSEL_Reg_Mapping,u8_ADMODSEL_Data_Mapping[e_ad_run_mode]);
	
	e_ad_run_mode++;
}

/*******************************************************************************
* Function Name: _int_SwTrigAdComp
* Description  : End of Software trigger A/D
* Arguments    : void
* Return Value : void
*******************************************************************************/
void _int_AD_Comple( void )
{
	U8 u8_reg_data = 0;
	
	f_AFE_Int_Opr = ON;
	
	AFE_Reg_Read(p8_ADIF_Reg_Mapping,1,&u8_reg_data);

	if(u8_reg_data & u8_ADIR_Data_Mapping)
	{
		AFE_Reg_Write(p8_ADIF_Reg_Mapping,~u8_ADIR_Data_Mapping);								// Clear IF flag
		afe_ReadAD();
		afe_SW_TriggerAD();
		afe_AD_Overflow_Chk();
	}

	f_AFE_Int_Opr= OFF;
}

void afe_AD_Overflow_Chk( void )
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_ADIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ADIR_Data_Mapping)
	{
		f_AFE_AD_Int_OVF = ON;
	}
}


