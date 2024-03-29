/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 ADC / Bandgap input demo code                                                       */
/************************************************************************************************************/
#include "ms51_16k.h"

/************************************************************************************************************/
/*   PWM interrupt subroutine                                                                               */
/************************************************************************************************************/
void PWM_ISR (void) interrupt 13
{
    _push_(SFRS);
  
    clr_PWMCON0_PWMF;               // clear PWM interrupt flag

    _pop_(SFRS);
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{

/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (22.1184MHz/8)/(0x3FF + 1)
                = 2.7KHz
***********************************************************************/
    PWM2_P10_OUTPUT_ENABLE;
    P10_PUSHPULL_MODE;
    PWM_INT_PWM2;
    PWM_FALLING_INT;          /*Setting Interrupt happen when PWM0 falling signal */
    
//    PWM_CLOCK_DIV_8;
    PWMPH = 0x03;              /*Setting PWM period  */
    PWMPL = 0xFF;
    PWM2H = 0x00;              /*PWM0 high duty = 1/2 PWM period */
    PWM2L = 0xFF;  

    ENABLE_PWMM0_INTERRUPT;                  /*Enable PWM interrupt  */
    ENABLE_GLOBAL_INTERRUPT;                  
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);
}