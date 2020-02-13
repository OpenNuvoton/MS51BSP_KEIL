/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                  */
/***********************************************************************************************************/

/***********************************************************************************************************/
/*  File Function: MS51 IAP erase / program / read verify demo code                                        */
/***********************************************************************************************************/
#include "MS51_8K.H"

/***********************************************************************************************************/
/*  Step 1 Enable CONFIG to boot from LDROM , LDROM siez 2K                                                */
/*  Step 2 Define APROM buffer data loop from 0 to 0x7F                                                    */
/*  Step 3 erase / erase blank check / program / read verify APROM process                                 */
/***********************************************************************************************************/
void main (void) 
{
    unsigned char i;
  
/*Modify boot from LDROM and LDROM size 2k */
    if (PCON|CLR_BIT4)
    {
      Modify_CONFIG(0x6F,0xFD,0xFF,0xFF,0xFF);
    }
    
    for (i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
/*if P1.7 trig to low start Write APROM */ 
/*Check with Nulink ICP please always keep P1.7 to high */
    while(P17);
    Erase_APROM(0,128);
    Erase_Verify_APROM(0,128);
    Program_APROM(0,128);
    Program_Verify_APROM(0,128);

    while(1);
}