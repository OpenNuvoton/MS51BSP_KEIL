/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define  GPIO_LED                P35
#define  GPIO_LED_QUASI_MODE     P35_QUASI_MODE
#define  GPIO_PRINTF             P06

#define  BOOT_APROM     0
#define  BOOT_LDROM     2

extern bit BIT_TMP;

unsigned char Read_APROM_BYTE(unsigned int code *u16_addr);
void Software_Reset(unsigned char u8Bootarea);
void PowerDown_Mode(bit PDStatus);
void Idle_Mode(bit IdleStatus);