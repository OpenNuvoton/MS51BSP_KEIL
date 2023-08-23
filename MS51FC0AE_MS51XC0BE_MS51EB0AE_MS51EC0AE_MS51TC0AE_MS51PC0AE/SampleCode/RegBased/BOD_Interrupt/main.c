/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 BOD interrupt demo code
//***********************************************************************************************************
#include "ms51_32k.h"

bit bodflag=0;
void BOD_ISR (void) interrupt 8           // Vector @  0x43
{
    clr_CHPCON_IAPEN; 
    clr_BODCON0_BOF;
    bodflag=0;
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



