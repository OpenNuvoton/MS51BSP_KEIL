/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 read UCID demo
//***********************************************************************************************************
#include "ms51_32k.h"

/***********************/
/* main loop           */
/***********************/ 
void main(void)
{
  unsigned char u8Counter;
	
  
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
  
  
  Read_UCID();
  printf ("\n UCID = ");
  for(u8Counter=0;u8Counter<12;u8Counter++)
  {
    printf (" 0x%bx",UCIDBuffer[u8Counter]);
  }
  while(1);


}