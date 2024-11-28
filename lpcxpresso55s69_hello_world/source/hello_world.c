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

#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/



/*******************************************************************************
 * Prototypes
 ******************************************************************************/
bool constant(const void *a, const void *b, size_t length);
/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 *
 */
bool constantaa(const void *a, const void *b, size_t length){
	const char *ca =a, *cb=b;
	bool result = true;
	for(size_t i=0; i< length; i++){
		result &=ca[i] == cb[i];
	return result;
	}
}
int main(void)
{
    char ch;

    /* Init board hardware. */
    /* set BOD VBAT level to 1.65V */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
#if !defined(DONT_ENABLE_FLASH_PREFETCH)
    /* enable flash prefetch for better performance */
    SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif
    char password_stored[20]="1234";
    char input[20];
    uint32_t DWT1, DWT2,status;

    while (1)
    {
    		SCANF("%s", input);
    	    DWT1 = DWT -> CYCCNT;
    	    status= constantaa(input,password_stored, strlen(password_stored));
    	    DWT2=DWT-> CYCCNT;
    	    PRINTF("\r\nCycles in function %d", DWT2-DWT1);
    	    PRINTF("\r\ninput:  %s",input);
    	    if (status==1){
    	    	PRINTF("\r\ninput correct");
    	    }
    	    else {
    	    	PRINTF("\r\ninput invalid");
    	    }

        ch = GETCHAR();
        PUTCHAR(ch);
    }
}
