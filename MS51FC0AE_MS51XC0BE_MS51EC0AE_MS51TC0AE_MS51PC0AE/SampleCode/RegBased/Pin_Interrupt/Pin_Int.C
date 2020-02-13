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
/*  File Function: MS51 pin interrupt demo                                                                  */
/************************************************************************************************************/
#include "MS51_32K.h"

void PinInterrupt_ISR (void) interrupt 7
{
    _push_(SFRS);
  
  if ((PIF|CLR_BIT0)==0xFF)
  {
    P35 = 1;
  }
  if ((PIF|CLR_BIT1)==0xFF)
  {
    P35 = 0;
  }
  PIF = 0;
  
    _pop_(SFRS);
}	
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{

    P13_INPUT_MODE;
    ENABLE_P13_PULLUP;
    P33_INPUT_MODE;
    ENABLE_P33_PULLDOWN;
    P35_QUASI_MODE;
    P35 = 1;
/*----------------------------------------------------*/
/*  P1.3 set as falling edge trig pin interrupt function */
/*  otherwise, MCU into idle mode.                    */
/*----------------------------------------------------*/
    ENABLE_PIT0_P13_LOWLEVEL;
    ENABLE_PIT1_P33_RISINGEDGE;
    ENABLE_PIN_INTERRUPT;                            // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    set_PCON_PD;
    while(1);


}


