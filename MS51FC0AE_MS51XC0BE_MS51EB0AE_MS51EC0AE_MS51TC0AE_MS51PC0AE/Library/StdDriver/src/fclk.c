/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ms51_32k.h"
unsigned char data  TA_REG_TMP,BYTE_TMP,SFRS_TMP;


  /**
  * @brief This API configures ADC module to be ready for convert the input from selected channel
  * @param[in] u8OpMode Decides the ADC operation mode. Valid values are:
  *                       - \ref ADC_SINGLE               :Single mode.
  *                       - \ref ADC_CONTINUOUS           :Continuous scan mode.
  * @param[in] u8ChMask Channel enable bit. Each bit corresponds to a input channel. 0 is channel 0, 1 is channel 1..., 7 is channel 7.
  *              VBG means band-gap voltage, VTEMP means temperature sensor, VLDO means LDO voltage.
  * @return  None
  * @note ML51 series MCU ADC can only convert 1 channel at a time. If more than 1 channels are enabled, only channel
  *       with smallest number will be convert.
  * @note This API does not turn on ADC power nor does trigger ADC conversion
  * @exmaple :  ADC_Open(ADC_SINGLE,0);
  */
void FsysSelect(unsigned char u8FsysMode)
{
  switch (u8FsysMode)
  {
    //***** HXT enable part*****
    case FSYS_HXT:
        ClockEnable(FSYS_HIRC);                 //step1: switching system clock to HIRC
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_HXT);                  //step2: switching system clock to HXT
        ClockSwitch(FSYS_HXT);
        clr_CKEN_HIRCEN;                      //step4: disable HIRC if needed 
    break;    
        
        //***** HIRC enable part *****  
    case FSYS_HIRC:
        ClockEnable(FSYS_HIRC);                 //step1: switching system clock HIRC
        ClockSwitch(FSYS_HIRC);
    break;
    
    //***** LIRC enable part*****
    case FSYS_LIRC:
        ClockEnable(FSYS_LIRC);                 //step2: switching system clock LIRC
        ClockSwitch(FSYS_LIRC);
        clr_CKEN_HIRCEN;                        //step4: disable HIRC if needed 
    break;
        
    /***** ECLK enable part clock in with P3.0 *****/      
    case FSYS_ECLK_P30:
        ClockEnable(FSYS_HIRC);                 //step1: switching system clock to HIRC
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_ECLK_P30);                 //step1: switching system clock to External clock
        ClockSwitch(FSYS_ECLK_P30);
        clr_CKEN_HIRCEN;                        //step5: disable HIRC if needed 
    break;
    
    /***** ECLK enable part clock in with P0.0 *****/ 
    case FSYS_ECLK_P00:
        ClockEnable(FSYS_HIRC);                 //step1: switching system clock to HIRC
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_ECLK_P00);                 //step1: switching system clock to External clock
        ClockSwitch(FSYS_ECLK_P00);
        clr_CKEN_HIRCEN;                        //step5: disable HIRC if needed 
    break;
  }
}

void ClockEnable(unsigned char u8FsysMode)
{
  switch (u8FsysMode)
  {
    /***** HIRC enable part ******/
    case FSYS_HXT:
        clr_CKEN_EXTEN1;                        /*step1: Enable extnal 4~ 24MHz crystal clock source.*/
        set_CKEN_EXTEN0;
        while(CKSWT&SET_BIT7);                  /*step2: check clock source status and wait for ready*/
    break;
   
    /***** HIRC enable part ******/
    case FSYS_HIRC:
        set_CKEN_HIRCEN;                        //step1: Enable extnal clock source.
        while(!(CKSWT&SET_BIT5);      //step2: check clock source status and wait for ready
    break;
   
    /***** LIRC enable part******/
    case FSYS_LIRC:
        set_CKEN_LIRCEN;                        //step1: Enable extnal clock source.
        while(!(CKSWT&SET_BIT4);      //step2: check clock source status and wait for ready
    break;
    
    /***** ECLK P30 enable part ******/
    case FSYS_ECLK_P30:
        set_CKEN_EXTEN1;                        //step1: Enable extnal clock source.
        set_CKEN_EXTEN0;
        while(!(CKSWT&SET_BIT3);      //step2: check clock source status and wait for ready
    break;
    
    /***** ECLK P00 enable part ******/
    case FSYS_ECLK_P00:
        set_CKEN_EXTEN1;                        //step1: Enable extnal clock source.
        clr_CKEN_EXTEN0;
        while(!(CKSWT&SET_BIT6);      //step2: check clock source status and wait for ready
    break;
  }
}

void ClockDisable(unsigned char u8FsysMode)
{
  bit closeflag=0;
  switch (u8FsysMode)
  {
    /***** HXT Disable part ******/
    case FSYS_HXT:
      closeflag = 1;                
    break;
     /***** HIRC Disable part ******/
    case FSYS_HIRC:
        clr_CKEN_HIRCEN;                        
    break;
    /***** LIRC Disable part******/
    case FSYS_LIRC:
        clr_CKEN_LIRCEN;                        
    break;
    //***** ECLK from P3.0 Disable part ******/
    case FSYS_ECLK_P30:
        closeflag = 1; 
    break;
    //***** ECLK from P0.0 Disable part ******/
    case FSYS_ECLK_P00:
        closeflag = 1; 
    break;
  }
  if (closeflag)
  {
    SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0x3F;EA=BIT_TMP;
    closeflag = 0;
  }
  
}

void ClockSwitch(unsigned char u8FsysMode)
{
  bit exflag=0;
  BIT_TMP=EA;EA=0;
  switch (u8FsysMode)
  {
    /***** HXT Disable part*****/
    case FSYS_HXT:
        exflag = 1;
    break;    
    /***** HIRC Disable part ******/
    case FSYS_HIRC:
        clr_CKSWT_OSC1;
        clr_CKSWT_OSC0;
    break;
    /***** LIRC Disable part******/
    case FSYS_LIRC:
        set_CKSWT_OSC1;
        clr_CKSWT_OSC0;
    break;
    /***** ECLK P30 Disable part ******/
    case FSYS_ECLK_P30:
        exflag = 1;
    break;
    /***** ECLK P00 Disable part ******/
    case FSYS_ECLK_P00:
        exflag = 1;
    break;
  }
  if (exflag)
  {
        clr_CKSWT_OSC1;
        set_CKSWT_OSC0;
  }
  EA = BIT_TMP;
}


