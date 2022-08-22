/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Timer 2 capture function demo                                                       */
//***********************************************************************************************************/
#include "MS51_16K.H"

/************************************************************************************************************/
/*    Capture interrupt subroutine                                                                   */
/************************************************************************************************************/
void Capture_ISR (void) interrupt 12
{
    _push_(SFRS);
  
    clr_CAPCON0_CAPF0;                  /* clear capture0 interrupt flag  */
    P1 = C0L;                            /* For capture mode CxL/CxH with data capture from I/O pin*/
    P2 = C0H;                            
    clr_T2CON_TF2;

    _pop_(SFRS);
}
/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
    ALL_GPIO_QUASI_MODE;
    P00_QUASI_MODE;
    P00 = 1;

    TIMER2_CAP2_Capture_Mode;
    IC3_P00_CAP3_BOTHEDGE_CAPTURE;
      
    set_EIE_ECAP;                        //Enable Capture interrupt
    set_T2CON_TR2;                       //Triger Timer2
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}
