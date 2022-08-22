/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 read UCID demo
//***********************************************************************************************************
#include "MS51_8K.H"


/***********************/
/* main loop           */
/***********************/ 
void main(void)
{
  unsigned char u8Counter;

  MODIFY_HIRC(HIRC_24);

  Read_UCID();
  
  printf ("\n UCID = ");
  for(u8Counter=0;u8Counter<12;u8Counter++)
  {
    printf (" 0x%bx",UCIDBuffer[u8Counter]);
  }
  DISABLE_UART0_PRINTF;

  while(1);


}