/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2022 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"

/**
  * @brief     WKT Interrupt vector demo
  * @note      mark with #if 0 not active.
*/
#if 0
void WKT_ISR (void) interrupt 17            /* Vector @  0x8B  */
{
PUSH_SFRS;

    clr_WKCON_WKTF;

POP_SFRS;
}
#endif


/**
  * @brief WKT delay interrupt initial setting 
  * @param[in] u16WKTRLData define delay time base is ms leve.  the maxima value base on LIRC
  *                       - \ref  value range is 10 ~ 1000.  means wakeupt time from about 10ms ~ 1000ms
  * @note      Delay time value from 10 ~ 100000.  means wakeupt time from about 10mS ~ 100s.
  * @example   WKT_AutoReload_Interrupt_Initial_MS(200);
*/
void WKT_AutoReload_Interrupt_Initial_MS( unsigned int u16WKTRLData)
{
   unsigned int WKTCT;

    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x03;     /*fix divider 64 */
    WKCON &= 0xDF;
    WKTCT = 65535ul-(u16WKTRLData/6ul);          /* divider 64 means 6.4ms per tick */
    SFRS=2; RWKH = HIBYTE (WKTCT);
    SFRS=0; RWKL = LOBYTE (WKTCT);
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}
/**
  * @brief WKT delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u16WKTRLData define delay time base is ms leve.  the maxima value base on LIRC
  *                       - \ref value range is 1 ~ 13100.  means delay time from about 1s ~ 13100s
  * @note      Always check delay range setting.
  * @example   WKT_AutoReload_Interrupt_Initial_S(3600) means 1 hour;
*/
void WKT_AutoReload_Interrupt_Initial_S(unsigned int u16WKTRLData)
{
   unsigned long WKTCT;

    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x07;     /*fix divider 2048 */
    WKTCT = 65535ul-(u16WKTRLData*5ul);   /* divider 2048 means 204.8ms per tick */
    SFRS=2; RWKH = HIBYTE (WKTCT);
    SFRS=0; RWKL = LOBYTE (WKTCT);

    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
 * @brief       Wakeup time setting 
 * @param       u16WKTDIV WKT counter divider select  (1/4/16/64/256/512/1024/2048)
 * @param       u8WKTRLData reload counter value(Value < 256) 
 * @return      none
 * @details     wake up time = u16WKTRLData * u16WKTDIV / 10000    (unit S)
 * @note        Once timer1 or timer3 use as baudrate generator, please not define as timer delay.
 * @example      WKT_Open (256,100);
 */

void WKT_Open(unsigned int u16WKTDIV, unsigned int u16WKTRLData)
{
    SFRS = 0;
    WKCON &= 0xDF;

    switch (u16WKTDIV)
    {
      case 1: WKCON &= 0xF8; break;
      case 4: WKCON &= 0xF8; WKCON |= 0x01; break;
      case 16: WKCON &= 0xF8; WKCON |= 0x02; break;
      case 64: WKCON &= 0xF8; WKCON |= 0x03; break;
      case 256: WKCON &= 0xF8; WKCON |= 0x04; break;
      case 512: WKCON &= 0xF8; WKCON |= 0x05; break;
      case 1024: WKCON &= 0xF8; WKCON |= 0x06; break;
      case 2048: WKCON &= 0xF8; WKCON |= 0x07; break;
    }
    SFRS=2;
    RWKH = HIBYTE (65535 - u16WKTRLData);
    SFRS=0;
    RWKL = LOBYTE (65535 - u16WKTRLData);
    set_WKCON_WKTR;
}

/**
 * @brief       Wakeup time interrupt Enable/disable 
 * @return      WKT_Current_Value
 * @example      WKT_Interrupt(Enable);
 */
void WKT_Interrupt(unsigned char u8WKTINT)
{
    switch (u8WKTINT)
    {
        case Disable: DISABLE_WKT_INTERRUPT;
        case Enable:  ENABLE_WKT_INTERRUPT;
    }
}

/**
  * @brief WKT close disable 
*/
void WKT_Close(void)
{
    clr_WKCON_WKTR;
}
