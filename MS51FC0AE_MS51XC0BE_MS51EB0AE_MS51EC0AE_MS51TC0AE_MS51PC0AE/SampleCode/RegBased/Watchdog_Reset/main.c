/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"
 

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    WDT_Clear();
/* Note WDT timer base is LIRC 10Khz*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    
    printf (" \n\r  Enable WDT in CONFIG  \n\r ");
    WDT_Clear();
    printf (" \n\r  Test start MCU reset  \n\r ");
    WDT_Clear();
    printf (" \n\r  P35 connect to VSS, WDT not reset  \n\r ");
    WDT_Clear();
//--------------------------------------------------------
//Warning:
//Pleaes always check CONFIG WDT disable first 
//only when WDT reset disable, WDT use as pure timer
//--------------------------------------------------------
    GPIO_LED_QUASI_MODE;
    WDT_Open(256);
    WDT_Interrupt(Disable);
    DISABLE_GLOBAL_INTERRUPT;
    while (!GPIO_LED)
    {
      WDT_Clear();
    }

}
