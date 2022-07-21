/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Library File Function: MS51 Access SPI Flash (W25Q16BV)
//***********************************************************************************************************

#include "MS51_32K.h"

/****************************************************************/
void Spi_Write_Byte(unsigned char u8SpiWB)
{
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    clr_SPSR_SPIF;
}
/****************************************************************/
unsigned char Spi_Read_Byte(unsigned char u8SpiWB)
{
    unsigned char u8SpiRB;
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    u8SpiRB = SPDR;
    clr_SPSR_SPIF;
    return u8SpiRB;
}