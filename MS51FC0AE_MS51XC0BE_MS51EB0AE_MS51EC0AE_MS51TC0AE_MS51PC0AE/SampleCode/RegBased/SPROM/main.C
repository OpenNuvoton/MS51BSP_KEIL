/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "ms51_32k.h"
#include "sprom.h"


void main (void) 
{

    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer1,115200);
    ENABLE_UART0_PRINTF;
    
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window
    printf ("\n protect bit is 0x%BX", protect);
    while(1)
    {
      SPROM_CODE();
      printf ("\n SPTEMP= 0x%BX", SPTEMP);
      Timer0_Delay(24000000,300,1000);
    }

}
