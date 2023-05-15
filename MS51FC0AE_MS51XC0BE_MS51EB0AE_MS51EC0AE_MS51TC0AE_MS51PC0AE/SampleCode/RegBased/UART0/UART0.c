/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 UART0 initial demo code                                                             */
/************************************************************************************************************/
#include "MS51_32K.h"


/*******************************************************************************
 * FUNCTION_PURPOSE: Main function 
 ******************************************************************************/
void main (void)
{
/* Modify HIRC to 24MHz for UART baud rate function only */
   MODIFY_HIRC(HIRC_24);

   P06_PUSHPULL_MODE;
   P07_INPUT_MODE;
   UART_Open(24000000,UART0_Timer3,115200);
   ENABLE_UART0_INTERRUPT;
   ENABLE_GLOBAL_INTERRUPT;

    while(1)
    {
        UART_Send_Data(UART0,0x55);      /* check uart.c*/
        Timer0_Interrupt_Init(24000000,100,1000);
    }
    
}
  
