/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jun/21/2020
//***********************************************************************************************************

#include "MS51_32K.h"

unsigned char uart2rvbuffer=0;
bit uart2rvflag;

void SMC0_ISR(void) interrupt 21          // Vector @  0x9B
{
    _push_(SFRS);
 /* Since only enable receive interrupt, not add flag check */
        SFRS = 2;
        uart2rvflag = 1;
        uart2rvbuffer = SC0DR;
        
    _pop_(SFRS);
}
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

/****************************************************************************************************************/  
/**** UART Receive data without interrupt                                                                       */
/**** For example: UART_Open(UART0_Timer1,1200)                                                                 */
/****************************************************************************************************************/ 
//void UART2_Receive_10byte(void)
//{  
//  set_SC0IE_RDAIEN;
//  BIT_TMP = EA;
//  EA = 1;
//  while (uart2rvlength!=10)
//  {
//    if (uart2rvflag)
//    {
//      uart2buffer[uart2rvlength]= SC0DR;
//    }
//    uart2rvflag=0;
//  }
//  uart2rvlength = 0;
//  EA = BIT_TMP;
//}

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
    while((SC0TSR&SET_BIT1)==SET_BIT1);
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
      while(!(SC0TSR|SET_BIT3));
      clr_SC0CR0_TXOFF;
}


/**
 * @brief       UART interrupt enable setting 
 * @param       u8UARTPort: UART0/UART1/UART2/UART2 baudrate value
 * @param       u8UARTINTStatus: Disable/Enable
 * @return      none
 * @details     none
 * @note        max baud rate = 1.5MHz when Fsys = 24MHz
 * @example:    UART2_Interrupt(UART2_TXD,Enable)
 */
//void UART2_Interrupt(unsigned char u8UART2INTSel,unsigned char u8UART2INTStatus)
//{
//        switch (u8UART2INTSel)
//        {
//          case UART2_TXD:
//            switch(u8UART2INTStatus)
//            {
//              case Disable: clr_SC0IE_TBEIEN;   break;
//              case Enable: set_SC0IE_TBEIEN;    break;
//            }break;
//            case UART2_RXD:
//            switch(u8UART2INTStatus)
//            {
//              case Disable:  clr_SC0IE_RDAIEN;   break;
//              case Enable:   set_SC0IE_RDAIEN;   break;
//            }break;
//        }

//}



