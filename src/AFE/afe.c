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
* System Name	: RAA241xxx RBMS-P Firmware for Renesas
* File Name		: afe.c
* Contents		: RAA241xxx AFE
* Compiler		: CC-RL
* Note			:
*************************************************************************
* Copyright,2022 (2012-2022) RENESAS ELECTRONICS CORPORATION,
*                            All right reserved.
*""FILE COMMENT END""*****************************************************/
#define _AFE_C

#include "define.h"
#include "afe.h"
#include "device_register.h"
#include "device_mapping.h"
#include "afewindow_mapping.h"

// - Declare Internal function -------------------------------------------------
static void afe_ISR_Clear(void);
static U8 afe_HW_Init(void);
static st_afe_init_result_t afe_Get_Info(void);
static void         * p_ctx = (void *)0;

// - Internal variable ---------------------------------------------------------
/* Saved PSW value used by nested critical-section helpers. */
static U8 u8_psw;
/* Nested critical-section depth counter. */
static U8 u8_nest_dept;
/* Cached current AFE register window selection. */
static U8 u8_AFE_Window;
/* User callback and opaque context dispatched from ISR bridge. */
static afe_callback_t st_callback  = (afe_callback_t)0;
/* Error flag for invalid PUSH/POP nesting usage. */
static U8 u8_psw_error;
// - Define function -----------------------------------------------------------
/*******************************************************************************
* Function Name: PSW_PUSH
* Description  : PSW_PUSH
* Arguments    : void
* Return Value : void
*******************************************************************************/

void MCU_PSW_PUSH(void)
{
	/* On first entry, save PSW and disable interrupts. */
	if(u8_nest_dept == 0)
	{
		u8_psw = __get_psw();
		DI();
	}
	u8_nest_dept++;
	/* Detect wrap-around to guard against misuse of push/pop API. */
	if(u8_nest_dept == 255)
	{
		u8_psw_error = ON;
	}
}

void MCU_PSW_POP(void)
{
	/* Prevent underflow when pop is called without matching push. */
	if(u8_nest_dept == 0)
	{
		u8_psw_error = ON;
		return;
	}
	
	u8_nest_dept--;
	
	if(u8_nest_dept == 0)
	{
		/* Restore original PSW only when outermost critical section exits. */
		 __set_psw(u8_psw);	
	}
}
U8 MCU_PSW_Get_Error(void)
{
	/* Return sticky error state for critical-section misuse diagnostics. */
	return u8_psw_error;
}
/*******************************************************************************
* Function Name: PSW_POP
* Description  : PSW_POP
* Arguments    : void
* Return Value : void
*******************************************************************************/
U8 afe_HW_Init(void)
{
	U8 u8_reg_check = TRUE;
	
	MCU_Pin_Init();
	MCU_AFE_Pin_Init();

	if(u8_reg_check == TRUE)
	{
		u8_reg_check = AFE_PWR_Reset();
	}
	if(u8_reg_check == TRUE)
	{
		// Load AFE trimming data before functional setup.
		u8_reg_check = AFE_Trimming_Setting();
	}
	
	return u8_reg_check;
}
st_afe_init_result_t AFE_Init( st_afe_config_t st_afe_config )
{
	st_afe_init_result_t init_result;
	
	init_result = afe_Get_Info();
	// Perform hardware-level initialization.
	init_result.u8_init_result =afe_HW_Init();
	if(init_result.u8_init_result == FALSE)
	{
		return init_result;
	}
	// Configure the AFE clock source.
	init_result.u8_init_result = AFE_PWR_Control(st_afe_config.e_afe_clock); 														// Clock = OCO
	if(init_result.u8_init_result == FALSE)
	{
		return init_result;
	}
	afe_ISR_Clear();
	// Configure AFE timers.
	AFE_Timer_Init(); 													// Initialize AFE timer
	
	// Configure the ADC block.
	init_result.u8_init_result = AFE_AD_Init(st_afe_config.st_afe_adc_config);
	if(init_result.u8_init_result == FALSE)
	{
		return init_result;
	}

	// Configure the current integration (CC) block.
	AFE_CI_Init();
	
	// Ensure conditioning block starts from a known stopped state.
	AFE_CB_Stop();

	// Initialize FET control state.
	AFE_FET_Init();
	
	// Initialize high-voltage protection block.
	AFE_HVP_Init();

	// Configure abnormal detection blocks (WDT/OC).
	init_result.u8_init_result = AFE_Abn_WDT_Init(st_afe_config.e_afe_wdt_config);
	if(init_result.u8_init_result == FALSE)
	{
		return init_result;
	}

	init_result.u8_init_result = AFE_Abn_OC_Init(st_afe_config.st_afe_hw1_config);
	if(init_result.u8_init_result == FALSE)
	{
		return init_result;
	}
	// Configure wake-up sources.
	init_result.u8_init_result = AFE_WKUP_Init(st_afe_config.st_afe_hw2_config);
	if(init_result.u8_init_result == FALSE)
	{
		return init_result;
	}

	EI();
	
	return init_result;
}
/*******************************************************************************
* Function Name: AFE_Reg_Write
* Description  : AFE_Reg_Write
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_Reg_Write( volatile __far U8 *p_reg, U8 u8_data )
{
	MCU_PSW_PUSH();								// Save PSW and enter critical section if needed.

	CS = HI;										// Assert chip select.
	*p_reg = u8_data;								// Write one byte to the target AFE register.
	CS = LOW;									// Deassert chip select.
	
	MCU_PSW_POP(); 								// Restore PSW when the nested critical section exits.
}


/*******************************************************************************
* Function Name: AFE_Reg_Read
* Description  : AFE_Reg_Read
* Arguments    : void
* Return Value : void
*******************************************************************************/
void AFE_Reg_Read( volatile __far U8 *p_reg, U8 u8_size, U8 __near *p_data )
{
	U8	u8_index = 0;
	if( u8_size <=14 )								// Protect against invalid burst sizes.
	
	{
		MCU_PSW_PUSH();							// Save PSW and enter critical section if needed.
			
		CS = HI;									// Assert chip select.
		
		for( u8_index=0; u8_index<u8_size; u8_index++ )// Read registers sequentially into the output buffer.
		{
			p_data[u8_index] = p_reg[u8_index]; 		// Copy one register byte.
		}
		CS = LOW;								// Deassert chip select.

		MCU_PSW_POP(); 							// Restore PSW when the nested critical section exits.
	}
}
U8 AFE_WindowTo( E_AFE_WINDOW_ITEM e_window )
{
	U8 u8_window_check = TRUE;

	/* Reject invalid window values from caller. */
	if(e_window > E_AFE_WINDOW2)
	{
		return FALSE;
	}

	/* Only allow transitions to window1/window2 from window0. */
	if(u8_AFE_Window != E_AFE_WINDOW0)
	{
		if((e_window == E_AFE_WINDOW1)||(e_window == E_AFE_WINDOW2))
		{
			return FALSE;
		}
	}
	
	/* When currently in window1/window2, force return path through window0. */
	if((u8_AFE_Window == E_AFE_WINDOW1)||(u8_AFE_Window == E_AFE_WINDOW2))
	{
		if(e_window != E_AFE_WINDOW0)
		{
			return FALSE;
		}

	}
	
	u8_AFE_Window = e_window;
	if(e_window != E_AFE_WINDOW0)
	{
		/* Keep interrupts locked while operating in non-default windows. */
		 MCU_PSW_PUSH();
	}
	
	AFE_Reg_Write(p8_WINDOW_Reg_Mapping,u8_WINDOW_Data_Mapping[e_window]);
	
	if(e_window == E_AFE_WINDOW0)
	{
		/* Release lock once default window is restored. */
		MCU_PSW_POP();
	}

	return u8_window_check;
}

U8 AFE_Get_Window( void )
{
	/* Return cached logical window state. */
	return u8_AFE_Window;
}

void AFE_Callback_ISR(afe_callback_t st_cb, void * p_context)
{
	/* Update callback atomically to avoid ISR/main race on function pointer. */
	MCU_PSW_PUSH();
	st_callback  = st_cb;
	p_ctx = p_context;
	MCU_PSW_POP();
}

U32 AFE_Int_HwOvf_Get(void)
{
	U32 u32_snap;
	/* Snapshot overflow bits atomically for main-loop inspection. */
	MCU_PSW_PUSH();
	u32_snap = u32_AFE_IntOVF_Flg;
	MCU_PSW_POP();
	return u32_snap;
}

void AFE_Int_HwOvf_Clear(U32 mask)
{
	/* Clear only the requested overflow bits. */
	MCU_PSW_PUSH();
	u32_AFE_IntOVF_Flg &= ~mask;
	MCU_PSW_POP();
}

void AFE_DispatchFrom_ISR(E_AFE_EVENT_ITEM e_ev)
{
	/* Bridge ISR events to user callback while preserving critical section. */
	MCU_PSW_PUSH();
	if (st_callback)
	{
		st_afe_callback_args_t args = { e_ev, p_ctx };
		st_callback(&args);
	}
	MCU_PSW_POP();
}

void afe_ISR_Clear(void)
{
	U8 u8_afe_seq = 0;
	
	/* Execute mandatory reset-write sequence for internal ISR flags. */
	for(u8_afe_seq = 0; u8_afe_seq < U8_ISR_RESET_SEQ; u8_afe_seq++)
	{
		AFE_Reg_Write((volatile U8 __far *)p8_ISR_Reset_Sequence_Mapping,0x00);	
	}
	
}
st_afe_init_result_t afe_Get_Info(void)
{
	st_afe_init_result_t init_result;
	
	/* Provide static capabilities and driver identity information. */
	init_result.u8_init_result = TRUE;
	init_result.u8_max_cell_series = U8_MAX_CELL_COUNT;
	init_result.u8_max_thermistor_series =  U8_MAX_THERMISTOR_COUNT;
	init_result.e_target_deviece = E_AFE_DEV_RAJ240100;
	init_result.u16_driver_version= U16_DRVICE_VERSION;

	return init_result;
}
