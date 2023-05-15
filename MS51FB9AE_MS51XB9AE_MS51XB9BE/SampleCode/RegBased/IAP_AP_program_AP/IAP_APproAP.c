/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP erase / program / read verify demo code
//***********************************************************************************************************
#include "MS51_16K.H"

//---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------
#define     DATA_SIZE           128
#define     DATA_START_ADDR     0x3800 


//-----------------------------------------------------------------------------------------------------------
void main (void) 
{
    unsigned char i;

    P12_INPUT_MODE;

    for(i=0;i<128;i++)
       IAPDataBuf[i] =  i;
       
    while(P12);
    Erase_APROM(DATA_START_ADDR,128);
    Erase_Verify_APROM(DATA_START_ADDR,128);
    Program_APROM(DATA_START_ADDR,128);
    Program_Verify_APROM(DATA_START_ADDR,128);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
