/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 system clock enable ECLK demo code
//***********************************************************************************************************
#include "ms51_32k.h"

/*=============================================================================================*/
/*  The test process:                                                                          */
/*  1. Power on is run as default HIRC, show LED Fsys tickle faster                            */
/*  2. toggle P3.5 to GND. Call modify Fsys code to External clock, oscillator input.          */
/*  3. toggle P3.5 to VDD. Call modify Fsys code to HIRC.                                      */
/*  4. LED tickle speed slowly than before                                                     */
/*=============================================================================================*/


void main(void)
{

/* Note
  MCU power on system clock is HIRC (16 MHz)
  Please keep P3.0 HIGH before you want to modify Fsys to LIRC
*/
    P35_INPUT_MODE;
    P11_PUSHPULL_MODE;
    set_CKCON_CLOEN;                                  // Also can check P1.1 CLO pin for clock to find the Fsys change.
    while(P35);
    FsysSelect(FSYS_OSCIN_P30);
    Timer0_Delay(16000000,200,1000);
    while (!P35);
    FsysSelect(FSYS_HIRC);
    Timer0_Delay(16000000,2000,1000);
    set_PCON_PD;
    while(1);

}

