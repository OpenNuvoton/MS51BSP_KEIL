/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Timer 3 with interrupt demo                                                         */
/************************************************************************************************************/
#include "ms51_32k.h"

#define DIV1      1
#define DIV2      2
#define DIV4      4
#define DIV8      8
#define DIV16     16
#define DIV32     32
#define DIV64     64
#define DIV128    128

/************************************************************************************************************
*    TIMER 3 interrupt subroutine
************************************************************************************************************/
void Timer3_ISR (void) interrupt 16 
{
    PUSH_SFRS;
  
    clr_T3CON_TF3;
    P35 = ~P35;
  
    POP_SFRS;
}	

/************************************************************************************************************
*    TIMER 3 interrupt Initial setting
************************************************************************************************************/
void Timer3_INT_Initial(unsigned char u8TMDIV, 
                        unsigned char u8RH3, 
                        unsigned char u8RL3)
{
    SFRS = 0x00;
    switch (u8TMDIV)
    {
      case DIV1:T3CON&=0xF8; break;
      case DIV2:T3CON&=0xF8;T3CON|=0x01; break;
      case DIV4:T3CON&=0xF8;T3CON|=0x02; break;
      case DIV8:T3CON&=0xF8;T3CON|=0x03; break;
      case DIV16:T3CON&=0xF8;T3CON|=0x04; break;
      case DIV32:T3CON&=0xF8;T3CON|=0x05; break;
      case DIV64:T3CON&=0xF8;T3CON|=0x06; break;
      case DIV128:T3CON&=0xF8;T3CON|=0x07; break;
    }
      clr_T3CON_TF3;
      RH3 = u8RH3;
      RL3 = u8RL3;
      set_EIE1_ET3;                              //enable Timer3 interrupt
}

 /************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    
    P35_QUASI_MODE;

    Timer3_INT_Initial(DIV16,0x20,0x00);
    ENABLE_GLOBAL_INTERRUPT;                                  //enable global interrupts
    set_T3CON_TR3;                              //Timer3 run

    while(1);
}

