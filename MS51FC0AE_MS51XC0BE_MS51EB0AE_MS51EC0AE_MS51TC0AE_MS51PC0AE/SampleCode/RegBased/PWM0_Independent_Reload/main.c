/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_32k.h"

/**
 * @brief       PWM indepedent mode PWM0 channel 0~5 output demo and reload PWM0_CH0 every 3s.
 * @param       None
 * @return      None
 * @details     Channel 0 high duty 10%, Channel 1 high duty 20% ..... Channel 5 high duty 60%.
 */

void main (void) 
{

/* PWM0 initial setting  
   * include pwm.c in Library for PWM mode setting
   @note: the period setting of all PWM0 should be same, for example following 0x6FF.
*/
    PWM0_ClockSource(PWM_FSYS,128);                                    // define PWM0 clock source and divider.
  
    ENABLE_PWM0_CH0_P12_OUTPUT;                                       //Mark since P0.2 also ICE_CLK pin
    P12_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x6FF,10);    // setting PWM channel 0 as 10% duty high of 0x6FF PWM period = 0x00B3

    ENABLE_PWM0_CH2_P10_OUTPUT;
    P10_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(2,Independent,EdgeAligned,0x6FF,30);    // setting PWM channel 2 as 30% duty high of 0x6FF PWM period = 0x0219
  
    ENABLE_PWM0_CH3_P00_OUTPUT;
    P00_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(3,Independent,EdgeAligned,0x6FF,40);    // setting PWM channel 3 as 40% duty high of 0x6FF PWM period = 0x02CC

    ENABLE_PWM0_CH4_P01_OUTPUT;
    P01_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(4,Independent,EdgeAligned,0x6FF,50);    // setting PWM channel 4 as 50% duty high of 0x6FF PWM period = 0x037F

    ENABLE_PWM0_CH5_P03_OUTPUT;
    P03_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(5,Independent,EdgeAligned,0x6FF,60);    // setting PWM channel 5 as 60% duty high of 0x6FF PWM period = 0x0432

    PWM0_RUN();

    while(1)
    {
      Timer2_Delay(24000000,128,3000,1000);
      PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x6FF,90);
      PWM0_Reload();
      Timer2_Delay(24000000,128,3000,1000);
      PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x6FF,10);
      PWM0_Reload();
    }      
}



