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
* System Name	: RAJ240xxx Smart Battery Standard firmware
* File Name		: dataflash_flexible.c
* Version		: 0.01
* Contents		: Data flash flexible data control
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx Standard firmware
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* Note			: Split from dataflash_custom.c
************************************************************************
* Copyright,2020 (2012-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2026.04.17 Ver 0.01
* 				: Split flexible implementation from dataflash_custom.c
*""FILE COMMENT END""*****************************************************/
#define _DATAFLASH_FLEXIBLE

#include "define.h"
#include "dataflash_flexible.h"
#include "dataflash.h"
#include <string.h>

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: DataFlash update check function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void DataFlash_update_check(void)
*-------------------------------------------------------------------
* Function			: Check request of DataFlash updating.
*					: And execute it if there is.
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: This function will be called from main().
*-------------------------------------------------------------------
* History			: 2020.12.01 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Request_FlexibleData_update(void)
{
	f_flex_update_req = ON;
}

void DataFlash_update_check(void)
{
	if( f_flex_update_req == ON )				// Flexible data update req. ?
	{
		if( Write_FlexibleData() )				// Execute & OK ?
		{
			f_flex_update_req = OFF;			// Clear the request
		}
		// Clear Flex. update RC counter
	}
	
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Flexible data read function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void FlexibleData_Read(void)
*-------------------------------------------------------------------
* Function			: FlexibleData_Read
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.10.30 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void FlexibleData_Read(void)
{
	U16	u16_tblock;
	U8	u8_index;

	DataFlash_Enable();								// Enable DataFlash access
	Search_FlexibleData_read(&u16_tblock, &u8_index);	// Search Flexible data
	if( u16_tblock != NULL )						// Is there valid data ?
	{
												// Copy from DataFlash to RAM
		memcpy(	(char*)&st_flexible_data_ram,
				(char*)(u16_tblock + FLEX_INDEX_SIZE +((U16)u8_index*FLEX_AREA_SIZE)),
				FLEX_SIZE);
	} else {									// No valid data
		memset((char*)&st_flexible_data_ram, 0, FLEX_SIZE);	// Set default data
	}
	DataFlash_Disable();								// Disable DataFlash access
}

U8 Write_FlexibleData(void)
{
	U16	u16_tblock;
	U8	u8_dfl_en;
	U8	u8_flex_index;
	U8	*p8_data;
	U8	u8_index;
	U8	u8_data;
	U8	u8_df_ret;

	// Note: It checks DFLEN condition for calling this function from
	//       interrupt. (To prevent unexpected clearing DFLEN by interrupt.)
	if( DFLEN == 1 )							// Already DFLEN = 1 ?
	{
		u8_dfl_en = 1;								// Record it.
	} else {
		u8_dfl_en = 0;
		DataFlash_Enable();							// Enable DataFlash access
	}
	
	Search_FlexibleData_write(&u16_tblock, &u8_flex_index);	// Search Flexible data
	
	if( f_flex_stop == ON && u8_flex_index > (FLEX_AREA_NUM - 3))// Stop Flex.data update ?
	{
		if( u8_dfl_en == 0 )						// DFLEN is set by this ?
		{
			DataFlash_Disable();						// Disable DataFlash access
		}
		return TRUE;
	}

	DataFlash_Enable();								// Enable DataFlash access
	// Note: It sets DFLEN again because Search function may have erase
	//       operation.
												// Make write address
	p8_data = (U8*)(u16_tblock + FLEX_INDEX_SIZE + ((U16)u8_flex_index * FLEX_AREA_SIZE));
	for( u8_index=0; u8_index<FLEX_AREA_SIZE; u8_index++ )		// Empty check loop
	{
		if( *(p8_data+u8_index) != 0xFF )				// Not empty ?
		{
			p8_data = (U8*)(u16_tblock + u8_flex_index);	// Make index address
			if( *p8_data == 0xFF )				// Index is empty ?
			{
				u8_data = U8_FLEX_INDEX_WNG;			// Write index(WRITE NG)
				DataFlash_Write((U8*)(u16_tblock + u8_flex_index), &u8_data, 1);
			}
			if( u8_dfl_en == 0 )					// DFLEN is set by this ?
			{
				DataFlash_Disable();					// Restore DFLEN
			}
			return FALSE;
		}
	}
	DataFlash_Disable();								// Disable DataFlash access

												// Write Flexible data
	u8_df_ret = DataFlash_Write(p8_data, (U8*)&st_flexible_data_ram, FLEX_SIZE);
	if( u8_df_ret == PFDL_OK )						// OK ?
	{
		u8_data = U8_FLEX_INDEX_WOK;					// WRITE OK
	} else {									// NG
		u8_data = U8_FLEX_INDEX_WNG;					// WRITE NG
	}
												// Write index
	DataFlash_Write((U8*)(u16_tblock + u8_flex_index), &u8_data, 1);

	if( f_df0_erase_req == ON )					// Block0 erase request ?
	{
		DataFlash_Erase(0);						// Erase Block0
		f_df0_erase_req = OFF;					// Clear the flag
	} else {
		if( f_df1_erase_req == ON )				// Block1 erase request ?
		{
			DataFlash_Erase(1);					// Erase Block1
			f_df1_erase_req = OFF;				// Clear the flag
		}
	}

	if( u8_dfl_en == 1 )							// DFLEN is not set by this ?
	{
		DataFlash_Enable();							// Enable DataFlash access
	}

	return TRUE;
}


U8 FlexibleData_Write(void)
{
	return Write_FlexibleData();
}
