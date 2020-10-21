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
/*  File Function: MS51 INT1 extneranl interrupt demo                                                       */
/************************************************************************************************************/
#include "MS51_32K.h"

/* External pin interrupt INT0 subroutine */
void INT0_ISR(void) interrupt 2          // Vector @  0x03
{
    _push_(SFRS);
  
    clr_TCON_IE1;          //clr int flag wait next falling edge
    P35 ^= 1;
  
    _pop_(SFRS);
}

void main (void) 
{
    P35_PUSHPULL_MODE;
    P17_INPUT_MODE;                      //setting INT0 pin P1.7 as Quasi mode with internal pull high  
    ENABLE_P17_PULLUP;
    INT1_LOW_LEVEL_TRIG;                //setting trig condition level or edge
    set_IE_EX1;                         //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



