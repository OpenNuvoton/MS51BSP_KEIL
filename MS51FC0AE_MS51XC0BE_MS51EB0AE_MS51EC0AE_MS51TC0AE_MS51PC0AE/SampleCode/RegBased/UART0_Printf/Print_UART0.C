/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 use UART0 as printf function output demo                                            */
/************************************************************************************************************/
#include "MS51_32K.h"


void main (void) 
{

/* Modify HIRC to 24MHz is for UART baud rate deviation not over 1% */
    P06_QUASI_MODE;
    MODIFY_HIRC(HIRC_24);
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;                              // Important! use prinft function must set TI=1;
  
    while(1)
    {
      ENABLE_UART0_PRINTF;
      printf("\n Hello world!");
      DISABLE_UART0_PRINTF;
      Timer0_Delay(16000000,300,1000);
    }
}