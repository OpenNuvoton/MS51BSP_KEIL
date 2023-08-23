/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
 #include "ms51_16k.h"

unsigned long data TIMER0CT,TIMER1CT,TIMER2CT,TIMER3CT;
unsigned char data TH0TMP,TL0TMP,TH1TMP,TL1TMP;

/**
  * @brief Timer0 delay interrupt initial setting and timer 0 interrupt vector 
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref 16 / 24 (use HIRC)
  *                       - \ref 8  (use MIRC)
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref for 24MHz (use HIRC) value range is 100 ~ 32768.
  *                       - \ref for 8MHz  (use MIRC) value range is 100 ~ 65536.
  * @return  None 
  * @note    This initial subroutine must with following Timer 0 interrupt vector.
  * @exmaple :Timer0_AutoReload_Interrupt_Initial(24,450);
*/
#if 0   /* Interrup Vector demo */
void Timer0_ISR (void) interrupt 1        // Vector @  0x0B
{
_push_(SFRS);
      SFRS = 0;
/* following setting for reload Timer 0 counter */
      TH0 = TH0TMP;
      TL0 = TL0TMP;
/* following clear flag for next interrupt */
      clr_TCON_TF0;
_pop_(SFRS);
}
#endif 0

void Timer0_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit)
{
    TIMER0_FSYS_DIV12;                                          /* T0M=0, Timer0 Clock = Fsys/12   */
    ENABLE_TIMER0_MODE1;                                        /* Timer0 as 16-bit mode           */
    TIMER0CT = 65535ul-(u8SYSCLK*u32DLYUnit/12ul);
    TH0TMP = HIBYTE(TIMER0CT);
    TL0TMP = LOBYTE(TIMER0CT);
    TH0 = TH0TMP;
    TL0 = TL0TMP;
    clr_TCON_TF0;
    set_TCON_TR0;                                    //Start Timer0
    ENABLE_TIMER0_INTERRUPT;
}

void  Timer0_AutoReload_Interrupt_CounterClear(void)
{
    TH0 = TH0TMP;
    TL0 = TL0TMP;
    clr_TCON_TF0;
    set_TCON_TR0;
}
/**
  * @brief Timer1 delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref 24 (use HIRC)
  *                       - \ref 8  (use MIRC)
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref for 7.3728MHz (use HIRC) value range is 100 ~ 32768.
  *                       - \ref for 8MHz  (use MIRC) value range is 100 ~ 65536.
  * @return  None
  * @note    This initial subroutine must with following Timer 1 interrupt vector.
  * @exmaple :  Timer0_AutoReload_Interrupt_Initial(8,6400);
*/
#if 0
void Timer1_ISR (void) interrupt 3        // Vector @  0x1B
{ 
    _push_(SFRS);
/* following setting for reload Timer 0 counter, this is must for next time*/
      TH1 = TH1TMP;
      TL1 = TL1TMP;
/* following clear flag is necessary for next time */
      clr_TCON_TF1;
    _pop_(SFRS);
}
#endif

void Timer1_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit)
{
    TIMER1_FSYS_DIV12;                                           /* T1M=0, Timer1 Clock = Fsys/12   */
    ENABLE_TIMER1_MODE1;                                         /* Timer 1 as 16-bit mode           */
    TIMER1CT = 65535ul-(u8SYSCLK*u32DLYUnit/12ul);
    TH1TMP = HIBYTE(TIMER1CT);
    TL1TMP = LOBYTE(TIMER1CT);
    TH1 = TH1TMP;
    TL1 = TL1TMP;
    clr_TCON_TF1;
    set_TCON_TR1;
    ENABLE_TIMER1_INTERRUPT;
}



/**
  * @brief Timer2 delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref 24 (use HIRC)
  *                       - \ref 8  (use MIRC)
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref for 7.3728MHz (use HIRC) value range is 100 ~ 699050.  means delay time from about 100us ~ 700ms
  *                       - \ref for 8MHz  (use MIRC) value range is 100 ~ 2097120.  means delay time from about 100us ~ 2.1s
  * @return  None
  * @note    Timer 2 divider fixed with 256. suggest delay range is from 10ms ~ 2s
  * @exmaple :  fsys = 8MHz, delay 6.4ms  : Timer2_AutoReload_Interrupt_Initial(8,6400);
*/
#if 0    
void Timer2_ISR (void) interrupt 5        // Vector @  0x2B
{
_push_(SFRS);
    clr_T2CON_TF2;
_pop_(SFRS);
}
#endif

void Timer2_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit)
{
    TIMER2_Auto_Reload_Delay_Mode;
    SFRS = 0;T2MOD&=0x8F;T2MOD|=0x60;                          /* fix divider 256 */
    TIMER2CT = 65535ul-(u8SYSCLK*u32DLYUnit/256ul);
    TH2 = HIBYTE(TIMER2CT);
    TL2 = LOBYTE(TIMER2CT);
    SFRS=1;
    RCMP2H = HIBYTE(TIMER2CT);
    RCMP2L = LOBYTE(TIMER2CT);
    clr_T2CON_TF2;
    set_T2CON_TR2;                                             /* Start Timer2  */
    ENABLE_TIMER2_INTERRUPT;
}

/**
  * @brief Timer3 delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref 24 (use HIRC)
  *                       - \ref 8  (use MIRC)
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref for 24MHz (use HIRC) value range is 100 ~ 349525.  means delay time from about 100us ~ 350ms
  * @return  None
  * @note    Timer 3 divider fixed with 128. Delay time from about 100us ~ 350ms
  * @exmaple :  fsys = 8MHz, delay 6.4ms  : Timer3_AutoReload_Interrupt_Initial(8,DIV128,6400);
*/
#if 0
void Timer3_ISR (void) interrupt 16        // Vector @  0x83
{
_push_(SFRS);
    clr_T3CON_TF3;
_pop_(SFRS);
}
#endif 

void Timer3_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit)
{
    SFRS = 0;
    T3CON&=0xF8;
    T3CON|=0x07;     /*  Timer 3 divider fixed with 128.*/
    TIMER2CT = 65535ul-(u8SYSCLK*u32DLYUnit/128ul);
    TIMER2CT &= 0xFFFF;
    RH3 = HIBYTE(TIMER2CT);
    RL3 = LOBYTE(TIMER2CT);
    clr_T3CON_TF3;
    set_T3CON_TR3;                                    /* Trigger Timer3  */
    ENABLE_TIMER3_INTERRUPT;
}

