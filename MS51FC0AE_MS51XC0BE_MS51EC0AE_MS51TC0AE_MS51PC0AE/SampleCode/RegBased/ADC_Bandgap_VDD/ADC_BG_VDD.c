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

//**********************************************************************************************************/
//  File Function: MS51 ADC read bandgap to VDD demo code                                                  */
//**********************************************************************************************************/

#include "MS51_32K.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
double  Bandgap_Voltage,VDD_Voltage,Bandgap_Value;      //please always use "double" mode for this
unsigned  char xdata ADCdataH, ADCdataL;
int ADCsumH=0, ADCsumL=0;
unsigned char ADCavgH,ADCavgL;


/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    double bgvalue;

/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;

/*Read bandgap value */
//    READ1_BANDGAP();
/* ADC Low speed initial*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
    AUXR1|=SET_BIT4;          /* ADC clock low speed */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;                                
    while(ADCF == 0);
    ADCdataH = ADCRH;
    ADCdataL = ADCRL;
/* to convert VDD value */
    bgvalue = (ADCRH<<4) + ADCRL;

    Bandgap_Voltage= READ_BANDGAP()*3/4;
    VDD_Voltage = (0x1000/bgvalue)*Bandgap_Voltage;


/*printf result value */
    printf ("\n BG Voltage = %e", Bandgap_Voltage); 
    printf ("\n VDD voltage = %e", VDD_Voltage);

    while(1);

}


