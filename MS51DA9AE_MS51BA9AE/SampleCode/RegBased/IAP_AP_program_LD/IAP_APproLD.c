/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/

//***********************************************************************************************************
//  File Function: MS51 IAP program LDROM demo code
//***********************************************************************************************************
#include "MS51_8K.H"



void main (void) 
{

    unsigned char i;
    P17_QUASI_MODE;
    P17=1;
  
/*Modify CONFIG Enable LDROM, LDROM size is 2k*/
      Modify_CONFIG(0xEF,0xFD,0xFF,0xFF,0xFF);

/* IAP data buffer size is 128 since each page of MS51 is 128 byte*/
    for(i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
		
		
/* Only when P1.7 to low to program LDROM process*/
    while (P17);
    Erase_LDROM(0,128);
    Erase_Verify_LDROM(0,128);
    Program_LDROM(0,128);
    Program_Verify_LDROM(0,128);

    while(1);

}

