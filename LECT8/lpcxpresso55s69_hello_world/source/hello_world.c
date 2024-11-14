/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "peripherals.h"
#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
void TimerIRQ(uint32_t flags)
{
	PRINTF("IRQ.\r\n");
}


void CTIMER2IRQ(uint32_t flags)
{
	PRINTF("LED.\r\n");


}

void PWM_IRQ(uint32_t flags)
{
	static uint32_t duty = 0;
	static uint8_t UpDown = 0;

	CTIMER_UpdatePwmDutycycle(CTIMER2_PERIPHERAL, CTIMER2_PWM_0_CHANNEL,duty);
	if(duty==100)
	{
		UpDown=1;
	}
	else if(duty==0)
	{
		UpDown =0;
	}

	if (UpDown==0)
	{
		duty++;
	}
	else if(UpDown==1)
	{
		duty--;
	}
}
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
char ch;

int main(void)
{


    /* Init board hardware. */
    /* set BOD VBAT level to 1.65V */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    BOARD_InitPeripherals();
#if !defined(DONT_ENABLE_FLASH_PREFETCH)
    /* enable flash prefetch for better performance */
    SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif

    PRINTF("hello world.\r\n");

    CTIMER_StartTimer(CTIMER1_PERIPHERAL);
    CTIMER_StartTimer(CTIMER2_PERIPHERAL);

    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
    }
}
