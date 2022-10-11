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

unsigned char PinIntFlag;

/******************************************************************************
Pin interrupt subroutine.
******************************************************************************/
void PinInterrupt_ISR (void) interrupt 7
{
_push_(SFRS);
  
    SFRS = 0;
    switch(PIF)
    {
      case (SET_BIT0): PinIntFlag = SET_BIT0; PIF&=CLR_BIT0; break;
      case (SET_BIT3): PinIntFlag = SET_BIT3; PIF&=CLR_BIT3; break;
      default: break;
    }

_pop_(SFRS);
}
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
  /* UART0 initial for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n PIT test start!");
  /* Disable BOD for power down current */
    BOD_DISABLE;

  /* PIT initial setting */
    P00_QUASI_MODE;
    P03_INPUT_MODE;

    ENABLE_INT_PORT0;
    ENABLE_BIT0_FALLINGEDGE_TRIG;
    ENABLE_BIT3_BOTHEDGE_TRIG;
    ENABLE_PIN_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

    switch(PinIntFlag)
    {
      case (SET_BIT0): printf("\n PIT0 interrupt!"); PinIntFlag&=CLR_BIT0; break;
      case (SET_BIT3): printf("\n PIT3 interrupt!"); PinIntFlag&=CLR_BIT2; break;
      default: break;
    }

}