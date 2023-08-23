/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ms51_32k.h"

/**
 * @brief       PWM Synchronous mode PWM0 channel 0/2/4 setting and channel 1/3/4 follow output demo
 * @param       None
 * @return      None
 * @details     Channel 0 high duty 10%, Channel 2 high duty 30% , Channel 4 high duty 50%.
 */

void main (void) 
{

/** PWM0 initial setting  
   * include pwm.c in Library for PWM mode setting
   * @note: the period setting of all PWM0 should be same, for example following 0x6FF.
*/
  
    PWM0_ClockSource(PWM_FSYS,128);                                    // define PWM0 clock source and divider.
 
    ENABLE_PWM0_CH2_P10_OUTPUT;                                         
    P10_PUSHPULL_MODE;
    ENABLE_PWM0_CH3_P00_OUTPUT;                                       
    P00_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(2,Synchronous,EdgeAligned,0x6FF,30);    // setting PWM channel 2&3 as 30% duty high of 0x6FF PWM period = 0x0219

    ENABLE_PWM0_CH4_P01_OUTPUT;                                       
    P01_PUSHPULL_MODE;
    ENABLE_PWM0_CH5_P03_OUTPUT;                                       
    P03_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(4,Synchronous,EdgeAligned,0x6FF,50);    // setting PWM channel 4&5 as 50% duty high of 0x6FF PWM period = 0x037F
    
    PWM0_RUN();
  
    while(1);
}



