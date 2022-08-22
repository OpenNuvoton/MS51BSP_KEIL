/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************/
/*  File Function: MS51 ADC multi channel input demo code                                                 */
/**********************************************************************************************************/
#include "MS51_8K.H"

/* For printf code only. Disable this define to reduce code size. */
//#define print_function 

unsigned char xdata ADCdataAIN5H, ADCdataAIN5L;
unsigned char xdata ADCdataVBGH, ADCdataVBGL;

/*****************************************************************************/
/*The main C function.  Program execution starts                             */
/*here after stack initialization.                                           */
/*****************************************************************************/
void main (void) 
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
  
/*Enable channel 5 */ 
      ENABLE_ADC_CH5;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(ADCF == 0);
      ADCdataAIN5H = ADCRH;
      ADCdataAIN5L = ADCRL;
      DISABLE_ADC;
#ifdef print_function
      printf("\n ADC channel 5 =0x%bx", ADCdataAIN5H);
#endif

/*Enable Bandgap */     
      ENABLE_ADC_BANDGAP;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(ADCF == 0);
      ADCdataVBGH = ADCRH;
      ADCdataVBGL = ADCRL;
      DISABLE_ADC;
#ifdef print_function
      printf("\n ADC channel bandgap =0x%bx", ADCdataVBGH);
#endif
      
    while(1);  
}