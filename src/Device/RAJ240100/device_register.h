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
* System Name	: RBMS-M Firmware for Renesas
* File Name		: afe_device.h
* Contents		: general define
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2019 (2012-2019) RENESAS ELECTRONICS CORPORATION
*                            AND RENESAS SOLUTIONS CORPORATION
*""FILE COMMENT END""*****************************************************/

#ifndef _AFE_REG_H
#define _AFE_REG_H

/************************************WINDOW 0*************************/

#define AFE_PCODEL		AFEREG00					//(F0500)
#define AFE_PCODEH		AFEREG01					//(F0501)
#define AFE_RECODE		AFEREG02					//(F0502)
#define AFE_WINCHG		AFEREG03					//(F0503)
#define AFE_PDCNT		AFEREG04					//(F0504)
#define AFE_AFESWRST		AFEREG05					//(F0505)
#define AFE_AMOCON		AFEREG06					//(F0506)
#define AFE_PCON			AFEREG07					//(F0507)
#define AFE_AWDTCON		AFEREG08					//(F0508)
#define AFE_AWDTRF		AFEREG09					//(F0509)
#define AFE_VRG2LVD		AFEREG0B					//(F050B)
#define AFE_FCON			AFEREG0C					//(F050C)
#define AFE_DFOCON		AFEREG0D					//(F050D)
#define AFE_CFOCON		AFEREG0E					//(F050E)
#define AFE_FMON			AFEREG0F					//(F050F)
#define AFE_PWMCON		AFEREG10					//(F0510)
#define AFE_PWMPRE		AFEREG11					//(F0511)
#define AFE_PWMTIML		AFEREG12					//(F0512)
#define AFE_PWMTIMH		AFEREG13					//(F0513)
#define AFE_PWMFETSEL	AFEREG14					//(F0514)
#define AFE_AFMK0		AFEREG18					//(F0518)
#define AFE_AFMK1		AFEREG19					//(F0519)
#define AFE_AFMK2		AFEREG1A					//(F051A)
#define AFE_AFMK3		AFEREG1B					//(F051B)
#define AFE_AFIF0			AFEREG1C					//(F051C)
#define AFE_AFIF1			AFEREG1D					//(F051D)
#define AFE_AFIF2			AFEREG1E					//(F051E)
#define AFE_AFIF3			AFEREG1F					//(F051F)
#define AFE_ADCON0		AFEREG20					//(F0520)
#define AFE_ADCON1		AFEREG21					//(F0521)
#define AFE_ADCON2		AFEREG22					//(F0522)
#define AFE_ADMSEL0		AFEREG23					//(F0523)
#define AFE_ADMSEL1		AFEREG24					//(F0524)
#define AFE_ADMSEL3		AFEREG26					//(F0526)
#define AFE_ADMSEL4		AFEREG27					//(F0527)
#define AFE_ADMSEL5		AFEREG28					//(F0528)
#define AFE_ADSTS		AFEREG29					//(F0529)
#define AFE_ADORL		AFEREG2A					//(F052A)
#define AFE_ADORH		AFEREG2B					//(F052B)
#define AFE_ADRL1		AFEREG2C					//(F052C)
#define AFE_ADRH1		AFEREG2D					//(F052D)
#define AFE_ADRL2		AFEREG2E					//(F052E)
#define AFE_ADRH2		AFEREG2F					//(F052F)
#define AFE_ADRL3		AFEREG30					//(F0530)
#define AFE_ADRH3		AFEREG31					//(F0531)
#define AFE_ADRL4		AFEREG32					//(F0532)
#define AFE_ADRH4		AFEREG33					//(F0533)
#define AFE_ADRL5		AFEREG34					//(F0534)
#define AFE_ADRH5		AFEREG35					//(F0535)
#define AFE_ADRL6		AFEREG36					//(F0536)
#define AFE_ADRH6		AFEREG37					//(F0537)
#define AFE_IMPRL0		AFEREG3A					//(F053A)
#define AFE_IMPRH0		AFEREG3B					//(F053B)
#define AFE_IMPRL1		AFEREG3C					//(F053C)
#define AFE_IMPRH1		AFEREG3D					//(F053D)
#define AFE_IMPRL2		AFEREG3E					//(F053E)
#define AFE_IMPRH2		AFEREG3F					//(F053F)
#define AFE_IMPRL3		AFEREG40					//(F0540)
#define AFE_IMPRH3		AFEREG41					//(F0541)
#define AFE_IMPRL4		AFEREG42					//(F0542)
#define AFE_IMPRH4		AFEREG43					//(F0543)
#define AFE_IMPRL5		AFEREG44					//(F0544)
#define AFE_IMPRH5		AFEREG45					//(F0545)
#define AFE_IMPRL6		AFEREG46					//(F0546)
#define AFE_IMPRH6		AFEREG47					//(F0547)
#define AFE_COND0		AFEREG4C					//(F054C)
#define AFE_COND1		AFEREG4D					//(F054D)
#define AFE_COND2		AFEREG4E					//(F054E)
#define AFE_CCCON		AFEREG50					//(F0550)
#define AFE_CCRL			AFEREG51					//(F0551)
#define AFE_CCRM			AFEREG52					//(F0552)
#define AFE_CCRH			AFEREG53					//(F0553)
#define AFE_IMPCON0		AFEREG54					//(F0554)
#define AFE_PMHV			AFEREG58					//(F0558)
#define AFE_PHV			AFEREG59					//(F0559)
#define AFE_POMHV		AFEREG5A					//(F055A)
#define AFE_PMSHV		AFEREG5B					//(F055B)
#define AFE_HVIODIN		AFEREG5C					//(F055C)
#define AFE_ANPULL		AFEREG5D					//(F055D)
#define AFE_EXBPULL		AFEREG5E					//(F055E)
#define AFE_SCDCON		AFEREG60					//(F0560)
#define AFE_DOC1DCON	AFEREG61					//(F0561)
#define AFE_DOC2DCON	AFEREG62					//(F0562)
#define AFE_COCDCON		AFEREG63					//(F0563)
#define AFE_SCDTIME		AFEREG64					//(F0564)
#define AFE_DOC1DTIME1	AFEREG65					//(F0565)
#define AFE_DOC1DTIME2	AFEREG66					//(F0566)
#define AFE_DOC2DTIME1	AFEREG67					//(F0567)
#define AFE_DOC2DTIME2	AFEREG68					//(F0568)
#define AFE_COCDTIME		AFEREG69					//(F0569)
#define AFE_OCDSTS		AFEREG6A					//(F056A)
#define AFE_OCDRSTRT		AFEREG6B					//(F056B)
#define AFE_DWUDCON1	AFEREG6E					//(F056E)
#define AFE_DWUDCON2	AFEREG6F					//(F056F)
#define AFE_CWUDCON1	AFEREG70					//(F0570)
#define AFE_CWUDCON2	AFEREG71					//(F0571)
#define AFE_DBPTCON1		AFEREG72					//(F0572)
#define AFE_DBPTCON2		AFEREG73					//(F0573)
#define AFE_WUDTIME		AFEREG74					//(F0574)
#define AFE_WUDSTS		AFEREG75					//(F0575)
#define AFE_WUDRSTRT		AFEREG76					//(F0576)
#define AFE_ATMACR		AFEREG78					//(F0578)
#define AFE_ATMAR		AFEREG79					//(F0579)
#define AFE_ATMBCR		AFEREG7C					//(F057C)
#define AFE_ATMBR		AFEREG7D					//(F057D)
#define AFE_ATMBPRE1		AFEREG7E					//(F057E)
#define AFE_TMMCON		AFEREG7F					//(F057F)

/************************************WINDOW 1*************************/
#define AFE_OCOCON		AFEREG06					//(F0506)
#define AFE_BFUCON		AFEREG07					//(F0507)
#define AFE_AWDTMON0	AFEREG08					//(F0508)
#define AFE_AWDTMON1	AFEREG09					//(F0509)
#define AFE_AWDTMON2	AFEREG0A					//(F050A)
#define AFE_HVEG			AFEREG18					//(F0518)
#define AFE_HVDT			AFEREG19					//(F0519)
#define AFE_PONEG		AFEREG1A					//(F051A)
#define AFE_PONMON		AFEREG1B					//(F051B)
#define AFE_DADCON0		AFEREG20					//(F0520)
#define AFE_DADCON1		AFEREG21					//(F0521)
#define AFE_DADCON2		AFEREG22					//(F0522)
#define AFE_DADORL		AFEREG24					//(F0524)
#define AFE_DADORH		AFEREG25					//(F0525)
#define AFE_DADRL		AFEREG26					//(F0526)
#define AFE_DADRH		AFEREG27					//(F0527)
#define AFE_DIMPRL		AFEREG28					//(F0528)
#define AFE_DIMPRH		AFEREG29					//(F0529)
#define AFE_ADPERIO0		AFEREG30					//(F0530)
#define AFE_ADPERIO1		AFEREG31					//(F0531)
#define AFE_ADPERIO2		AFEREG32					//(F0532)
#define AFE_ADPERICL		AFEREG33					//(F0533)
#define AFE_ADPERICH		AFEREG34					//(F0534)
#define AFE_ADPERIDL		AFEREG35					//(F0535)
#define AFE_ADPERIDH		AFEREG36					//(F0536)
#define AFE_ADPERIMON	AFEREG37					//(F0537)
#define AFE_ADPESTATCL	AFEREG38					//(F0538)
#define AFE_ADPESTATCH	AFEREG39					//(F0539)
#define AFE_ADPESTATDL	AFEREG3B					//(F053B)
#define AFE_ADPESTATDH	AFEREG3C					//(F053C)
#define AFE_ADPERICLR		AFEREG3E					//(F053E)
#define AFE_MUXBICUP		AFEREG40					//(F0540)
#define AFE_CCEVA0		AFEREG50					//(F0550)
#define AFE_CCEVA1		AFEREG51					//(F0551)
#define AFE_DOC1CAL		AFEREG61					//(F0561)
#define AFE_COCCAL		AFEREG63					//(F0563)
#define AFE_DOC3DCON	AFEREG64					//(F0564)
#define AFE_DOC4DCON	AFEREG65					//(F0565)
#define AFE_DOC3DTIME1	AFEREG66					//(F0566)
#define AFE_DOC3DTIME2	AFEREG67					//(F0567)
#define AFE_DOC4DTIME1	AFEREG68					//(F0568)
#define AFE_DOC4DTIME2	AFEREG69					//(F0569)
#define AFE_OCDICON		AFEREG6B					//(F056B)
#define AFE_WUICON		AFEREG6C					//(F056C)
#define AFE_DWUCAL		AFEREG6E					//(F056E)
#define AFE_DWUACAL		AFEREG6F					//(F056F)
#define AFE_CWUCAL		AFEREG70					//(F0570)
#define AFE_CWUACAL		AFEREG71					//(F0571)
#define AFE_DBPTCAL		AFEREG72					//(F0572)
#define AFE_DBPTACAL		AFEREG73					//(F0573)

/**********************WINDOW 0 AFE Parameter*************************/
												// - (F0503) WINCHG -
#define		WINCHG_RM0		0b00000000			// Select Register map 0
#define		WINCHG_RM1		0b00000001			// Select Register map 1
#define		WINCHG_TR		0b10000000			// Select trimming register

												// - (F0506) AMOCON -
#define		MCLKSEL_AOCO	0b00000000			// AOCO select
#define		MCLKSEL_ALOCO	0b00000001			// ALOCO select
#define		MCLKSTS_AOCO	0b00000000			// AOCO operation
#define		MCLKSTS_ALOCO	0b00010000			// ALOCO operation


												// - (F0507) PCON -
#define		BUFCEN1_EN		0b00000001			// BUFC1 enable
#define		BUFCEN1_DIS		0b00000000			// BUFC1 disable
#define		BUFCEN2_EN		0b00000010			// BUFC2 enable
#define		BUFCEN2_DIS		0b00000000			// BUFC2 disable
#define		BUFCEN3_EN		0b00000100			// BUFC3 enable
#define		BUFCEN3_DIS		0b00000000			// BUFC3 disable
#define		BUFCEN4_EN		0b00001000			// BUFC4 enable
#define		BUFCEN4_DIS		0b00000000			// BUFC4 disable
#define		VCPC_EN			0b00100000			// VCPC enable
#define		VCPC_DIS		0b00000000			// VCPC disable
#define		REG1C_EN		0b01000000			// REG1C enable
#define		REG1C_DIS		0b00000000			// REG1C disable


												// - (F0508) AWDTCON -
#define		WDT_64S			0b00000000			// Detect time 64sec
#define		WDT_32S			0b00000001			// Detect time 32sec
#define		WDT_16S			0b00000010			// Detect time 16sec
#define		WDT_8S			0b00000011			// Detect time 8sec
#define		WDT_4S			0b00000100			// Detect time 4sec
#define		WDT_2S			0b00000101			// Detect time 2sec
#define		WDT_STOP		0b00000111			// Stop
#define		WDT_MTRSEL_EN	0b01000000			// Reset output enable
#define		WDT_MTRSEL_DIS	0b00000000			// Reset output disable

												// - (F050B) VRG2LVD -
#define		VRG2LV_EN		0b00000001			// VRG2LV enable
#define		VRG2LV_DIS		0b00000000			// VRG2LV disable
#define		VRG2LVMD_INT	0b00000000			// VRG2LVMD:interrupt
#define		VRG2LVMD_RST	0b00000010			// VRG2LVMD:Reset
#define		VRG2LF_D		0b00010000			// VRG2LV detection
#define		VRG2LF_ND		0b00000000			// VRG2LV non detection


												// - (F050C) FCON -
#define		FET_OFF			0b00000000			// C=OFF, D=OFF
#define		FET_CD			0b00000011			// C=ON,  D=ON
#define		FET_C			0b00000010			// C=ON,  D=OFF
#define		FET_D			0b00000001			// C=OFF, D=ON

												// - (F050D) DFOCON -
#define		DFET_GND		0b00000001			// DFET Low Side
#define		DFET_VPACK		0b00000000			// DFET High Side
#define		DFCLP_EN		0b00000000			// DFET Clamp enabled
#define		DFCLP_DIS		0b00000010			// DFET Clamp disabled
#define		DFOFFBST_EN		0b00001000			// DFET OFF Boost enabled
#define		DFOFFBST_DIS	0b00000000			// DFET OFF Boost disabled
#define		DFOFFBSTC_EN	0b00010000			// PACK voltage output during OFF boost
#define		DFOFFBSTC_DIS	0b00000000			// (PACK - 10) voltage output during OFF boost

												// - (F050E) CFOCON -
#define		CFET_GND		0b00000001			// CFET Low Side
#define		CFET_VBAT		0b00000000			// CFET High Side
#define		CFCLP_EN		0b00000000			// CFET Clamp enabled
#define		CFCLP_DIS		0b00000010			// CFET Clamp disabled
#define		CFOFFBST_EN		0b00001000			// CFET OFF Boost enabled
#define		CFOFFBST_DIS	0b00000000			// CFET OFF Boost disabled
#define		CFOFFBSTC_EN	0b00010000			// VBAT voltage output during OFF boost
#define		CFOFFBSTC_DIS	0b00000000			// (VBAT - 10) voltage output during OFF boost

												// - (F050F) FMON -
#define		DFMON2_OFF		0b00000000			// Not DFET force OFF control for overcurrent
#define		DFMON2_ON		0b00000100			// DFET force OFF control for overcurrent
#define		DFMON3_OFF		0b00000000			// Not DFET force OFF control for wakeup
#define		DFMON3_ON		0b00001000			// DFET force OFF control for wakeup
#define		CFMON2_OFF		0b00000000			// Not DFET force OFF control for overcurrent
#define		CFMON2_ON		0b01000000			// DFET force OFF control for overcurrent
#define		CFMON3_OFF		0b00000000			// Not DFET force OFF control for wakeup
#define		CFMON3_ON		0b10000000			// DFET force OFF control for wakeup

												// - (F0510) PWMCON -
#define		PWM_EN			0b00000001			// PWM enable
#define		PWM_DIS			0b00000000			// PWM disable
#define		PWM_f1			0b00000000			// PWM count source(f1)
#define		PWM_f1half		0b00000010			// PWM count source(f1/2)
#define		PWM_8bit		0b00000000			// PWM mode 8bit resolution
#define		PWM_10bit		0b00100000			// PWM mode 10bit resolution

												// - (F0514) PWMFETSEL -
#define		PWM_CFET		0b00000000			// Select CFET for PWM
#define		PWM_DFET		0b00000001			// Select DFET for PWM

												// - (F0518) AFE Interrupt control 0 -
#define		INT_ADMSK		0b00000001			// AD interrupt enable
#define		INT_CCMSK		0b00000010			// CC interrupt enable
#define		INT_DADMSK		0b00001000			// AD conversion complete for heavy load current detection interrupt enable
#define		INT_PONMSK		0b00010000			// CHMON pin interrupt enable when the valid edge input
#define		INT_DWUMSK		0b00100000			// Discharge wakeup current detection interrupt enable
#define		INT_CWUMSK		0b01000000			// Charge wakeup current detection interrupt enable
#define		INT_HDLMSK		0b10000000			// Heavy load detection current detection interrupt enable


												// - (F0519) AFE Interrupt control 1 -
#define		INT_SCDMSK		0b00000001			// SCD interrupt enable
#define		INT_DOCDMSK	0b00000010			// DOCD interrupt enable
#define		INT_COCDMSK	0b00001000			// COCD interrupt enable
#define		INT_AWDTMSK	0b00010000			// MCU runaway detection interrupt enable
#define		INT_VDETMSK		0b00100000			// Battery cell voltage and temperature detection interrupt enable
#define		INT_CPUVMSK		0b01000000			// Charge pump under voltage detection interrupt enable

												// - (F051A) AFE Interrupt control 2 -
#define		INT_DISABLE		0b00000000			// HVIO0 & 1 pin interrupt disabled
#define		INT_HVP0MSK		0b00000001			// HVIO0 pin interrupt enable when the valid edge input
#define		INT_HVP1MSK		0b00000010			// HVIO1 pin interrupt enable when the valid edge input
#define		INT_HVP2MSK		0b00000100			// HVIO2 pin interrupt enable when the valid edge input

												// - (F051B) AFE Interrupt control 3 -
#define		INT_AFETRAMSK	0b00000001			// AFE timer A interrupt enable
#define		INT_AFETRBMSK	0b00000010			// AFE timer B interrupt enable


												// - (F051C) AFE Interrupt request 0 -
#define		INT_CLEAR		0b00000000			// interrupt requse clear
#define		INT_ADIR		0b00000001			// AD interrupt request
#define		INT_CCIR			0b00000010			// CC interrupt request
#define		INT_CCFSTFLG		0b00000100			// First CC interrupt request
#define		INT_CHGIR		0b00010000			// CHG interrupt request
#define		INT_DWUIR		0b00100000			// Discharge Wakeup interrupt request
#define		INT_CWUIR		0b01000000			// Charge Wakeup interrupt request
#define		INT_DBPTIR		0b10000000			// DBPT interrupt request

												// - (F051D) AFE Interrupt request 1 -
#define		INT_SCDIR		0b00000001			// SCD interrupt request
#define		INT_DOC1DIR		0b00000010			// DOC1D interrupt request
#define		INT_COCDIR		0b00001000			// COCD interrupt request
#define		INT_WDTIR		0b00010000			// WDT interrupt request
#define		INT_OVADIR		0b00100000			// Over Voltage interrupt for AD request
#define		INT_VRG2IR		0b01000000			// VREG2 voltage drop interrupt request

												// - (F051E) AFE Interrupt request 2 -
#define		INT_HVP0IR		0b00000001			// HVP0 interrupt request
#define		INT_HVP1IR		0b00000010			// HVP1 interrupt request
#define		INT_HVP2IR		0b00000100			// HVP2 interrupt request

												// - (F051F) AFE Interrupt request 3 -
#define		INT_AFETRAIR		0b00000001				// AFE timer A interrupt request
#define		INT_AFETRBIR		0b00000010				// AFE timer B interrupt request

												// - (F0520) ADC control 0 -
#define		ADC_EN			0b00000001			// ADC enable
#define		ADC_DIS			0b00000000			// ADC disable

												// - (F0521) ADC control 1 -
#define		ADC_FSP			0b00000000			// ADC force stop
#define		ADC_BTMODE1	0b00000001			// ADC Battery measurement mode 1
#define		ADC_BTMODE2	0b00000010			// ADC Battery measurement mode 2
#define		ADC_HVPMODE	0b00000100			// ADC HVP measurement mode
#define		ADC_THERMMODE	0b00000101			// ADC Themistor measurement mode
#define		ADC_SFUNCMODE	0b00000110			// ADC safety function mode
#define		ADC_ADIMPSEL	0b10000000			// IMP measurement enabled

												// - (F0522) ADC control 2 -

#define		ADATTIME1		0b00000000			// AD auto mode AD time(1msec)
#define		ADATTIME2		0b00000001			// AD auto mode AD time(2msec)
#define		ADATTIME4		0b00000010			// AD auto mode AD time(4msec)
#define		ADATTIME8		0b00000011			// AD auto mode AD time(8msec)
#define		ADATWAITTIME1	0b00000000			// AD auto mode AD Wait time(80usec)
#define		ADATWAITTIME2	0b00010000			// AD auto mode AD Wait time(120usec)
#define		ADATWAITTIME3	0b00100000			// AD auto mode AD Wait time(160usec)
#define		ADATWAITTIME4	0b00110000			// AD auto mode AD Wait time(200usec)
#define		ADATWAITTIME5	0b01000000			// AD auto mode AD Wait time(250usec)
#define		ADATWAITTIME6	0b01010000			// AD auto mode AD Wait time(500usec)
#define		ADATWAITTIME7	0b01100000			// AD auto mode AD Wait time(750usec)
#define		ADATWAITTIME8	0b01110000			// AD auto mode AD Wait time(1000usec)

												// - (F0523) ADC mesurement item select 0 -
#define		ADATOFF			0b00000001			// AD auto mode offset
#define		ADATCELL1		0b00000010			// AD auto mode cell1
#define		ADATCELL2		0b00000100			// AD auto mode cell2
#define		ADATCELL3		0b00001000			// AD auto mode cell3
#define		ADATCELL4		0b00010000			// AD auto mode cell4
#define		ADATCELL5		0b00100000			// AD auto mode cell5
#define		ADATALLCELL3	0b00001111			// AD auto mode cell1-3
#define		ADATALLCELL4	0b00011111			// AD auto mode cell1-4
#define		ADATALLCELL5	0b00111111			// AD auto mode cell1-5

												// - (F0524) ADC mesurement item select 1 -
#define		ADATOFF1		0b00000001			// AD auto mode offset
#define		ADATCELL6		0b00000010			// AD auto mode cell6
#define		ADATCELL7		0b00000100			// AD auto mode cell7
#define		ADATCELL8		0b00001000			// AD auto mode cell8
#define		ADATCELL9		0b00010000			// AD auto mode cell9
#define		ADATCELL10		0b00100000			// AD auto mode cell10
#define		ADATALLCELL7	0b00000111			// AD auto mode cell6-7
#define		ADATALLCELL8	0b00001111			// AD auto mode cell6-8
#define		ADATALLCELL9	0b00011111			// AD auto mode cell6-9
#define		ADATALLCELL10	0b00111111			// AD auto mode cell6-10

												// - (F0526) ADC mesurement item select 3 -
#define		ADATOFF2		0b00000001			// AD auto mode offset
#define		ADATPACK		0b00000010			// AD auto mode Pack voltage
#define		ADATPON		0b00000100			// AD auto mode PON voltage
#define		ADATVIN10		0b00001000			// AD auto mode VIN10(cell total voltage)

												// - (F0527) ADC mesurement item select 4 -
#define		ADATOFF3		0b00000001			// AD auto mode offset
#define		ADATAN0			0b00000010			// AD auto mode AN0
#define		ADATAN1			0b00000100			// AD auto mode AN1
#define		ADATAN2			0b00001000			// AD auto mode AN2
#define		ADATVREGpullAN0pull	0b00010000		// AD auto mode AN0 with pullup
#define		ADATVREGpullAN1pull	0b00100000		// AD auto mode AN1 with pullup
#define		ADATVREGpullAN2pull	0b01000000		// AD auto mode AN2 with pullup
#define		ADATVREGpull		0b10000000			// AD auto mode VREG pullup

												// - (F0528) ADC mesurement item select 5 -
#define		ADATOFF4		0b00000001			// AD auto mode offset
#define		ADATADREF		0b00000010			// AD auto mode AD reference voltage
#define		ADATCCREF		0b00000100			// AD auto mode CC reference voltage
#define		ADATADCCREF	0b00001000			// AD auto mode AD/CC reference voltage
#define		ADATMCUREF		0b00010000			// AD auto mode MCU reference voltage
#define		ADATETHERM		0b00100000			// AD auto mode simple thermistor
#define		ADATCREG2		0b01000000			// AD auto mode CREG2 voltage

												// - (F0529) ADC Status -
#define		ADOPFLG			0b00000001			// AD operation flag
#define		DADOFLG			0b00000010			// cell voltage measurement in DBPT flag
#define		ADSPFLG			0b00000100			// AD measurement stop flag
#define		ADRSTFLG		0b10000000			// MCU reference voltage measurement flag

												// - (F054C) COND0 -			
#define		COND_OFF		0b00000000			// Conditioning off
#define		COND_V1		0b00000001			// Conditioning V1
#define		COND_V2		0b00000010			// Conditioning V2
#define		COND_V3		0b00000100			// Conditioning V3
#define		COND_V4		0b00001000			// Conditioning V4
#define		COND_V5		0b00010000			// Conditioning V5
#define		COND_V6		0b00100000			// Conditioning V6
#define		COND_V7		0b01000000			// Conditioning V7
#define		COND_V8		0b10000000			// Conditioning V8

												// - (F054D) COND1 -			
#define		COND_V9		0b00000001			// Conditioning V9
#define		COND_V10		0b00000010			// Conditioning V10

												// - (F0550) CC control 0 -
#define		CCSHORT			0b00000001			// ISENS1-ISENS0 short
#define		CCDR_200		0b00000010			// Dynamic range 200mV
#define		CCDR_100		0b00000000			// Dynamic range 100mV
#define		CCDR_50			0b00000100			// Dynamic range 50mV
#define		CC_STOP			0b00000000			// CC stop
#define		CC_START		0b11000000			// CC start

												// - (F0554) CC control 0 for IMP measurement-
#define		IMPSEL			0b00000001			// select secondary filter

												// - (F0558) PMHV
#define		HVP0_OUTPUT		0b00000000			// HVP0 Output mode
#define		HVP0_INPUT		0b00000001			// HVP0 Input mode
#define		HVP1_OUTPUT		0b00000000			// HVP1 Output mode
#define		HVP1_INPUT		0b00000010			// HVP1 Input mode
#define		HVP2_OUTPUT		0b00000000			// HVP2 Output mode
#define		HVP2_INPUT		0b00000010			// HVP2 Input mode

												// - (F0559) PHV
#define		HVP0_LOW		0b00000000			// HVP0 Output /Input Low 
#define		HVP0_HIGH		0b00000001			// HVP0 Output /Input High 
#define		HVP1_LOW		0b00000000			// HVP1Output /Input Low 
#define		HVP1_HIGH		0b00000010			// HVP1Output /Input High 
#define		HVP2_LOW		0b00000000			// HVP2Output /Input Low 
#define		HVP2_HIGH		0b00000100			// HVP2Output /Input High 

												// - (F055A) POMHV	
#define		HVP0OUT_DIS		0b00000000			// HVP0 Output Disable
#define		HVP0OUT_NCH	0b00000001			// HVP0 N-ch open-drain output (VCC tolerance)
#define		HVP0OUT_PCH	0b00010000			// HVP0 P-ch open-drain output (VCC tolerance)
#define		HVP1OUT_DIS		0b00000000			// HVP1 Output Disable
#define		HVP1OUT_NCH	0b00000010			// HVP1 N-ch open-drain output (VCC tolerance)
#define		HVP1OUT_PCH	0b00100000			// HVP1 P-ch open-drain output (VCC tolerance)
#define		HVP2OUT_DIS		0b00000000			// HVP2 Output Disable
#define		HVP2OUT_NCH	0b00000100			// HVP2 N-ch open-drain output (VCC tolerance)
#define		HVP2OUT_PCH	0b01000000			// HVP2 P-ch open-drain output (VCC tolerance)
												// - (F055B) PMSHV
#define		HVP_READ_PHV	0b00000000			// PHV register value is read
#define		HVP_READ_LEVEL	0b00000001			// Output level of the pin
												
												// - (F055C) PIMHV
#define		PHIO0_BUF_OFF	0b00000000			// PHIO0 register value is read
#define		PHIO0_BUF_ON	0b00000001			// PHIO0 Output level of the pin
#define		PHIO1_BUF_OFF	0b00000000			// PHIO1 register value is read
#define		PHIO1_BUF_ON	0b00000010			// PHIO1 Output level of the pin
#define		PHIO2_BUF_OFF	0b00000000			// PHIO2 register value is read
#define		PHIO2_BUF_ON	0b00000100			// PHIO2 Output level of the pin

												// - (F0560) SCD control-
#define 		SC_DIS			0b00000000			// Hardware overcurrent detection disable
#define		SC_EN			0b10000000			// Discharge short current detection enabled
#define		SC_FETEN		0b01000000			// Discharge FET control enabled
#define		SCCMPV			0b00001010			// Discharge short current setting (12.5[mV] * 10 + 25[mV]= 150[mV] )

												// - (F0561) DOC 1 control-
#define		DOC1_DIS		0b00000000			// Discharge over current detection disable												
#define		DOC1_EN			0b10000000			// Discharge over current detection enabled
#define		DOC1_FETEN		0b01000000			// Discharge FET control enabled
#define		DOC1CMPV		0b00100010			// Discharge over current setting (2.5[mV] * (n-1) + 15[mV] = 100[mV] )(n = 22)

												// - (F0562) DOC 2 control-
#define		DOC2_DIS		0b00000000			// Discharge over current detection disable													
#define		DOC2_EN			0b10000000			// Discharge over current detection enabled
#define		DOC2_FETEN		0b01000000			// Discharge FET control enabled
#define		DOC2CMPV		0b00100010			// Discharge over current setting (2.5[mV] * (n-1) + 15[mV] = 100[mV] )(n = 22)

												// - (F0563) COCD control-
#define		COC_DIS			0b00000000			// Charge over current detection disable	
#define		COC_EN			0b01000000			// Charge FET control enabled
#define		COC_FETEN		0b10000000			// Charge over current detection enabled
#define		COCCMPV		0b00011100			// Charge over current setting (-5 [mV] * (n - 1CH) - 60[mV]= - 60[mV] )(n = 1C)

												// - (F0564) SCDTIME control-
#define		SCITIM			0b00000101			// Discharge short current detection time (61[us] * 5 = 305[us])

												// - (F0565) DOCTIME control-
#define		DOC1ITIM		0b01100100			// Discharge over current detection time (0.488[ms] * 100 = 48.8[ms])

												// - (F0566) COCTIME control-
#define		COCITIM			0b11111111			// Charge over current detection time (61[us] * 255 = 15555[us])

												// - (F056A) OCDSTS
#define		SCRFLG			0b00000001			// SCR FLAG
#define		DOC1FLG			0b00000010			// DOC1 FLAG
#define		DOC2FLG			0b00000100			// DOC2 FLAG
#define		COCRFLG			0b00001000			// COC FLAG
#define		DOC3FLG			0b00010000			// DOC3 FLAG
#define		DOC4FLG			0b00100000			// DOC4 FLAG


												// - (F056B) CD restart
#define		SCRSTRT			0b00000001			// SCR restart
#define		DOC1RSTRT		0b00000010			// DOC1 restart
#define		DOC2RSTRT		0b00000100			// DOC2 restart
#define		COCRSTRT		0b00001000			// COC restart
#define		DOC3RSTRT		0b00010000			// DOC3 restart
#define		DOC4RSTRT		0b00100000			// DOC4 restart

												// - (F056F) Discharge Wakeup current detection control 2 -
#define		DWUCALEN		0b00000001			// Discharge wakeup calibration enable
#define		DWUACALEN		0b00000010			// Discharge wakeup Auto calibration enable
#define		DWUPERIODIC	0b00000100			// Discharge wakeup Auto calibration(periodic)
#define		DWUGAIN_2		0b00000000			// Input gain 2
#define		DWUGAIN_5		0b00001000			// Input gain 5
#define		DWUGAIN_10		0b00010000			// Input gain 10
#define		DWUGAIN_20		0b00011000			// Input gain 20
#define		DWUEN			0b10000000			// Discharge wakeup detect enable
#define		DWUFETEN		0b01000000			// Discharge FET control enable
#define		DWUDIS			0b00000000			// Discharge wakeup detect disable

												// - (F0571) Charge Wakeup current detection control 2 -
#define		CWUCALEN		0b00000001			// Charge wakeup calibration enable
#define		CWUACALEN		0b00000010			// Charge wakeup Auto calibration enable
#define		CWUPERIODIC		0b00000100			// Charge wakeup Auto calibration(periodic)
#define		CWUGAIN_2		0b00000000			// Input gain 2
#define		CWUGAIN_5		0b00001000			// Input gain 5
#define		CWUGAIN_10		0b00010000			// Input gain 10
#define		CWUGAIN_20		0b00011000			// Input gain 20
#define		CWUEN			0b10000000			// Charge wakeup detect enable
#define		CWUFETEN		0b01000000			// Charge FET control enable
#define		CWUDIS			0b00000000			// Charge wakeup detect disable

												// - (F0573) Current detection control 2 for DBPT -
#define		DBPTCALEN		0b00000001			// Current calibration for DBPT enable
#define		DBPTACALEN		0b00000010			// DBPT Auto calibration enable
#define		DBPTEN			0b10000000			// Current detect for DBPT enable

												// - (F0575) Wakeup current detect status -
#define		DWUDFLG		0b00000001			// DWUD flag
#define		CWUDFLG		0b00000010			// CWUD flag
#define		DBPTFLG			0b00000100			// DBPT flag

												// - (F0576) Wakeup current detect restart -
#define		DWUDRSTRT		0b00000001			// DWUD restart
#define		CWUDRSTRT		0b00000010			// CWUD restart
#define		DBPTRSTRT		0b00000100			// DBPT restart

												// - (F0578) AFE timer A control -
#define		AFETRASTART_ST	0b00000001			// AFE timer A count start
#define		AFETRASTART_SP	0b00000000			// AFE timer A count stop
#define		AFETRASTOP		0b00000100			// AFE timer A count force stop
#define		AFETRACLKSEL_32K	0b00000000		// AFE timer A source 32kHz
#define		AFETRACLKSEL_16K	0b00001000		// AFE timer A source 16kHz

												// - (F0578) AFE timer B control -
#define		AFETRBSTART_ST	0b00000001			// AFE timer B count start
#define		AFETRBSTART_SP	0b00000000			// AFE timer B count stop
#define		AFETRBSTOP		0b00000100			// AFE timer B count force stop

/**********************WINDOW 1 AFE Parameter*************************/
												// - (F0506) OCOCON -
#define		AOCO_EN		0b00000001			// AOCO enable
#define		AOCO_DIS		0b00000000			// AOCO disable
#define		ALOCO_EN		0b00000010			// ALOCO enable
#define		ALOCO_DIS		0b00000000			// ALOCO disable

												// - (F0507) BUFCON -
#define		BUFON1_EN		0b00000001			// BUFON1 enable
#define		BUFON1_DIS		0b00000000			// BUFON1 disable
#define		BUFON2_EN		0b00000010			// BUFON2 enable
#define		BUFON2_DIS		0b00000000			// BUFON2 disable
#define		BUFON3_EN		0b00000100			// BUFON3 enable
#define		BUFON3_DIS		0b00000000			// BUFON3 disable
#define		BUFON4_EN		0b00001000			// BUFON4 enable
#define		BUFON4_DIS		0b00000000			// BUFON4 disable
#define		BUFON5_EN		0b00010000			// BUFON5 enable
#define		BUFON5_DIS		0b00000000			// BUFON5 disable
#define		VCPON_EN		0b10000000			// VCPON enable
#define		VCPON_DIS		0b00000000			// VCPON disable

												// - (F051A) PONEG -								// - (F051A) PONEG -
#define		PONDIS			0b00000000			// PON pin valid edge selection (Disable)
#define		PONRE			0b00010000			// PON pin valid edge selection (Rising edge)
#define		PONFE			0b00000001			// PON pin valid edge selection (Falling edge)
#define 		PONBE			0b00010001			// PON pin valid edge selection (Both edge)

												// - (F051B) POMON -
#define		PONLOW			0b00000000			// Status of PON pin (Low level)
#define		PONHIGH			0b00000001			// Status of PON pin (High level)
												// - (F0520) DADCON0 -
#define		DTBST			0b00000001			// Cell voltage auto measurement start for DBPT
#define		DADEN			0b00000010			// Cell voltage auto measurement enable for DBPT
#define		DADOCOFF		0b00000100			// Offset of cell voltage for DBPT

												// - (F0521) DADCON1 -
#define		OFFSET_SEL		0b00000000			// Offset voltage measurement
#define		CELL1_SEL		0b00000001			// Cell 1 voltage measurement
#define		CELL2_SEL		0b00000010			// Cell 2 voltage measurement
#define		CELL3_SEL		0b00000011			// Cell 3 voltage measurement
#define		CELL4_SEL		0b00000100			// Cell 4 voltage measurement
#define		CELL5_SEL		0b00000101			// Cell 5 voltage measurement
#define		CELL6_SEL		0b00000110			// Cell 6 voltage measurement
#define		CELL7_SEL		0b00000111			// Cell 7 voltage measurement
#define		CELL8_SEL		0b00001000			// Cell 8 voltage measurement
#define		CELL9_SEL		0b00001001			// Cell 9 voltage measurement
#define		CELL10_SEL		0b00001010			// Cell 10 voltage measurement
#define		PACK_SEL		0b00001011			// Pack voltage measurement
#define		WU_SEL			0b00001100			// Wakeup voltage measurement
#define		ALLCELL_SEL		0b00001101			// Total cell  voltage measurement

												// - (F0522) DADCON2 -
#define		ADTIME1			0b00000000			// AD time(1msec)
#define		ADTIME2			0b00000001			// AD time(2msec)
#define		ADTIME4			0b00000010			// AD time(4msec)
#define		ADTIME8			0b00000011			// AD time(8msec)
#define		ADWAITTIME1		0b00000000			// AD Wait time(80usec)
#define		ADWAITTIME2		0b00010000			// AD Wait time(120usec)
#define		ADWAITTIME3		0b00100000			// AD Wait time(160usec)
#define		ADWAITTIME4		0b00110000			// AD Wait time(200usec)
#define		ADWAITTIME5		0b01000000			// AD Wait time(250usec)
#define		ADWAITTIME6		0b01010000			// AD Wait time(500usec)
#define		ADWAITTIME7		0b01100000			// AD Wait time(750usec)
#define		ADWAITTIME8		0b01110000			// AD Wait time(1000usec)

												// - (F0561) DOC1CAL -
#define		DOC1CAL_EN		0b10000000			// Discharge over current 1 Calibraton enable
#define		DOC1CAL_DIS		0b00000000			// Discharge over current 1 Calibraton disable

												// - (F0563) COCCAL -
#define		COCCAL_EN		0b10000000			// Charge over current Calibraton enable
#define		COCCAL_DIS		0b00000000			// Charge over current Calibraton disable

												// - (F0564) DOC 3 control-
#define		DOC3EN			0b10000000			// Discharge over current detection enabled
#define		DOC3FETEN		0b01000000			// Discharge FET control enabled
#define		DOC3CMPV		0b00100010			// Discharge over current setting (2.5[mV] * (n-1) + 15[mV] = 100[mV] )(n = 22)

												// - (F0565) DOC 4 control-
#define		DOC4EN			0b10000000			// Discharge over current detection enabled
#define		DOC4FETEN		0b01000000			// Discharge FET control enabled
#define		DOC4CMPV		0b00100010			// Discharge over current setting (2.5[mV] * (n-1) + 15[mV] = 100[mV] )(n = 22)

												// - (F056B) OCDWUICON -
#define		INT_SCEN		0b00000001			// SC interrupt enable
#define		INT_DOC1EN		0b00000010			// DOC1 interrupt enable
#define		INT_DOC2EN		0b00000100			// DOC2 interrupt enable
#define		INT_COCEN		0b00001000			// COC interrupt enable
#define		INT_DWUEN		0b00010000			// DWU interrupt enable
#define		INT_CWUEN		0b00100000			// DWU interrupt enable
#define		INT_DBPTEN		0b01000000			// DBPT interrupt enable

												// - (F056C) WUDICON -
#define		DWUIEN			0b00000001			// Enabled to output the interrupt signal in the discharge wakeup current detction
#define		CWUIEN			0b00000010			// Enabled to output the interrupt signal in the charge wakeup current detction
#define		HLDIEN			0b00000100			// Enabled to output the interrupt signal in the heavy current detection circuit

#endif
