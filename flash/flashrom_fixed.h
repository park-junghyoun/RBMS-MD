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
* File Name		: flashrom.h
* Version		: 0.01
* Contents		: FlashROM function header file
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
#ifndef _FLASHROM_H
#define _FLASHROM_H

#ifdef	_FLASHROM
#define		GLOBAL
#else	// _FLASHROM
#define		GLOBAL	extern
#endif	// _FLASHROM

#include "r_bms_api.h"
#include "r_bms_api_limits.h"
#include "define.h"

// - Function declaration -
void MoveToFlashUpdate(void);		// Move to Flash update mode
void FlashWrite_Key(void);

// - Control flag definition -
typedef struct
{
	//Basic Control
	U8 f_start_ship			:1;			// bit  0 : Start from ship mode
									//		(On: start ship , Off: start normal)
	U8 f_fullychg_fet		:1; 			// bit  1 : Fully charge C FET Control
									//		(On: C-FET OFF , Off: C-FET ON)
	U8 f_fullydsg_fet		:1;			// bit  2 : Fully discharge D FET Control
									//		(On: D-FET OFF , Off: D-FET ON)
	U8 f_sfdis_en			:1; 			// bit  3 : Self discharge Enable
									//		(On: enable , Off: disable)
	U8 f_cb_en 			:1; 			// bit  4 : Cell Balancing Enable
									//		(On: enable , Off: disable)							
	U8 DUMMY5			:1;			// bit  5 : Resreved
	U8 DUMMY6			:1;			// bit  6 : Resreved
	U8 DUMMY7			:1;			// bit  7 : Resreved
	U8 DUMMY8			:1; 			// bit  8 : Resreved
	U8 DUMMY9			:1;			// bit  9 : Resreved
	U8 DUMMY10			:1;			// bit 10 : Resreved
	U8 DUMMY11			:1;			// bit 11 : Resreved
	U8 DUMMY12			:1;			// bit 12 : Resreved
	U8 DUMMY13			:1;			// bit 13 : Resreved
	U8 DUMMY14			:1; 			// bit 14 : Reserved
	U8 DUMMY15			:1; 			// bit 15 : Reserved

}st_control_flag1_t;

typedef struct
{
	//Intermediate Control
	U8 f_calib1p			:1;			// bit  0 : Initial Calibration 1Point Enable
									//		(On: enable , Off: disable)
	U8 f_pinshutdown		:1; 			// bit 1 : PIN Shutdown Enable
									//(On: shutdown , Off: shipmode)
	U8 DUMMY3			:1; 			// bit	3 : Resreved
	U8 DUMMY4			:1; 			// bit	4 : Reserved
	U8 DUMMY5			:1; 			// bit	5 : Reserved 
	U8 DUMMY6			:1; 			// bit	6 : Resreved
	U8 DUMMY7			:1; 			// bit	7 : Resreved
	U8 DUMMY8			:1; 			// bit	8 : Resreved
	U8 DUMMY9			:1; 			// bit	9 : Resreved
	U8 DUMMY10			:1; 			// bit 10 : Resreved
	U8 DUMMY11			:1; 			// bit 11 : Resreved
	U8 DUMMY12			:1; 			// bit 12 : Resreved
	U8 DUMMY13			:1; 			// bit 13 : Reserved
	U8 DUMMY14			:1; 			// bit 14 : Reserved
	U8 DUMMY15			:1; 			// bit 15 : Reserved
}st_control_flag2_t;

typedef struct
{
	U8 f_jeita				:1;			// bit  0 : JEITA Enable
									//	    (On: enable , Off: disable)	
	U8 DUMMY1			:1; 			// bit  1 : Reserved 
	U8 DUMMY2			:1; 			// bit  2 : Resreved
	U8 DUMMY3			:1; 			// bit  3 : Resreved
	U8 DUMMY4			:1;			// bit  4 : Reserved
	U8 DUMMY5			:1;			// bit  5 : Reserved 
	U8 DUMMY6			:1;			// bit  6 : Resreved
	U8 DUMMY7			:1;			// bit  7 : Resreved
	U8 DUMMY8			:1;			// bit  8 : Resreved
	U8 DUMMY9			:1;			// bit  9 : Resreved
	U8 DUMMY10			:1;			// bit 10 : Resreved
	U8 DUMMY11			:1;			// bit 11 : Resreved
	U8 DUMMY12			:1;			// bit 12 : Resreved
	U8 DUMMY13			:1;			// bit 13 : Reserved
	U8 DUMMY14			:1;			// bit 14 : Reserved
	U8 DUMMY15			:1;			// bit 15 : Reserved

}st_library_flag_t;

typedef struct
{
	U8 f_lookup			:1;			// bit  0 : LUT using Enable
									//	    (On: enable , Off: disable)	
	U8 f_chpt 			:1; 			// bit  1 : Charge relearning porint
	U8 f_dspt 			:1; 			// bit  2 : Discharge relearning point
									//		   (1=CP_H, 0=CP_L)
	U8 f_initcap			:1; 			// bit  3 : InitCap Table Enable
									//		(On: enable , Off: disable) 
	U8 DUMMY4			:1;			// bit  4 : Reserved
	U8 DUMMY5			:1;			// bit  5 : Reserved 
	U8 DUMMY6			:1;			// bit  6 : Resreved
	U8 DUMMY7			:1;			// bit  7 : Resreved
	U8 DUMMY8			:1;			// bit  8 : Resreved
	U8 DUMMY9			:1;			// bit  9 : Resreved
	U8 DUMMY10			:1;			// bit 10 : Resreved
	U8 DUMMY11			:1;			// bit 11 : Resreved
	U8 DUMMY12			:1;			// bit 12 : Resreved
	U8 DUMMY13			:1;			// bit 13 : Reserved
	U8 DUMMY14			:1;			// bit 14 : Reserved
	U8 DUMMY15			:1;			// bit 15 : Reserved

}st_lut_flag_t;


typedef struct
{
	U8		au8_manufacturer_name[32];	// [32byte] 0x20:manufacturer Name
	U8		au8_manufacturer_data[32];		// [32byte] 0x23:manufacturer Data
	U8		au8_dev_name[32];			// [32byte] 0x21:DeviceName
	U8		au8_dev_chem[4];				// [4byte] 0x22:DeviceChemistry
	U16		au16_seal_pawd[2];			// [4byte] Unseal Password
}st_device_info_t;							// [104byte] device info

typedef struct
{
	U16	d_CPV_T1T2;				// 0xD938	// [2byte] ChargePause V at T1-T2
									// 0xD939	// 
	U16	d_CPV_T3T4;				// 0xD93A	// [2byte] ChargePause V at T3-T4
									// 0xD93B	//
	U16	d_CPRELT1T2;				// 0xD93C	// [2byte] ChargePause release V at T1T2
									// 0xD93D	//
	U16	d_CPRELT3T4;				// 0xD93E	// [2byte] ChargePause release V at T3T4
	U8	d_JEITA_T2; 			// 0xDAF0	// [1byte] JEITA T2
									// 0xDAF2	//	
	U8	d_JEITA_T3; 			// 0xDAF3	// [1byte] JEITA T3
	U16	d_JTCC_T1T2;				// 0xDAFA	// [2byte] CC at T1T2
	U16	d_JTCC_T2T3;				// 0xDB06	// [2byte] CC at T2T3
	U16	d_JTCC_T3T4;				// 0xDB12	// [2byte] CC at T3T4
	U16	d_JTCV_T1T2;				// 0xDB18	// [2byte] CV at T1T2
	U16	d_JTCV_T2T3;				// 0xDB1C	// [2byte] CV at T2T3
	U16	d_JTCV_T3T4;				// 0xDB20	// [2byte] CV at T3T4
}st_jeita_t;

typedef struct
{
	U16		u16_deterioration_capa_uAh;	// [2byte] Deterioration capacity [1uAh]
	U8		u8_cph_per;					// [1byte] Correction point(H) [%]
	U8		u8_cpl_per;					// [1byte] Correction point(H) [%]
	S16		s16_fcc_up_high_temp_0p1dC;	// [2byte] fcc update high temperature [0.1degC]
	S16		s16_fcc_up_low_temp_0p1dC;	// [2byte] fcc update low temperature [0.1degC]	
}st_lut_config_t;							// [25byte]

typedef struct
{
	U16		u16_charging_volt_mV;			// [2byte] 0x15:ChargingVoltage/Cell [mV]
	U16		u16_charging_current;			// [2byte] 0x14:ChargingCurrent [mA]
	U16		u16_precharge_voltage;			// [2byte] Precharge voltage [mV]
	U16		u16_precharge_current;			// [2byte] Precharge voltage [mV]
}st_normal_chg_dsg_info_t;

typedef struct
{
	U8		u8_slave_addr;				// [1byte] smbus slave address
	U8		u8_sleep_entry_time;			// [1byte] sleep entery time [min]
	U16		u16_sleep_current_mA;			// [2byte] sleep current [mA]
	U16		u16_pd_volt_mV;				// [2byte] Power down voltage [mV]
	U16		u16_cutoff_chg_curr_mA;		// [2byte] Full charge cutoff current [mA]
	U16		u16_cutoff_dsg_volt_mV;		// [2byte] Discharge cutoff voltage [mV]	
}st_system_t;								// [10byte] 


// - FlashROM fixed data definition -

typedef struct
{
	U32	au32_ther_table[21];				// [84byte] Thermistor characteristic table
}st_thermister_table_t;

typedef struct
{
	U8	au8_init_rsoc_table[6];				// [6byte] Initial capacity table
	U16	au16_init_volt_table[6];				// [12byte] Initial voltage table
}st_lut_capacity_t;

typedef struct
{
	U16 au16_imp_cycle[4];					// [8byte] impedance cycle
	U16	au16_imp_table[4];				// [8byte] Internal impedance table
}st_lut_cp_impedance_t;

typedef struct
{
	U16	au16_crate_0p01C[4];				// [8byte] CP table C-rate [0.01C]
	S16	as16_trate_0p1dC[5];				// [10byte] CP table T-rate [0.1degC]
	U16	au16_cph_volt[20];				// [40byte] Correction point High Voltage table
	U16	au16_cpl_volt[20];					// [40byte] Correction point Low Voltage table
}st_lut_cp_table_t;							// [98byte] Correction point struct

typedef struct
{
	st_device_info_t		st_device_info;		// [104byte] device info
	st_sys_config_t		st_bms_init_config;		// [6byte] bms core init info
	st_operating_profile_t	st_bms_normal_config;	// [12byte] normal config
	st_operating_profile_t	st_bms_sleep_config;	// [12byte] sleep config
	st_operating_profile_t	st_bms_sleep2_config;	// [12byte] sleep2 config
	st_operating_profile_t	st_bms_ship_config;	// [12byte] ship config
	st_afe_hw1_config_t	st_hw1_config;		// [12byte] curr config
	st_afe_hw2_config_t	st_hw2_config;		// [7byte] wkup config
	U8					u8_reserved1;			// [1byte] reserved
	st_bal_config_t		st_bal_config;			// [6byte] balancing
	st_bal_self_dsg_config_t st_self_dsg_config;		// [8byte] self discharge
	st_protection_config_t	st_bms_prot_config;	// [70byte] protection
	st_system_t			st_system_info;		// [10byte] system
	U16					u8_reserved2[4];			// [8byte]
	st_thermister_table_t	st_thermister1_table;	// [84byte] thermister 1 table
	st_thermister_table_t	st_thermister2_table;	// [84byte] thermister 2 table
	st_thermister_table_t	st_thermister3_table;	// [84byte] thermister 3 table
	st_thermister_table_t	st_thermister4_table;	// [84byte] thermister 4 table
	st_thermister_table_t	st_thermister5_table;	// [84byte] thermister 5 table
	st_control_flag1_t		st_control_flag1;		// [2byte] Control flag 1
	st_control_flag2_t		st_control_flag2;		// [2byte] Control flag 2
	st_library_flag_t		st_library_flag;			// [2byte] library flag
	st_lut_flag_t			st_lut_flag;			// [2byte] gauging flag
	st_lut_config_t			st_lut_config;			// [8byte] gaigng table
	st_lut_cp_table_t		st_lut_cp;			// [98byte] correction point
	st_lut_cp_impedance_t	st_lut_cp_imp;			// [16byte] impedance table
	st_lut_capacity_t		st_lut_init_cap;		// [18byte] init capacity table
	U8					u8_reserved3[174];	// [174byte]
	U16					u16_fixed_chekcsum;	// [2bytes] Fixed Data Checksum

}st_fixed_data_t;									// - FlashROM fixed data definition -


#define FDSIZE	sizeof(st_fixed_data_t)				// FixedData size


#pragma address st_fixed_data = 0x0FD800
GLOBAL st_fixed_data_t	st_fixed_data;

#define au8_SMB20_mfg_name	st_fixed_data.st_device_info.au8_manufacturer_name
#define au8_SMB23_mfg_data	st_fixed_data.st_device_info.au8_manufacturer_data
#define au8_SMB21_dev_name	st_fixed_data.st_device_info.au8_dev_name
#define au8_SMB22_dev_chem	st_fixed_data.st_device_info.au8_dev_chem
#define au16_seal_password		st_fixed_data.st_device_info.au16_seal_pawd

#define u8_slave_addr			st_fixed_data.st_system_info.u8_slave_addr
#define u16_sleep_current		st_fixed_data.st_system_info.u16_sleep_current_mA


U8 InitFixed_Chk(void);	
U8 FLASH_Check_FixedData(void);

#undef		GLOBAL

#endif	// _FLASHROM_H


