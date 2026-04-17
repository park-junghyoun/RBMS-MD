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
* File Name		: int.c
* Version		: 0.01
* Contents		: FlashROM functions
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx Standard firmware
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* Note			: 
************************************************************************
* Copyright,2020 (2012-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2020.10.16 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/

#define _FLASHROM

// - Include header file -
#include <stddef.h>
#include "define.h"								// Common definition
#include "flashrom.h"
#include "ram.h"
#include "dataflash_custom.h"
#include "afe.h"
#include "uif_fsl.h"
#include "inline_asm.h"

typedef struct
{
	U16 u16_start;
	U16 u16_end;
}st_fixed_reserved_range_t;

#define FLASH_SET_RESERVED_RANGE(_member_path) \
	{ \
		(U16)offsetof(st_fixed_data_t, _member_path), \
		(U16)(offsetof(st_fixed_data_t, _member_path) + sizeof(((st_fixed_data_t *)0)->_member_path)) \
	}

static U8 FLASH_IsReservedFixedDataIndex(U16 u16_index)
{
	U8 u8_index;
	const st_fixed_reserved_range_t *pst_range;
	static const st_fixed_reserved_range_t st_reserved_ranges[] =
	{
		// Add all au8_reserved fields in st_fixed_data here.
		FLASH_SET_RESERVED_RANGE(st_device_info.au8_reserved),
		FLASH_SET_RESERVED_RANGE(st_gauging_info.au8_reserved),
		FLASH_SET_RESERVED_RANGE(st_system_info.au8_reserved),
		FLASH_SET_RESERVED_RANGE(st_operating_info.au8_reserved),
	};

	for( u8_index = 0; u8_index < (sizeof(st_reserved_ranges) / sizeof(st_reserved_ranges[0])); u8_index++ )
	{
		pst_range = &st_reserved_ranges[u8_index];
		if( u16_index >= pst_range->u16_start && u16_index < pst_range->u16_end )
		{
			return TRUE;
		}
	}

	return FALSE;
}

#undef FLASH_SET_RESERVED_RANGE

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: Fixed Data Check Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		:  U8 InitFixed_Chk(void)
 *--------------------------------------------------------------------------
 * Function			: Check whether there are some fixed data or not.
 *					: Even if there is just one vacant data, FALSE is returned.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: TRUE=There are all necessary data.
 *					: FALSE=There are some vacant data.
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 * History			: 2016.02.15 Ver 1.00
 *					:  New Create
 *					: 
 *""FUNC COMMENT END""*****************************************************/
U8 FLASH_Check_FixedData(void)
{
	U16	u16_index;
	U8		*pu8_fixed_data;

	pu8_fixed_data = (U8 *)&st_fixed_data;
	for( u16_index = 0; u16_index < FDSIZE; u16_index++ )
	{
		if( FLASH_IsReservedFixedDataIndex(u16_index) == TRUE )
		{
			continue;
		}

		if( pu8_fixed_data[u16_index] == 0xFF )
		{
			return FALSE;
		}
	}

	return TRUE;
}
