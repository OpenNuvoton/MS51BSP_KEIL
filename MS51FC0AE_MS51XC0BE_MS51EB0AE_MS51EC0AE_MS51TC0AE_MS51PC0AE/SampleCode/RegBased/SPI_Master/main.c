/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 SPI in Master mode demo code
//***********************************************************************************************************
#include "ms51_32k.h"

#define  SS_PIN             P15
#define  spi_trans_delay
//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    while(1);                                       // SPI error 
}

//-----------------------------------------------------------------------------------------------------------
void SPI_Initial(void)
{      
    P15_QUASI_MODE;                                  // P15 (SS) Quasi mode
    P10_QUASI_MODE;                                  // P10 (SPCLK) Quasi mode
    P00_QUASI_MODE;                                  // P00 (MOSI) Quasi mode
    P01_QUASI_MODE;                                  // P01 (MISO) Quasi mode
    
    set_SPSR_DISMODF;                                // SS General purpose I/O ( No Mode Fault ) 
    clr_SPCR_SSOE;
   
    clr_SPCR_LSBFE;                                  // MSB first

    clr_SPCR_CPOL;                                   // The SPI clock is low in idle mode
    set_SPCR_CPHA;                                   // The data is sample on the second edge of SPI clock 
    
    set_SPCR_MSTR;                                   // SPI in Master mode 
    SPICLK_FSYS_DIV16;                                    // Select SPI clock 
    set_SPCR_SPIEN;                                  // Enable SPI function 
    clr_SPSR_SPIF;
}
//-----------------------------------------------------------------------------------------------------------
void Start_SPI_process(UINT8 *pu8MID,UINT8 *pu8DID)
{
    SS_PIN = 0;

    Spi_Write_Byte(0x90);
    if(SPDR != 0x4E)
       SPI_Error(); 

#ifdef spi_trans_delay                      /* if slave is interrupt mode, add delay to wait */
    _delay_();                              /* remark #define spi_trans_delay for normal polling transmittion */
#endif

    Spi_Write_Byte(0x01);
    if(SPDR != 0x55)
       SPI_Error();

#ifdef spi_trans_delay
    _delay_();
#endif

    Spi_Write_Byte(0x02);
    if(SPDR != 0x56)
       SPI_Error();

#ifdef spi_trans_delay
    _delay_();
#endif

    Spi_Write_Byte(0x03);
    if(SPDR != 0x4F)
       SPI_Error();

#ifdef spi_trans_delay
    _delay_();
#endif

    Spi_Write_Byte(0x04);
    if(SPDR != 0x54)
       SPI_Error();

#ifdef spi_trans_delay
    _delay_();
#endif

   /* Slave Polling receive data*/
    *pu8MID = Spi_Read_Byte(0xFF);                             // Receive Slave 1st DATA from Slave
    *pu8DID = Spi_Read_Byte(0xFF);                             // Receive Slave 2nd DATA from Slave

    SS_PIN = 1;    
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{      
    unsigned char u8MID,u8DID;

    SPI_Initial();
    Start_SPI_process(&u8MID,&u8DID);
  
    if((u8MID != 0x4F)&&(u8DID != 0x4E))
        SPI_Error();

    while(1);                                    // SPI transmission finish and P0.6 flash
}
//-----------------------------------------------------------------------------------------------------------
