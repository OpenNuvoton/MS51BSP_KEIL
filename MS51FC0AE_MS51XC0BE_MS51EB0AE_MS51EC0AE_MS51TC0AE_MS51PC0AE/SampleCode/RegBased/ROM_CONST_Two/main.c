/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"
#include "table_address.h"
#include "table_data.h"

//=========================================================================================================
void main(void)
{
    unsigned char readtemp, readtemp1;
   
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
  
    readtemp = table_address[0];
    readtemp1 = table_data[1];

    printf ("\n\r Table_Address_Locate = 0x%bx", readtemp);
    printf ("\n\r Table_Data_Locate = 0x%bx", readtemp1);

    while(1);
}