/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "ms51_8k.h"

unsigned char code protect [] = { 
0X32,0X33,0X34,0X55
}; 


void main (void) 
{
    unsigned char i;

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);

    for(i=0;i<10;i++)
    {
      UART_Send_Data(UART0,0x55);
      Timer0_Delay(24000000,1,1000);
    }
    for(i=0;i<4;i++)
    {
      UART_Send_Data(UART0,protect[i]);
      Timer0_Delay(24000000,1,1000);
    }

  while(1);

}



