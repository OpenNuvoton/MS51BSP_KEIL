/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "MS51_32K.h"
#include "SPROM.h"


void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window
    UART_Open(24000000,UART0_Timer1,115200);

    while(1)
    {
      SPROM_CODE();
      ENABLE_UART0_PRINTF;
      printf ("\n SPTEMP= 0x%BX", SPTEMP);
      DISABLE_UART0_PRINTF;
      Timer0_Delay(24000000,300,1000);
    }

}
