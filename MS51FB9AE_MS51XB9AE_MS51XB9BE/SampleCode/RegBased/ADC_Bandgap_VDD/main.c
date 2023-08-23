/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"

double  Bandgap_Voltage,VDD_Voltage;      //please always use "double" mode for this

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void) 
{
    uint16_t ADC_BG_Result;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

/* ADC sampling timing setting for Bandgap*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(ADCF == 0);
/* ADC convert current Bandgap value */
    ADC_BG_Result = ADCRH<<4 ;
    ADC_BG_Result = ADC_BG_Result|(ADCRL&0x0F);
    DISABLE_ADC;              /*Disable ADCEN each time after ADC trig */

/*                  VDD  Now                         READ_BANDGAP() VALUE              */
/*    ------------------------------------- = ----------------------------------       */
/*    3072mV(Storage value test condition)      NOW ADC Bandgap convert reuslt         */
      VDD_Voltage = ((float)READ_BANDGAP()/(float)ADC_BG_Result)*3.072;

/*            Bandgap real voltage                    READ_BANDGAP() VALUE             */
/*    ------------------------------------- = ----------------------------------       */
/*    3072mV(Storage value test condition)              4096(12bit ADC)                */
      Bandgap_Voltage = ((float)READ_BANDGAP()*3/4/1000);

/*printf result value */
    printf ("\n BG Voltage = %e", Bandgap_Voltage); 
    printf ("\n VDD voltage = %e", VDD_Voltage);

    while(1);

}
