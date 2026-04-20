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
* File Name		: smbus.h
* Version			: 0.01
* Contents		: SMBus function header file
* Customer		: Renesas Electronics Corp.
* Model			: RAJ240xxx RBMS-M
* Order			: 
* CPU			: RAJ240xxx
* Compiler		: CC-RL (V1.08.00)
* Note			: 
************************************************************************
* Copyright,2020 (2012-2020) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
************************************************************************
* History		: 2020.10.01 Ver 0.01
* 				: Replace overall
*				: 
*""FILE COMMENT END""*****************************************************/
#ifndef _SMBUS_H
#define _SMBUS_H

#ifdef	_SMBUS
#define		GLOBAL
#else	// _SMBUS
#define		GLOBAL	extern
#endif	// _SMBUS

#include "define.h"

// - Function declaration -
void SMBus_initialize(void);						// SMBus initializing
void SMBus_timeout_check(void);					// SMBus timeout check
void SMBus_state_check(void);					// SMBus state check

// - Grobal variable -
typedef struct									// SMBus comm. information
{
	U8			u8_status;					// SMBus status
	U8			u8_len;						// SMBus data size
	__near U8		*p8_data;				// Pointer of SMBus data
} st_smb_frame_t;

typedef union
{
	U8	u8_data[34];
	U16	u16_data[17];
} st_smbus_buff_t;

GLOBAL st_smb_frame_t		st_smb_frame;

GLOBAL st_smbus_buff_t		st_smbus_buff;				// SMBus buffer
#define au8_smb_buff		st_smbus_buff.u8_data
#define au16_smb_buff		st_smbus_buff.u16_data

GLOBAL U8				u8_received_cmd;				// Receive command
GLOBAL U8				u8_smb_num;					// SMBus communicated number

GLOBAL U8				u8_pec;						// PEC
GLOBAL U8				u8_received_addr;				// Received Slave address

GLOBAL U8				u8_smbus_s_timeout_cnt;		// Slave timeout counter
GLOBAL U8				u8_smbus_scl_timeout_cnt;		// SCL timeout counter
GLOBAL U16				u16_smbus_no_timeout_cnt;		// No SMBus time counter
GLOBAL U8				u8_smbus_scl_hold_cnt;			// SCL Low hold counter
GLOBAL U8				u8_smbus_sda_hold_cnt;		// SDA Low hold counter
GLOBAL U8				u8_smbus_off_cnt;					// Off state counter
GLOBAL U8				u8_smbus_on_cnt;					// On state counter

GLOBAL U16				u16_tsmbus_flg;				// Flags for SMBus
#define f_nosmb			DEF16_BIT0(&u16_tsmbus_flg)	// No communication flag
#define f_recv				DEF16_BIT1(&u16_tsmbus_flg)	// Data received flag
#define f_wwpec			DEF16_BIT2(&u16_tsmbus_flg)	// PEC sent flag
#define f_comerr			DEF16_BIT3(&u16_tsmbus_flg)	// Communication error flag
#define f_slvto_req			DEF16_BIT6(&u16_tsmbus_flg)	// Slave timeout check req.
#define f_sclto_req			DEF16_BIT7(&u16_tsmbus_flg)	// SCL timeout check req.
#define f_tm01_using		DEF16_BIT8(&u16_tsmbus_flg)	// TM01 using flag

// - IIC Register setting -
#define U8_IICWL0_400KHz			0x0A					// IICWL0 setting for 400KHz
#define U8_IICWH0_400KHz			0x07						// IICWH0 setting for 400KHz
#define U8_IICCTL01_400KHz		0x0C					// IICCTL01 setting for 400KHz
#define U8_IICWL0_100KHz			0x26						// IICWL0 setting for 100KHz
#define U8_IICWH0_100KHz			0x28						// IICWH0 setting for 100KHz
#define U8_IICCTL01_100KHz		0x00						// IICCTL01 setting for 100KHz

#define U8_SMBUS_TIMEOUT			25

typedef enum{
	E_SMBUS_ERR_OK = 0,							/* OK */
	E_SMBUS_ERR_BUSY,							/* Busy */
	E_SMBUS_ERR_RESV,							/* Reserved Command */
	E_SMBUS_ERR_UNSPT,							/* Unsupported Command */
	E_SMBUS_ERR_ACSSD,							/* Access Denied */
	E_SMBUS_ERR_OVFLW,							/* Overflow/Underflow */
	E_SMBUS_ERR_BADSIZE,						/* Bad Size */
	E_SMBUS_ERR_UNKNOW,						/* Unknoun Error */
	E_SMBUS_ERR_NUM							/* Access Denied */
}E_SMBUS_ERR_ITEM;

GLOBAL E_SMBUS_ERR_ITEM e_smbus_err_code;
// - enum definition -
enum{ 											/*  - SMBus status - */
	SADR_CHK,									/*  Slave address check */
	CMD_CHK,									/*  Command check */
	RW_CHK,										/*  Read/Write check */
	RS_SADR_CHK,								/*  ReStart Slave address check */
	READ_SEND,									/*  Read data send */
	WRITE_RCV,									/*  Write data receive */
	BW_SIZE_CHK,								/*  BlockWrite size check */
	SMBUS_ERR									/*  SMBus error */
}E_SMBUS_STATUS_ITEM;

#undef		GLOBAL

#endif	// _SMBUS_H



