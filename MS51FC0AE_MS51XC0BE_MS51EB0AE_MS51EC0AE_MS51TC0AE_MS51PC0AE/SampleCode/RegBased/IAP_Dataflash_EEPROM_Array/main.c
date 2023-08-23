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
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;;

    /*loop here while P46 = 1; */
    P35_INPUT_MODE;

    while (P35);

    /** IAP program APROM as EEPROM way * include eeprom.c in Library       */

    Write_DATAFLASH_BYTE(0x3882, 0x34);

    for (i = 0; i < 50; i++)
    {
        ArrayData[i] = i;
    }

    StructData.a = 0x5555;
    StructData.b = 0x55555555;
    StructData.c = 0x55;

    Write_DATAFLASH_ARRAY(0x38E0, ArrayData, 50); //write 50 bytes
    Write_DATAFLASH_ARRAY(0x38FE, (unsigned char *)&StructData, sizeof(StructData)); //write structure


    /*call read byte */
    system16highsite = ((Read_APROM_BYTE(0x38FD) << 8) + Read_APROM_BYTE(0x38FE));

    printf("\n system16highsite = 0x%X", system16highsite);
    DISABLE_UART0_PRINTF;

    while (1);
}



