/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define DIV1      1
#define DIV2      2
#define DIV4      4
#define DIV8      8
#define DIV16     16
#define DIV32     32
#define DIV64     64
#define DIV128    128

extern unsigned long data TIMER0CT,TIMER1CT,TIMER2CT,TIMER3CT;
extern unsigned char data TH0TMP,TL0TMP,TH1TMP,TL1TMP;

void Timer0_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer0_AutoReload_Interrupt_CounterClear(void);
void Timer3_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
