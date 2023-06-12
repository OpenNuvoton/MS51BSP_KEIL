/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************/
/*  File Function: MS51 ADC multi channel input demo code                                                 */
/**********************************************************************************************************/
#include "MS51_16K.H"

unsigned int ADCdataAIN5, ADCdataVBG;

/*****************************************************************************/
/*The main C function.  Program execution starts                             */
/*here after stack initialization.                                           */
/*****************************************************************************/
void main (void) 
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

/*Enable Bandgap */
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0X30;            /* clock divider */
    ADCCON2|=0X0E;            /* AQT time */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(!(ADCCON0&SET_BIT7));;
    ADCdataVBG = ADCRH<<4;
    ADCdataVBG |= ADCRL&0x0F;
    DISABLE_ADC;
    printf("\n ADC channel bandgap =0x%x", ADCdataVBG);
    Timer0_Delay(24000000,200,1000);

/*Enable channel 5 */ 
    ENABLE_ADC_AIN5;
    ADCCON1|=0X30;            /* clock divider */
    ADCCON2|=0X0E;            /* AQT time */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(!(ADCCON0&SET_BIT7)); /* wait ADCF */
    ADCdataAIN5 = ADCRH<<4;
    ADCdataAIN5 |= ADCRL&0x0F;
    DISABLE_ADC;
    printf("\n ADC channel 5 =0x%x", ADCdataAIN5);
    Timer0_Delay(24000000,200,1000);

    while(1);
      
    while(1);  
}