/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/*  Website: http://www.nuvoton.com                                                                        */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/

/**********************************************************************************************************/
/*  File Function: MS51 ADC multi channel input demo code                                                 */
/**********************************************************************************************************/
#include "MS51_32K.h"

unsigned int xdata temp;

/*****************************************************************************/
/*The main C function.  Program execution starts                             */
/*here after stack initialization.                                           */
/*****************************************************************************/
void main (void) 
{

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;

    while(1)
    {  
/*Enable channel 4 */ 
        ENABLE_ADC_CH4; 
        ADC_ConvertTime(ADC_CH4,2,7);
        clr_ADCCON0_ADCF;
        set_ADCCON0_ADCS;                  // ADC start trig signal
        while(ADCF == 0);
        temp=(ADCRH<<4)+(ADCRL&0x0F);
        printf ("\n ADC CH4 = 0x%02X", temp);
        Timer2_Delay(24000000,128,300,1000);
/*Enable channel 10 */ 
        ENABLE_ADC_CH10;           
        ADC_ConvertTime(ADC_CH10,4,7);
        clr_ADCCON0_ADCF;
        set_ADCCON0_ADCS;                  // ADC start trig signal
        while(ADCF == 0);
        temp=(ADCRH<<4)+(ADCRL&0x0F);
        printf ("\n ADC CH10 = 0x%02X", temp);
        Timer2_Delay(24000000,128,300,1000);
    }

}