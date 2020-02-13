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

/***********************************************************************************************************
//  File Function: MS51 UART0 receive and transmit loop test
/***********************************************************************************************************/
#include "MS51_8K.H"

/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{
    P17_PUSHPULL_MODE;
/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    set_IE_ES;                                  /* Enable UART0 interrupt */
    set_IE_EA;                                  /* Global interrupt enable */
  
/* while receive data from RXD, send this data to TXD */
/* IMPORTANT : MS51 tiny baord P2.0 connect reset pull high resister, must remove then test UART0 input function */
  while(1)
  {
    if (uart0_receive_flag)
    {
      uart0_receive_flag = 0;
      clr_IE_ES;
      UART_Send_Data(UART0,uart0_receive_data);
      set_IE_ES;
    }
  }
}