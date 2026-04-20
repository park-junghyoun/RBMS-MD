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
* File Name		: smbus_custom.c
* Version		: 0.01
* Contents		: SMBus functions (custom)
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
* History		: 2020.10.06 Ver 0.01
* 				: Replace overall
* 
*""FILE COMMENT END""**************************************************/
#define _SMBUS_CUSTOM

// - Include header file -
#include "define.h"								
#include "flashrom.h"							
#include "dataflash_custom.h"
#include "ram.h"
#include "smbus.h"
#include "smbus_custom.h"
#include "init_calib.h"
#include "renesas.h"
#include "main_custom.h"
#include "mode.h"
#include "capacity.h"
#include "afe.h"
#include "charge.h"
#include "mcu_custom.h"
#include "safety_custom.h"
#include "inline_asm.h"

// - Firmware version -
#define MODEL_CODE	0x0000

// Maker code for Sub version
#define MAKER_CODE	0x0000

// Version information

const __near U16	Version = ( VERSION | MODEL_CODE );
const __near U16	SubVer	= ( SUB_VERSION | MAKER_CODE | TEST_CODE);
const __near U16	Seal_Sts = 0x0001;			// Dummy for the tool use
#ifdef	RAJ240094
const __near U8		IC_Name[10] = {'R','A','J','2','4','0','0','9','4'};
#else
const __near U8		IC_Name[10] = {'R','A','J','2','4','0','0','9','5'};
#endif
const __near U16	PJ_Suffix = 0x0001;

const __near st_smb_frame_t st_smb_command_table[] =		// SMBus command info. table
{
	// Note: Size of ReadWord/WriteWord should be set to 0.
	 { SMBUS_ERR		, 0	, (U8*)NULL }					// 00 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 01 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 02 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 03 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 04 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 05 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 06 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 07 Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&s16_SMB08_temp}		// 08 Temperature1
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB09_total_v }	// 09 Voltage()
	,{ RS_SADR_CHK	, 4	, (U8*)&s32_SMB0A_curr }		// 0A Current()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 0B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 0C Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB0D_rsoc }		// 0D RelativeStateOfCharge()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 0E Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&u32_SMB0F_rc }		// 0F RemainingCapacity()
	,{ RS_SADR_CHK	, 0	, (U8*)&u32_SMB10_fcc }		// 10 FullChargeCapacity()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 11 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 12 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 13 Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&s32_SMB14_chg_curr }	// 14 ChargingCurrent()
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB15_chg_volt }	// 15 ChargingVoltage()
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB16_batt_status }	// 16 BatteryStatus()
	,{ RS_SADR_CHK	, 0	, (U8*)&u32_SMB17_cycle_cnt }	// 17 CycleCount()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 18 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 19 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 1A Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 1B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 1C Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 1D Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 1E Reserved
	,{ RS_SADR_CHK	, 32	, (U8*)NULL }					// 1F Reserved
	,{ RS_SADR_CHK	, 32	, (U8*)&au8_SMB20_mfg_name }	// 1B ManufacturerName()
	,{ RS_SADR_CHK	, 32	, (U8*)&au8_SMB21_mfg_data }	// 21 ManufactureDate()
	,{ RS_SADR_CHK	, 32	, (U8*)&au8_SMB22_serial_num }	// 22 Serial Number()
	,{ RS_SADR_CHK	, 32	, (U8*)&au8_SMB23_dev_name }	// 23 DeviceName()
	,{ RS_SADR_CHK	, 4	, (U8*)&au8_SMB24_dev_chem }	// 24 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 25 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 26 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 27 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 28 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 29 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 2A Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 2B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 2C Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 2D Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 2E Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 2F Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 30 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 31 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL } 					// 32 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 33 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 34 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 35 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 36 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 37 Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB38_safety_status }	// 38 SafetyStatus
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB39_pf_status }	// 3A PFStatus
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 39 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 3B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 3C Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 3D Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 3E Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 3F Reserved
	,{ RW_CHK		, 0	, (U8*)&u16_extfunc }			// 40 ExtraFunction()
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB41_oper_status }	// 41 OperationStatus()
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB42_pack_status }	// 42 PackStatus()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 43 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 44 Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)u16_SMB45_sd_status }	// 45 Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB46_cb_status }	// 46 CBStatus()
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB47_pack_volt }	// 47 PACKVoltage
	,{ RS_SADR_CHK	, 0	, (U8*)&u16_SMB48_soh}		// 48 StateOfHealth()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 49 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 4A Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 4B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 4C Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 4D Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 4E Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 4F Reserved
	,{ RW_CHK		, 0	, (U8*)&u16_seal }				// 50 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 51 Reserved
	,{ RW_CHK		, 0	, (U8*)NULL }					// 52 Escape from PF
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 53 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 54 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 55 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 56 Reserved
	,{ RW_CHK		, 0	, (U8*)&tcalib_ref }				// 57 InitialCalibrationRef.()
	,{ RW_CHK		, 0	, (U8*)&tcalib_cmd }			// 58 InitialCalibration()
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 59 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 5A Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 5B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 5C Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 5D Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 5E Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 5F Reserved 
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[0]) }	// 60 cell1 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[1]) }	// 61 cell2 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[2]) }	// 62 cell3 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[3]) }	// 63 cell4 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[4]) }	// 64 cell5 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[5]) }	// 65 cell6 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[6]) }	// 66 cell7 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[7]) }	// 67 cell8 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[8]) }	// 68 cel9 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB60_volt[9]) }	// 69 cell10 voltage
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB6A_temp[0]) }	// 6A temperature AN0
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB6A_temp[1]) }	// 6B temperature AN1
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB6A_temp[2]) }	// 6C temperature AN2
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB6A_temp[3]) }	// 6D temperature AN3
	,{ RS_SADR_CHK	, 0	, (U8*)&(u16_SMB6A_temp[4]) }	// 6E temperature AN4
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 6F Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 70 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 71 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 72 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 73 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 74 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 75 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 76 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 77 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 78 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 79 Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 7A Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 7B Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 7C Reserved
	,{ SMBUS_ERR	, 0	, (U8*)NULL }					// 7D Reserved
	,{ RS_SADR_CHK	, 0	, (U8*)&tfwsum }				// 7E CheckSUM of Firmware
	,{ RS_SADR_CHK	, 0	, (U8*)&tfixsum }				// 7F CheckSUM of Fixed data
};


const __near st_smb_frame_t st_smb_fwinfo_table[] =			// F/W info command info. table
{
	 { RS_SADR_CHK	, 8	, (U8*)&s_tool_info }			// F0 for RSB_TOOL2
	,{ RS_SADR_CHK	, 0	, (U8*)&Version }				// F1 Firmware version
	,{ RS_SADR_CHK	, 0	, (U8*)&SubVer }				// F2 Firmware sub version
	,{ RS_SADR_CHK	, 9	, (U8*)&IC_Name[0] }			// F3 RenesasICName
	,{ RS_SADR_CHK	, 0	, (U8*)&PJ_Suffix }				// F4 Project suffix
};


// - Define definition -
#define CMD_TABLE_MAX		0x7F				// Number of Command table
#define CMD_FWINFO_START	0xF0				// Command of F/W info. start
#define CMD_FWINFO_END		0xF4				// Command of F/W info. end

#define DATA_SEAL			0x0000				// Data of Seal

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus command receive function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: U8 SMB_ReceiveCommand(void)
*-------------------------------------------------------------------
* Function			: Check received command.
*					: And set SMBus comm. information.
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: U8	: 1 = Valid command
*					:		  0 = Invalid command
*-------------------------------------------------------------------
* Input				: u8_received_cmd	: Received command
* Output			: st_smb_frame	: SMBus communication information
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
U8 SMB_ReceiveCommand(void)
{
	U8	al1;

	if( u8_received_cmd <= CMD_TABLE_MAX )						// Command is in table ?
	{
														// Set SMBus comm. information
		st_smb_frame = st_smb_command_table[u8_received_cmd];


		// - variable length data setting -
		if( u8_received_cmd == 0x20							// ManufacturerName()
			|| u8_received_cmd == 0x21							// or DeviceName()
			|| u8_received_cmd == 0x22 )						// or DeviceChemistry() ?
		{
			// Check valid data
			if( st_smb_frame.p8_data != (U8*)NULL )
			{
				for( al1=0; al1<st_smb_frame.u8_len && st_smb_frame.p8_data[al1] != 0x00; al1++ );
				st_smb_frame.u8_len = al1;
			}
			else
			{
				st_smb_frame.u8_len = 0;
			}
			// Note: It is not necessary if the data length is fixed.
			// Note: It needs to consider the number of NULL if there is
			//       the data including NULL.
		}

	} else {									// Command is out of table
		st_smb_frame.u8_status = SMBUS_ERR;					// Receive mode: SMBus error

		if( u8_received_cmd >= CMD_FWINFO_START		// Command of F/W information ?
			&& u8_received_cmd <= CMD_FWINFO_END )
		{
			st_smb_frame = st_smb_fwinfo_table[u8_received_cmd - 0xF0];
		}

		// TODO: Add some operation for command of out of table if necessary.
	}

	// TODO: Add some operation if additional setting is necessary.

	if( st_smb_frame.u8_status != SMBUS_ERR )					// Valid command ?
	{	
		return 1;
		
	} else {									// Invalid command
		return 0;
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus read data setting function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMB_SetReadData(void)
*-------------------------------------------------------------------
* Function			: Set read data to SMBus buffer.
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: u8_received_cmd	: Received command
* Output			: au8_smb_buff	: SMBus buffer
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMB_SetReadData(void)
{
	_SBYTE	al1;

	// Set read data
	switch( u8_received_cmd )							// Command is ...
	{
		// TODO: Add some command own setting if necessary.
		
		case 0xF0:								// 0xF0: RSB_TOOL2 information
			au8_smb_buff[0] = st_smb_frame.u8_len;				// Set data length to buffer
			for( al1=1; al1<=st_smb_frame.u8_len; al1++ )
			{
				// Note: s_tool_info[] is far data.
				//       Then it can't be set by near pointer.
				au8_smb_buff[al1] = s_tool_info[al1-1];
			}
			break;
			
		case 0x57:								// 0x57: InitCalibRef.
			CalibRef_read_request();			// CalibRef. read request
			break;
		
		default:								// Others
			if( st_smb_frame.u8_len == 0 )					// ReadWord ?
			{
												// Set data to buffer
				au8_smb_buff[0] = *st_smb_frame.p8_data;
				au8_smb_buff[1] = *(st_smb_frame.p8_data+1);

				// TODO: Add some additional operation if the buffer needs
				//       to modify.
				// Note: Basically, data modification should be done before
				//       setting read data.

			} else {							// BlockRead
			
				au8_smb_buff[0] = st_smb_frame.u8_len;			// Set data length to buffer
												// Set data to buffer
				for( al1=1; al1<=st_smb_frame.u8_len; al1++ )
				{
					au8_smb_buff[al1] = *st_smb_frame.p8_data;
					st_smb_frame.p8_data++;
				}

				// TODO: Add some additional operation if the buffer needs
				//       to modify.
				// Note: Basically, data modification should be done before
				//       setting read data.
			}
			break;
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus received data storing function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMB_StoreReceiveData(void)
*-------------------------------------------------------------------
* Function			: Store received data.
*					: And it may have some additional operation.
*-------------------------------------------------------------------
* Argument			: None
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: u8_received_cmd	: Received command
*					: au8_smb_buff	: SMBus buffer
*					: ssmb_info	: SMBus communication information
* Output			: RAM data specified by ssmb_info
*					: Some additional data (If necessary)
*-------------------------------------------------------------------
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMB_StoreReceiveData(void)
{
	_SBYTE	al1;

	switch( u8_received_cmd )							// Command is ...
	{		
		// - Extra function -
		case 0x40:								// 0x40: ExtraFunction()
		
			ExtraFunction();
			break;
			
		case 0x50:								// 0x50: Seal/Unseal()
			Seal_Proc();
			break;

		case 0x52:								// 0x52: Escape from PF
			if( f_unseal == ON )				// Only works when unseal
			{
				if( au8_smb_buff[0] == 0xFF && au8_smb_buff[1] == 0xFF )
				{
					if( amode == M_PF )			// PF ?
					{
						amode = M_RELAX;		// Change to RELAX Mode
					}
					acause = 0;					// Clear PF cause
					f_pf = OFF;					// Clear PackStatus:PF
					f_fuseout_alrdy = OFF;
					PFStatus = 0;					// PF Status Clear
					FuseBlow_control(HV_LOW);		// Set fuseout pin LOW
					aflex_reason = FLEXUP_SMB;		// Set Reason of Flex update
					Write_FlexibleData();			// Update Flexible data
				}
			}
			break;
		
		// - Initial calibration -
		case 0x57:								// 0x57: InitialCalibrationRef.
			tcalib_ref = au16_smb_buff[0];			// Set received data
			CalibRef_write_request();			// Ref.value writing request
			break;

		case 0x58:								// 0x58: InitialCalibration
			tcalib_cmd = au16_smb_buff[0];			// Set received data
			Calibration_request();				// Calibration request
			break;
			
		case 0x1B:								// ManufatureDate Write
			if( f_unseal == ON )				// Only works when unseal
			{
				a_com1b[0] = au8_smb_buff[0];
				a_com1b[1] = au8_smb_buff[1];
				Request_FlexibleData_update();
				aflex_reason = FLEXUP_SMB;		// Set Reason of Flex update
			}
			break;
			
		case 0x1C:								// SerialNumber Write
			if( f_unseal == ON )				// Only works when unseal
			{
				a_com1c[0] = au8_smb_buff[0];
				a_com1c[1] = au8_smb_buff[1];				
				Request_FlexibleData_update();
				aflex_reason = FLEXUP_SMB;		// Set Reason of Flex update
			}
			break;
			
		// TODO: Add some command own setting if necessary.

		default:								// Others
			for( al1=0; al1<st_smb_frame.u8_len; al1++ )	// Set data to buffer
			{
				*st_smb_frame.p8_data = au8_smb_buff[al1];
				st_smb_frame.p8_data++;
			}
			// TODO: Add some operation if necessary.
			break;
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus custom function when Stop condition
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMB_custom_StopCondition(void)
*-------------------------------------------------------------------
* Function			: Custom function when receiving Stop condition.
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
* Caution			: Empty function is enough if there is not any
*					: customized operation.
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMB_custom_StopCondition(void)
{
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus custom function when slave communication
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMB_custom_SlaveComm(void)
*-------------------------------------------------------------------
* Function			: Custom function when slave communication.
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
* Caution			: Empty function is enough if there is not any
*					: customized operation.
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMB_custom_SlaveComm(void)
{
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus custom function when receiving Slave address
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMB_custom_SlaveAddress_receive(void)
*-------------------------------------------------------------------
* Function			: Custom function when receiving Slave address.
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
* Caution			: Empty function is enough if there is not any
*					: customized operation.
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMB_custom_SlaveAddress_receive(void)
{
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus custom function when SCL/SDA interrupt
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMB_custom_SCLSDA(void)
*-------------------------------------------------------------------
* Function			: Custom function when SCL/SDA interrupt.
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
* Caution			: Empty function is enough if there is not any
*					: customized operation.
*-------------------------------------------------------------------
* History			: 2020.10.13 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMB_custom_SCLSDA(void)
{
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Extra function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void ExtraFunction(void)
*-------------------------------------------------------------------
* Function			: Renesas own extra function.
*					: It is used when receiving SMBus 0x40.
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
* History			: 2020.10.16 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void ExtraFunction(void)
{
	u16_extfunc = au16_smb_buff[0];					// Store received data

	// - Check ExtraFunction enable / disable -
	if( u16_extfunc == DATA_EXTFUNC_DIS )			// ExtFunc disable request ?
	{
		if( f_extfunc_en1 == OFF )				// 2nd request ?
		{
			f_extfunc_en2 = OFF;
		} else {								// 1st request
			f_extfunc_en1 = OFF;
		}
	} else {
		if( u16_extfunc == DATA_EXTFUNC_EN )		// ExtFunc enable request ?
		{
			if( f_extfunc_en1 == ON )			// 2nd request ?
			{
				f_extfunc_en2 = ON;
			} else {							// 1st request
				f_extfunc_en1 = ON;
			}
		} else {								// Others
			if( f_extfunc_en2 == ON )			// Already enabled ?
			{
				f_extfunc_en1 = ON;
			} else {							// Disabled
				f_extfunc_en1 = OFF;
			}
		}
	}

	if( f_extfunc_en2 == ON )					// ExtraFunction enabled ?
	{
		// Force PowerDown
		if( f_comjib == ON )					// Force PowerDown flag = ON ?
		{
			if( u16_extfunc == 0x0908 )			// Data is correct ?
			{
				__PowerDown(CAUSE_COM,FLEXUP_SMB);	// PowerDown function
				
			} else {							// Data is wrong
				f_comjib = OFF;					// Clear the flag
			}
		} else {								// Force PowerDown flag = OFF
			if( u16_extfunc == 0x0b0a )			// PowerDown req. command ?
			{
				f_comjib = ON;					// Set force PowerDown flag
			}
		}
		// Force PF
		if( f_compf1 == ON )											// Force Perm fail = ON ?
		{
			if( u16_extfunc == 0x0706 )										// Data is correct ?
			{
				f_fpf = ON;
				Set_PF(CAUSE_PF_COM,FLEXUP_SMB);						// PermanentFailure function
			} 
			else 
			{															// Data is wrong
				f_compf1 = OFF;											// Clear the flag
			}
		} 
		else 
		{																// Force PowerDown flag = OFF
			if( u16_extfunc == 0x0d0c )										// PowerDown req. command ?
			{
				f_compf1 = ON;											// Set force PowerDown flag
			}
		}

		if( u16_extra_func.u8_data[1] == 0xEE )				// Data is 0xEE** ?
		{
			switch( u16_extra_func.u8_data[0] )				// ** is ...
			{
				case 0x11:						// Flash update mode request
					if( f_unseal == ON )		// Only works when unseal
					{
						f_flashup = ON;			// Set Flash update mode req.
						aflex_reason = FLEXUP_FLASH;// Set Reason of Flex update
					}
					break;
					
				case 0x22:						// Read version information
					u16_extfunc = Version;		// Set version to command data
					break;
					
				case 0x33:						// S/W reset
					ASM_SW_RESET();				// Make reset
					break;
				
				case 0xC0:						// Fcc relearn cancel. unit
					f_hldtmin = ON;				// FCC relearn cancel. from hrs to min flag
					break;
				case 0xC1:						// Fcc relearn cancel. unit
					f_hldtmin = OFF;			// FCC relearn cancel. from min to hrs flag
					break;
				case 0x60:
					f_force_fetoff_ent  = ON;
					f_force_fetoff_ext = OFF;
					break;
				case 0x61:
					f_force_fetoff_ext  = ON;
					f_force_fetoff_ent = OFF;
					break;
			}
		}	
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Seal/Unseal function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Seal_Proc(void)
*-------------------------------------------------------------------
* Function			: Seal/Unseal setting function.
*					: It is used when receiving SMBus 0x50.
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
* History			: 2020.10.16 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Seal_Proc(void)
{
	if (D_PASS[0] == 0xFFFF && D_PASS[1]== 0xFFFF)
	{
		return;
	}
	
	if( f_unseal == ON )						// Unseal now ?
	{
		if( au16_smb_buff[0] == DATA_SEAL )			// Seal command ?
		{
			f_unseal = OFF;						// Clear unseal
			f_unseal_1st = OFF;					// Clear unseal 1st command
			tseal = STS_SEAL;					// Set Seal status
			f_ss = ON;							// Set PackStatus[SS]
			Request_FlexibleData_update();
			aflex_reason = FLEXUP_SMB;			// Set Reason of Flex update
		}
		
	} else {									// Seal now
		if( f_unseal_1st == OFF )				// 1st data check ?
		{
			if( D_PASS[1] != 0xFFFF )			// No specified password ?
			{					
				if( au16_smb_buff[0] == D_PASS[1] )	// Correct data ?
				{
					f_unseal_1st = ON;			// Set 1st command received
				}
			}
			
		} else {								// 2nd data check
			if( D_PASS[0] != 0xFFFF )			// No specified password ?
			{					
				if( au16_smb_buff[0] == D_PASS[0] )	// Correct data ?
				{
					f_unseal = ON;				// Set Unseal
					tseal = STS_UNSEAL;			// Set Unseal status
					f_ss = OFF;					// Set PackStatus[SS]
					Request_FlexibleData_update();
					aflex_reason = FLEXUP_SMB;	// Set Reason of Flex update

				} else {						// Incorrect
					f_unseal_1st = OFF;			// Clear 1st command received
				}
			}
		}
	}

}
