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
* File Name		: smbus_custom.h
* Version		: 0.01
* Contents		: SMBus function (custom) header file
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
* History		: 2020.10.12 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#ifndef _SMBUS_CUSTOM_H
#define _SMBUS_CUSTOM_H

#ifdef	_SMBUS_CUSTOM
#define		GLOBAL
#else	// _SMBUS_CUSTOM
#define		GLOBAL	extern
#endif	// _SMBUS_CUSTOM


// - Function declaration -
U8 SMB_ReceiveCommand(void);						// Receive command
void SMB_SetReadData(void);							// Set Read data to the buffer
void SMB_StoreReceiveData(void);						// Store received data
void SMB_custom_StopCondition(void);						// Function of Stop condition
void SMB_custom_SlaveComm(void);							// Function of Slave comm.
void SMB_custom_SlaveAddress_receive(void);				// Function of receive SAdr.
void SMB_custom_SCLSDA(void);								// Function of SCL/SDA int.

void ExtraFunction(void);								// ExtraFunction()
void Seal_Proc(void);									// Seal/Unseal()


// - Grobal variable -
GLOBAL U16					tfwsum;						// SUM of Firmware
GLOBAL U16					tfixsum;					// SUM of Fixed data

GLOBAL u16_byte_t		u16_extra_func;					// 0x40:ExtraFunction()
#define u16_extfunc		u16_extra_func.u16_data
#define au8_extfunc		u16_extra_func.u8_data

GLOBAL U16					u16_extra_func_flag;				// Flags for ExtraFunction()
#define f_extfunc_en1			DEF16_BIT0(&u16_extra_func_flag)	// 1st enable flag
#define f_extfunc_en2			DEF16_BIT1(&u16_extra_func_flag)	// 2nd enable flag
#define f_extfunc_ramw			DEF16_BIT2(&u16_extra_func_flag)	// RAM write flag
#define f_comjib				DEF16_BIT3(&u16_extra_func_flag)	// Force PowerDown flag
#define f_hldtmin				DEF16_BIT4(&u16_extra_func_flag)	// FCC relearn cancel. unit (OFF = hours, ON = minutes)
#define f_force_fetoff_ent		DEF16_BIT5(&u16_extra_func_flag)	// Force fet OFF Entery
#define f_force_fetoff_ext		DEF16_BIT6(&u16_extra_func_flag)	// Force fet OFF Exit
#define f_compf1				DEF16_BIT7(&u16_extra_func_flag)	// Force PF flag

GLOBAL U16						u16_seal;								// Seal status
#define STS_SEAL					0x0000							// Status of Seal
#define STS_UNSEAL				0x0001							// Status of Unseal

// - Define definition -
#define DATA_EXTFUNC_DIS			0x0000					// ExtraFunction disable data
#define DATA_EXTFUNC_EN			0x0080					// ExtraFunction enable data



#undef		GLOBAL

#endif	// _SMBUS_CUSTOM_H



