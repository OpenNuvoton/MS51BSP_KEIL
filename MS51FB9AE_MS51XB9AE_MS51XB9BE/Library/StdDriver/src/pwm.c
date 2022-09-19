/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "MS51_16K.h"

/****** PWM0 SETTING ********/
 /**
 * @brief This function config PWM clock base
 * @param[in] u8PWMCLKSource PWM0 clock source from HIRC or TIMER1.
                   - \ref  PWM_FSYS
                   - \ref  PWM_TIMER1
 * @param[in] u8PWM0CLKDIV the divider value of PWM clock.  - \ref (1\2\4\8\16\32\64\128) 
 * @return none
 * @note        
 * @example PWM0_ClockSource(PWM0_HIRC,128);
  */
void PWM0_ClockSource(unsigned char u8PWMCLKSource, unsigned char u8PWM0CLKDIV)
{
    switch (u8PWMCLKSource)
    {
        case PWM_FSYS:  clr_CKCON_PWMCKS; break;
        case PWM_TIMER1: set_CKCON_PWMCKS; break;
    }
    switch (u8PWM0CLKDIV)
    {
//        case 1:    PWM0_CLOCK_DIV_1; break;
        case 2:    PWM0_CLOCK_DIV_2; break;
        case 4:    PWM0_CLOCK_DIV_4; break;
        case 8:    PWM0_CLOCK_DIV_8; break;
        case 16:   PWM0_CLOCK_DIV_16; break;
        case 32:   PWM0_CLOCK_DIV_32; break;
        case 64:   PWM0_CLOCK_DIV_64; break;
        case 128:  PWM0_CLOCK_DIV_128; break;
    }
}

 /**
 * @brief This function config PWM generator 
 * @param[in] u8ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u8OPMode PWM run mode select from Independent, Complementary or Synchronized mode.
 * @param[in] u8PwmType select Edge-Aligned Type or Center-Aligned Type
 * @param[in] u32PWM0Frequency Target generator frequency, note the actually PWM period is 16bit value. from 0x0000 ~ 0xFFFF
 * @param[in] u16DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return none
 * @note  none       
 * @example PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x6FF,10);
  */
void PWM0_ConfigOutputChannel(unsigned char u8PWM0ChannelNum,
                              unsigned char u8PWM0OPMode,
                              unsigned char u8PWM0PwmType,
                              unsigned long u32PWM0Frequency,
                              unsigned int u16PWM0DutyCycle)
{
  set_SFRS_SFRPAGE;
  switch (u8PWM0OPMode)
  {
      case Independent:    PWMCON1&=0x3F;break;
      case Complementary:  PWMCON1&=0x3F;PWMCON1|=0x40;break;
      case Synchronous:    PWMCON1&=0x3F;PWMCON1|=0x80;break;
  }
  switch (u8PWM0PwmType)
  {
      case EdgeAligned:    PWMCON1&=0xEF;break;
      case CenterAligned:  PWMCON1|=0x10;break;
  }
  switch (u8PWM0ChannelNum)
  {
      case 0:  PWM1H=(u32PWM0Frequency*u16PWM0DutyCycle/100)>>8;PWM0L=(u32PWM0Frequency*u16PWM0DutyCycle/100);break;
      case 1:  PWM1H=(u32PWM0Frequency*u16PWM0DutyCycle/100)>>8;PWM1L=(u32PWM0Frequency*u16PWM0DutyCycle/100);break;
      case 2:  PWM2H=(u32PWM0Frequency*u16PWM0DutyCycle/100)>>8;PWM2L=(u32PWM0Frequency*u16PWM0DutyCycle/100);break;
      case 3:  PWM3H=(u32PWM0Frequency*u16PWM0DutyCycle/100)>>8;PWM3L=(u32PWM0Frequency*u16PWM0DutyCycle/100);break;
      case 4:  PWM4H=(u32PWM0Frequency*u16PWM0DutyCycle/100)>>8;PWM4L=(u32PWM0Frequency*u16PWM0DutyCycle/100);break;
      case 5:  PWM5H=(u32PWM0Frequency*u16PWM0DutyCycle/100)>>8;PWM5L=(u32PWM0Frequency*u16PWM0DutyCycle/100);break;
  }
  PWMPH = u32PWM0Frequency>>8;
  PWMPL = u32PWM0Frequency;
  clr_SFRS_SFRPAGE;}

 /**
 * @brief This function config PWM Complementary pair inset dead zone time 
 * @param[in] u8PWM0Pair PWM0 channel pair need insert pair define. (PWM0_CH01 / PWM0_CH23 / PWM0_CH45 / PWM0_ALL) 
 * @param[in] u8PWM0DZValue the insert value.  PWM dead-time = (u8PWM0DZValue+1)/Fsys
 * @return none
 * @note        
 * @example PWM0_DeadZoneEnable(PWM0_CH01,0x55);
  */
void PWM0_DeadZoneEnable(unsigned char u8PWM0Pair, unsigned int u16PWM0DZValue)
{
    SFRS = 0x01;
    BIT_TMP=EA;EA=0;
    ACC=u16PWM0DZValue&0x0100>>4;
    TA=0xAA;TA=0x55;PDTEN|=ACC;
    switch (u8PWM0Pair)
    {
        case PWM0_CH01:  TA=0xAA;TA=0x55;PDTEN|=0x01; break;
        case PWM0_CH23:  TA=0xAA;TA=0x55;PDTEN|=0x02; break;
        case PWM0_CH45:  TA=0xAA;TA=0x55;PDTEN|=0x04; break;
        case PWM0_ALL:   TA=0xAA;TA=0x55;PDTEN|=0x07; break;
    }
    ACC=u16PWM0DZValue;
    TA=0xAA;TA=0x55;
    PDTCNT=ACC;
    EA=BIT_TMP;
}

/**
* @brief This function disable all PWM Complementary pair inset dead zone time 
* @param[in] none
* @return none
* @note        
* @example PWM0_DeadZone_ALL_Disable();
*/
void PWM0_DeadZone_ALL_Disable(void)
{
    SFRS = 0x01;
    TA=0xAA;TA=0x55;
    PDTEN=0x00;
    EA=BIT_TMP;
}
    
/**
* @brief This function action all PWM run
* @param[in] none
* @return none
* @note        
* @example PWM0_RUN();
*/
void PWM0_RUN(void)
{
    set_PWMCON0_PWMRUN;
}

/**
* @brief This function action all PWM stop run
* @param[in] none
* @return none
* @note        
* @example PWM0_RUN();
*/
void PWM0_STOP(void)
{
  clr_PWMCON0_PWMRUN;
}

/**
* @brief This function action PWM value reload
* @param[in] none
* @return none
* @note        
* @example PWM0_Reload();
*/
void PWM0_Reload(void)
{
    set_PWMCON0_LOAD;
}


