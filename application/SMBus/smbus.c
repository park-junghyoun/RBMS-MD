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
* File Name		: smbus.c
* Version		: 0.01
* Contents		: SMBus functions
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
* History		: 2020.10.06 Ver 0.01
* 				: Replace overall
* 
*""FILE COMMENT END""**************************************************/
#define _SMBUS

// - Interrupt routine definition -
#include "define.h"								// union/define definition
#pragma interrupt _int_SMBus(vect=INTIICA0)
#pragma interrupt _int_SCLSDA(vect=INTP0)

// - Include header file -
#include "flashrom.h"							// FlashROM data definition
#include "dataflash_custom.h"
#include "ram.h"
#include "smbus.h"
#include "smbus_custom.h"
#include "mode.h"
#include "afe.h"
#include "uif.h"
#include "dataflash.h"



// - Internal function declaration -
void SlaveAddress_check(void);					// Slave address check
void Command_check(void);						// Command check
void ReadWrite_check(void);						// Read/Write check
void ReStart_check(void);						// ReStart condition check
void BlockWrite_size_check(void);				// BlockWrite data size check
void Read_data_send(void);						// Read data sending
void Write_data_receive(void);					// Write data receiving
void SMBus_error(void);							// SMBus error
void SMBus_error_nak(void);						// SMBus error with NAK
void Send_ACK(void);							// Send ACK

U8	au8_m_smbus_buff[5];								// Master send buffer

// - Internal variable -
static const __near DWORD SMBusFunction_table[] = {
												// SMBus function table
	(DWORD)SlaveAddress_check,					// Slave address check
	(DWORD)Command_check,						// Command check
	(DWORD)ReadWrite_check,						// Read/Write check
	(DWORD)ReStart_check,						// Restart condition check
	(DWORD)Read_data_send,						// Read data sending
	(DWORD)Write_data_receive,					// Write data receiving
	(DWORD)BlockWrite_size_check,				// BlockWrite data size check
	(DWORD)SMBus_error							// SMBus error function
};

#define		CRC8TBL				((U8 (*)(U8))(0x0FBA0))

// - Define definition -
#define CRC8_Calc(a)	u8_pec = CRC8TBL(a^u8_pec)	// PEC calculation macro

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: PEC calculation function for Master communication
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void CRC8_Master(void)
*-------------------------------------------------------------------
* Function			:  Calculate PEC when master communication.
*					:
*-------------------------------------------------------------------
* Argument			:  None
*-------------------------------------------------------------------
* Return			:  None
*-------------------------------------------------------------------
* Input				:  None
* Output			:  None
*-------------------------------------------------------------------
* 					: 
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2012.08.01
*	 				: New create
*					: 
*""FUNC COMMENT END""**********************************************/
void CRC8_Master(void)
{
	au8_m_smbus_buff[0] = CRC8TBL(au8_m_smbus_buff[1] ^ CRC8TBL(au8_m_smbus_buff[2] ^ CRC8TBL(au8_m_smbus_buff[3] ^ CRC8TBL(au8_m_smbus_buff[4]))));
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus initializing function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMBus_initialize(void)
*-------------------------------------------------------------------
* Function			: Initializing SMBus.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMBus_initialize(void)
{
	PM6 |= 0x03;							// PM60,PM61 = INPUT
	P6 &= 0xFC;								// P60,P61 = LOW

	IICA0EN = 1;							// Enable IICA0 input clock
	IICE0 = 0;								// IIC disable
	IICAMK0 = 1;							// IICA0 interrupt disable
	IICAIF0 = 0;							// Clear IICA0 interrupt
	IICAPR00 = 1;							// IICA0 interrupt priority
	IICAPR10 = 0;							//   Level 1

	IICWL0 = IICWL0_100KHz;					// IICA Low Level width setting
	IICWH0 = IICWH0_100KHz;					// IICA High Level width setting
	IICCTL01 = IICCTL01_100KHz;				// IICA control register 01
	

	if( st_fixed_data.st_smbus.u8_slave_addr!= 0xFF					// the value is not 0xFF/0x00 ?
		&& st_fixed_data.st_smbus.u8_slave_addr != 0x00 )
	{
		SVA0 = st_fixed_data.st_smbus.u8_slave_addr;					// SMBus Slave address = Specified
	} else {								// Set default Slave address
		SVA0 = 0x16;						// SMBus Slave address = 0x16
	}

	IICCTL00 = 0x04;						// IICA control register 00
	STCEN0 = 0;								// StartCond. enable after StopCond
	IICRSV0 = 1;							// Disable comm. reservation
	IICE0 = 1;								// IICE0 enable
	LREL0 = 1;								// Exit from current communication
	PM6 &= 0xFC;							// PM60,PM61 = OUTPUT

	// - RAM Initializing for SMBus -
	st_smb_frame.u8_status = SADR_CHK;					// SMBus status: Slave adr. check
	u16_tsmbus_flg = 0;							// Clear all flags for SMBus
	u8_smbus_m_timeout_cnt = 0;							// Clear Master timeout counter
	u8_smbus_s_timeout_cnt = 0;							// Clear Slave timeout counter
	u8_smbus_scl_timeout_cnt = 0;							// Clear SCL timeout counter

	// - Initializing SCL/SDA interrupt (INTP0) -
	EGP0.0 = 0;								// SCL/SDA interrupt edge
	EGN0.0 = 1;								// falling edge
	PPR00 = 1;								// SCL/SDA interrupt priority
	PPR10 = 0;								// Level 1
	PIF0 = 0;								// Clear SCL/SDA Interrupt flag
	PMK0 = 0;								// SCL/SDA interrupt enable

	IICAIF0 = 0;							// Clear IICE0 interrupt
 	IICAMK0 = 0;							// IICE0 interrupt enable
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus timeout function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMBus_timeout(void)
*-------------------------------------------------------------------
* Function			: Execute SMBus timeout.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMBus_timeout(void)
{
	if( f_tm01_using == OFF )				// Not using TM01 ?
	{
		TT0L.1 = 1;							// Stop timer TM01(1msec timer)
	}
	SMBus_initialize();						// SMBus initializing
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: IIC interrupt function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void _int_SMBus(void)
*-------------------------------------------------------------------
* Function			: IIC interrupt function.
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
* History			: 2020.10.08 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void _int_SMBus(void)
{
	WUP0 = 0;								// Wakeup disable
	NOP();									// wait 5clock
	NOP();
	NOP();
	NOP();
	NOP();

	if( SPD0 == 1							// Stop condition ?
	  || (STD0 == 1							// Considering in case of receiving
		&& (st_smb_frame.u8_status == READ_SEND			// start condition before interrupt
		  || st_smb_frame.u8_status == WRITE_RCV)) )		// of stop condition.
	{
		if( f_slvto_req == ON )				// Start condition is received ?
		{
			WTIM0 = 0;						// Set IIC interrupt by 8 clock
			if( f_comerr == OFF )			// No communication error ?
			{
				if( f_recv == ON )			// Data received ?
				{
											// Store received data
					__SMB_StoreReceiveData();
				}
				e_smbus_err_code = ERR_OK;			// Error code = OK
				__custom_StopCondition();	// Custom function when Stop cond.
			}

			f_recv = OFF;					// Clear data received flag
			f_comerr = OFF;					// Clear comm. error flag
			f_wwpec = OFF;					// Clear PEC sent flag
			st_smb_frame.u8_status = SADR_CHK;			// SMBus status: Slave adr. check
			if( (COI0 == ON || EXC0 == ON)	// Slave address match
				&& ACKD0 == ON				// & ACK detected
				&& CLD0 == LOW )			// & CLK = LOW ?
			{								// (next communication received)
				IICAIF0 = 0;				// Clear IIC interrupt request
				SlaveAddress_check();		// Slave address check
			} else {						// No next communication
				// Note: f_tm01_using should be set if other function use TM01.
				if( f_tm01_using == OFF )	// Not using TM01 ?
				{
					TT0L.1 = 1;				// Stop timer TM01(1msec timer)
				}
				f_slvto_req = OFF;			// Clear slave timeout check req.
				tnosmb_cnt = 0;				// Clear no comm time counter
				f_nosmb = OFF;				// Clear no comm flag
				f_sclto_req = OFF;			// Clear SCL timeout check req.
				PIF0 = 0;					// Clear SCL/SDA interrupt request
				PMK0 = 0;					// SCL/SDA interrupt enable
				SPIE0 = OFF;				// Disable Stop condition interrupt
			}
		} else {							// Start condition is not receive
			st_smb_frame.u8_status = SADR_CHK;			// SMBus status: Slave adr. check
			if( (COI0 == ON || EXC0 == ON)	// Slave address match
				&& ACKD0 == ON				// & ACK detected
				&& CLD0 == LOW )			// & CLK = LOW ?
			{								// (next communication received)
				IICAIF0 = 0;				// Clear IIC interrupt request
				SlaveAddress_check();		// Slave address check
			} else {
				PIF0 = 0;					// Clear SCL/SDA interrupt request
				PMK0 = 0;					// SCL/SDA interrupt enable
				SPIE0 = OFF;				// Disable Stop condition interrupt
			}
		}

	} else {								// Not stop condition

		if( f_master == OFF )				// Slave communication ?
		{
											// Operates current SMBus status
			((void(*)(void))SMBusFunction_table[st_smb_frame.u8_status])();
			tnosmb_cnt = 0;					// Clear no comm time counter
			f_nosmb = OFF;					// Clear no comm flag
			f_sclto_req = OFF;				// Clear SCL timeout check req.
			__custom_SlaveComm();			// Custom function when Slave comm.
			
		} else {							// Master communication
			u8_smbus_m_timeout_cnt = 0;					// Clear master timeout counter
			if( ALD0 == OFF )				// Not arbitration lost ?
			{
				if( ACKD0 == 1 )			// Received ACK ?
				{					
					if( u8_smb_num == 0xFF )	// Completed to send ?
					{
						SPT0 = 1;			// Make stop condition
						f_mstto_req = OFF;	// Clear master timeout check req.
						f_master = OFF;		// Clear master comm flag
					} else {				// Sending
											// Set send data to IICA0 reg.
						IICA0 = au8_m_smbus_buff[u8_smb_num];
						u8_smb_num--;			// Count communicated number
					}
				} else {					// Received NAK
					st_smb_frame.u8_status = SADR_CHK;	// SMBus status: Slave adr. check
					SPT0 = 1;				// Make stop condition
					f_mstto_req = OFF;		// Clear master timeout check req.
					f_master = OFF;			// Clear master comm flag
				}
				u8_smbus_scl_timeout_cnt = 0;				// Clear SCL timeout counter
				f_sclto_req = ON;			// Set SCL timeout check req.
			} else {						// Detect arbitration lost
				f_mstto_req = OFF;			// Clear master timeout check req.
				f_master = OFF;				// Clear master comm flag
				if( TRC0 == OFF )			// Receiving condition ?
				{
					if( COI0  == ON )		// Slave address match ?
					{	
						SlaveAddress_check();// Slave address check
					} else {				// Slave address mismatch
						LREL0 = 1;			// Exit from communication
					}
				}
			}
		}
	}
	aclklow_cnt = 0;						// Clear low hold counter
	asdalow_cnt = 0;
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus timeout checking function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMBus_timeout_check(void)
*-------------------------------------------------------------------
* Function			: Checking SMBus timeout.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMBus_timeout_check(void)
{
	if( u8_smbus_m_timeout_cnt >= 10 )					// Master timeout(10ms) detected ?
	{
		SPT0 = 1;							// Make stop condition
		LREL0 = 1;
		f_master = OFF;	
		f_mstto_req = OFF;					// Clear master timeout check req.
		
	} else {
		if( u8_smbus_s_timeout_cnt < 25					// No Slave timeout(25ms)
			&& u8_smbus_scl_timeout_cnt < 25 )			// & No SCL timeout(25ms) detect ?
		{
			return;
		}
	}
	SMBus_timeout();						// SMBus timeout function
	// Note: Flags and counters should be cleared in SMBus initializing
	//       function through SMBus timeout function.
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus Slave address checking function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SlaveAddress_check(void)
*-------------------------------------------------------------------
* Function			: Function when receiving slave address after start
*					:  condition.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SlaveAddress_check(void)
{
	u8_received_addr = IICA0;						// Get received data as SlaveAdr.
	if( COI0 == ON							// Slave address match
		&& EXC0 == OFF )					// & not extend code ?
	{
		SPIE0 = ON;							// Enable stop condition interrupt
		PMK0 = 1;							// Disable SCL/SDA interrupt
		
		__custom_SlaveAddress_receive();	// custom function when
											// Slave address receiving
		if( TRC0 == 0 )						// R/W Bit is Write ?
		{
			u8_pec = 0;						// Initialize PEC
			CRC8_Calc(u8_received_addr);			// Calculate PEC
			st_smb_frame.u8_status = CMD_CHK;				// Receive mode: Command check
			WTIM0 = 0;						// Set IIC interrupt by 8 clock
			WREL0 = 1;						// Wait release
		} else {							// R/W Bit is Read
			e_smbus_err_code = ERR_UNSPT;			// Error code: Unsupported
			SMBus_error_nak();				// Error with Nak
		}
	} else {								// Slave address mismatch
		e_smbus_err_code = ERR_UNKNOW;				// Error code: Unknown error
		LREL0 = 1;							// Exit from communication
	}

	TT0L.1 = 1;								// Stop timer TM01(1msec timer)
	while( TE0L.1 == ON );					// Wait until timer stop
	TS0L.1 = 1;								// Start timer TM01(1msec timer)
	u8_smbus_s_timeout_cnt = 0;							// Clear slave timeout counter
	f_slvto_req = ON;						// Set slave timeout check req.
	f_sclto_req = OFF;						// Clear SCL timeout check req.
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus Command checking function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Command_check(void)
*-------------------------------------------------------------------
* Function			: Function when receiving command.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Command_check(void)
{
	if( EXC0 == OFF )						// Not extend code ?
	{
		arcv_cmd = IICA0;					// Set received data as command
		CRC8_Calc(arcv_cmd);				// Calculate PEC
		if( __SMB_ReceiveCommand() )		// Valid command ?
		{
			u8_smb_num = 0;					// Clear communicated number
			Send_ACK();						// Send ACK
			if( arcv_cmd != 0x16 )			// Command is not BatteryStatus() ?
			{
				e_smbus_err_code = ERR_OK;			// Error code: OK
			}
		} else {							// Undefine command
			e_smbus_err_code = ERR_UNSPT;			// Error code: Unsupported
			SMBus_error_nak();				// Error with Nak
		}
	} else {								// Extend code
		e_smbus_err_code = ERR_UNKNOW;				// Error code: Unknown error
		SMBus_error_nak();					// Error with Nak
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus Read/Write checking function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void ReadWrite_check(void)
*-------------------------------------------------------------------
* Function			: Check the communication is Read or Write when
*					: receiving command supporting both Read and Write.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void ReadWrite_check(void)
{
	U8	aiic_dat;						// Receive data

	aiic_dat = IICA0;						// Set received data
	CRC8_Calc(aiic_dat);					// Calculate PEC
	if( TRC0 == 1 )							// Read ?
	{
		if( COI0 == ON						// Slave address match
			&& EXC0 == OFF )				// & not extend code ?
		{
			__SMB_SetReadData();			// Set Read data to the buffer
			if( st_smb_frame.u8_len == 0 )				// ReadWord ?
			{
				st_smb_frame.u8_len = 2;				// Set Data size = 2
			} else {						// BlockRead
				st_smb_frame.u8_len++;					// Increment data size
											// (for the data of length)
			}
			CRC8_Calc(au8_smb_buff[u8_smb_num]);	// Calculate PEC
			WTIM0 = 1;						// Set IIC interrupt by 9 clock
			IICA0 = au8_smb_buff[u8_smb_num];		// Send data
			st_smb_frame.u8_status = READ_SEND;			// Receive mode: Send Read data
		} else {
			e_smbus_err_code = ERR_UNKNOW;			// Error code: Unknown error
			SMBus_error_nak();				// Error with Nak
		}
	} else {								// Write
		if( STD0 == OFF )					// No start condition ?
		{
			// Note: st_smb_frame.u8_len should be set to 0 when U16 communication.
			if( st_smb_frame.u8_len == 0 )				// WriteWord ?
			{
				st_smb_frame.u8_len = 2;				// Set Data size = 2
											// Set received data
				au8_smb_buff[u8_smb_num] = aiic_dat;
				u8_smb_num++;					// Count communicated number
				st_smb_frame.u8_status = WRITE_RCV;		// Receive mode: Receive write data
				Send_ACK();					// Send ACK
			} else {						// BlockWrite
				if( st_smb_frame.u8_len >= aiic_dat )	// Received length is in the range?
				{
					st_smb_frame.u8_len = aiic_dat;	// Set data size
					st_smb_frame.u8_status = WRITE_RCV;	// Receive mode: Receive write data
					Send_ACK();				// Send ACK
				} else {					// Over the length
											// Error code: Bad size
					e_smbus_err_code = ERR_BADSIZE;
					SMBus_error_nak();		// Error with Nak
				}
			}
		} else {							// Detect start condition
			e_smbus_err_code = ERR_UNKNOW;			// Error code: Unknown error
			SMBus_error_nak();				// Error with Nak
		}
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus ReStart condition checking function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void ReStart_check(void)
*-------------------------------------------------------------------
* Function			: Function when receiving slave address after
*					:  Re-start condition.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void ReStart_check(void)
{
	U8	aiic_dat;						// Receive data

	aiic_dat = IICA0;						// Store received data
	CRC8_Calc(aiic_dat);					// Calculate PEC

	if( COI0 == ON							// Slave address match
		&& EXC0 == OFF						// & not extend code
		&& TRC0==1 )						// & Read ?
	{
		__SMB_SetReadData();				// Set Read data to the buffer
		if( st_smb_frame.u8_len == 0 )					// ReadWord ?
		{
			st_smb_frame.u8_len = 2;					// Set Data size = 2
		} else {							// BlockRead
			st_smb_frame.u8_len++;						// Increment data size
											// (for the data of length)
		}
		CRC8_Calc(au8_smb_buff[u8_smb_num]);		// Calculate PEC
		WTIM0 = 1;							// Set IIC interrupt by 9 clock
		IICA0 = au8_smb_buff[u8_smb_num];			// Send data
		st_smb_frame.u8_status = READ_SEND;				// Receive mode: Send read data
	} else {
		e_smbus_err_code = ERR_ACSSD;				// Error code: Access Denied
		SMBus_error_nak();					// Error with Nak
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus BlockWrite size checking function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void BlockWrite_size_check(void)
*-------------------------------------------------------------------
* Function			: Function when receiving data size of BlockWrite.
*					: 
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
* Caution			: This function may not be used if there is not
*					: protocol of only BlockWrite.
*-------------------------------------------------------------------
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void BlockWrite_size_check(void)
{
	U8	aiic_dat;						// Receive data

	if( TRC0 == 0							// Write ?
		&&  STD0 == OFF )					// & No start condition ?
	{
		aiic_dat = IICA0;					// Set received data
		if( st_smb_frame.u8_len >= aiic_dat )			// Data length is same as spec ?
		{
			CRC8_Calc(aiic_dat);			// Calculate PEC
			st_smb_frame.u8_len = aiic_dat;			// Set data size
			st_smb_frame.u8_status = WRITE_RCV;			// Receive mode: Receive write data
			Send_ACK();						// Send ACK
		} else {							// data length mismatch
			e_smbus_err_code = ERR_BADSIZE;			// Error code: Bad Size
			SMBus_error_nak();				// Error with Nak
		}
	} else {
		e_smbus_err_code = ERR_UNSPT;				// Error code: Unsupported
		SMBus_error_nak();					// Error with Nak
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus Read data sending function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Read_data_send(void)
*-------------------------------------------------------------------
* Function			: Send ReadWord and BlockRead data.
*					: 
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Read_data_send(void)
{
	if( EXC0 == OFF )						// Not extend code ?
	{
		if( u8_smb_num < st_smb_frame.u8_len )			// Not complete to send yet ?
		{
			u8_smb_num++;						// Count communicated number
			if( u8_smb_num == st_smb_frame.u8_len )		// Send complete ?
			{
				if( ACKD0 == 0 )			// NAK ?
				{
					WTIM0 = 0;				// Set IIC interrupt by 8 clock
					ACKE0 = 0;				// ACK disable
					WREL0 = 1;				// Wait release
				} else {					// ACK
					IICA0 = u8_pec;			// Send PEC
				}
			} else {						// Not complete to send yet
				if( ACKD0 == 1 )			// ACK ?
				{
											// Calculate PEC
					CRC8_Calc(au8_smb_buff[u8_smb_num]);
											// Output data
					IICA0 = au8_smb_buff[u8_smb_num];
				} else {					// NAK
					e_smbus_err_code = ERR_UNKNOW;	// Error code: Unknown error
					SMBus_error();			// SMBus error
				}
			}
		} else {							// Already completed to send
			if( ACKD0 == 0 )				// NAK ?
			{
				WTIM0 = 0;					// Set IIC interrupt by 8 clock
				ACKE0 = 0;					// ACK disable
				WREL0 = 1;					// Wait release
			} else {
				e_smbus_err_code = ERR_UNKNOW;		// Error code: Unknown error
				SMBus_error();				// SMBus error
			}
		}
	} else {
		e_smbus_err_code = ERR_UNKNOW;				// Error code: Unknown error
		SMBus_error();						// SMBus error
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus Write data receiving function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Write_data_receive(void)
*-------------------------------------------------------------------
* Function			: Receive WriteWord and BlockWrite data.
*					: 
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Write_data_receive(void)
{
	if( EXC0 == OFF )						// Not extend code ?
	{
		if( u8_smb_num < st_smb_frame.u8_len )			// Not complete to receive yet ?
		{
			au8_smb_buff[u8_smb_num] = IICA0;		// Receive data
			CRC8_Calc(au8_smb_buff[u8_smb_num]);	// Calculate PEC
			u8_smb_num++;						// Count communicated number
			if( u8_smb_num == st_smb_frame.u8_len )		// Complete to receive ?
			{
				f_recv = ON;				// Set received flag
			}
			Send_ACK();						// Send ACK
		} else {							// Already completed to receive
			if( f_wwpec == OFF )			// PEC is not send yet ?
			{
				if( u8_pec == IICA0 )			// PEC is correct ?
				{
					ACKE0 = 1;				// ACK enable
					WREL0 = 1;				// Wait release
				} else {					// PEC error
					f_comerr = ON;			// Set communication error flag
					ACKE0 = 0;				// ACK disable
					WREL0 = 1;				// wait release
				}
				f_wwpec = ON;				// Set PEC send flag
			} else {						// Already PEC is sent
				SMBus_error_nak();			// Error with Nak
			}
		}
	} else {
		f_recv = OFF;						// Clear received flag
		e_smbus_err_code = ERR_UNKNOW;				// Error code: Unknown error
		SMBus_error();						// SMBus error
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus error function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMBus_error(void)
*-------------------------------------------------------------------
* Function			: Function when SMBus error is occured.
*					: 
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMBus_error(void)
{
	st_smb_frame.u8_status = SMBUS_ERR;					// Receive mode: SMBus error
	f_comerr = ON;							// Set communication error flag
	LREL0 = 1;								// Exit from communication
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus error function (with NAK)
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMBus_error_nak(void)
*-------------------------------------------------------------------
* Function			: Function when SMBus error is occured.
*					: And it sends NAK.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMBus_error_nak(void)
{
	ACKE0 = 0;								// ACK disable
	WREL0 = 1;								// Wait release
	st_smb_frame.u8_status = SMBUS_ERR;					// Receive mode: SMBus error
	f_comerr = ON;							// Set communication error flag
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: ACK send function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Send_ACK(void)
*-------------------------------------------------------------------
* Function			: Send ACK.
*					: 
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void Send_ACK(void)
{
	ACKE0 = 1;								// ACK enable
	WREL0 = 1;								// Wait release
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SCL/SDA interrupt function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void _int_SCLSDA(void)
*-------------------------------------------------------------------
* Function			: SCL/SDA interrupt function.
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
* History			: 2020.10.12 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void _int_SCLSDA(void)
{
	aoffs_cnt = 0;								// Clear OffState counter
	f_nosmb = OFF;								// Clear no comm flag
	tnosmb_cnt = 0;
	
	TT0L.1 = 1;									// Stop TM01(1msec timer)
	while( TE0L.1 == ON ) ;						// Wait for stop timer
	TS0L.1 = 1;									// Start TM01(1msec timer)
	u8_smbus_scl_timeout_cnt = 0;								// Clear SCL timeout counter
	f_sclto_req = ON;							// Set SCL timeout check req.

	__custom_SCLSDA();							// Custom function of SCL/SDA
												//  interrupt
}


/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: SMBus state check function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void SMBus_state_check(void)
*-------------------------------------------------------------------
* Function			: Check SMBus condition.
*					: (Off state, On state, SCL or SDA low hold)
*					: 
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
* Caution			: This function should be called on 125ms cycle.
*					: 10sec cycle also should call this. But it has 
*					: delay of each judgment due to the difference of
*					: cycle.
*-------------------------------------------------------------------
* History			: 2020.10.16 Ver 0.01
* 					: Replace overall
* 
*""FUNC COMMENT END""**********************************************/
void SMBus_state_check(void)
{
	// - Off state check -
	if( CLD0 == LOW								// SCL = LOW
		&& DAD0 == LOW )						// & SDA = LOW ?
	{
		if( aoffs_cnt < 20 )					// Not Off state yet ?
		{
			aoffs_cnt++;						// Count Off state time
			if( aoffs_cnt == 20 )				// Detect Off state ?
			{
				SMBus_timeout();				// Reset SMBus
				aons_cnt = 0;					// Clear On state counter
				// Note: On state counter will be cleared when Off state.
				//       The counter should not be cleared by detecting
				//       SCL/SDA=LOW once. Because On state may have condition
				//       of SCL/SDA=LOW while communicating.				
			}
		}
	} else {									// SCL or SDA = HI
		aoffs_cnt = 0;							// Clear Off state counter
		if( aons_cnt < 80 )						// less than 10sec at OnState ?
		{
			aons_cnt++;							// Count On state time
		}
	}

	// - SCL low hold check -
	if( CLD0 == LOW								// SCL = LOW
		&& DAD0 == HI )							// & SDA = HI ?
	{
		aclklow_cnt++;							// Count SCL low hold counter
		if( aclklow_cnt >= 20 )					// 2.5sec has passed ?
												// (125ms x 20)
		{
			aclklow_cnt = 0;					// Clear the counter
			SMBus_timeout();					// Reset SMBus
		}
	} else {									// Not SCL low hold
		aclklow_cnt = 0;						// Clear the counter
	}

	// - SDA low hold check -
	if( CLD0 == HI								// SCL = HI
		&& DAD0 == LOW )						// & SDA = LOW ?
	{
		asdalow_cnt++;							// Count SDA low hold counter
		if( asdalow_cnt >= 20 )					// 2.5sec has passed ?
												// (125ms x 20)
		{
			asdalow_cnt = 0;					// Clear the counter
			SMBus_timeout();					// Reset SMBus
		}
	} else {									// Not SDA low hold
		asdalow_cnt = 0;						// Clear the counter
	}
}


/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Master send function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: U8 Master_Send()
*-------------------------------------------------------------------
* Function			: Make master send.
*					: This function is called from Master_Chk().
*					: 
*					: 
*-------------------------------------------------------------------
* Argument			:  None
*-------------------------------------------------------------------
* Return			:  None
*-------------------------------------------------------------------
* Input				:  None
* Output			:  None
*-------------------------------------------------------------------
* 					: 
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2012.08.01
*	 				: New create
*					: 
*""FUNC COMMENT END""**********************************************/
U8 Master_Send(void)
{
	if ( IICBSY0 == ON )											// Bus Busy? ?
	{
		// Do Nothing
	} else {
		PMK0 = 1;													// SDA interrupt disable
		WTIM0 = 1;													// 9bit communication
		STT0 = 1;													// Make Start condition

		IICA0 = au8_m_smbus_buff[4];											// Set slave address
		u8_smbus_m_timeout_cnt = 0;												// Init master timeout counter
		f_mstto_req = ON;											// Set master timeout check req.
		u8_smb_num = 3;												// Set number of remain data
		f_master = ON;												// Set master comm flag
		u8_smbus_scl_timeout_cnt = 0;												// Clear SCL timeout counter
		f_sclto_req = OFF;
		
		TT0L.1 = 1;													// Stop timer TM01(1msec timer)
		while( TE0L.1 == ON ) ;										// Wait until timer stop
		TS0L.1 = 1;													// Start timer TM01(1msec timer)
		return TRUE;
	}
	return FALSE;
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Check bus free of master send function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: U8 Master_BusFree_Chk()
*-------------------------------------------------------------------
* Function			: Check the condition of bus free.
*					: Make stop condition, if  bus busy conditions.
*					:
*					: 
*					: 
*-------------------------------------------------------------------
* Argument			:  None
*-------------------------------------------------------------------
* Return			:  None
*-------------------------------------------------------------------
* Input				:  None
* Output			:  None
*-------------------------------------------------------------------
* 					: 
* Used function 	: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2012.08.01
*	 				: New create
*					: 
*""FUNC COMMENT END""**********************************************/
void Master_BusFree_Chk(void)
{
#define	SMBUS_FREE_COUNT	15
#define	SMBUS_STT0_COUNT	15

	U8	acnt;
	if( IICBSY0 == ON )
	{
		for( acnt=0; acnt < SMBUS_FREE_COUNT; acnt++ )
		{
			if( IICBSY0 == ON && CLD0 == HI && DAD0 == HI )
			{
				// Do Nothing
			} else {
				break;
			}
		}

		if( acnt == SMBUS_FREE_COUNT )
		{
			IICAMK0 = 1;											// SMBus interrupt disabled
			IICAIF0 = 0;											// SMBus interrupt request flag clear
			PMK0 = 1;												// SDA interrupt disable
			IICE0 = 0;												// SMBus disable
			SPIE0 = 0;												// SMBus stop condition disabled
			IICE0 = 1;												// SMBus enabled
			LREL0 = 1;												// Exit from communication
			SPT0 = 1;												// Make stop condition
			
			for( acnt=0; acnt<SMBUS_STT0_COUNT; acnt++ )
			{
				if( SPD0 == 1 )										// Stop condition ?
				{
					break;
				}
			}
			SPIE0 =1;												// SMBus stop condition enable

			PIF0 = 0;												// Interrupt flag clear
			PMK0 = 0;												// SCL/SDA Interrupt enable

			IICAIF0 = 0;											// SMBus interrupt request flag clear
 			IICAMK0 = 0;											// SMBus interrupt enabled
		}
	}
}

/*""FUNC COMMENT""***************************************************
* ID : 1.0
* module outline	: Master send function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: U8 Master_Chk()
*-------------------------------------------------------------------
* Function			: Check the condition and make master send if 
*					: it satisfy the conditions.
*					: 
*					:  
*-------------------------------------------------------------------
* Argument			:  None
*-------------------------------------------------------------------
* Return			:  None
*-------------------------------------------------------------------
* Input				:  None
* Output			:  None
*-------------------------------------------------------------------
* Used function		: CRC8_Master(), Master_Send()
*  					: 
*-------------------------------------------------------------------
* Caution			: 
*-------------------------------------------------------------------
* History			: 2012.08.01
*	 				: New create
*					: 
*""FUNC COMMENT END""**********************************************/
void Master_Chk(void)
{
	if (st_fixed_data.st_smbus.u8_charger_addr == 0x00)				// Charger address is 0?
	{
		st_fixed_data.st_smbus.u8_charger_addr = 0x12;				// Set the default as 0x12
	}
	if(f_mster30 == ON )											// 30sec has passed ?
	{
		Master_BusFree_Chk();										// check if the bus is free
		
		if( IICBSY0 == OFF && CLD0 == HI && DAD0 == HI )				// Bus is free & SMBus available ?
		{
			au8_m_smbus_buff[4] = st_fixed_data.st_smbus.u8_charger_addr;		// Set Charger(W) slave address
			if( f_mtr15 == OFF )									// Send 0x14 command ?
			{
				au8_m_smbus_buff[3] = 0x14;									// ChargingCurrent()
				au8_m_smbus_buff[2] = u16_charging_current.u8_data[0];			// Data U8(L)
				au8_m_smbus_buff[1] = u16_charging_current.u8_data[1];			// Data U8(H)
				CRC8_Master();									// Calculate PEC
				if( Master_Send() )									// Succeed to send ?
				{
					f_mtr15 = ON;									// Set 0x15 send request
				}
			} else {												// Send 0x15 command
				au8_m_smbus_buff[3] = 0x15;									// ChargingVoltage()
				au8_m_smbus_buff[2] = u16_charging_voltage.u8_data[0];			// Data U8(L)
				au8_m_smbus_buff[1] = u16_charging_voltage.u8_data[1];			// Data U8(H)
				CRC8_Master();									// Calculate PEC
				if( Master_Send() )									// Succeed to send ?
				{
					f_mtr15 = OFF;								// Clear 0x15 send request
					f_mster30 = OFF;								// Clear 30sec passed flag
				}
			}
		}
	}
	
	if(f_mster10 == ON) 											// 10sec has passed & OCA or TDA or OTA?
	{
		Master_BusFree_Chk();										// check if the bus is free
		
		if( IICBSY0 == OFF && CLD0 == HI && DAD0 == HI )			// Bus is free & SMBus available ?
		{
			au8_m_smbus_buff[4] = D_CHGSLADDR;								// Set Charger(W) slave address
			au8_m_smbus_buff[3] = 0x16;										// ChargingCurrent()
			au8_m_smbus_buff[2] = abatsts[0];								// Data U8(L)
			au8_m_smbus_buff[1] = abatsts[1];								// Data U8(H)
			CRC8_Master();											// Calculate PEC
			if( Master_Send())										// Succeed to send ?
			{
				f_mster10 = OFF;									// Clear 10sec passed flag
			}
		}
	}
}

