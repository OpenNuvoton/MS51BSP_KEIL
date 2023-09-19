/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_32k.h"

 /**
  * @brief This configures ADC module to be ready for convert the input from selected channel
  * @param[in] u16ADCRBase Decides the ADC RAM Base Address High byte + Low byte total
  * @param[in] u8ADCRLength Decides the ADC continui The total sampling numbers for ADC continue sampling select. 
  * @param[in] u8ADCSpeed is the ADCSR.7 Setting for select ADC low speed. 
  * @return  None
  * @note ML51 series MCU ADC can only convert 1 channel at a time. If more than 1 channels are enabled, only channel
  *       with smallest number will be convert.
  * @example ADC_InitialContinous(0x0300,128);
  */
void ADC_InitialContinous(unsigned int u16ADCRBase, unsigned char u8ADCRLength)
{
  SFRS=2;
  ADCBAL=u16ADCRBase;
  ADCBAH = u16ADCRBase>>8;
  ADCSN  = u8ADCRLength - 1;   //Offset value, since the actually sampling number= ADCSN[7:0] + 1
	SFRS = 0;
}


 /**
  * @brief This configures ADC Sampling time 
  * @param[in] u8ADCDIV Decides the ADC clock devider value. Value from 0 ~ 7, devider is from 1 ~ 128, default value is 0 means Fadc = Fsys/1 
  * @param[in] u8ADCAQT Decides the ADC acquisition time base to add sampling time for ADC input, value is from 0 ~ 7, time = (4*u8ADCAQT+10)/Fadc, default value is 10/Fsys = 417ns.
  * @return  None
  * @note 
  * @example ADC_ConvertTime(ADC_CH10,2,7);
  */
void ADC_ConvertTime(unsigned char u8AINCHNSEL, unsigned char u8ADCDIV, unsigned char u8ADCAQT)
{
  SFRS=0;
  ADCCON1 &= 0xCF;
  ADCCON1 |= (u8ADCDIV&0x07)<<4;
  switch (u8AINCHNSEL)
  {
      case ADC_CH0:
      case ADC_CH1:
      case ADC_CH2:
      case ADC_CH3:
      case ADC_CH4:
      case ADC_CH5:
      case ADC_CH6:
      case ADC_CH7:
      case ADC_BANDGAP:
           ADCCON2&=0xF1;
           ADCCON2|=(u8ADCAQT&0x07)<<1;
           break;
      
      case ADC_CH9:
      case ADC_CH10:
      case ADC_CH11:
      case ADC_CH12:
      case ADC_CH13:
      case ADC_CH14:
      case ADC_CH15:
           SFRS = 2;
           ADCCON3&=0xF1;
           ADCCON3|=(u8ADCAQT&0x07)<<1;
           break;
   }
}

/**
  * @brief Read the bandgap value base on Vref = 3.072V storage address after UID area.
  * @param[in] none
  * @return 12bit bandgap value
  * @example temp = READ_BANDGAP();
  */
unsigned int READ_BANDGAP()
{
    unsigned char BandgapHigh,BandgapLow;
    unsigned int u16bgvalue;
    set_CHPCON_IAPEN;
    IAPCN = READ_UID;
    IAPAL = 0x0d;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    BandgapLow = IAPFD&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    BandgapHigh = IAPFD;
    u16bgvalue = (BandgapHigh<<4)+BandgapLow;
    clr_CHPCON_IAPEN;
    return (u16bgvalue);
}

