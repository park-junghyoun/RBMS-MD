/****************************************************************************
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
* System Name	: RBMS-M Series Driver for Renesas
* File Name		: bms_user_firmware_example.c
* Contents		: Example application main entry and hardware init
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#include "bms_user_firmware_example.h"
/*
 * Example application integrating the BMS library on target hardware.
 *
 * The sample is split by feature area so users can reuse only the sections
 * they need: application setup, event callbacks, measurement handling and
 * platform power control.
 */

/*******************************************************************************
* Function Name: app_init_leds
* Description  : Executes app_init_leds routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void app_init_leds(void)
{
	PM0 = PM0 & 0b11111100;
	PM1 =  PM1 & 0b10000110;
	/* initialize the LEDs to low. */
	LED1=1;
	LED2=1;
	LED3=1;
	LED4=1;
	LED5=1;
	LED6=1;
	LED7=1;
}

/*******************************************************************************
* Function Name: main
* Description  : Executes main routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void main(void)
{
	U8 u8_ret;
	
	SMBus_initialize();										// SMBus initializing
	app_init_leds();
	
	u8_ret = APP_BMS_Core_Init() 

	if(u8_ret == FALSE)
	{
		while (1)
		{

		}
	}
	u8_ret = APP_Callbacks_Register();
	
	app_configure_mode_profile();
	app_configure_protection();
	app_configure_hw_protection_path();
	//app_configure_thermistor_tables();
	app_apply_calibration_profiles();

	while (1)
	{
		BMS_Event_Process();
		/*
		 * Application processing is intentionally driven from app_on_alarm()
		 * so periodic work stays aligned with the BMS alarm scheduler.
		 */
		Stop_Mode();
	}
}
