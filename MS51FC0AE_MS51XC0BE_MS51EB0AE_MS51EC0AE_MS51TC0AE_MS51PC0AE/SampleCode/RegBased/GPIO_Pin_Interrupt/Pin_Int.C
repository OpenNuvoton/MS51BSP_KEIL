/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 pin interrupt demo                                                                  */
/************************************************************************************************************/
#include "MS51_32K.h"

bit  stopflag=0;

void PinInterrupt_ISR (void) interrupt 7
{
    _push_(SFRS);
  
  if (PIF&SET_BIT0)
  {
    P35 = 1;
    CLEAR_PIN_INTERRUPT_PIT0_FLAG;
  }
  if (PIF&SET_BIT1)
  {
    P35 = 0;
    stopflag =1;
    CLEAR_PIN_INTERRUPT_PIT1_FLAG;
  }
  ;
  
    _pop_(SFRS);
}  
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    BOD_DISABLE;            /* Disable BOD for less power consumption*/

    P13_INPUT_MODE;
    P13_PULLUP_ENABLE;
    P32_INPUT_MODE;
    P32_PULLDOWN_ENABLE;
    P35_QUASI_MODE;
    P35 = 1;
/*----------------------------------------------------*/
/*  P1.3 set as falling edge trig pin interrupt function */
/*  otherwise, MCU into idle mode.                    */
/*----------------------------------------------------*/
    ENABLE_PIT0_P13_LOWLEVEL;
    ENABLE_PIT1_P32_BOTHEDGE;
    ENABLE_PIN_INTERRUPT;                   // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    set_PCON_PD;
    while(!stopflag);
    DISABLE_PIT1_P32_BOTHEDGE;
    while(1);
}


