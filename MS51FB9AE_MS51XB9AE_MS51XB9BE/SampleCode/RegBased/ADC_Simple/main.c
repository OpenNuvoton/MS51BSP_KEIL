/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"

unsigned char xdata ADCdataAINH, ADCdataAINL;

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void) 
{
/* Initial UART0 for printf */
    unsigned char temp;
  
    ENABLE_ADC_AIN4;            

  /* ADC Low speed initial*/  
    ADCCON1|=0X30;            /* clock divider */
    ADCCON2|=0X0E;            /* AQT time */

    P12_PUSHPULL_MODE;
 
    while(1)
    {
      Timer2_Delay(16000000,128,100,1000);;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      temp = ADCRH;
      P12 ^= 1;
    }
}


