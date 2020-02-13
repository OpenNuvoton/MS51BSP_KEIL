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
#include "MS51_8K.H"


void PinInterrupt_ISR (void) interrupt 7
{
    _push_(SFRS);

  if (PIF|CLR_BIT3)
  {
    P17 = ~P17;
  }
  else if (PIF|CLR_BIT4)
  {
    P17 = ~P17;
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
    P04_QUASI_MODE;
    P04 = 1;
    P17_QUASI_MODE;
    P17 = 0;

/*----------------------------------------------------*/
/*  P1.3 set as highlevel trig pin interrupt function */
/*  otherwise, MCU into idle mode.                    */
/*----------------------------------------------------*/
    ENABLE_INT_PORT0;
    ENABLE_BIT3_RISINGEDGE_TRIG;
    ENABLE_BIT4_FALLINGEDGE_TRIG;
    set_EIE_EPI;                            // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    set_PCON_IDLE;
    while(1);


}


