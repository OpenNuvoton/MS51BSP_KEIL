/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 PWM insert dead time demo code                                                      */
/************************************************************************************************************/
#include "ms51_32k.h"

/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main(void)
{
    ALL_GPIO_QUASI_MODE;
/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (16MHz/8)/(0x7CF+1) = 1KHz (1ms)
  PWM4 high duty   = PWM4H,PWM4L = 0x01CF = 1/4 PWM period
  PWM0 high duty   = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/16000000 = 32 us (max value)
-----------------------------------------------------------------------------------------------------------------*/
    ENABLE_PWM0_CH0_P12_OUTPUT;
    ENABLE_PWM0_CH1_P11_OUTPUT;
    ENABLE_PWM0_CH4_P01_OUTPUT;
    ENABLE_PWM0_CH5_P15_OUTPUT;

  
    PWM0_COMPLEMENTARY_MODE;          //Only this mode support deat time function
    PWM0_CLOCK_DIV_8;
    PWM0PH = 0x07;
    PWM0PL = 0xCF;

    PWM0C0H = 0x03;
    PWM0C0L = 0xCF;
    SFRS=1;                    // PWM4 and PWM5 duty value need set SFPPAGE 1
    PWM0C4H = 0x01;
    PWM0C4L = 0xCF;
    SFRS=0;
    
    PWM0_DeadZoneEnable(PWM0_CH01,0x110);      //value never over 0x1FF
    
/*Please always setting Dead time if needed before PWM run.    */
    set_PWM0CON0_LOAD;
    set_PWM0CON0_PWM0RUN;
    while(1);    
}