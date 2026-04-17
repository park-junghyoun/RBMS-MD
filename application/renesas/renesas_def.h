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
* Copyright,2024 (2012-2024) RENESAS ELECTRONICS CORPORATION
******************************************************************************
* History		: 2017.11.29 Ver 0.01
* 				  New Create
* 
*				: 2018.07.17 Ver0.02
*				  Added MSI definition to EN_PC_MODEL.
*				  Added Getac definition to EN_PACK_MAKER.
* 
*				: 2018.10.18 Ver0.03
*				  Added RETW_STD definition to EN_PACK_MAKER.
*
*				: 2018.11.06 Ver0.04
*                 Added Huawei definition to EN_PC_MODEL.
*
*				: 2019.03.14 Ver0.05
*                 Added _WINDOWS compile option
*
*				: 2019.04.08 Ver0.06
*                 Added SEC definition to EN_PC_MODEL.
*                 Added RAA241000 definition to EN_DEVICE_INFO
*
*				: 2020.10.15 Ver0.07
*                 Added MICROSOFT definition to EN_PC_MODEL.
*
*				: 2020.10.23 Ver0.08
*                 Added DEVICE_INFO_OTHER definition to EN_DEVICE_INFO.
*                 Added EN_DEVICE_INFO_2 enumeration.
*                 Added DONT_USE_THIS_DEFINITION definition.
*                 Modified _ST_TOOL_INFO structer.
*                 (Reduced Reserved size from 2 to 1, and added device_info. )
*
*				: 2021.08.17 Ver0.09
*                 Added Facebook definition to EN_PC_MODEL.
*
*				: 2021.08.27 Ver0.0A
*				  Added RDM_STD definition to EN_PACK_MAKER.
*
*				: 2021.12.13 Ver0.0B
*                 Added RECN_STD definition to EN_PACK_MAKER.
*
*				: 2022.01.17 Ver0.0C
*                 Added LBG_R, LBG_S definition to EN_PACK_MAKER.
*
*				: 2022.11.02 Ver0.0D
*                 Added RAJ240297 definition to EN_DEVICE_INFO_2.
*
*				: 2022.12.12 Ver0.0E
*                 Modified RECN_STD definition to RDB_STD.
*
*				: 2022.12.20 Ver0.0F
*                 Added FileFish definition to EN_PACK_MAKER.
*
*				: 2023.09.28 Ver0.10
*                 Added RAJ240401 and RL78/F2 4definition to EN_DEVICE_INFO_2.
*
*				: 2023.11.08 Ver0.11
*                 Added Note section.
*                 Added COSXM and SONY definition to EN_PC_MODEL.
*
*				: 2024.01.06 Ver0.12
*                 Added RAJ240091 definition to EN_DEVICE_INFO_2.
*
*				: 2024.05.14 Ver0.13
*                 Added Online Update Program definition to EN_PC_MODEL.
*
*				: 2024.11.27 Ver0.14
*                 Added Sonos definition to EN_PC_MODEL.
*
*				: 2025.01.29 Ver0.15
*                 Added LBG_F, LBG_SI definition to EN_PACK_MAKER
*                 Added RAJ240053 definition to EN_DEVICE_INFO_2
*
*				: 2025.02.25 Ver0.16
*                 Added RIONI definition to EN_PC_MODEL
*                 Added RAJ240094 and RAJ240095 definition to EN_DEVICE_INFO_2
*
*****************************************************************************/
#ifndef	_RENESAS_DEF_H_
#define	_RENESAS_DEF_H_


#ifndef	_WINDOWS
#include "define.h"
#endif

/*****************************************************************************/
/* Note                                                                      */
/*****************************************************************************/
/* Define end maker in PC_MODEL. At that time, PACK_MAKER's definition is    */
/* STD basically.                                                            */
/* However, if there is a special specification for each PACK_MAKER, it uses */
/* definition other than STD.                                                */
/* When there is no correspondence definition, create a new definition.      */
/*****************************************************************************/


/*****************************************************************************/
/*							Enumeration										 */
/*****************************************************************************/

/* Enumeration of pc model (~0xFF) */
typedef enum {
	PC_MODEL_RENESAS,							/* [0x00]Renesas             */
	PC_MODEL_LENOVO_LBG,						/* [0x01]Lenovo LBG          */
	PC_MODEL_LENOVO_TBG,						/* [0x02]Lenovo TBG          */
	PC_MODEL_ASUS,								/* [0x03]ASUS                */
	PC_MODEL_ACER,								/* [0x04]Acer                */
	PC_MODEL_VAIO,								/* [0x05]Vaio                */
	PC_MODEL_TOSHIBA,							/* [0x06]Toshiba             */
	PC_MODEL_DELL,								/* [0x07]Dell                */
	PC_MODEL_FUJITSU,							/* [0x08]Fujitsu             */
	PC_MODEL_HP,								/* [0x09]HP                  */
	PC_MODEL_DELL_CHROMEBOOK,					/* [0x0A]Dell Chromebook     */
	PC_MODEL_XIAOMI,							/* [0x0A]XiaoMi              */
	PC_MODEL_LENOVO_NEC,						/* [0x0C]Lenovo NEC          */
	PC_MODEL_LENOVO_COMMON,						/* [0x0D]Lenovo common       */
	PC_MODEL_LENOVO_FWUP,						/* [0x0E]Lenovo FW update    */
	PC_MODEL_MSI,								/* [0x0F]MSI                 */
	PC_MODEL_HUAWEI,							/* [0x10]Huawei              */
	PC_MODEL_SEC,								/* [0x11]Samsung Electronics */
	PC_MODEL_MICROSOFT,							/* [0x12]Microsoft           */
	PC_MODEL_FACEBOOK,							/* [0x13]Facebook            */
	PC_MODEL_COSMX,								/* [0x14]COSMX               */
	PC_MODEL_SONY,								/* [0x15]SONY                */
	PC_MODEL_ONLINE_UPDATE,						/* [0x16]Online Update       */
	PC_MODEL_SONOS,								/* [0x17]Sonos               */
	PC_MODEL_RION,								/* [0x18]Rion                */
	
	PC_MODEL_MAX
} EN_PC_MODEL;

/* Enumeration of pack maker (~0x0F) */
typedef enum {
	PACK_MAKER_STD,								/* [0x00]Standard        */
	PACK_MAKER_LGC,								/* [0x01]LGC Custom      */
	PACK_MAKER_SDI,								/* [0x02]SDI Custom      */
	PACK_MAKER_CELXPERT,						/* [0x03]Celxpert Custom */
	PACK_MAKER_SIMPLO,							/* [0x04]Simplo Custom   */
	PACK_MAKER_DYNAPACK,						/* [0x05]Dynapack Custom */
	PACK_MAKER_GETAC,							/* [0x06]Getac           */
	PACK_MAKER_RETW_STD,						/* [0x07]RETW Standard   */
	PACK_MAKER_RDM_STD,							/* [0x08]RDM Standard    */
	PACK_MAKER_RDB_STD,							/* [0x09]RDB Standard    */
	PACK_MAKER_LBG_R,							/* [0x0A]LBG R Version   */
	PACK_MAKER_LBG_S,							/* [0x0B]LBG S Version   */
	PACK_MAKER_FILEFISH,						/* [0x0C]FileFish        */
	PACK_MAKER_LBG_F,							/* [0x0D]LBG F Version   */
	PACK_MAKER_LBG_SI,							/* [0x0E]LBG Si Version  */
	
	PACK_MAKER_MAX
} EN_PACK_MAKER;

/* Enumeration of device (~0x0F) */
typedef enum {
	DEVICE_INFO_045,							/* [0x00]RAJ240045 */
	DEVICE_INFO_080,							/* [0x01]RAJ240080 */
	DEVICE_INFO_500,							/* [0x02]RAJ240500 */
	DEVICE_INFO_275,							/* [0x03]RAJ240275 */
	DEVICE_INFO_090,							/* [0x04]RAJ240090 */
	DEVICE_INFO_267,							/* [0x05]RAJ240267 */
	DEVICE_INFO_100,							/* [0x06]RAJ240100 */
	DEVICE_INFO_071,							/* [0x07]RAJ240071 */
	DEVICE_INFO_072,							/* [0x08]RAJ240072 */
	DEVICE_INFO_073,							/* [0x09]RAJ240073 */
	DEVICE_INFO_074,							/* [0x0A]RAJ240074 */
	DEVICE_INFO_075,							/* [0x0B]RAJ240075 */
	DEVICE_INFO_046,							/* [0x0C]RAJ240046 */
	DEVICE_INFO_047,							/* [0x0D]RAJ240047 */
	DEVICE_INFO_1000,							/* [0x0E]RAA241000 */
	
	DEVICE_INFO_OTHER,							/* [0x0F]Other Devices */
	
	DEVICE_INFO_MAX
} EN_DEVICE_INFO;

/* Enumeration of device part 2 (~0xFF) */
typedef enum {
	DEVICE_INFO_1300,							/* [0x00]RAA241300 */
	DEVICE_INFO_1500,							/* [0x01]RAA241500 */
	DEVICE_INFO_0301,							/* [0x02]RAJ240301 */
	DEVICE_INFO_0310,							/* [0x03]RAJ240310 */
	DEVICE_INFO_0055,							/* [0x04]RAJ240055 */
	DEVICE_INFO_0057,							/* [0x05]RAJ240057 */
	DEVICE_INFO_0287,							/* [0x06]RAJ240287 */
	DEVICE_INFO_1200,							/* [0x07]RAA241200 */
	DEVICE_INFO_1001,							/* [0x08]RAA241001 */
	DEVICE_INFO_0297,							/* [0x09]RAJ240297 */
	DEVICE_INFO_0401,							/* [0x0A]RAJ240401 */
	DEVICE_INFO_F24,							/* [0x0B]RL78/F24  */
	DEVICE_INFO_0091,							/* [0x0C]RAJ240091 */
	DEVICE_INFO_0053,							/* [0x0D]RAJ240053 */
	DEVICE_INFO_0094,							/* [0x0E]RAJ240094 */
	DEVICE_INFO_0095,							/* [0x0F]RAJ240095 */
	
	DEVICE_INFO_2_MAX
} EN_DEVICE_INFO_2;

/*****************************************************************************/
/*								definition									 */
/*****************************************************************************/
/* If you dose not use device_info, please set this definition. */
#define	DONT_USE_THIS_DEFINITION	( 0xFF )


/*****************************************************************************/
/*								struct / union								 */
/*****************************************************************************/

typedef struct {
	U16	version;
	U8	pc_model;
	U8	pack_maker;
	U16	sub_version;
	U8	device_info;
	U8	reserved[ 1 ];
} _ST_TOOL_INFO;

typedef union {
	_ST_TOOL_INFO	sinfo;
	U8			uc[sizeof(_ST_TOOL_INFO)];
} _TOOL_INFO;



#endif	/* _RENESAS_DEF_H_ */

