/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 read UID demo
//***********************************************************************************************************
#include "ms51_8k.h"

/* For printf code only. Disable this #include "ms51_8k.h" to reduce code size. */
//#define  print_function 

void main(void)
{

#ifdef print_function 
  unsigned char READ1;
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
#endif

  Read_UID();
  
#ifdef print_function   
  ENABLE_UART0_PRINTF;
  printf ("\n UID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf (" 0x%BX",UIDBuffer[READ1]);
  }
  DISABLE_UART0_PRINTF;
#endif  
  
  while(1);


}