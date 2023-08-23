/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Following define by customer                                                                            */
/* Please confirm the start addresss not overlap the applictaion area                                      */
/*---------------------------------------------------------------------------------------------------------*/
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
