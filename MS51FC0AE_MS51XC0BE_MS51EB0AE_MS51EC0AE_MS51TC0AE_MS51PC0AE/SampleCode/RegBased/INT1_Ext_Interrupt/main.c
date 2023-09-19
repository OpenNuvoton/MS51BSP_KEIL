/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 INT1 extneranl interrupt demo                                                       */
/************************************************************************************************************/
#include "ms51_32k.h"

/* External pin interrupt INT0 subroutine */
void INT0_ISR(void) interrupt 2          // Vector @  0x03
{
    PUSH_SFRS;
  
    clr_TCON_IE1;          //clr int flag wait next falling edge
    P35 ^= 1;
  
    POP_SFRS;
}

void main (void) 
{
    P35_PUSHPULL_MODE;
    P17_INPUT_MODE;                      //setting INT0 pin P1.7 as Quasi mode with internal pull high  
    P17_PULLUP_ENABLE;
    INT1_LOW_LEVEL_TRIG;                //setting trig condition level or edge
    set_IE_EX1;                         //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



