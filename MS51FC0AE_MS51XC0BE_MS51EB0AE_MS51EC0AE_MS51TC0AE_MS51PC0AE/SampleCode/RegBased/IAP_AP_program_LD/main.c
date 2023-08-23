/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP program LDROM demo code
//***********************************************************************************************************
#include "ms51_32k.h"

void main (void) 
{
    unsigned char i;

  /* IAP data buffer size is 128 since each page of MS51 is 128 byte*/
    for(i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }

    /* Only when P3.5 to low to program LDROM process*/
    P35_QUASI_MODE;
    while (P35);
    
/*Modify CONFIG to Enable LDROM, LDROM size is 2k*/
    Modify_CONFIG(0xEF,0xFD,0xFF,0xFF,0xFF);
    
    Erase_LDROM(0,128);
    Erase_Verify_LDROM(0,128);
    Program_LDROM(0,128);
    Program_Verify_LDROM(0,128);

    while(1);

}

