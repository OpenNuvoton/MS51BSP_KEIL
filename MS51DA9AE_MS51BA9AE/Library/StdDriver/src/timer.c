/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/*  Website: http://www.nuvoton.com                                                                        */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/
 #include "MS51_8K.H"


void Timer0_ISR (void) interrupt 1           /*interrupt address is 0x000B */
{
    _push_(SFRS);
  
    TF0=0;

    _pop_(SFRS);
}


//-------------------------------------------------------------------------
void Timer0_Interrupt_Init(unsigned long u32SYSCLK, unsigned int u16CNT, unsigned int u16DLYUnit)
{
    unsigned int i;
    BIT_TMP=EA;
    ENABLE_TIMER0_MODE1;
    TIMER0_FSYS_DIV12;
    ENABLE_TIMER0_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    for(i=0;i<u16CNT;i++)
    {
      TL0 = LOBYTE(65535-((u32SYSCLK/1000000)*u16DLYUnit/12));
      TH0 = HIBYTE(65535-((u32SYSCLK/1000000)*u16DLYUnit/12));
      set_TCON_TR0;                                    //Start Timer0
      while(!TF0);
      clr_TCON_TR0;
    }
    DISABLE_TIMER0_INTERRUPT;
    EA=BIT_TMP;
}

void Timer0_Interrupt_Disable(void)
{
	  clr_TCON_TR0;
    DISABLE_TIMER0_INTERRUPT;
}
