/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"


/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
/*=============================================================================================*/
/*  The test process:                                                                          */
/*  1. Power on is run as default HIRC, show LED Fsys tickle faster                            */
/*  2. toggle P1.7 to GND. Call modify Fsys code to LIRC.                                      */
/*  3. toggle P1.7 to VDD. Call modify Fsys code to HIRC.                                      */
/*  4. LED tickle speed slowly than before                                                     */
/*=============================================================================================*/
void main(void)
{
    P11_QUASI_MODE;
    set_CKCON_CLOEN;                                  // Also can check P1.1 CLO pin for clock to find the Fsys change.
    while (P17);
    FsysSelect(FSYS_LIRC);
    Timer0_Delay(10000,200,1000);
    while (!P17);
    FsysSelect(FSYS_HIRC);
    Timer0_Delay(16000000,2000,1000);
    while (P17);
    set_PCON_PD;
    while(1);

}

