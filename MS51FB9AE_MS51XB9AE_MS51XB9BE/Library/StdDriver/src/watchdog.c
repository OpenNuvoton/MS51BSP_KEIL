/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************
#include "MS51_16K.H"

void Enable_WDT_Reset_Config(void)
{
    set_CHPCON_IAPEN;
    IAPAL = 0x04;
    IAPAH = 0x00;
    IAPFD = 0x0F;
    IAPCN = BYTE_PROGRAM_CONFIG;
    set_IAPUEN_CFUEN;
    set_IAPTRG_IAPGO;                                  //trigger IAP
    while((CHPCON&SET_BIT6)==SET_BIT6);          //check IAPFF (CHPCON.6)
    clr_IAPUEN_CFUEN;
    clr_CHPCON_IAPEN;
    set_CHPCON_SWRST;
}

/****************************************************************************/
/* WDT CONFIG disable                                                       */
/* warning : this macro is for CONFIG already enable WDT Reset to disable.  */
/* Since erase CONFIG is full page                                          */
/* step 1. storage CONFIG value in RAM                                      */
/* step 2. modify RAM CONFIG4 WDT value to disable                          */
/* step 3. erase CONFIG page                                                */
/* step 4. re writer CONFIG.                                                */
/* **************************************************************************/
void Disable_WDT_Reset_Config(void)
{
  UINT8 cf0,cf1,cf2,cf3,cf4;
  
    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = BYTE_READ_CONFIG;
    set_IAPTRG_IAPGO;                                  //Storage CONFIG0 data
    cf0 = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;                                  //Storage CONFIG1 data
    cf1 = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;                                  //Storage CONFIG2 data
    cf2 = IAPFD;
    IAPAL = 0x03;
    set_IAPTRG_IAPGO;                                  //Storage CONFIG3 data
    cf3 = IAPFD;
    IAPAL = 0x04;
    set_IAPTRG_IAPGO;                                  //Storage CONFIG4 data
    cf4 = IAPFD;
    cf4 |= 0xF0;                                      //Moidfy Storage CONFIG4 data disable WDT reset
    
    set_IAPUEN_CFUEN;  
    IAPCN = PAGE_ERASE_CONFIG;                        //Erase CONFIG all
    IAPAH = 0x00;
    IAPAL = 0x00;
    IAPFD = 0xFF;
    set_IAPTRG_IAPGO;
    
    IAPCN = BYTE_PROGRAM_CONFIG;                    //Write CONFIG
    IAPFD = cf0;
    set_IAPTRG_IAPGO;
    IAPAL = 0x01;
    IAPFD = cf1;
    set_IAPTRG_IAPGO;
    IAPAL = 0x02;
    IAPFD = cf2;
    set_IAPTRG_IAPGO;
    IAPAL = 0x03;
    IAPFD = cf3;
    set_IAPTRG_IAPGO;
    IAPAL = 0x04;
    IAPFD = cf4;
    set_IAPTRG_IAPGO;

    set_IAPUEN_CFUEN;
    clr_CHPCON_IAPEN;
    if (WDCON&SET_BIT3)
    {
      clr_WDCON_WDTRF;
      set_CHPCON_SWRST;
    }
}
