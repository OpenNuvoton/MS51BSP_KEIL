/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Wakeup timer demo code with interrupt                                               */
/************************************************************************************************************/

#include "MS51_32K.h"

bit  wktflag = 0;

void WakeUp_Timer_ISR (void)   interrupt 17     //ISR for self wake-up timer
{
    _push_(SFRS);

    wktflag = 1;
    clr_WKCON_WKTF;                                   //clear interrupt flag

    _pop_(SFRS);
}


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{

    P35_PUSHPULL_MODE;
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
//-----------------------------------------------------
//  WKT initial   
//-----------------------------------------------------  
    SFRS = 0;
    WKCON = 0x02;                     //timer base 10k, Pre-scale = 1/16
    SFRS = 2;
    RWKH = 0xFC;
    SFRS = 0;
    RWKL = 0X00;                      //  if prescale is 0x00, never set RWK = 0xff
    ENABLE_WKT_INTERRUPT;                          // enable WKT interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_WKCON_WKTR;                         // Wake-up timer run 

    while(1)
    {
      if (wktflag)
      {
            clr_WKCON_WKTR;
            SFRS=0; printf ("\n WKT interrupt!");
            set_WKCON_WKTR;
      }
      P35 = ~P35 ;
      Timer0_Delay(16000000,200,1000);
    }
}

