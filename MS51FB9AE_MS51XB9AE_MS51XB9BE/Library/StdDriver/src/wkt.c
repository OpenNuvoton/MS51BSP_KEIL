/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "MS51_16K.h"

/**
  * @brief     WKT Interrupt vector demo
  * @note      mark with #if 0 not active.
*/
#if 0
void WKT_ISR (void) interrupt 17            /* Vector @  0x8B  */
{
_push_(SFRS);

    clr_WKCON_WKTF;

_pop_(SFRS);
}
#endif


/**
  * @brief WKT delay s level application lib 
  * @param[in] u8WKTRLData define Fsys clock value. for example 8, use the real Fsys value.
  *                   - \ref  value range is 1 ~ 25.  means wakeupt time from about 1s ~ 50s
  * @note      limitation of the 8bit delay time. Range is 1s ~ 50s
  * @example   WKT_AutoReload_Interrupt_Initial_S(16);
*/
void WKT_AutoReload_Interrupt_Initial_S(unsigned int u16WKTRLData)
{
    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x07;     /*fix divider 2048: */
    RWK = 256 - (u16WKTRLData*5);                /* divider 2048 means 204ms per tick */ 
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
  * @brief WKT delay ms level application lib 
  * @param[in] u8WKTRLData define wakeup time value. for example 80 
  *                  - \ref  value range is 10 ~ 1000.  means wakeupt time from about 10 ms ~ 1000 ms
  * @note      limitation of the 8bit delay time. Range is 10 ms ~ 1000 ms
  * @example   WKT_AutoReload_Interrupt_Initial_MS(200);
*/
void WKT_AutoReload_Interrupt_Initial_MS(unsigned int u16WKTRLData)
{

    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x03;     /*fix divider 64: */
    RWK = 256 - (u16WKTRLData/6);                /* means 6.4ms per tick */
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
 * @brief       Wakeup time setting 
 * @param       u8WKTCLKSouce clock source select define (LIRC / LXT)
 * @param       u16WKTDIV WKT counter divider select  (1/4/16/64/256/512/1024/2048)
 * @param       u8WKTRLData reload counter value(Value < 256) 
 * @return      none
 * @details     wake up time = u16WKTRLData * u16WKTDIV / 10000    (unit S)
 * @note        Once timer1 or timer3 use as baudrate generator, please not define as timer delay.
 * @example      WKT_Open (256,100);
 */

void WKT_Open(unsigned int u16WKTDIV, unsigned char u8WKTRLData)
{
    SFRS = 0;
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
    RWK = u8WKTRLData;
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
        case Enable: ENABLE_WKT_INTERRUPT;
    }
}

//****************************************************************************************************************  
//**** WKT close   
//**** 1. Disable WKT 
//**** 2. clear WKT reload counter 
//**** 3. return WKT current counter value
void WKT_Close()
{
    clr_WKCON_WKTR;
}