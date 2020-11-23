/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2020                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: MS51 pin interrupt demo                                                                  */
/************************************************************************************************************/
#include "MS51_16K.H"


void PinInterrupt_ISR (void) interrupt 7
{
_push_(SFRS);
  
     if (PIF&=SET_BIT2)
     {
       P02 ^= 1;
     }
     if (PIF&=SET_BIT2)
     {
       P03 ^= 1;
     }

_pop_(SFRS);
}
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    P02_QUASI_MODE;
    P03_QUASI_MODE;
  
    P12_QUASI_MODE;
    P13_INPUT_MODE;
/*----------------------------------------------------*/
/*  P1.3 set as highlevel trig pin interrupt function */
/*  otherwise, MCU into idle mode.                    */
/*----------------------------------------------------*/
    ENABLE_INT_PORT1;
    ENABLE_BIT2_BOTHEDGE_TRIG;
    ENABLE_BIT3_FALLINGEDGE_TRIG;
    set_EIE_EPI;                            // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    set_PCON_IDLE;
    while(1);


}


