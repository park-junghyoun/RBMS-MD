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
* Contents		: ADC channel setup, conversion control, and conversion-result access
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
typedef union {
	U16		data;				// ADC raw count
	U8		buffer[sizeof(U16)];
}U_AD_ADC;

// - Internal variable ---------------------------------------------------------
static U16 u16_get_adc[E_AFE_MEA_NUM];
static U8 u8_ad_enable_item[E_AD_MODE_NUM];									// include offset ad
static E_AFE_AD_ITEM e_ad_run_mode = E_AD_MODE_NUM;
static U_AD_ADC u_ad_adc_raw[U8_AD_MEA_SIZE];

// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: AFE_AD_Init
* Description  : Initialize ADC block and apply user ADC configuration.
* Arguments    : config : ADC enable/time configuration
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 AFE_AD_Init( st_afe_adc_config_t config )
{
	U8 u8_reg_check = TRUE;
	U8 u8_reg_data = 0;
	U8 u8_index = 0;

	// Buffer Init
	for(u8_index = 0; u8_index <E_AFE_MEA_NUM; u8_index++)
	{
		u16_get_adc[u8_index] = 0xFFFF;
	}
	
	AFE_Reg_Write(p8_ADIF_Reg_Mapping,~u8_ADIR_Data_Mapping);								// Clear IF flag
	
	u8_reg_check = AFE_AD_Setting(config);
	
	AFE_Reg_Read(p8_ADMK_Reg_Mapping,1,&u8_reg_data);
	AFE_Reg_Write(p8_ADMK_Reg_Mapping,u8_reg_data | u8_ADMK_Data_Mapping);

	return u8_reg_check;
}
/*******************************************************************************
* Function Name: AFE_AD_Setting
* Description  : Program AD enable map and conversion timing registers.
* Arguments    : config : ADC enable/time configuration
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 AFE_AD_Setting( st_afe_adc_config_t config )
{
	U64 u64_bit_mask = 0;
	U8 u8_mode_index = 0;
	U8 u8_ad_limit_settime = 0;
	U8 u8_ad_limit_time = 0;
	U8 u8_reg_check = TRUE;
	U8 u8_reg_data = 0;
	
	AFE_AD_Stop_SW_Trigger();
	// admsel buffer setting
	for(u8_mode_index = 0; u8_mode_index <E_AD_MODE_NUM; u8_mode_index++)
	{
		// Fleid mask
		u64_bit_mask = (1 << (u8_Mode_Real_Size[u8_mode_index]+1)) -1;
		// Fleid output
		u8_ad_enable_item[u8_mode_index] = (config.u64_adc_enable >> (U8_AD_MEA_SIZE *u8_mode_index)) & u64_bit_mask;
		//If the ADC you want to measure is not empty
		if(u8_ad_enable_item[u8_mode_index] != 0)
		{
			// include offset voltage
			u8_ad_enable_item[u8_mode_index] = (u8_ad_enable_item[u8_mode_index] << 1) +1;
			// Write ADMSEL
			AFE_Reg_Write(p8_ADMSEL_Reg_Mapping[u8_mode_index],u8_ad_enable_item[u8_mode_index]);
			// Check ADMSEL
			AFE_Reg_Read(p8_ADMSEL_Reg_Mapping[u8_mode_index],1, &u8_reg_data);
			if(u8_reg_data != u8_ad_enable_item[u8_mode_index])
			{
				u8_reg_check = FALSE;
			}
		}
		
	}
	// AD Time Setting
	if(config.u8_adc_settime > U8_AD_SETTIME_MAX)
	{
		u8_ad_limit_settime = U8_AD_SETTIME_MAX;
	}
	else
	{
		u8_ad_limit_settime = config.u8_adc_settime;
	}
	if(config.u8_adc_time > U8_AD_TIME_MAX)
	{
		u8_ad_limit_time = U8_AD_TIME_MAX;
	}
	else
	{
		u8_ad_limit_time = config.u8_adc_time;
	}

	u8_ad_limit_time = (U8)((u8_ad_limit_settime<<4)|(u8_ad_limit_time));
	
	AFE_Reg_Write(p8_ADTIME_Reg_Mapping,u8_ad_limit_time);
	// Check ADTIME
	AFE_Reg_Read(p8_ADTIME_Reg_Mapping,1, &u8_reg_data);
	if(u8_reg_data != u8_ad_limit_time)
	{
		u8_reg_check = FALSE;
	}

	return u8_reg_check;
}
/*******************************************************************************
* Function Name: AFE_AD_Start_SW_Trigger
* Description  : Start ADC software-trigger conversion sequence.
* Arguments    : void
* Return Value : U8 : TRUE/FALSE
*******************************************************************************/
U8 AFE_AD_Start_SW_Trigger( void )
{
	U8 u8_index = 0;
	
	if( f_AFE_AD_Run == ON)
	{
		return FALSE;
	}
	
	f_AFE_AD_Run  = ON;
	e_ad_run_mode = E_AD_MODE1;
	// internal buffer Clear
	for(u8_index =0; u8_index < E_AFE_MEA_NUM; u8_index++)
	{
		u16_get_adc[u8_index] = 0xFFFF;
	}
	AFE_Reg_Write(p8_ADCEN_Reg_Mapping, u8_ADCEN_Data_Mapping[ON]);
	AFE_Reg_Write(p8_ADMODSEL_Reg_Mapping,u8_ADMODSEL_Data_Mapping[e_ad_run_mode]);

	return TRUE;
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
	f_AFE_AD_Run  = OFF;
	AFE_Reg_Write(p8_ADCEN_Reg_Mapping, u8_ADCEN_Data_Mapping[OFF]);
	e_ad_run_mode = E_AD_MODE1;
}

/*******************************************************************************
* Function Name: AFE_AD_Get_AdData
* Description  : Read last converted ADC value for selected measurement item.
* Arguments    : u8_ad_num : Measurement item index
* Return Value : U16 : Converted raw ADC value
*******************************************************************************/
U16 AFE_AD_Get_AdData( E_AFE_MEA_MODE_ITEM u8_ad_num )
{
	U16 u16_ad = 0;
	
	if(u8_ad_num >= 0x24)
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
* Arguments    : void
* Return Value : void
*******************************************************************************/
void afe_ReadAD( void )
{
	U8 u8_ad_index = 0;

	// Mode Check
	if(e_ad_run_mode >= E_AD_MODE_NUM)
	{
		return;
	}
	// AFE Register Read
	AFE_Reg_Read(p8_ADR_Reg_Mapping, u8_Mode_Real_Size[e_ad_run_mode]*2,u_ad_adc_raw[0].buffer);

	for(u8_ad_index = 0; u8_ad_index <u8_Mode_Real_Size[e_ad_run_mode]; u8_ad_index++)
	{
		//Enable item?
		if(u8_ad_enable_item[e_ad_run_mode]>>(u8_ad_index+1) & 0x01)
		{
			// Get adc
			u16_get_adc[(U8_AD_MEA_SIZE*e_ad_run_mode)+u8_ad_index] = u_ad_adc_raw[u8_ad_index].data;
		}
	}
}
/*******************************************************************************
* Function Name: afe_SW_TriggerAD
* Description  : 
* Arguments    : 
* Return Value : 
*******************************************************************************/
void afe_SW_TriggerAD( void )
{
	U8 u8_item_index = 0;
	
	if(e_ad_run_mode >= E_AD_MODE_NUM)
	{
		AFE_DispatchFrom_ISR(E_AFE_EVENT_AD);
		f_AFE_AD_Run  = OFF;
		return;
		
	}
	//find enable mode index 
	for(u8_item_index =e_ad_run_mode; u8_item_index < E_AD_MODE_NUM; u8_item_index++)
	{
		if(u8_ad_enable_item[e_ad_run_mode] == NULL)
		{
			e_ad_run_mode++;	
			if(e_ad_run_mode >= E_AD_MODE_NUM)
			{
				AFE_DispatchFrom_ISR(E_AFE_EVENT_AD);
				f_AFE_AD_Run  = OFF;
				return;
			}
		}
	}
	AFE_Reg_Write(p8_ADCEN_Reg_Mapping, u8_ADCEN_Data_Mapping[ON]);
	e_ad_run_mode++;
	AFE_Reg_Write(p8_ADMODSEL_Reg_Mapping,u8_ADMODSEL_Data_Mapping[e_ad_run_mode]);
}
/*******************************************************************************
* Function Name: _int_AD_Comple
* Description  : 
* Arguments    : 
* Return Value : 
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
/*******************************************************************************
* Function Name: afe_AD_Overflow_Chk
* Description  : 
* Arguments    : 
* Return Value : 
*******************************************************************************/
void afe_AD_Overflow_Chk( void )
{
	U8 u8_reg_data = 0;
	
	AFE_Reg_Read(p8_ADIF_Reg_Mapping,1,&u8_reg_data);
	
	if(u8_reg_data & u8_ADIR_Data_Mapping)
	{
		f_AFE_AD_Int_OVF = ON;
	}
}


