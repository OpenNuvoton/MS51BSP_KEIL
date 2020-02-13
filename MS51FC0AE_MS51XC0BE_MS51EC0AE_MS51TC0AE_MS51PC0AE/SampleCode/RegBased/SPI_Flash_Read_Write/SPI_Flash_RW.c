/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2020
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: MS51 Access SPI Flash (W25Q16BV) demo code
//***********************************************************************************************************
#include "MS51_32K.h"

#define SPI_CMD_WRITE_ENABLE    0x06
#define SPI_CMD_WRITE_DISABLE   0x04
#define SPI_CMD_READ_DATA       0x03
#define SPI_CMD_PAGE_PROGRAM    0x02
#define SPI_CMD_CHIP_ERASE      0xC7
#define SPI_CMD_SECTOR_ERASE    0x20
#define SPI_CMD_READ_STATUS1    0x05

/***************************************************/
void SPI_Error(void)
{
    while(1);
}
/***************************************************/
void SPI_Initial(void)
{
    P15_QUASI_MODE;                            // P15 (SS) Quasi mode
    P10_QUASI_MODE;                            // P10 (SPCLK) Quasi mode
    P00_QUASI_MODE;                            // P00 (MOSI) Quasi mode
    P01_QUASI_MODE;                            // P22 (MISO) Quasi mode


    set_SPCR_SPR1;
    clr_SPCR_SPR0;
/* /SS General purpose I/O ( No Mode Fault ) */
    set_SPSR_DISMODF;
    clr_SPCR_SSOE;

    /* SPI in Master mode */
    set_SPCR_MSTR;

    /* MSB first */
    clr_SPCR_LSBFE;

    clr_SPCR_CPOL;
    clr_SPCR_CPHA;
    
    /* Enable SPI function */
    set_SPCR_SPIEN;
}

/****************************************************************/
void Flash_Check_StatusBusy(void)
{
    unsigned char u8Status;

    SS_PIN = 0;
    do{
        Spi_Write_Byte(SPI_CMD_READ_STATUS1);
        u8Status = Spi_Read_Byte(0xFF);
    }while((u8Status&0x01)==0x01);
    SS_PIN = 1;    
}
/****************************************************************/
void SpiFlash_Write_Enable(void)
{
    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_WRITE_ENABLE);
    SS_PIN = 1;
}
/****************************************************************/
void SpiFlash_Write_Disable(void)
{
    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_WRITE_DISABLE);
    SS_PIN = 1; 
}

/****************************************************************/
void SpiFlash_Read_MID_DID(UINT8 *pu8A,UINT8 *pu8B)
{
    SS_PIN = 0;
    Spi_Write_Byte(0x90);
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    *pu8A = Spi_Read_Byte(0xFF);
    *pu8B = Spi_Read_Byte(0xFF);
    SS_PIN = 1;    
}
/****************************************************************/
void SpiFlash_Chip_Erase(void)
{
    SpiFlash_Write_Enable();
    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_CHIP_ERASE);
    SS_PIN = 1;
    Flash_Check_StatusBusy();
    SpiFlash_Write_Disable();
}
/****************************************************************/
void SpiFlash_Sector_Erase(unsigned char u8add0,unsigned char u8add1,unsigned char u8add2)
{
    SpiFlash_Write_Enable();
    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_SECTOR_ERASE);
    Spi_Write_Byte(u8add0);
    Spi_Write_Byte(u8add1);
    Spi_Write_Byte(u8add2);
    SS_PIN = 1;
    Flash_Check_StatusBusy();
    SpiFlash_Write_Disable();
}

/***************************************************/
void SpiFlash_Erase_Verify(void)
{
    unsigned int  u16CNT;
    unsigned char u8Data;

    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_READ_DATA);
    /* 24-bit Address */
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    for(u16CNT=0;u16CNT<256;u16CNT++)
    {
        u8Data = Spi_Read_Byte(0x00);
        if(u8Data != 0xFF)
        {
            SPI_Error();
        }
    }
     SS_PIN = 1; 
}

/***************************************************/
void SpiFlash_Program(void)
{
    unsigned int  u16CNT;

    SpiFlash_Write_Enable();
    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_PAGE_PROGRAM);
    /* 24-bit Address */
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    for(u16CNT=0;u16CNT<256;u16CNT++)
        Spi_Write_Byte((unsigned char)u16CNT);
    SS_PIN = 1;

    Flash_Check_StatusBusy();
    SpiFlash_Write_Disable();
}

void SpiFlash_Program_Verify(void)
{
    unsigned int  u16CNT;
    unsigned char u8Data;

    SS_PIN = 0;
    Spi_Write_Byte(SPI_CMD_READ_DATA);
    /* 24-bit Address */
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    Spi_Write_Byte(0x00);
    for(u16CNT=0;u16CNT<256;u16CNT++)
    {
        u8Data = Spi_Read_Byte(0x00);
        if(u8Data != (unsigned char)u16CNT)
        {
            SPI_Error();
        }
    }
    SS_PIN = 1;
}
/************ main loop **************/
void main(void)
{
    unsigned char u8MID,u8DID;

    SPI_Initial();

    SpiFlash_Read_MID_DID(&u8MID,&u8DID);
    if((u8MID != 0xEF)&&(u8DID != 0x14))
        SPI_Error();

/* The procedure of SPI Flash at erase mode */
    SpiFlash_Sector_Erase(0,0,0);
    SpiFlash_Erase_Verify();

/* The procedure of SPI Flash at program mode */
    SpiFlash_Program();
    SpiFlash_Program_Verify();

    while(1);
}
