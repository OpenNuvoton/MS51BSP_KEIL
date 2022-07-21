/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "MS51_32K.h"

/**
  * @brief      Enable specify I2C controller and set divider
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u32SYSCLK: Define Fsys clock value in Hz.
  *                  - \ref 8000000
  * @param[in]  u32I2CCLK: The target I2C bus clock in Hz. Use HIRC the I2C clock is from 23473 ~ 2000000
  * @return     None
  * @details    The function enable the specify I2C controller and set proper clock divider
  *             in I2C CLOCK DIVIDED REGISTER (I2CLK) according to the target I2C Bus clock.
  *             I2C bus clock = PCLK / (4*(u32I2CCLK+1).
  * @exmaple :  I2C_Open(24000000,100000);
  */
void I2C_Master_Open(unsigned long u32SYSCLK, unsigned long u32I2CCLK)
{
    SFRS = 0x00;
    I2CLK = (u32SYSCLK/4/u32I2CCLK-1); 
    set_I2CON_I2CEN;

}

/**
  * @brief      Enable specify I2C Slave address
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u32SYSCLK: Define Fsys clock value in Hz.
  *                  - \ref 8000000
  * @param[in]  u32I2CCLK: The target I2C bus clock in Hz. Use HIRC the I2C clock is from 23473 ~ 2000000
  * @return     None
  * @details    The function enable the specify I2C controller and set proper clock divider
  *             in I2C CLOCK DIVIDED REGISTER (I2CLK) according to the target I2C Bus clock.
  *             I2C bus clock = PCLK / (4*(u32I2CCLK+1).
  * @exmaple :  I2C_Open(0xA4);
  */
void I2C_Slave_Open( unsigned char u8SlaveAddress0)
{
        SFRS = 0; 
        I2ADDR = u8SlaveAddress0; 
        set_I2CON_I2CEN;
        set_I2CON_AA;
}
/**
  * @brief      Disable I2C function
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @exmaple :  I2C0_Close(I2C0);
*/
void I2C_Close(void)
{
    SFRS = 0;
    clr_I2CON_I2CEN;
}

/**
  * @brief      Enable specify I2C controller interrupt, also need enable globle interrupt in main loop.
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u8I2CStatus:  Specify I2C interrupt status
  *                  - \ref Enable
  *                  - \ref Disable
  * @exmaple :  I2C_Interrupt();
*/
void I2C_Interrupt(unsigned char u8I2CStatus)
{
    SFRS = 0;
         switch (u8I2CStatus)
         {
           case Enable: ENABLE_I2C_INTERRUPT; break;
           case Disable: DISABLE_I2C_INTERRUPT; break;
         }
}

/**
  * @brief      Get I2C bus status value
  * @param[in]  u8I2CSel:  Specify I2C port
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @return     I2C status data 
  * @exmaple :  I2C_GetStatus(I2C0);
*/
unsigned char I2C_GetStatus(void)
{
    unsigned char u8i2cstat;
    SFRS = 0;
     u8i2cstat=I2STAT;
    return (u8i2cstat);
}

/**
 * @brief      Enable Time-out Function with support long time-out
 * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u8I2CTRStatus:  Specify I2C Timer status
  *                  - \ref Enable
  *                  - \ref Disable
 * @return     None
 * @Note       This function enable time-out function and configure DIV4 to support longer time-out.
 * @example    I2C_Timeout(Enable);
 */
void I2C_Timeout( unsigned char u8I2CTRStatus )
{
        switch (u8I2CTRStatus)
        {
          case Enable: set_I2TOC_DIV; set_I2TOC_I2TOCEN; break;
          case Disable: clr_I2TOC_I2TOCEN; break;
        }
}

void I2C_ClearTimeoutFlag(void)
{
    SFRS = 0;
    I2TOC&=0xFE; ;
}

/**
 * @brief      Special design for 8051 I2C SI check
 * @param[in]  none
 * @return     None
 * @details    This function setting the slave address mask bit.
 */
void I2C0_SI_Check(void)
{
    clr_I2CON_SI;
    
    while(I2CON&SET_BIT3)     /* while SI==0; */
    {
        if(I2STAT == 0x00)
        {
            set_I2CON_STO;
        }
        SI = 0;
        if(!SI)
        {
            clr_I2CON_I2CEN;
            set_I2CON_I2CEN;
            clr_I2CON_SI;
        } 
    }
}
