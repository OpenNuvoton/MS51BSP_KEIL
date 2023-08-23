/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main(void)
{
  P11_PUSHPULL_MODE;
  P12_PUSHPULL_MODE;
  set_CKCON_CLOEN;
/* clock out about  100khz base on HIRC div 160 */
  CKDIV = 0X50;
  while (P20)
  {
    MODIFY_HIRC(HIRC_16);
    P12 = 1;
    Timer0_Delay(16000000,5,1000);;
    P12 = 0;
    Timer0_Delay(16000000,5,1000);
  }
/* HIRC modify to 24MHz  */
  MODIFY_HIRC(HIRC_24);
  while(1);
  
}