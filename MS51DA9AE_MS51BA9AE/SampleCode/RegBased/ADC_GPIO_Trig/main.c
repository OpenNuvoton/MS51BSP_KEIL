/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ADC trig by GPIO demo
//***********************************************************************************************************
#include "ms51_8k.h"

/* For printf code only. Disable this #include "ms51_8k.h" to reduce code size. */
//#define  print_function 

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) interrupt 11
{
    _push_(SFRS);
  
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    
#ifdef print_function
    printf ("\n Value = 0x%bx",ADCRH);
#endif
    _pop_(SFRS);
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    ALL_GPIO_QUASI_MODE;

/* UART0 settting for printf function */
/* Only for printf function enabled */
//    MODIFY_HIRC(HIRC_24);
//    P06_PUSHPULL_MODE;
//    UART_Open(24000000,UART0_Timer1,115200);
//    ENABLE_UART0_PRINTF;

/*---------------------------------------------------------------*/
/* ADC port trig initial setting toggle P0.4 to start ADC        */
/*---------------------------------------------------------------*/
    ENABLE_ADC_CH0;                              // Enable AIN0 P1.7 as ADC pin
    P04_INPUT_MODE;
    P04_FALLINGEDGE_TRIG_ADC;                      // P0.4 falling edge as adc start trig signal
/* Enable ADC interrupt */
    set_IE_EADC;                                  // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
/* Trig P04 falling edge to start adc, no need set ADCS bit*/
    while(1);                                      // Wait ADC interrupt


}


