/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2020                                                                                   */
/***********************************************************************************************************/

//***********************************************************************************************************/
/*  File Function: MS51 ADC / Bandgap input demo code                                                       */
/************************************************************************************************************/
#include "MS51_16K.H"
 
/*****************************************************************************************************************
 ONLY Write CONFIG to enable WDT Reset Function:
******************************************************************************************************************/


void Enable_WDT_Reset_Config(void)
{
    set_CHPCON_IAPEN;                                  // Enable IAP function
    IAPCN = BYTE_PROGRAM_CONFIG;
    set_IAPUEN_CFUEN;                                  // Enable CONFIG writer bit
    IAPAL = 0x04;
    IAPAH = 0x00;
    IAPFD = 0x0F;
    set_IAPTRG_IAPGO;                                  //trigger IAP
    clr_IAPUEN_CFUEN;
    clr_CHPCON_IAPEN;
}

/*-----------------------------------------------------------------------------------------------*/
void main (void) 
{

  ALL_GPIO_QUASI_MODE;
/* If first time after reset, To modify P2.0 as GPIO input, not reset pin */
  if ((PCON&SET_BIT4)==SET_BIT4)        
      Modify_CONFIG(0xEB,0xFF,0xFF,0xFF,0xFF);

/*only P2.0 to low , enable WDT reset */
  while(P12);
  if ((PCON&SET_BIT4)==SET_BIT4)        
  {
      Enable_WDT_Reset_Config();
      PCON&=CLR_BIT4;    /*clr POF */
  }
  while(1);
}


