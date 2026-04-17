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


// - Function declaration -
void MoveToFlashUpdate(void);		// Move to Flash update mode
void FlashWrite_Key(void);

// - Control flag definition -
typedef struct
{
	//Basic Control
	U8 f_start_ship		:1;			// bit 0 : Start from ship mode
									//(On: enable , Off: disable)

	U8 DUMMY3			:1;			// bit  3 : Resreved
	U8 DUMMY4			:1;			// bit  4 : Resreved
	U8 DUMMY5			:1;			// bit  5 : Resreved
	U8 DUMMY6			:1;			// bit  6 : Resreved
	U8 DUMMY7			:1;			// bit  7 : Resreved
	U8 f_jeita			:1;			// bit  1 : JEITA Enable
									//	    (On: enable , Off: disable)	
	U8 f_sf_dis			:1; 		// bit	3 : Self discharge Enable
									//		(On: enable , Off: disable)
	U8 f_cben 		:1; 		// bit	0 : Cell Balancing Enable
									//		(On: enable , Off: disable)

	U8 DUMMY9			:1;			// bit  9 : Resreved
	U8 DUMMY10		:1;			// bit 10 : Resreved
	U8 DUMMY11		:1;			// bit 11 : Resreved
	U8 DUMMY12		:1;			// bit 12 : Resreved
	U8 DUMMY13		:1;			// bit 13 : Resreved
}st_control_flag1_t;

typedef struct
{
	//Intermediate Control

	U8 f_pinshutdown	:1; 		// bit 1 : PIN Shutdown Enable
									//(On: shutdown , Off: shipmode)

	U8 f_calib1p			:1;			// bit  2 : Initial Calibration 1Point Enable
									//	    (On: enable , Off: disable)

	U8 DUMMY4			:1;			// bit  4 : Reserved
	U8 DUMMY5			:1;			// bit  5 : Reserved
	U8 DUMMY6			:1;			// bit  6 : Resreved
	U8 DUMMY7			:1;			// bit  7 : Resreved

	U8 DUMMY8			:1;			// bit	9 : Resreved

	U8 DUMMY13		:1;			// bit 13 : Reserved
	U8 f_pinshutdown	:1;			// bit 14 : PIN Shutdown Enable
									// 		(On: enable , Off: disable)
	U8 f_forcepd		:1;			// bit 15 : Force PD Enable
									// 		(On: enable , Off: disable)


}st_control_flag2_t;

typedef struct
{

	
	U8 f_lookup			:1;			// bit  8 : LUT using Enable
									//	    (On: enable , Off: disable)	
	U8 f_chpt 		:1; 		// bit 10 : Charge relearning porint
	U8 f_dspt 		:1; 		// bit 11 : Discharge relearning point
									//		   (1=CP_H, 0=CP_L)
	U8 f_initcap			:1; 		// bit 12 : InitCap Table Enable
									//		(On: enable , Off: disable) 

	U8 DUMMY1			:1;			// bit  1 : Reserved
	U8 DUMMY2			:1;			// bit  2 : Reserved
	U8 DUMMY3			:1;			// bit  3 : Reserved
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

}st_control_flag3_t;

typedef struct
{
	U8		au8_manufacturer_name[32];	// [32byte] 0x20:manufacturer Name
	U8		au8_manufacturer_data[32];		// [32byte] 0x23:manufacturer Data
	U8		au8_dev_name[32];			// [32byte] 0x21:DeviceName
	U8		au8_dev_chem[4];				// [4byte] 0x22:DeviceChemistry
	U8		u32_design_capacity;			// [2byte] 0x18:DesignCapacity [mAh]
	U8		au8_seal_pawd[4];				// [4byte] Unseal Password
	U8		au8_reserved[20];				// [20byte] Reserved
}st_device_info_t;

typedef struct
{
	U8		u8_cell_series;					// [1byte] Series number of cell
	U8		u8_thermistor_num;			// [1byte] number of thermistor
	U8		u8_thermistor_bit;				// [1byte] used thermistor bit
	U8		u8_shunt_R_0p1mOhm;			// [1byte] Board shunt resistance
	U16		u16_mask_current_mA;			// [2byte] Mask Current (Charge or Discharge or Idle)
}st_bms_core_init_t;

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
	U8 u8_base_fet_bit;

	U8 u8_ad_period_125ms_n;
	U8 u8_cc_period_250ms_n;
	
	U8 u8_consumption_current;				// [1byte] Consumption current [mA]

	U16 u16_wakeup_policy_bit;

	st_protection_policy_t st_prot_policy;

}st_bms_core_mode_t;

typedef struct
{
	U16		u16_full_charge_voltage;		// [2byte] Full charge judgment voltage [mV]
	U16		u16_full_charge_current;		// [2byte] Full charge judgment current [mA]
	U16		u16_full_discharge_voltage;		// [2byte] 0% voltage [mV]
	U8		u8_deterioration_capacity;		// [1byte] Deterioration capacity [1mAh]
	U8		u8_correction_point_high;		// [1byte] Correction point(H) [%]
	U8		u8_correction_point_low;		// [1byte] Correction point(H) [%]
	U8		au8_reserved[20];				// [20byte] Reserved
}st_gauging_info_t;

typedef struct
{
	U16		u16_charging_voltage;			// [2byte] 0x15:ChargingVoltage/Cell [mV]
	U16		u16_charging_current;			// [2byte] 0x14:ChargingCurrent [mA]
	U16		u16_precharge_voltage;			// [2byte] Precharge voltage [mV]
	U16		u16_precharge_current;			// [2byte] Precharge voltage [mV]

	U8		au8_reserved[20];				// [20byte] Reserved
}st_charger_info_t;

typedef struct
{
	U8		u8_force_ship_entry_time;		// [1byte] Force ship mode entry delay time [sec]
	U16		u16_sleep_current;				// [2byte] sleep current [mA]
	
	U8		au8_reserved[20];				// [20byte] Reserved
}st_system_t;

typedef struct
{
	U16		u16_powerdown_voltage;		// [2byte] Power down voltage [mV]		
	U8		u8_force_ship_entry_time;		// [1byte] Force ship mode entry delay time [sec]


	U8		au8_reserved[20];				// [20byte] Reserved
}st_operating_t;
typedef struct
{
	U8		u8_slave_addr;				// [1byte] smbus slave address	
	U8		u8_charger_addr;				// [1byte] charge address
}st_smbus_t;

// - FlashROM fixed data definition -

typedef struct
{
	U32	au32_ther_table[21];				// [21byte] Thermistor characteristic table
}st_thermister_table_t;

typedef struct
{
	U8	au8_init_rsoc_table[6];					// [5byte] Initial capacity table
	U16	au16_init_volt_table[6];					// [10byte] Initial voltage table
}st_init_capacity_t;

typedef struct
{
	U8	au8_imp_table[4];						// [4bytes] Internal impedance table
}st_impedance_t;

typedef struct
{
	U8	u8_cph;					// [1byte] Correction point(H) [%]
	U8	u8_cpl;					// [1byte] Correction point(L) [%]
	U8	au8_crate[4];				// [4byte] CP table C-rate [0.01C]
	S8	au8_trate[6];				// [5byte] CP table T-rate [-128Åé]
	U16	au16_cph_volt[20];		// [40byte] Correction point High Voltage table
	U16	au16_cpl_volt[20];			// [40byte] Correction point Low Voltage table
}st_correction_point_t;

typedef struct
{
	st_device_info_t st_device_info;
	st_bms_core_init_t st_bms_init_config;
	st_bms_core_mode_t st_bms_normal_config;
	st_bms_core_mode_t st_bms_sleep_config;
	st_bms_core_mode_t st_bms_sleep2_congfig;
	st_bms_core_mode_t st_bms_ship_config;
	st_afe_hw1_config_t st_hw1_config;
	st_afe_hw2_config_t st_hw2_config;
	st_bal_config_t st_bal_config;
	st_bal_self_dsg_config_t st_self_dsg_config;
	st_protection_config_t st_bms_prot_config;
	st_thermister_table_t st_thermister1_table;
	st_thermister_table_t st_thermister2_table;
	st_thermister_table_t st_thermister3_table;
	st_thermister_table_t st_thermister4_table;
	st_thermister_table_t st_thermister5_table;
	st_control_flag1_t	st_control_flag1;			//[2byte] Control flag 1
											//
	st_control_flag2_t	st_control_flag2;			// [2byte] Control flag 2
											//
	st_control_flag2_t	st_control_flag3;			// [2byte] Control flag 2
	st_smbus_t st_smbus;
	st_init_capacity_t st_init_cap;
	st_correction_point_t st_cp;
	st_impedance_t st_imp;					

	U16	u16_fixed_chekcsum;					// [2bytes] Fixed Data Checksum
	
	
}st_fixed_data_t;									// - FlashROM fixed data definition -


#define FDSIZE	sizeof(st_fixed_data_t)				// FixedData size


#pragma address st_fixed_data = 0x0FD800
GLOBAL st_fixed_data_t	st_fixed_data;

						

U8 InitFixed_Chk(void);	

#undef		GLOBAL

#endif	// _FLASHROM_H



