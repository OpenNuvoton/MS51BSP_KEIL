/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ADC simple convert demo code
//***********************************************************************************************************
#include "ms51_32k.h"
 bit  ADC_CONT_FINAL_FLAG; 
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/

void main (void) 
{
/* Initial UART0 for printf */
    unsigned int temp;

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
  
    ENABLE_ADC_CH0;           
   
    while(1)
    {
      Timer2_Delay(24000000,128,300,1000);;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      temp=(ADCRH<<4)+(ADCRL&0x0F);
      printf ("\n ADC Value = 0x%02X", temp);
      P35 ^= 1;
    }
}


