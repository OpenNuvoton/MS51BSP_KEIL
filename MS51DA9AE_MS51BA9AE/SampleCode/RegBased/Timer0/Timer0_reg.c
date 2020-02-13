 /*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: Ms51 simple GPIO toggle out demo code                                                    */
/************************************************************************************************************/
 #include "MS51_8K.H"


bit TIMER0_FLAG=0;

/**
 * @brief       Timer0 interrupt subroutine
 * @param       None
 * @return      None
 * @details     
 */
void Timer0_ISR(void) interrupt 1        // Vector @  0x0B
{
    _push_(SFRS);
  
    clr_IE_ET0;
    clr_TCON_TF0;
    clr_TCON_TR0;                                     //Stop Timer0
    TIMER0_FLAG=1;

    _pop_(SFRS);
}

/**
  * @brief   Timer0 16-bit delay register base setting 
*/
void Timer0_Delay_Check_Flag(void)
{
    clr_CKCON_T0M;                                  // T0M=0, Timer0 Clock = Fsys/12
    TIMER0_MODE1_ENABLE;                            // Timer0 is 16-bit mode
    TL0 = 0xFF;                                      // delay time = (0xFFFF - 0x1FFF)*12 / Fsys
    TH0 = 0X1F;                                      // Define value =  0xFFFF-(0xE000/12*Fsys/1000000)
    clr_TCON_TF0;
    set_TCON_TR0;                                    // Start Timer0
    while (TF0 != 1);                               // Check Timer0 Time-Out Flag
    clr_TCON_TF0;
    clr_TCON_TR0;                                   // Stop Timer0
}

/**
  * @brief   Timer0 16-bit delay register base with interrupt setting 
*/
void Timer0_Delay_Interrupt_Initial(void)
{
    clr_CKCON_T0M;                                  // T0M=0, Timer0 Clock = Fsys/12
    TIMER0_MODE1_ENABLE;                             // Timer0 is 16-bit mode
    TL0 = 0xFF;                                      // delay time = (0xFFFF - 0x8FFF)*12 / Fsys
    TH0 = 0x8F;                                      // Define value =  0xFFFF-(0x7000/12*Fsys/1000000)
    set_IE_ET0;
    EA = 1;
    set_TCON_TR0;                                    // Start Timer0
}

void main (void) 
{
/* Setting Multi function pin setting for GPIO toggle 
   * include gipo.c in Common for GPIO mode setting
*/  
    P17_QUASI_MODE;

    while(1)
    {
        P17 = ~P17;
        Timer0_Delay_Check_Flag();
        P17 = ~P17;
        Timer0_Delay_Interrupt_Initial();
        while(!TIMER0_FLAG);
        TIMER0_FLAG=0;
    }
}



