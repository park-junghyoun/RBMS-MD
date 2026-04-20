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
******************************************************************************
* Copyright,2017 (2012-2017) RENESAS ELECTRONICS CORPORATION
******************************************************************************
* History		: 2017.11.29 Ver 0.01
* 				  New Create
*
*****************************************************************************/
#pragma section @@CNSTL VERINFO

#ifndef	_RENESAS_C_
#define	_RENESAS_C_


#include "version.h"
#include "renesas_def.h"

/*****************************************************************************/
/*								Macro definition							 */
/*****************************************************************************/

#define	PC_MODEL		( PC_MODEL_RENESAS )			/* PC model */

#define	PACK_MAKER		( PACK_MAKER_FILEFISH )			/* Pack maker */

#define	DEVICE_INFO		( DEVICE_INFO_OTHER )			/* Device name */
#ifdef	RAJ240094
#define	DEVICE_INFO_2	( DEVICE_INFO_0094 )			/* Device name 2 */
#else
#define	DEVICE_INFO_2	( DEVICE_INFO_0095 )			/* Device name 2 */
#endif

/*****************************************************************************/
/*								Constant Value								 */
/*****************************************************************************/

const __far _TOOL_INFO sinfo = {
	VERSION,
	PC_MODEL,
	(PACK_MAKER << 4) | DEVICE_INFO,
	SUB_VERSION,
	DEVICE_INFO_2,
	0xFF
};



#endif	/* _RENESAS_C_ */

