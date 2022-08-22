/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 read UID demo
//***********************************************************************************************************
#include "MS51_16K.H"


void main(void)
{
  unsigned char READ1;
  ALL_GPIO_QUASI_MODE;

/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;

  Read_UID();
  printf ("\n UID = ");
  for(READ1=0;READ1<12;READ1++)
  {
//    printf (" 0x%bx",UIDBuffer[READ1]);
  }
  
  while(1);


}