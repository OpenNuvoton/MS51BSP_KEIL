/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP erase / program / read verify demo code
//***********************************************************************************************************
#include "ms51_32k.h"

//---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------
#define     DATA_SIZE           4096
#define     DATA_START_ADDR     0x3800


void main (void) 
{
    unsigned char i;
    for(i=0;i<128;i++)
    {
       IAPDataBuf[i] = i;
    }

    P35_QUASI_MODE;
    while (P35);
  
    Erase_APROM(0x4700,1024);
    Erase_Verify_APROM(0x4700,1024);
    Program_APROM(0x4700,128);
    Program_Verify_APROM(0x4700,128);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
