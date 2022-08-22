/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/



//***********************************************************************************************************
//  File Function: MS51 LDROM program APROM demo code
//***********************************************************************************************************
#include "MS51_16K.H"

//***********************************************************************************************************
//  Before using this demo code, please remind below CONFOGs setting, thanks.
//                 CONFIG0.7 --> CBS=0
//                 CONFIG1 = 0xFC, because this demo code size is 2495 Byte

/*-----------------------------------------------------------------------------------------------------------*/
void main (void) 
{
    unsigned char i;
    P12_INPUT_MODE;
    for(i=0;i<128;i++)
      IAPDataBuf[i]=i;

    while (P12);
    Erase_APROM(0x80,128);
    Erase_Verify_APROM(0x80,128);
    Program_APROM(0x80,128);
    Program_Verify_APROM(0x80,128);

    while(1);
}

