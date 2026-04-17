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
* File Name		: dataflash.c
* Version		: 0.01
* Contents		: Data flash controlling functions
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
#define _DATAFLASH

// - Include header file -
#include "define.h"								// Common definition
#include "uif_pfdl.h"
#include "dataflash.h"
#include "dataflash_custom.h"


// - Define definition -
#define PFDL_FREQUENCY			8				// PFDL CPU frequency (8MHz)
#define PFDL_FLASH_VOLTAGE		1				// PFDL voltage mode setting
												// (not 0x00:wide voltage mode)
#define DATAFLASH_WRITE_CHUNK_SIZE	64			// Chunk size for write/verify

// - Internal variable -
//	Initialize data for PFDL
const __near pfdl_descriptor_t	pfdl_descriptor_pstr
					 = { PFDL_FREQUENCY, PFDL_FLASH_VOLTAGE };
				//         |            +-------- wide voltage mode
				//         +-------------- Clock(Selected by compile option)

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: DataFlash write function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: U8 DataFlash_Write(U8 *apadr, U8 *apdata,
*					:									U16 tsize)
*-------------------------------------------------------------------
* Function			: Write data to DataFlash.
*					: It writes the data by 64bytes unit to prevent 
*					: SMBus error by disabling interrupt long time.
*-------------------------------------------------------------------
* Argument			: U8 *apadr	: Pointer of write address
*					: U8 *apdata	: Pointer of writing data
*					: U16 tsize	: Write size
*-------------------------------------------------------------------
* Return			: U8	: Return code of PFDL library.
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.12.01 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
U8 DataFlash_Write(U8 *p8_addr, U8 *p8_data, U16 u16_size)
{
	static U8			u8_fw_step;
	U8				*p8_write_addr;
	U8				*p8_write_data;
	U16				u16_write_cnt;
	pfdl_request_t		pfdl_req;
	pfdl_status_t		pfdl_ret;					// Return code

	if( u8_fw_step != 0 )							// FlashWrite executing ?
	{
		return PFDL_BUSY;						// Abort
	}

	MCU_PSW_PUSH();									// PSW -> STACK
	u8_fw_step = 1;								// Set Flash Write step

	PFDL_Open( (__near pfdl_descriptor_t*)&pfdl_descriptor_pstr );

	pfdl_req.index_u16 = (pfdl_u16)p8_addr;			// Set write address
	pfdl_req.bytecount_u16 = u16_size;				// Set write size
												// Set Blank check command
	pfdl_req.command_enu = PFDL_CMD_BLANKCHECK_BYTES;
	pfdl_ret = PFDL_Execute( &pfdl_req );				// Blank check
	while( pfdl_ret == PFDL_BUSY )					// Wait for finish checking
	{
		pfdl_ret = PFDL_Handler();					// Ststus check
	}

	if( pfdl_ret == PFDL_OK )						// Blank check OK ?
	{
		p8_write_addr = p8_addr;					// Initialize write address
		p8_write_data = p8_data;					// Initialize write data
		u16_write_cnt = u16_size;						// Initialize write size
		do										// Writing loop
		{
			pfdl_req.index_u16 = (pfdl_u16)p8_write_addr;
			pfdl_req.data_pu08 = p8_write_data;	// Set write data
			if( u16_write_cnt >= DATAFLASH_WRITE_CHUNK_SIZE )	// Size >= chunk ?
			{
				pfdl_req.bytecount_u16 = DATAFLASH_WRITE_CHUNK_SIZE;
												// Set write size = chunk
			} else {
												// Set write size
				pfdl_req.bytecount_u16 = u16_write_cnt;
			}
												// Set Write command
			pfdl_req.command_enu = PFDL_CMD_WRITE_BYTES;
			pfdl_ret = PFDL_Execute( &pfdl_req );		// Write
			while( pfdl_ret == PFDL_BUSY )			// Wait for finish writing
			{
				pfdl_ret = PFDL_Handler();			// Status check
			}
			if( pfdl_ret == PFDL_OK )				// Write OK ?
			{
												// Set Verify command
				pfdl_req.command_enu = PFDL_CMD_IVERIFY_BYTES;
				pfdl_ret = PFDL_Execute( &pfdl_req );	// Verify
				while( pfdl_ret == PFDL_BUSY )		// Wait for finish verifying
				{
					pfdl_ret = PFDL_Handler();		// Status check
				}
			}
			
			if( pfdl_ret != PFDL_OK )				// Write NG ?
			{
				break;
			}

			p8_write_addr += pfdl_req.bytecount_u16;	// Update write address
			p8_write_data += pfdl_req.bytecount_u16;	// Update write data
												// Update write count
			u16_write_cnt -= pfdl_req.bytecount_u16;
		} while(u16_write_cnt > 0);
	}


	PFDL_Close();								// Flash data library close
	u8_fw_step = 0;								// Clear Flash Write step
	MCU_PSW_POP();							// STACK -> PSW

	return pfdl_ret;
}


/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: DataFlash erase function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: U8 DataFlash_Erase(U8 ablock)
*-------------------------------------------------------------------
* Function			: Erase a block of DataFlash.
*-------------------------------------------------------------------
* Argument			: U8 ablock	: Erase block
*-------------------------------------------------------------------
* Return			: U8	: Return code of PFDL library.
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.12.01 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
U8 DataFlash_Erase(U8 u8_block)
{
	pfdl_request_t		pfdl_req;
	pfdl_status_t		pfdl_ret;					// Return code

	MCU_PSW_PUSH();									// PSW -> STACK
												// Flash data library open
	PFDL_Open( (__near pfdl_descriptor_t*)&pfdl_descriptor_pstr );

	pfdl_req.index_u16 = (pfdl_u16)u8_block;		// Set block number of erase
	pfdl_req.command_enu = PFDL_CMD_ERASE_BLOCK;	// Set Erase command
	pfdl_ret = PFDL_Execute( &pfdl_req );				// Erase
	while( pfdl_ret == PFDL_BUSY )					// Wait for finish erasing
	{
		pfdl_ret = PFDL_Handler();					// Ststus check
	}
	MCU_PSW_POP();										// STACK -> PSW

	PFDL_Close();								// Flash data library close

	return pfdl_ret;
}


/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: DFLEN setting function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void DataFlash_Enable(void)
*-------------------------------------------------------------------
* Function			: Enable Data flash access.
*					: Set DFLEN=1, and wait for the setup time.
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
* Caution			: This function is for LS mode of Flash Operation Mode.
*					: The setup time at LS mode is 720ns.
*					: RET operation use 6clock(750ns on 8MHz), then
*					: the additional waiting time is not necessary.
*-------------------------------------------------------------------
* History			: 2020.10.08 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void DataFlash_Enable(void)
{
	DFLEN = 1;
}



/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: DFLEN clearing function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void DataFlash_Disable(void)
*-------------------------------------------------------------------
* Function			: Disable Data flash access.
*					: Set DFLEN=0.
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
* History			: 2020.11.05 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void DataFlash_Disable(void)
{
	DFLEN = 0;
}


/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Flexible data search function (Read)
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Search_FlexibleData_read(U16 *tblock, U8 *aidx)
*-------------------------------------------------------------------
* Function			: Search the data index of read Flexible data.
*-------------------------------------------------------------------
* Argument			: U16 *tblock	: Pointer of using Block address
*					:				: It will be set to NULL if there is error.
*					: U8 *aidx	: Index of read
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: DFLEN must be 1 before calling this function.
*-------------------------------------------------------------------
* History			: 2020.10.30 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Search_FlexibleData_read(U16 *p16_tblock, U8 *p8_aidx)
{
	S8	s8_aidx0, s8_aidx1;
	U8	*p8_apdata;

	// Seach Flexible data index
												// Seach Block0
	for( s8_aidx0 = FLEX_AREA_NUM - 1, p8_apdata =(U8*)U16_BLOCK_0;
		 s8_aidx0>=0 && p8_apdata[s8_aidx0]!= U8_FLEX_INDEX_WOK; s8_aidx0-- );
												// Seach Block1
	for( s8_aidx1 = FLEX_AREA_NUM - 1, p8_apdata =(U8*)U16_BLOCK_1;
		 s8_aidx1>=0 && p8_apdata[s8_aidx1]!= U8_FLEX_INDEX_WOK; s8_aidx1-- );
		 
	if( s8_aidx0 < 0 )								// Block0 is empty ?
	{
		if( s8_aidx1 < 0 )							// Block1 is empty ?
		{
			*p16_tblock = NULL;						// Set NULL
		} else {								// Block1 is not empty
			*p16_tblock = U16_BLOCK_1;					// Use Block1
			*p8_aidx = (U8)s8_aidx1;
		}
	} else {									// Block0 is not empty
		if( s8_aidx1 < 0 )							// Block1 is empty ?
		{
			*p16_tblock = U16_BLOCK_0;					// Use Block0
			*p8_aidx = s8_aidx0;
		} else {								// Block1 is not empty
			if( s8_aidx0 < s8_aidx1 )					// Block0 is less than Block1 ?
			{
				*p16_tblock = U16_BLOCK_0;				// Use Block0
				*p8_aidx = s8_aidx0;
			} else {							// Block0 is same or bigger
				*p16_tblock = U16_BLOCK_1;				// Use Block1
				*p8_aidx = s8_aidx1;
			}
		}
	}
}


/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Flexible data search function (Write)
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Search_FlexibleData_write(U16 *tblock, U8 *aidx)
*-------------------------------------------------------------------
* Function			: Search the data index of write Flexible data.
*-------------------------------------------------------------------
* Argument			: U16 *tblock	: Pointer of using Block address
*					: U8 *aidx	: Index of write
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: DFLEN must be 1 before calling this function.
*-------------------------------------------------------------------
* History			: 2020.10.30 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Search_FlexibleData_write(U16 *p16_tblock, U8 *p8_aidx)
{
	U8	u8_aidx0, u8_aidx1;
	U8	*p8_apdata;

	// Seach Flexible data index
	for( u8_aidx0 = 0, p8_apdata=(U8*)U16_BLOCK_0;		// Seach Block0
		 u8_aidx0 < FLEX_AREA_NUM && p8_apdata[u8_aidx0]!= U8_FLEX_INDEX_EMPTY; u8_aidx0++ );
		 
	for( u8_aidx1 = 0, p8_apdata = (U8*)U16_BLOCK_1;		// Seach Block1
		 u8_aidx1 < FLEX_AREA_NUM && p8_apdata[u8_aidx1]!= U8_FLEX_INDEX_EMPTY; u8_aidx1++ );
		 
	if( u8_aidx0 == 0 )							// Block0 is empty ?
	{
		if( u8_aidx1 == 0 )						// Block1 is empty ?
		{
			*p16_tblock = U16_BLOCK_0;					// Use Block0
			*p8_aidx = 0;
		} else {								// Block1 is not empty
			if( u8_aidx1 == FLEX_AREA_NUM )		// Block1 is full ?
			{
				*p16_tblock = U16_BLOCK_0;				// Use Block0
				*p8_aidx = 0;
			} else {							// Not full
				*p16_tblock = U16_BLOCK_1;				// Use Block1
				*p8_aidx = u8_aidx1;
			}
		}
	} else {									// Block0 is not empty
		if( u8_aidx1 == 0 )						// Block1 is empty ?
		{
			if( u8_aidx0 == FLEX_AREA_NUM )		// Block 0 is full ?
			{
				*p16_tblock = U16_BLOCK_1;				// Use Block1
				*p8_aidx = 0;
			} else {
				*p16_tblock = U16_BLOCK_0;				// Use Block0
				*p8_aidx = u8_aidx0;
			}
		} else {								// Block1 is not empty
			if( u8_aidx0 < u8_aidx1 )					// Block0 is less than Block1 ?
			{
				*p16_tblock = U16_BLOCK_0;				// Use Block0
				*p8_aidx = u8_aidx0;
				if( u8_aidx0 >= (FLEX_AREA_NUM - 3)) // Block0 is last 3 area ?
				{
					if( f_pf == OFF )			// Not PF ?
					{
						f_df1_erase_req = ON;	// Set Block1 erase request
						
					} else {					// PF
						f_flex_stop = ON;		// Set Stop Flex.data update
					}
				}
			} else {							// Block0 is same or bigger
				*p16_tblock = U16_BLOCK_1;				// Use Block1
				if( u8_aidx1 == FLEX_AREA_NUM )	// Block1 is full ?
				{								// (Both blocks are full)
					if( f_pf == OFF )			// Not PF ?
					{
						DataFlash_Erase(1);		// Erase Block1
						*p8_aidx = 0;				// Use 1st area
					} else {					// PF
						f_flex_stop = ON;		// Set Stop Flex.data update
					}
				} else {						// Block1 is not full
					*p8_aidx = u8_aidx1;				// Set index
												// Block1 is last 3 area ?
					if( u8_aidx1 >= (FLEX_AREA_NUM - 3) )
					{
						if( f_pf == OFF )		// Not PF ?
						{
												// Set Block1 erase request
							f_df0_erase_req = ON;
						} else {				// PF
							f_flex_stop = ON;	// Set Stop Flex.data update
						}
					}
				}
			}
		}
	}
}
