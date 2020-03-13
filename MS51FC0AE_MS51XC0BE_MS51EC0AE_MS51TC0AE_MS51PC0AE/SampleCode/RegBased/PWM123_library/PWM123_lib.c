/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.        */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/*  Website: http://www.nuvoton.com                                                                        */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Aug/21/2020                                                                                   */
/***********************************************************************************************************/

#include "MS51_32K.h"

/**
 * @brief       PWM call library PWM1 PWM2 PWM3 output demo
 * @param       None
 * @return      None
 * @details     Channel 0 high duty 10%, Channel 1 high duty 20% ..... Channel 5 high duty 60%.
 */

 /************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    P12_PUSHPULL_MODE;
    P11_PUSHPULL_MODE;
    P05_PUSHPULL_MODE;
    P30_PUSHPULL_MODE;
    P17_PUSHPULL_MODE;
    P34_PUSHPULL_MODE;

    PWM123_ClockSource(PWM1,8);
    PWM123_ClockSource(PWM2,8);
    PWM123_ClockSource(PWM3,2);

    PWM123_ConfigOutputChannel(PWM1,CH0_P12, 0x06FF,10);
    PWM123_ConfigOutputChannel(PWM1,CH1_P11, 0x06FF,20);
    PWM123_ConfigOutputChannel(PWM2,CH0_P05, 0x06FF,30);
    PWM123_ConfigOutputChannel(PWM2,CH1_P30, 0x06FF,40);
    PWM123_ConfigOutputChannel(PWM3,CH0_P05, 0x06FF,50);
    PWM123_ConfigOutputChannel(PWM3,CH1_P34, 0x06FF,60);
	
	  PWM_ALL_RUN();
    while(1);
}

