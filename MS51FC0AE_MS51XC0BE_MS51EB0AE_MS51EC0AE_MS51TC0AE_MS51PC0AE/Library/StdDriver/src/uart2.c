/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"

unsigned char uart2rvbuffer;
BIT uart2rvflag;

/**
 * @brief       SC0 interrupt vector demo
 * @param       None
 * @return      None
 * @details     Store receive data.
 */
#if 0
void SC0_ISR(void) interrupt 21          // Vector @  0x9B
{
    PUSH_SFRS;
 /* Since only enable receive interrupt, not add flag check */
        SFRS = 2;
        uart2rvflag = 1;
        uart2rvbuffer = SC0DR;

    POP_SFRS;
}
#endif
/**
 * @brief       UART2 transfer data without interrupt 
 * @param       u32SysClock , define Fsys value(value)
 * @param       u32Baudrate, Define baudrate (value)
 * @return      none
 * @details     none
 * @example:    UART2_Open(24000000,115200)
 */ 
void UART2_Open(unsigned long u32SysClock, unsigned long u32Baudrate)
{
    set_SC0CR0_SCEN;         /* Enable SC module */
    set_SC0CR1_UARTEN;       /* set as UART mode */
    set_SC0CR1_CLKKEEP;      
    clr_SC0CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC0CR0_AUTOCEN;
 
    SC0ETURD0 = LOBYTE((u32SysClock/8/u32Baudrate)-1);  /* define baud rate low byte */
    SC0ETURD1 &= 0xF0;                                /* define baud rate high byte */
    SC0ETURD1 |= (HIBYTE(u32SysClock/8/u32Baudrate-1))&0x0F; 
    set_SC0CR1_PBOFF;     //parity bit disable
    SC0CR1&=0xCF;        //datalegth 8bit
    set_SC0CR0_NSB;      //stop bit = 1bit
}

/**
 * @brief       UART2 receive data without interrupt 
 * @param       baudrate value
 * @return      received data
 * @details     none
 * @example:    temp = UART2_Receive_Data()
 */ 
unsigned char UART2_Receive_One_Byte()
{
    unsigned char c;
    clr_SC0CR0_RXOFF;
    while(SC0TSR&SET_BIT1);
    c = SC0DR;
    return (c);
}

/**
 * @brief       UART2 transfer data without interrupt 
 * @param       baudrate value
 * @return      none
 * @details     none
 * @example:    UART2_Send_Data(0x55)
 */ 
void UART2_Send_Data(unsigned char c)
{
      clr_SC0CR0_TXOFF;
      SC0DR = c;
      while(!(SC0TSR&SET_BIT3));
      clr_SC0CR0_TXOFF;
}


