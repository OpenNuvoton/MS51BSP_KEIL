/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define UART3_TXD   0
#define UART3_RXD   1


extern bit uart3rvflag;
extern unsigned char uart3rvbuffer;

void UART3_Open(unsigned long u32SysClock, unsigned long u32Baudrate);
void UART3_Receive_10byte(void);
unsigned char UART3_Receive_Data();
void UART3_Send_Data(unsigned char c);
void UART3_Interrupt(unsigned char u8UART3INTSel,unsigned char u8UART3INTStatus);