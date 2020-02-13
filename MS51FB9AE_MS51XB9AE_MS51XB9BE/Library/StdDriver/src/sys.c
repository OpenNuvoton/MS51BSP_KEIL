/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2020
//***********************************************************************************************************
#include "MS51_16K.H"

bit BIT_TMP;
unsigned char data  TA_REG_TMP,BYTE_TMP,SFRS_TMP;

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
    unsigned char data hircmap0,hircmap1;
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
    clr_CHPCON_IAPEN;
    switch (u8HIRCSEL)
    {
      case HIRC_166:
        trimvalue16bit = ((hircmap0 << 1) + (hircmap1 & 0x01));
        trimvalue16bit = trimvalue16bit - 15;
        hircmap1 = trimvalue16bit & 0x01;
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
  *                       - \ref FSYS_HIRC                :Internal HIRC (16MHz as default).
  *                       - \ref FSYS_LIRC                :Internal LIRC.
  *                       - \ref FSYS_OSCIN_P00           :External clock input from P0.0.
  * @note      None.
  * @exmaple : FsysSelect(FSYS_LIRC);
  */
void FsysSelect(unsigned char u8FsysMode)
{
  switch (u8FsysMode)
  {
        //***** HIRC enable part *****  
    case FSYS_HIRC:
        ClockEnable(FSYS_HIRC);                 //Enable HIRC
        ClockSwitch(FSYS_HIRC);                 //Switching system clock HIRC
    break;
    
    //***** LIRC enable part*****
    case FSYS_LIRC:
        ClockSwitch(FSYS_LIRC);                 // LIRC always on switch system to LIRC
        clr_CKEN_HIRCEN;                        // Disable HIRC if needed 
    break;
    
    /***** ECLK enable part clock in with P3.0 *****/ 
    case FSYS_OSCIN_P30:
        ClockEnable(FSYS_HIRC);                 //Enable and system clock to HIRC
        ClockSwitch(FSYS_HIRC);
        ClockEnable(FSYS_OSCIN_P30);            //Enable External clock source
        ClockSwitch(FSYS_OSCIN_P30);            //Switching system clock to OSCIN 
        clr_CKEN_HIRCEN;                        //step5: disable HIRC if needed 
    break;
  }
}

void ClockEnable(unsigned char u8FsysMode)
{
  switch (u8FsysMode)
  {
    /***** HIRC enable part ******/
    case FSYS_HIRC:
        set_CKEN_HIRCEN;                        //step1: Enable extnal clock source.
        while((CKSWT|CLR_BIT5)==CLR_BIT5);      //step2: check clock source status and wait for ready
    break;
    /***** ECLK P30 enable part ******/
    case FSYS_OSCIN_P30:
        TA=0xAA;TA=0x55;CKEN|=0xC0;                        //step1: Enable extnal clock source.
        while((CKSWT|CLR_BIT3)==CLR_BIT3);      //step2: check clock source status and wait for ready
    break;
  }
}

void ClockDisable(unsigned char u8FsysMode)
{
  SFRS = 0;
  switch (u8FsysMode)
  {
     /***** HIRC Disable part ******/
    case FSYS_HIRC:
        clr_CKEN_HIRCEN;                        
    break;
    //***** ECLK from P3.0 Disable part ******/
    case FSYS_OSCIN_P30:
       TA=0xAA;TA=0x55;CKEN&=0x3F;
    break;
  }
}

void ClockSwitch(unsigned char u8FsysMode)
{
  SFRS = 0 ;
  BIT_TMP=EA;EA=0;
  switch (u8FsysMode)
  {
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
        set_CKSWT_ECLKST;
    break;
  }
  EA = BIT_TMP;
}

