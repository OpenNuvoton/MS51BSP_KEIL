/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_32k.h"

  /**
  * @brief This API configures modify system HIRC value
  * @param[in] u8FsysMode . Valid values are:
  *                       - \ref HIRC_24                 :Internal HIRC 24MHz .
  *                       - \ref HIRC_16                 :Internal HIRC 16MHz.
  *                       - \ref HIRC_166                :Internal HIRC 16.6MHz.
  * @note      None.
  * @exmaple : MODIFY_HIRC(HIRC_24);
  */
void MODIFY_HIRC(unsigned char u8HIRCSEL)
{
    unsigned char data hircmap0,hircmap1,offset,judge;
    unsigned int trimvalue16bit;
    /* Check if power on reset, modify HIRC */
    SFRS = 0 ;
    switch (u8HIRCSEL)
    {
      case HIRC_24:
        IAPAL = 0x38;
      break;
      case HIRC_16:
        IAPAL = 0x30;
      break;
      case HIRC_166:
        IAPAL = 0x30;
      break;
    }
    set_CHPCON_IAPEN;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPTRG_IAPGO;
    hircmap0 = IAPFD;
    IAPAL++;
    set_IAPTRG_IAPGO;
    hircmap1 = IAPFD;

    switch (u8HIRCSEL)
    {
      case HIRC_166:
        trimvalue16bit = ((hircmap0 << 1) + (hircmap1 & 0x01));
        judge = trimvalue16bit&0xC0;
        offset = trimvalue16bit&0x3F;
        trimvalue16bit -= 14;

        IAPCN = READ_DID;
        IAPAL = 1;
        IAPAH = 0;
        set_IAPTRG_IAPGO;
        if ((IAPFD==0x4B)||(IAPFD==0x52)||(IAPFD==0x53))    /* MS51 process */
        {
          if (offset<15)
          {
              if ((judge==0x40)||(judge==0x80)||(judge==0xC0))
              trimvalue16bit -= 14;
          }
          else 
            trimvalue16bit -= 4;
        }
        hircmap0 = trimvalue16bit >> 1;

      break;
      default: break;
    }

    TA = 0xAA;
    TA = 0x55;
    RCTRIM0 = hircmap0;
    TA = 0xAA;
    TA = 0x55;
    RCTRIM1 = hircmap1;
    clr_CHPCON_IAPEN;
    PCON &= CLR_BIT4;
}


  /**
  * @brief This API configures system clock source
  * @param[in] u8FsysMode . Valid values are:
  *                       - \ref FSYS_HXT                 :External crsytal input.
  *                       - \ref FSYS_HIRC                :Internal HIRC (16MHz as default).
  *                       - \ref FSYS_LIRC                :Internal LIRC.
  *                       - \ref FSYS_OSCIN_P30            :External clock input from P3.0.
  *                       - \ref FSYS_HXTIN_P00            :External clock input from P0.0.
  * @note      None.
  * @exmaple : FsysSelect(FSYS_HXT);
  */
void FsysSelect(unsigned char u8FsysMode)
{
  switch (u8FsysMode)
  {
    //***** HXT enable part*****
    case FSYS_HXT:
        ClockEnable(FSYS_HIRC);                      /*step1: switching system clock to HIRC */
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_HXT);                       /*step2: switching system clock to HXT  */
        ClockSwitch(FSYS_HXT);
        clr_CKEN_HIRCEN;                             /*step4: disable HIRC if needed  */
    break;    
        
        //***** HIRC enable part *****  
    case FSYS_HIRC:
        ClockEnable(FSYS_HIRC);                      /*step1: switching system clock HIRC */
        ClockSwitch(FSYS_HIRC);
    break;
    
    //***** LIRC enable part*****
    case FSYS_LIRC:
        ClockEnable(FSYS_LIRC);                      /*step2: switching system clock LIRC  */
        ClockSwitch(FSYS_LIRC);
        clr_CKEN_HIRCEN;                             /*step4: disable HIRC if needed  */
    break;
        
    /***** ECLK enable part clock in with P3.0 *****/      
    case FSYS_OSCIN_P30:
        ClockEnable(FSYS_HIRC);                      /*step1: switching system clock to HIRC  */
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_OSCIN_P30);                 /*step1: switching system clock to External clock  */
        ClockSwitch(FSYS_OSCIN_P30);
        clr_CKEN_HIRCEN;                             /*step5: disable HIRC if needed */
    break;
    
    /***** ECLK enable part clock in with P0.0 *****/ 
    case FSYS_HXTIN_P00:
        ClockEnable(FSYS_HIRC);                      /*step1: switching system clock to HIRC */
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_HXTIN_P00);                 /*step1: switching system clock to External clock */
        ClockSwitch(FSYS_HXTIN_P00);
        clr_CKEN_HIRCEN;                             /*step5: disable HIRC if needed */
    break;
  }
}

void ClockEnable(unsigned char u8FsysMode)
{
  switch (u8FsysMode)
  {
    /***** HIRC enable part ******/
    case FSYS_HXT:
        clr_CKEN_EXTEN1;                          /*step1: Enable extnal 4~ 24MHz crystal clock source.*/
        set_CKEN_EXTEN0;
        while(!(CKSWT&SET_BIT7));                 /*step2: check clock source status and wait for ready*/
    break;
   
    /***** HIRC enable part ******/
    case FSYS_HIRC:
        set_CKEN_HIRCEN;                          /*step1: Enable extnal clock source.                  */
        while(!(CKSWT&SET_BIT5));                 /*step2: check clock source status and wait for ready */
    break;
   
    /***** LIRC enable part******/
    case FSYS_LIRC:
        set_CKEN_LIRCEN;                         /*step1: Enable extnal clock source.                   */
        while(!(CKSWT&SET_BIT4));                /*step2: check clock source status and wait for ready */
    break;
    
    /***** ECLK P30 enable part ******/
    case FSYS_OSCIN_P30:
        set_CKEN_EXTEN1;                        /*step1: Enable extnal clock source. */
        set_CKEN_EXTEN0;
        while(!(CKSWT&SET_BIT3));               /*step2: check clock source status and wait for ready  */
    break;
    
    /***** HXT P00 enable part ******/
    case FSYS_HXTIN_P00:
        set_CKEN_EXTEN1;                        /*step1: Enable extnal clock source. */
        clr_CKEN_EXTEN0;
        while(!(CKSWT&SET_BIT7));               /*step2: check clock source status and wait for ready */
    break;
  }
}

void ClockDisable(unsigned char u8FsysMode)
{
  bit closeflag=0;

  SFRS = 0;
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
    case FSYS_OSCIN_P30:
        closeflag = 1; 
    break;
    //***** ECLK from P0.0 Disable part ******/
    case FSYS_HXTIN_P00:
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
  SFRS = 0 ;
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
    case FSYS_OSCIN_P30:
        exflag = 1;
    break;
    /***** ECLK P00 Disable part ******/
    case FSYS_HXTIN_P00:
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

