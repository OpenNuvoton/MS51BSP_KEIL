/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************
//  File Function: MS51 UART0 receive and transmit loop test
/***********************************************************************************************************/
#include "ms51_16k.h"

unsigned char uart_receive_data;
bit receiveFlag,bufOverFlag;

void Serial_ISR(void) interrupt 4
{
    _push_(SFRS);
  
    if (RI)
    {
        uart0_receive_flag = 1;
        uart0_receive_data = SBUF;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }

    if (TI)
    {
        if (!PRINTFG)
        {
            TI = 0;
        }
    }

    _pop_(SFRS);
}

/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{
    GPIO_LED_QUASI_MODE;
/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_INTERRUPT;                                  /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */

/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      GPIO_LED ^= 1;
      UART_Send_Data(UART0,uart0_receive_data);
      uart0_receive_flag = 0;
    }
  }
}