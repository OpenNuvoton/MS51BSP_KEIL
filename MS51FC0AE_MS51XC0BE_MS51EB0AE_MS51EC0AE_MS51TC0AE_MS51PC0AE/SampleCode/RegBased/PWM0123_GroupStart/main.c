/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ms51_32k.h"

/**
 * @brief       PWM indepedent mode PWM1 PWM2 PWM3 output demo
 * @param       None
 * @return      None
 * @details     Channel 0 high duty 10%, Channel 1 high duty 20% ..... Channel 5 high duty 60%.
 */

         
/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
/* For PWM0 Channel 0~5 GPIO  mode */
    P12_PUSHPULL_MODE;
    P11_PUSHPULL_MODE;
    P10_PUSHPULL_MODE;
    P00_PUSHPULL_MODE;
    P01_PUSHPULL_MODE;
    P03_PUSHPULL_MODE;
/* For PWM1 ~ PWM3   GPIO mode */
    P23_PUSHPULL_MODE;
    P14_PUSHPULL_MODE;
    P05_PUSHPULL_MODE;
    P04_PUSHPULL_MODE;
    P32_PUSHPULL_MODE;
    P34_PUSHPULL_MODE;

/* For PWM0 Channel 0~5 PWM Output enable */
    ENABLE_PWM0_CH0_P12_OUTPUT;
    ENABLE_PWM0_CH1_P11_OUTPUT;
    ENABLE_PWM0_CH2_P10_OUTPUT;
    ENABLE_PWM0_CH3_P00_OUTPUT;
    ENABLE_PWM0_CH4_P01_OUTPUT;
    ENABLE_PWM0_CH5_P03_OUTPUT;
/* For PWM1 ~ PWM3   PWM Output enable */ 
    ENABLE_PWM1_CH0_P23_OUTPUT;
    ENABLE_PWM1_CH1_P14_OUTPUT;
    ENABLE_PWM2_CH0_P05_OUTPUT;
    ENABLE_PWM2_CH1_P04_OUTPUT;
    ENABLE_PWM3_CH0_P32_OUTPUT;
    ENABLE_PWM3_CH1_P34_OUTPUT;

    PWM0_IMDEPENDENT_MODE;
    PWM1_IMDEPENDENT_MODE;
    PWM2_IMDEPENDENT_MODE;
    PWM3_IMDEPENDENT_MODE;
    
    PWM0_CLOCK_DIV_8;
    PWM1_CLOCK_DIV_8;
    PWM2_CLOCK_DIV_8;
    PWM3_CLOCK_DIV_8;
    
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x7CF + 1)
                = 1KHz (1ms)
***********************************************************************/
    SFRS = 0;
    PWM0PH = 0x00;
    PWM0PL = 0x64;
    SFRS = 2; 
    PWM1PH = 0x00;                     /*Setting PWM period  */
    PWM1PL = 0x64;
    PWM2PH = 0x00;                     /*Setting PWM period  */
    PWM2PL = 0x64;
    PWM3PH = 0x00;                     /*Setting PWM period  */
    PWM3PL = 0x64;

    SFRS = 0;
    PWM0C0H = 0x00;
    PWM0C0L = 0x08;
    PWM0C1H = 0x00;
    PWM0C1L = 0x0F;
    PWM0C2H = 0x00;
    PWM0C2L = 0x18;
    PWM0C3H = 0x00;
    PWM0C3L = 0x1F;
    
    SFRS = 1;                           /*PWM4 and PWM5 duty seting is in SFP page 1    */
    PWM0C4H = 0x00;            
    PWM0C4L = 0x28;
    PWM0C5H = 0x00;            
    PWM0C5L = 0x2F;

    SFRS = 2;
    PWM1C0H = 0x00;                      /*PWM1 high duty = 1/2 PWM period */
    PWM1C0L = 0x38;
    PWM1C1H = 0x00;
    PWM1C1L = 0x3F;

    PWM2C0H = 0x00;                      /*PWM1 high duty = 1/2 PWM period */
    PWM2C0L = 0x48;
    PWM2C1H = 0x00;
    PWM2C1L = 0x4F;

    PWM3C0H = 0x00;                     /*PWM1 high duty = 1/2 PWM period */
    PWM3C0L = 0x58;
    PWM3C1H = 0x00;
    PWM3C1L = 0x5F;
 
 /*-------- PWM start run--------------*/ 
    set_PWM0CON0_LOAD;
    set_PWM1CON0_LOAD;
    set_PWM2CON0_LOAD;
    set_PWM3CON0_LOAD;

    SFRS = 0;
    PWM0CON0 |= 0x8E;

    while(1);
}

