/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 BOD interrupt demo code
//***********************************************************************************************************
#include "MS51_16K.H"

bit bodflag=0;
void BOD_ISR (void) interrupt 8           // Vector @  0x43
{
    _push_(SFRS);
 
    clr_BODCON0_BOF;
    bodflag=1;

    _pop_(SFRS);
}

//----------------------------------------------------------------------------------------------//
void main (void)
{
/* As defaut all multi function define as GPIO */ 
  ALL_GPIO_QUASI_MODE;

  BOD_Open(Enable, VBOD_2_7, BOD_Reset_Disable);
  BOD_LowPower(LPBOD_Mode_3);
  BOD_Interrupt(Enable);
  ENABLE_GLOBAL_INTERRUPT;
  while(1)
  {
     P1=~P1;
     _delay_();
     if (bodflag)
     {
       while (1)
         P1=~P1;
     }
  }
}



