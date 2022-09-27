/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 pin interrupt wakeup power down modee                                               */
/************************************************************************************************************/
#include "MS51_16K.H"


void PinInterrupt_ISR (void) interrupt 7
{
_push_(SFRS);
  
     if (PIF&=SET_BIT0)
     {
       P12 ^= 1;
       CLEAR_PIN_INTERRUPT_PIT0_FLAG;
     }
     if (PIF&=SET_BIT3)
     {
       P12 ^= 1;
       CLEAR_PIN_INTERRUPT_PIT3_FLAG;
     }

_pop_(SFRS);
}
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    BOD_DISABLE;            /* Disable BOD for less power consumption*/

    P12_QUASI_MODE;
  
    P00_QUASI_MODE;
    P03_INPUT_MODE;

/*----------------------------------------------------*/
/*  Keep in power down mode unless trig setting GPIO  */
/*----------------------------------------------------*/
    ENABLE_INT_PORT0;
    ENABLE_BIT0_FALLINGEDGE_TRIG;
    ENABLE_BIT3_BOTHEDGE_TRIG;
    ENABLE_PIN_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

    while(1) 
    {
       set_PCON_PD;
    }

}