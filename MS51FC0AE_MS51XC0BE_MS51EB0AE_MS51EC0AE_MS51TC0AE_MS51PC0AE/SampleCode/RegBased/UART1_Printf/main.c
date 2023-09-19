/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"


/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART4 printf send data.
 */
void main (void) 
{
/* Modify HIRC to 24MHz for UART baud rate deviation not over 1%*/
    MODIFY_HIRC(HIRC_24);
    UART_Open(24000000,UART1_Timer3,115200);

    while(1)
    {
      ENABLE_UART1_PRINTF;
      printf("\n hello world !!!");
      DISABLE_UART1_PRINTF;
      Timer0_Delay(24000000,300,1000);
    }
  
}