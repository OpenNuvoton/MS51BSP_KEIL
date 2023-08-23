/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_32k.h"

struct
{
    unsigned int a;
    unsigned long b;
    unsigned char  c;

} StructData;

unsigned char ArrayData[50];
unsigned char i;

/**
 * @brief       IAP program dataflash as EEPROM
 * @param       None
 * @return      None
 * @details     define dataflash need be modify address and value,
 */

void main(void)
{
    unsigned int system16highsite;

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n Toggle P12 to low to start test...");
    /*loop here while P46 = 1; */
    P12_QUASI_MODE;
    while (P12);

    /** IAP program APROM as EEPROM way * include eeprom.c in Library       */
    for (i = 0; i < 50; i++)
    {
        ArrayData[i] = i;
    }

    StructData.a=0xA1A2;
    StructData.b=0xA3A4A5A6;
    StructData.c=0xA7;

    Write_SPROM_DATAFLASH_ARRAY(0, ArrayData, 50); //write 50 bytes
    system16highsite = Read_SPROM_BYTE(0x05);
    printf("\n SPROM 0x05 = 0x%X", system16highsite);
    system16highsite = Read_SPROM_BYTE(0x12) ;
    printf("\n SPROM 0x12 = 0x%X", system16highsite);

    Write_SPROM_DATAFLASH_ARRAY(0x11, (unsigned char *)&StructData, sizeof(StructData)); //write structure
    system16highsite = Read_SPROM_BYTE(0x05);
    printf("\n SPROM 0x05 Value is updated = 0x%X", system16highsite);
    system16highsite = Read_SPROM_BYTE(0x12);
    printf("\n SPROM 0x12 Value is updated = 0x%X", system16highsite);

    DISABLE_UART0_PRINTF;

    while (1);
}



