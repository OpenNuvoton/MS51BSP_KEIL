/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: MS51 PWM simple output demo                                                              */
/************************************************************************************************************/
#include "MS51_8K.H"


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    P10_PUSHPULL_MODE;
    P00_PUSHPULL_MODE;
    P01_PUSHPULL_MODE;
    P03_PUSHPULL_MODE;

    ENABLE_PWM0_CH2_P10_OUTPUT;
    ENABLE_PWM0_CH3_P00_OUTPUT;
    ENABLE_PWM0_CH4_P01_OUTPUT;
    ENABLE_PWM0_CH5_P03_OUTPUT;
  
    PWM0_IMDEPENDENT_MODE;
    PWM0_CLOCK_DIV_8;
    PWMPH = 0x30;
    PWMPL = 0x0f;
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x7CF + 1)
                = 1KHz (1ms)
***********************************************************************/
  
    PWM2H = 0x10;          
    PWM2L = 0x08;
    PWM3H = 0x00;            
    PWM3L = 0x25;
    
    set_SFRS_SFRPAGE;            //PWM4 and PWM5 duty seting is in SFP page 1
    PWM4H = 0x03;            
    PWM4L = 0xCF;
    PWM5H = 0x05;            
    PWM5L = 0xCF;
    clr_SFRS_SFRPAGE;                      
/* PWM output inversly enable */
    PWM0_CH2_OUTPUT_INVERSE;

/*-------- PWM start run--------------*/ 
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);

}