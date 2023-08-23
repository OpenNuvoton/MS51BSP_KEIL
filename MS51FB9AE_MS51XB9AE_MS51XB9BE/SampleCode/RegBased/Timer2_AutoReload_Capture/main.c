/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MG51 Timer 2 capture function demo                                                       */
//***********************************************************************************************************/
#include "ms51_16k.H"

BIT captureflag;
UINT8  capLowByte,capHighByte;
/************************************************************************************************************/
/*    Capture interrupt subroutine                                                                   */
/************************************************************************************************************/
void Capture_ISR (void) interrupt 12
{
    _push_(SFRS);

    clr_CAPCON0_CAPF2;                  /* clear capture2 interrupt flag  */
    capLowByte = C2L;                   /* For capture mode CxL/CxH with data capture from I/O pin*/
    capHighByte = C2H;                    
    clr_T2CON_TF2;
    captureflag = 1;

    _pop_(SFRS);
}
/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
    
    P04_QUASI_MODE;
    P04 = 0;
    
    TIMER2_Compare_Capture_Mode;
    TIMER2_CAP2_Capture_Mode;
    IC3_P04_CAP2_RISINGEDGE_CAPTURE;

    ENABLE_CAPTURE_INTERRUPT;            //Enable Capture interrupt
    set_T2CON_TR2;                       //Triger Timer2
    ENABLE_GLOBAL_INTERRUPT;

    while(1)
    {
      if (captureflag)
      {
        printf ("\n Capture low byte value = 0x%x",capLowByte);
        captureflag = 0;
      }
    }
        
}