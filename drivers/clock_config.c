/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v4.0
* BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/**
 * @file    clock_config.c
 * @brief   Board clocks initialization file.
 */
 
/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/

#include "fsl_common.h"
#include "clock_config.h"
/* ARM PLL configuration for RUN mode */
const clock_arm_pll_config_t armPllConfig = {
  .loopDivider = 88U};
/**
 * @brief Set up and initialize all required blocks and functions related to the board hardware.
 */
void BOARD_InitBootClocks(void) {
	/* The user initialization should be placed here */
    CLOCK_SetXtalFreq(24000000U);
    CLOCK_SetMux(kCLOCK_PeriphClk2Mux, 0x1); /* Set PERIPH_CLK2 MUX to OSC */
    CLOCK_SetMux(kCLOCK_PeriphMux, 0x1); /* Set PERIPH_CLK MUX to PERIPH_CLK2 */

    CLOCK_InitArmPll(&armPllConfig); /* Configure ARM PLL to 1056M */
    CLOCK_SetDiv(kCLOCK_ArmDiv, 0x1); /* Set ARM PODF to 0, divide by 2 */
    CLOCK_SetDiv(kCLOCK_AhbDiv, 0x0); /* Set AHB PODF to 0, divide by 1 */
    CLOCK_SetDiv(kCLOCK_IpgDiv, 0x3); /* Set IPG PODF to 3, divede by 4 */

    CLOCK_SetMux(kCLOCK_PrePeriphMux, 0x3); /* Set PRE_PERIPH_CLK to PLL1, 1056M */
    CLOCK_SetMux(kCLOCK_PeriphMux, 0x0); /* Set PERIPH_CLK MUX to PRE_PERIPH_CLK */

	/* Read core clock setting. */
	//SystemCoreClockUpdate();
    SystemCoreClock = 528000000;
}
