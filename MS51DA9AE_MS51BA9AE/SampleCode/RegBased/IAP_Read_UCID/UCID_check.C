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

//***********************************************************************************************************
//  File Function: MS51 read UCID demo
//***********************************************************************************************************
#include "MS51_8K.H"

/* For printf code only. Disable this define to reduce code size. */
//#define print_function 

/***********************/
/* main loop           */
/***********************/ 
void main(void)
{

#ifdef print_function
  unsigned char READ1;
/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
#endif 
    
  Read_UCID();
  
#ifdef print_function
  printf ("\n UCID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf (" 0x%bx",UCIDBuffer[READ1]);
  }
  DISABLE_UART0_PRINTF;
#endif

  while(1);


}