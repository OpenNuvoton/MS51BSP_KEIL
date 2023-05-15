/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP program LDROM demo code
//***********************************************************************************************************
#include "MS51_16K.H"


/*---------------------------------------------------------------
 * Try to avoid modify CONFIG in the program
 * NEVER modify config immediately after RESET
//---------------------------------------------------------------*/

void main (void) 
{
    P12_QUASI_MODE;
    P12 = 1;
    while(P12);

    if(PCON&SET_BIT4)        /* Check with power on flag. Only the first power on check with CONFIG */
    {
       Modify_CONFIG(0xEF,0xFF,0x6B,0xFF,0xFF);
       PCON&=CLR_BIT4;      /* Clear power on flag to avoid software reset modify CONFIG again. */
    }

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
