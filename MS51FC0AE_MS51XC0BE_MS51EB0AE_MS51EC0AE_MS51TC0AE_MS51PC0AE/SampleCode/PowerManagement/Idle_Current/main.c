/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.H"

//***********************************************************************************************************
//  File Function: MG51 power down code for test power down current, BOD disabled.
//***********************************************************************************************************

void main (void) 
{
/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
    clr_TCON_TR1;
/* Quasi mode better for power down power comsuption (necessary) */
    ALL_GPIO_QUASI_MODE;
    P0=0;
    P1=0;
    P2=0;

/*MUST Disable BOD to low power (necessary) */
    BOD_DISABLE;              //BOD enable power down current please check datasheet DC charactor.

/* Real into power down mode (necessary) */
    set_PCON_IDLE;
    while(1);
  
}



