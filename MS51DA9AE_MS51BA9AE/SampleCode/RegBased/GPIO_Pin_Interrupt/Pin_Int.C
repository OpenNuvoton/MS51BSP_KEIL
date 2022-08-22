/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 pin interrupt demo                                                                  */
/************************************************************************************************************/
#include "MS51_8K.H"


void PinInterrupt_ISR (void) interrupt 7
{
_push_(SFRS);

  if (PIF&SET_BIT3)
  {
    P17 ^= 1;
  }
  if (PIF&SET_BIT3)
  {
    P17 ^= 1;
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

    P03_QUASI_MODE;
    P03 = 0;
    P04_INPUT_MODE;
    P17_QUASI_MODE;


/*----------------------------------------------------*/
/*  P1.3 set as highlevel trig pin interrupt function */
/*  otherwise, MCU into idle mode.                    */
/*----------------------------------------------------*/
    ENABLE_INT_PORT0;
    ENABLE_BIT3_RISINGEDGE_TRIG;
    ENABLE_BIT4_BOTHEDGE_TRIG;
    set_EIE_EPI;                            // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    set_PCON_IDLE;
    while(1);


}


