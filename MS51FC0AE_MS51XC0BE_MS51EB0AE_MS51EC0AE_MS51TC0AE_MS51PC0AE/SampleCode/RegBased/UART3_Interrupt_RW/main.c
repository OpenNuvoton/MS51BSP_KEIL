/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"

#define     UART3_P12_P11

/**
 * @brief       SC1 interrupt vector
 * @param       None
 * @return      None
 * @details     Store receive data.
 */
void SC1_ISR(void) interrupt 22          // Vector @  0x9B
{
    PUSH_SFRS;
        SFRS = 2;
        uart3rvflag = 1;
        uart3rvbuffer = SC1DR;
    POP_SFRS;
} 
 
/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART3 send received data loop check.
 */
void main (void) 
{
  /* UART3 initial */
#ifdef          UART3_P12_P11
    P12_QUASI_MODE;
    P11_INPUT_MODE;
    ENABLE_UART3_TXD_P12;
    ENABLE_UART3_RXD_P11;
#elif  defined   UART3_P15_P25
    P15_QUASI_MODE;
    P25_INPUT_MODE;
    ENABLE_UART3_TXD_P15;
    ENABLE_UART3_RXD_P25;
#elif  defined   UART3_P05_P34
    P05_QUASI_MODE;
    P34_INPUT_MODE;
    ENABLE_UART3_TXD_P05;
    ENABLE_UART3_RXD_P34;
#endif
    MODIFY_HIRC(HIRC_24);
    UART3_Open(24000000,115200);                 /* Open UART3 use timer1 as baudrate generate and baud rate = 115200*/
    ENABLE_SC1_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart3rvflag)
    {
      uart3rvflag = 0;
      UART3_Send_Data(uart3rvbuffer);
    }
   }
 }