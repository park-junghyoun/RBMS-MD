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
* System Name	: RAJ2400X0 F/W FSL user interface library
* File Name		: fsl.h
* Version		: 0.01
* Contents		: FSL user interface function header file
* Customer		: 
* Model			: 
* Order			: 
* CPU			: RAJ2400X0
* Compiler		: CA78K0R (V.1.30)
* OS			: None
* Programmer	: 
* Note			: 
************************************************************************
* Copyright(C) 2013 (2012-2013) RENESAS ELECTRONICS CORPORATION
*                AND RENESAS SOLUTIONS CORPORATION
************************************************************************
* History		: 2013.01.01 Ver 0.01
* 				: New Create
*""FILE COMMENT END""**************************************************/

#ifndef _FSL_H
#define _FSL_H




/***********************************************************************
	define
***********************************************************************/

/*==============================================================================================*/
/* unsigned type definitions                                                                    */
/*==============================================================================================*/
typedef unsigned char                       fsl_u08;
typedef unsigned int                        fsl_u16;
typedef unsigned long int                   fsl_u32;


/*==============================================================================================*/
/* global type definitions                                                                      */
/*==============================================================================================*/

/* FSL descriptor type */
typedef struct {                                                  /* ---------------------------------------------- */
                  fsl_u08         fsl_flash_voltage_u08;          /* 1, setting of flash voltage mode               */
                  fsl_u08         fsl_frequency_u08;              /* 1, CPU frequency (MHz)                         */
                  fsl_u08         fsl_auto_status_check_u08;      /* 1, setting of status check mode                */
                } fsl_descriptor_t;                               /*------------------------------------------------*/
                                                                  /* 3 bytes in total                               */
                                                                  /*------------------------------------------------*/


/* FSL write type */
typedef struct {                                                  /* ---------------------------------------------- */
                  fsl_u08 __near  *fsl_data_buffer_p_u08;         /* 2, pointer to data buffer                      */
                  fsl_u32         fsl_destination_address_u32;    /* 4, starting address to write data              */
                  fsl_u08         fsl_word_count_u08;             /* 1, number of words to write data               */
                } fsl_write_t;                                    /*------------------------------------------------*/
                                                                  /* 7 bytes in total                               */
                                                                  /*------------------------------------------------*/


/* FSL get block end address type */
typedef struct {                                                  /* ---------------------------------------------- */
                  fsl_u32         fsl_destination_address_u32;    /* 4, destination variable for the end address    */
                  fsl_u16         fsl_block_u16;                  /* 2, block number                                */
                } fsl_getblockendaddr_t;                          /*------------------------------------------------*/
                                                                  /* 6 bytes in total                               */
                                                                  /*------------------------------------------------*/


/* FSL get and set flash shield window type */
typedef struct {                                                  /* ---------------------------------------------- */
                  fsl_u16         fsl_start_block_u16;            /* 2, start block number of FSW (destination)     */
                  fsl_u16         fsl_end_block_u16;              /* 2, end block number of FSW (destination)       */
                } fsl_fsw_t;                                      /*------------------------------------------------*/
                                                                  /* 4 bytes in total                               */
                                                                  /*------------------------------------------------*/


/*status code definitions returned by the FSL functions                                         */
#define   FSL_OK                    0x00      /* no problems                                    */
#define   FSL_ERR_PARAMETER         0x05      /* parameter error                                */
#define   FSL_ERR_PROTECTION        0x10      /* protection error (access right conflict)       */
#define   FSL_ERR_ERASE             0x1A      /* erase error                                    */
#define   FSL_ERR_BLANKCHECK        0x1B      /* blankcheck error (MRG11)                       */
#define   FSL_ERR_IVERIFY           0x1B      /* internal verify error (MRG11)                  */
#define   FSL_ERR_WRITE             0x1C      /* write error                                    */
#define   FSL_ERR_FLOW              0x1F      /* flow error (wrong timing calling)              */
#define   FSL_IDLE                  0x30      /* idle state (any action is not running)         */
#define   FSL_SUSPEND               0x43      /* previous flash action is suspended             */
#define   FSL_BUSY                  0xFF      /* command is being processed                     */




#define		FSL_Init						((fsl_u08			(*)(const __far fsl_descriptor_t*))(0xFA00))	// 01
#define		FSL_Open						((void				(*)(void))						 (0xFA18))	// 02
#define		FSL_Close						((void				(*)(void))						 (0xFA20))	// 03
#define		FSL_PrepareFunctions			((void				(*)(void))						 (0xFA28))	// 04
#define		FSL_PrepareExtFunctions			((void				(*)(void))						 (0xFA30))	// 05
#define		FSL_ChangeInterruptTable		((void				(*)(fsl_u16))						 (0xFA38))	// 06
#define		FSL_RestoreInterruptTable		((void				(*)(void))						 (0xFA48))	// 07
#define		FSL_BlankCheck					((fsl_u08			(*)(fsl_u16))						 (0xFA50))	// 08
#define		FSL_Erase						((fsl_u08			(*)(fsl_u16))						 (0xFA60))	// 09
#define		FSL_IVerify						((fsl_u08			(*)(fsl_u16))						 (0xFA70))	// 10
#define		FSL_Write						((fsl_u08			(*)(__near fsl_write_t*))			 (0xFA80))	// 11
#define		FSL_StatusCheck					((fsl_u08			(*)(void))						 (0xFA90))	// 12
#define		FSL_StandBy						((fsl_u08			(*)(void))						 (0xFA98))	// 13
#define		FSL_WakeUp						((fsl_u08			(*)(void))						 (0xFAA0))	// 14
#define		FSL_GetSecurityFlags			((fsl_u08			(*)(fsl_u08 __near *))			 (0xFAA8))	// 15
#define		FSL_GetBootFlag					((fsl_u08			(*)(fsl_u08 __near *))			 (0xFAB8))	// 16
#define		FSL_GetSwapState				((fsl_u08			(*)(fsl_u08 __near *))			 (0xFAC8))	// 17
#define		FSL_GetBlockEndAddr				((fsl_u08			(*)(__near fsl_getblockendaddr_t*))(0xFAD8))	// 18
#define		FSL_GetFlashShieldWindow		((fsl_u08			(*)(__near fsl_fsw_t*))			 (0xFAE8))	// 19
#define		FSL_SetBlockEraseProtectFlag	((fsl_u08			(*)(void))						 (0xFAF8))	// 20
#define		FSL_SetWriteProtectFlag			((fsl_u08			(*)(void))						 (0xFB00))	// 21
#define		FSL_SetBootClusterProtectFlag	((fsl_u08			(*)(void))						 (0xFB08))	// 22
#define		FSL_InvertBootFlag				((fsl_u08			(*)(void))						 (0xFB10))	// 23
#define		FSL_SetFlashShieldWindow		((fsl_u08			(*)(__near fsl_fsw_t*))			 (0xFB18))	// 24
#define		FSL_SwapBootCluster				((fsl_u08			(*)(void))						 (0xFB28))	// 25
#define		FSL_SwapActiveBootCluster		((fsl_u08			(*)(void))						 (0xFB30))	// 26
#define		FSL_ForceReset					((void				(*)(void))						 (0xFB38))	// 27
#define		FSL_GetVersionString			((__far fsl_u08*	(*)(void))						 (0xFB40))	// 28



#endif

