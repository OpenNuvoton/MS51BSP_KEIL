/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "MS51_8K.H"
#include "SPROM.h"

//#define  print_function

void main (void) 
{
#ifdef print_function
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
#endif
    
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window
    while(1)
    {
      SPROM_CODE();
#ifdef print_function
      printf ("\n SPTEMP= 0x%BX", SPTEMP);
#endif
      Timer0_Delay(24000000,300,1000);
    }

}
