/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 UART1 with interrupt demo                                                           */
/************************************************************************************************************/
#include "ms51_32k.h"

/****************************************************************************************************************
 * FUNCTION_PURPOSE: Main function 
 !!! MS51_8K UART1 pin also occupied by debug pin, 
 please remove Nu-link or not in debug mode to test UART1 function.
 External UART1 connect also disturb debug download
 ***************************************************************************************************************/

#define   UART1_P36_P37      /* This define UART1 pin assign*/

void main (void)
{
  /* Modify HIRC to 24MHz for UART baud rate deviation not over 1%*/
    MODIFY_HIRC(HIRC_24);

  /* UART1 initial */
#ifdef   UART1_P16_P02            /*  if define UART1_P16_P02 initial GPIO and MFP */
    P16_QUASI_MODE;
    P02_INPUT_MODE;
    ENABLE_UART1_TXD_P16;
    ENABLE_UART1_RXD_P02;
#elif defined  UART1_P36_P37      /*  if define UART1_P36_P37 initial GPIO and MFP */
    P36_QUASI_MODE;
    P37_INPUT_MODE;
    ENABLE_UART1_TXD_P36;
    ENABLE_UART1_RXD_P37;
#elif defined  UART1_P10_P00      /*  if define UART1_P10_P00 initial GPIO and MFP */
    P01_QUASI_MODE;
    P00_INPUT_MODE;
    ENABLE_UART1_TXD_P10;
    ENABLE_UART1_RXD_P00;
#endif
    UART_Open(24000000,UART1_Timer3,115200);
    ENABLE_UART1_INTERRUPT;                 //For interrupt enable , interrupt subroutine is in uart.c file
    ENABLE_GLOBAL_INTERRUPT;                //Enable global interrupt

    /* Wait UART receive data and send to TXD */
    while(1)
    {
      if (uart1_receive_flag)
      {   
          uart1_receive_flag = 0;
          UART_Send_Data(UART1,uart1_receive_data);

      }
    }
}
  
