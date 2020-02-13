/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 UART receive and transmit toggle out demo code
//***********************************************************************************************************

#include "MS51_32K.h"

/**
 * @brief       UART2 TXD output demo
 * @param       None
 * @return      None
 * @details     conned UART2 and UART0 to loop check.
 */

void main (void) 
{
    UART3_Open(16000000,115200);                 /* Open UART3 use timer1 as baudrate generate and baud rate = 115200*/
    P15_QUASI_MODE;                              /* Set UART3_TXD pin P1.5 as Quasi mode */
    P34_INPUT_MODE;                              /* Set UART3_RXD pin P3.4 as Input mode */
    ENABLE_UART3_TXD_P15;
    ENABLE_UART3_RXD_P34;

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