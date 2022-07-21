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

#include "MS51_32K.h"

/****** PWM123 SETTING ********/
 /**
 * @brief This function config PWM clock base

 * @param[in] u8PWMCLKDIV the divider value of PWM clock.  - \ref (1\2\4\8\16\32\64\128) 
 * @return none
 * @note        
 * @example PWM123_ClockSource(PWM1,128);
  */
void PWM123_ClockSource(unsigned char u8PWMNum, unsigned char u8PWMCLKDIV)
{
_push_(SFRS);
    switch (u8PWMNum)
    {
      case PWM1: 
        switch (u8PWMCLKDIV)
        {
            case 1:    PWM1_CLOCK_DIV_1; break;
            case 2:    PWM1_CLOCK_DIV_2; break;
            case 4:    PWM1_CLOCK_DIV_4; break;
            case 8:    PWM1_CLOCK_DIV_8; break;
            case 16:   PWM1_CLOCK_DIV_16; break;
            case 32:   PWM1_CLOCK_DIV_32; break;
            case 64:   PWM1_CLOCK_DIV_64; break;
            case 128:  PWM1_CLOCK_DIV_128; break;
        }
      break;
      case PWM2:
        switch (u8PWMCLKDIV)
        {
            case 1:    PWM2_CLOCK_DIV_1; break;
            case 2:    PWM2_CLOCK_DIV_2; break;
            case 4:    PWM2_CLOCK_DIV_4; break;
            case 8:    PWM2_CLOCK_DIV_8; break;
            case 16:   PWM2_CLOCK_DIV_16; break;
            case 32:   PWM2_CLOCK_DIV_32; break;
            case 64:   PWM2_CLOCK_DIV_64; break;
            case 128:  PWM2_CLOCK_DIV_128; break;
        }
      break;
      case PWM3:
        switch (u8PWMCLKDIV)
        {
            case 1:    PWM3_CLOCK_DIV_1; break;
            case 2:    PWM3_CLOCK_DIV_2; break;
            case 4:    PWM3_CLOCK_DIV_4; break;
            case 8:    PWM3_CLOCK_DIV_8; break;
            case 16:   PWM3_CLOCK_DIV_16; break;
            case 32:   PWM3_CLOCK_DIV_32; break;
            case 64:   PWM3_CLOCK_DIV_64; break;
            case 128:  PWM3_CLOCK_DIV_128; break;
        }
      break;
      }
_pop_(SFRS);
}

 /**
 * @brief This function config PWM generator 
 * @param[in] u8PWMNum PWM module.
                   - \ref  PWM1 \ PWM2 \ PWM3 
 * @param[in] u8ChannelNum PWM channel number. Valid values are between 0~1
 * @param[in] u16PWMFrequency Target generator frequency, note the actually PWM period is 16bit value. from 0x0000 ~ 0xFFFF
 * @param[in] u16DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return none
 * @note  none
 * @example PWM123_ConfigOutputChannel(PWM1,0,0x6FF,10);
 * @example PWM123_ConfigOutputChannel(PWM1,1,0x6FF,20);
  */
void PWM123_ConfigOutputChannel(unsigned char u8PWMNum,
                                unsigned char u8PWMoutputSel,
                                unsigned int u16PWMFrequency,
                                unsigned int u16PWMDutyCycle)
{
_push_(SFRS);
  SFRS = 2;
  switch (u8PWMNum)
  {
    case PWM1:
      switch (u8PWMoutputSel)
      {
          case CH0_P23:
          case CH0_P12:
            PWM1C0H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM1C0L=(u16PWMFrequency*u16PWMDutyCycle/100); break;
          case CH1_P22:
          case CH1_P14:
          case CH1_P11:
            PWM1C1H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM1C1L=(u16PWMFrequency*u16PWMDutyCycle/100); break;
      }
      PWM1PH = u16PWMFrequency>>8;
      PWM1PL = u16PWMFrequency;
      switch  (u8PWMoutputSel)
      {
          case CH0_P23:   ENABLE_PWM1_CH0_P23_OUTPUT; break;
          case CH0_P12:   ENABLE_PWM1_CH0_P12_OUTPUT; break;
          case CH1_P22:   ENABLE_PWM1_CH1_P22_OUTPUT; break;
          case CH1_P14:   ENABLE_PWM1_CH1_P14_OUTPUT; break;
          case CH1_P11:   ENABLE_PWM1_CH1_P11_OUTPUT; break;
      }
			break;
    case PWM2:
      switch (u8PWMoutputSel)
      {
          case CH0_P21:
          case CH0_P10:
          case CH0_P05:
            PWM2C0H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM2C0L=(u16PWMFrequency*u16PWMDutyCycle/100); break;
          case CH1_P30:
          case CH1_P31:
          case CH1_P00:
          case CH1_P04:
            PWM2C1H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM2C1L=(u16PWMFrequency*u16PWMDutyCycle/100); break;
      }
      PWM2PH = u16PWMFrequency>>8;
      PWM2PL = u16PWMFrequency;
      switch  (u8PWMoutputSel)
      {
          case CH0_P21:   ENABLE_PWM2_CH0_P21_OUTPUT; break;
          case CH0_P10:   ENABLE_PWM2_CH0_P10_OUTPUT; break;
          case CH0_P05:   ENABLE_PWM2_CH0_P05_OUTPUT; break;
          case CH1_P30:   ENABLE_PWM2_CH1_P30_OUTPUT; break;
          case CH1_P31:   ENABLE_PWM2_CH1_P31_OUTPUT; break;
          case CH1_P00:   ENABLE_PWM2_CH1_P00_OUTPUT; break;
          case CH1_P04:   ENABLE_PWM2_CH1_P04_OUTPUT; break;
      }
    break;
    case PWM3:
      switch (u8PWMoutputSel)
      {
          case CH0_P32:
          case CH0_P01:
          case CH0_P17:
            PWM3C0H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM3C0L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
          case CH1_P34:
          case CH1_P15:
          case CH1_P03:
            PWM3C1H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM3C1L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
      }
      PWM3PH = u16PWMFrequency>>8;
      PWM3PL = u16PWMFrequency;
      switch  (u8PWMoutputSel)
      {
          case CH0_P32:   ENABLE_PWM3_CH0_P32_OUTPUT; break;
          case CH0_P01:   ENABLE_PWM3_CH0_P01_OUTPUT; break;
          case CH0_P17:   ENABLE_PWM3_CH0_P17_OUTPUT; break;
          case CH1_P34:   ENABLE_PWM3_CH1_P34_OUTPUT; break;
          case CH1_P15:   ENABLE_PWM3_CH1_P15_OUTPUT; break;
          case CH1_P03:   ENABLE_PWM3_CH1_P03_OUTPUT; break;
      }
    break;
  }
_pop_(SFRS);
}

void PWM_ALL_RUN()
{
   SFRS=0; 
	 PWM0CON0 |= 0x8E;;
}

void PWM1_RUN()
{
	set_PWM1CON0_PWMRUN;
}
void PWM2_RUN()
{
	set_PWM2CON0_PWMRUN;
}
void PWM3_RUN()
{
	set_PWM3CON0_PWMRUN;
}