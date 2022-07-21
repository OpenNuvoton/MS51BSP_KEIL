/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jun/21/2020
//***********************************************************************************************************

#include "MS51_32K.h"

unsigned char uart3rvbuffer=0;
bit uart3rvflag;

void SMC1_ISR(void) interrupt 22          // Vector @  0x9B
{
    _push_(SFRS);
        SFRS = 2;
        uart3rvflag = 1;
        uart3rvbuffer = SC1DR;
    _pop_(SFRS);
}
/**
 * @brief       UART3 transfer data without interrupt 
 * @param       u32SysClock , define Fsys value(value)
 * @param       u32Baudrate, Define baudrate (value)
 * @return      none
 * @details     none
 * @example:    UART3_Open(24000000,115200)
 */ 
void UART3_Open(unsigned long u32SysClock, unsigned long u32Baudrate)
{
    set_SC1CR0_SCEN;         /* Enable SC module */
    set_SC1CR1_UARTEN;       /* set as UART mode */
    set_SC1CR1_CLKKEEP;      
    clr_SC1CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC1CR0_AUTOCEN;
    SC1ETURD0 = LOBYTE(u32SysClock/8/u32Baudrate-1);  /* define baud rate low byte */
    SC1ETURD1 &= 0xF0;                                /* define baud rate high byte */
    SC1ETURD1 |= (HIBYTE(u32SysClock/8/u32Baudrate-1))&0x0F; 
    set_SC1CR1_PBOFF;     //parity bit disable
    SC1CR1&=0xCF;        //datalegth 8bit
    set_SC1CR0_NSB;      //stop bit = 1bit
  }

/**
 * @brief       UART3 receive data without interrupt 
 * @param       baudrate value
 * @return      received data
 * @details     none
 * @example:    temp = UART3_Receive_Data()
 */ 
unsigned char UART3_Receive_Data()
{
    unsigned char c;

    clr_SC1CR0_RXOFF;
    while((SC1TSR&SET_BIT1)==SET_BIT1);
    c = SC1DR;
  
    return (c);
}

/**
 * @brief       UART3 transfer data without interrupt 
 * @param       baudrate value
 * @return      none
 * @details     none
 * @example:    UART3_Send_Data(0x55)
 */ 
void UART3_Send_Data(unsigned char c)
{
    clr_SC1CR0_TXOFF;
    SC1DR = c;
    while(!(SC1TSR&SET_BIT3));
    clr_SC1CR0_TXOFF;
}

