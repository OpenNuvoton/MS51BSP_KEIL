/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 INT0 pin external interrupt demo                                                    */
/************************************************************************************************************/
#include "ms51_8k.h"

/* External pin interrupt INT0 subroutine */
void INT0_ISR(void) interrupt 0          // Vector @  0x03
{
    _push_(SFRS);
  
    clr_TCON_IE0;          //clr int flag wait next falling edge

    _pop_(SFRS);
}


void main (void) 
{
    P30_QUASI_MODE;                      //setting INT0 pin P3.0 as Quasi mode with internal pull high  
    P30 = 1;
    INT0_FALLING_EDGE_TRIG;              //setting trig condition level or edge
    set_IE_EX0;                          //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;             //Global interrupt enable
    while(1);
}
 


