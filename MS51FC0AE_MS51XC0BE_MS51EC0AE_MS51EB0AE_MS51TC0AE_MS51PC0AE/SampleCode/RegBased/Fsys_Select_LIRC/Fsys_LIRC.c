/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.       */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/


//***********************************************************************************************************
//  File Function: MS51 system clock enable LIRC demo code
//***********************************************************************************************************
#include "MS51_32K.h"

/*=============================================================================================*/
/*  The test process:                                                                          */
/*  1. Power on is run as default HIRC, show LED Fsys tickle faster                            */
/*  2. toggle P3.5 to GND. Call modify Fsys code to LIRC.                                      */
/*  3. toggle P3.5 to VDD. Call modify Fsys code to HIRC.                                      */
/*  4. LED tickle speed slowly than before                                                     */
/*=============================================================================================*/
void main(void)
{

/* Note
  MCU power on system clock is HIRC (16 MHz)
  Please keep P3.0 HIGH before you want to modify Fsys to LIRC
*/
    P35_INPUT_MODE;
    P11_PUSHPULL_MODE;
    set_CKCON_CLOEN;                                  // Also can check P1.1 CLO pin for clock to find the Fsys change.
    while(P35);
    FsysSelect(FSYS_LIRC);
    Timer0_Delay(10000,200,1000);
    while (!P35);
    FsysSelect(FSYS_HIRC);
    Timer0_Delay(16000000,2000,1000);
    while(P35);
    set_PCON_PD;
    while(1);

}

