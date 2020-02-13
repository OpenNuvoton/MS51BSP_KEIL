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

/************************************************************************************************************/
/*  File Function: MS51 Watchdog reset disable by modify CONFIG setting demo                                */
/************************************************************************************************************/
#include "MS51_32K.h"

/***********************************************************************

/***********************************************************************************************************/
/*    Main function                                                                                        */
/************************************************************************************************************/
void main (void)
{
    unsigned char i;
    P35_QUASI_MODE;
    P00_INPUT_MODE;
    ENABLE_P00_PULLUP;
    Disable_WDT_Reset_Config();
/*----------------------------------------------------------------------------------------------*/
/* WDT Init !!! ENABLE CONFIG WDT FIRST !!!                                                     */
/* Warning:                                                                                     */
/* Always check CONFIG WDT enable first, CONFIG not enable, SFR can't enable WDT reset          */
/* Please call Enable_WDT_Reset_Config() function to enable CONFIG WDT reset                    */
/*----------------------------------------------------------------------------------------------*/
    for(i=0;i<3;i++)
    {
     P35=~P35;
     Timer0_Interrupt_Init(16000000,500,1000);
    }

    TA=0xAA;TA=0x55;WDCON|=0x07;                //Setting WDT prescale 
    set_WDCON_WDCLR;                            //Clear WDT timer
    while((WDCON|~SET_BIT6)==0xFF);             //confirm WDT clear is ok before into power down mode

    set_WDCON_WDTR;                             //WDT run

    while (1)
    {
      if (P00)
      {
         Disable_WDT_Reset_Config();               //Software disable WDT reset CONFIG setting
          for(i=0;i<5;i++)
          {
            P35=~P35;
            Timer0_Interrupt_Init(16000000,50,1000);
          }
      }
      else 
      {
         Enable_WDT_Reset_Config();
         set_PCON_PD;
      }
    }
}

