/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************
  Website: http://www.nuvoton.com
  E-Mail : MicroC-8bit@nuvoton.com
************************************************************************************************************/

#include "MS51_16K.h"

unsigned char xdata IAPSPDataBuf[127];



/**
 * @brief       Erase LDROM
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Page erase LDROM area base on data start address
 * @example     Erase_LDROM(0x0000,2048);
 */
void Erase_SPROM(void)
{

    set_CHPCON_IAPEN;                    // Disable IAP    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_SPMEN;                    //  SPROM memory modify Enable
    set_IAPUEN_SPUEN;                    //  SPROM modify enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF
    IAPCN = PAGE_ERASE_SPROM;

    IAPAL = 0x80;
    IAPAH = 0x01;
    set_IAPTRG_IAPGO;

    clr_IAPUEN_SPUEN;                    //  SPROM modify disable
    clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       LDROM blank check
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Check each byte of LDROM is FFH or not.
 * @example      LDROM_BlanckCheck(0x0000,2048);
 */
void Erase_Verify_SPROM(unsigned int u16IAPDataSize)
{
    unsigned int u16Count;
    set_CHPCON_IAPEN;
    set_IAPUEN_SPMEN;

    IAPAH = 0x01;
    IAPAL = 0x80;

    IAPCN = BYTE_READ_SPROM;

    for (u16Count = 0; u16Count < u16IAPDataSize; u16Count++)
    {
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;

        if (IAPFD != 0xFF)
            break;

        IAPAL++;

    }

    clr_CHPCON_IAPEN;
}

/**
 * @brief       LDROM program loop
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Copy IAPDataBuf to LDROM
 * @example      LDROM_Program(0x0000,1024);
 */
void Program_SPROM(unsigned int u16IAPDataSize)
{
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_SPMEN;                    //  SPROM memory modify Enable
    set_IAPUEN_SPUEN;                    //  SPROM modify enable
    IAPAH = 0x01;
    IAPAL = 0x80;
    IAPCN = BYTE_PROGRAM_SPROM;

    for (u16Count = 0; u16Count < u16IAPDataSize; u16Count++)
    {
        IAPFD = IAPSPDataBuf[u16Count];
        set_IAPTRG_IAPGO;
        IAPAL++;
    }

    clr_IAPUEN_SPUEN;                    //  SPROM modify disable
    clr_CHPCON_IAPEN;
}


/**
 * @brief       LDROM check loop
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Check with XRAM IAPDataBuf with LDROM
 * @example      LDROM_Program_Verify(0x0000,1024);
 */
void Read_Verify_SPROM(unsigned int u16IAPDataSize)
{
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_SPMEN;

    IAPAH = 0x01;
    IAPAL = 0x80;
    IAPCN = BYTE_READ_SPROM;

    for (u16Count = 0; u16Count < u16IAPDataSize; u16Count++)
    {
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;

        if (IAPFD != IAPSPDataBuf[u16Count])
            break;

        IAPAL++;
    }

    clr_CHPCON_IAPEN;
}
