/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_MODE_QUASI      0
#define	GPIO_MODE_PUSHPULL   1
#define GPIO_MODE_INPUT      2
#define GPIO_MODE_OPENDRAIN  3

#define  PORT0     0
#define  PORT1     1
#define  PORT2     2
#define  PORT3     3
#define  PORT4     4

#define  Port0  0
#define  Port1  1
#define  Port2  2
#define  Port3  3
#define  Port4  4

#define  PULLUP     0
#define  PULLDOWN   1
#define  PullUp     0
#define  PullDown   1

#define  Port30     1
#define  Port21     2
#define  Port20     3

void GPIO_SetMode(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8Mode);
void GPIO_Pull_Enable(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8PullMode);
void GPIO_Pull_Disable(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8PullMode);
void GPIO_SchmittTrigger(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SStauts);
void GPIO_SlewRate(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SStauts);
void GPIO_AutoReturnHigh(unsigned char u8Port, unsigned char u8RTtime);