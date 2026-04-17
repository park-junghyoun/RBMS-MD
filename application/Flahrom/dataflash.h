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
* File Name		: dataflash.h
* Version		: 0.01
* Contents		: Data Flash access function header file
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx Standard firmware
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* OS			: None
* Programmer	: Ryoji Kato
* Note			: 
************************************************************************
* Copyright,2020 (2012-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2020.10.01 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#ifndef _DATAFLASH_H
#define _DATAFLASH_H

#ifdef	_DATAFLASH
#define		GLOBAL
#else	// _DATAFLASH
#define		GLOBAL	extern

#endif	// _DATAFLASH

#include "dataflash_custom.h"

// - Function declaration -
void DataFlash_update_check(void);							// DataFlash updating
U8 DataFlash_Write(U8 *p8_addr, U8 *p8_data, U16 u16_size);		// DataFlash write
U8 DataFlash_Erase(U8 u8_block);								// DataFlash erase
void DataFlash_Enable(void);									// Set DFLEN=1
void DataFlash_Disable(void);									// Set DFLEN=0
void FlexibleData_Read(void);								// Read Flexible data
void Search_FlexibleData_read(U16 *p16_tblock, U8 *p8_aidx);		// Search read index
void Search_FlexibleData_write(U16 *p16_tblock, U8 *p8_aidx);		// Search write index
U8 Write_FlexibleData(void);									// Write Flexible data
U8 FlexibleData_Write(void);									// Legacy alias
st_cal_data_t CalbirationData_Read(void);						// Read Own data



// - Grobal variable -
GLOBAL U8			u8_df_flg;				// Flags for DataFlash
#define f_df0_erase_req		DEF_BIT0(&u8_df_flg)	// Block0 erase request
#define f_df1_erase_req		DEF_BIT1(&u8_df_flg)	// Block1 erase request
#define f_df2_erase_req		DEF_BIT2(&u8_df_flg)	// Block2 erase request
#define f_df3_erase_req		DEF_BIT3(&u8_df_flg)	// Block3 erase request
#define f_flex_stop			DEF_BIT4(&u8_df_flg)	// Stop Flexible data update
#define f_flex_update_req	DEF_BIT5(&u8_df_flg)	// Flexible data update request
#define f_dfe				DEF_BIT6(&u8_df_flg)	// DataFlash erasing flag


// - Define definition -
// DataFlash definition
#define U16_BLOCK_0				0x1000				// Start address of Block 0
#define U16_BLOCK_1				0x1400				// Start address of Block 1
#define U16_BLOCK_2				0x1800				// Start address of Block 2
#define U16_BLOCK_3				0x1C00				// Start address of Block 3

// Flexible data definition
#define U8_FLEX_INDEX_WOK		0xA0				// Flexible data index : OK
#define U8_FLEX_INDEX_WNG		0x07				// Flexible data index : NG
#define U8_FLEX_INDEX_EMPTY		0xFF				// Flexible data index : Empty



#undef 		GLOBAL

#endif	// _DATAFLASH_H



