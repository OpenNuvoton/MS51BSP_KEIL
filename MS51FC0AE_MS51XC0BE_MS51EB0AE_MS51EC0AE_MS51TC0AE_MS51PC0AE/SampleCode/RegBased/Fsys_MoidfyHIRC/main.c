/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 modify HIRC demo
//***********************************************************************************************************
#include "ms51_32k.h"

void main(void)
{
  P35_PUSHPULL_MODE;
  P11_PUSHPULL_MODE;
  P30_INPUT_MODE;
  set_CKCON_CLOEN;
/* clock out about  100khz base on HIRC div 160 */
  CKDIV = 50;
  while (1)
  {
    if (P30)
    {
      MODIFY_HIRC(HIRC_16);
      while(1)
      {
        P35 = 1;
        Timer0_Delay(1600000,200,1000);
        P35 = 0;
        Timer0_Delay(1600000,200,1000);
      }
    }
/* HIRC modify to 24 , clock out 150 khz */
    else 
    {
      MODIFY_HIRC(HIRC_24);
      while(1)
      {
        P35 = 1;
        Timer0_Delay(2400000,200,1000);
        P35 = 0;
        Timer0_Delay(2400000,200,1000);
      }
    }
  }
  
}