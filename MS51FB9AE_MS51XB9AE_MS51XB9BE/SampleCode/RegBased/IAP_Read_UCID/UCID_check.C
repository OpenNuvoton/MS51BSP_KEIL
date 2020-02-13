/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2020                                                                                   */
/***********************************************************************************************************/

//***********************************************************************************************************
//  File Function: MS51 read UCID demo
//***********************************************************************************************************
#include "MS51_16K.H"

unsigned char xdata UCIDBuffer[12];

/**********************************/
/* *only read one byte of UCID    */
/*********************************/ 
unsigned char UCID_BYTE(unsigned char Addr)
{
    unsigned char DATATEMP;
    set_CHPCON_IAPEN;
    IAPAL = Addr+0x20;      //The Acture UCID addrss is begin from 0x20
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPTRG_IAPGO;
    DATATEMP = IAPFD;
    clr_CHPCON_IAPEN;
    return DATATEMP;
}

/*********************************************/
/* read whole UCID and storage into XRAM     */
/*********************************************/ 
void All_UCID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x20;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UCIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}


/***********************/
/* main loo    */
/***********************/ 
void main(void)
{
  unsigned char READ1;
	
  ALL_GPIO_QUASI_MODE;
  
/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
  
  
  All_UCID_Read();
  printf ("\n UCID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf (" 0x%bx",UCIDBuffer[READ1]);
  }

  while(1);


}