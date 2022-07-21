/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************
#include "MS51_16K.h"

//volatile unsigned char xdata page_buffer[127];

/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
 unsigned char Read_SPROM_BYTE(unsigned char code *u8_addr)
{
    unsigned char rdata;
    set_IAPUEN_SPMEN;
    rdata = *(0xFF80+u8_addr);
    return rdata;
}

//-------------------------------------------------------------------------
void Write_SPROM_DATAFLASH_ARRAY(unsigned int u16_addr, unsigned char *pDat, unsigned int num)
{
    unsigned char CPageAddr, EPageAddr, cnt;
    CPageAddr = u16_addr >> 7;
    EPageAddr = (u16_addr + num) >> 7;

    while (CPageAddr != EPageAddr)
    {
        cnt = WriteDataToSPOnePage(u16_addr+0xFF80, pDat, 127);
        u16_addr += cnt;
        pDat += cnt;
        num -= cnt;
        CPageAddr = u16_addr >> 7;
    }

    if (num)
    {
        WriteDataToSPOnePage(u16_addr, pDat, num);
    }
}
//-------------------------------------------------------------------------
void Read_SPROM_DATAFLASH_ARRAY(unsigned int u16_addr, unsigned char *pDat, unsigned int num)
{
    unsigned int i;

    set_IAPUEN_SPMEN;
    for (i = 0; i < num; i++)
        pDat[i] = *(unsigned char code *)(u16_addr+0xFF80 + i);
}

//-----------------------------------------------------------------------------------------------------------
unsigned char WriteDataToSPOnePage(unsigned int u16_addr, const unsigned char *pDat, unsigned char num)
{
    unsigned char i, offset;
    unsigned char code *pCode;
    unsigned char xdata xd_tmp[127];

    set_CHPCON_IAPEN;
    set_IAPUEN_SPMEN;
    set_IAPUEN_SPUEN;

    offset = u16_addr & 0x007F;
    i = PAGE_SIZE - offset;

    if (num > i)num = i;

    pCode = (unsigned char code *)(0xFFFF);
    if (pCode == 0)
    {
            IAPAL = 0x80;
            IAPAH = 0x01;
            IAPCN = PAGE_ERASE_SPROM;
            IAPFD = 0xFF;
            set_IAPTRG_IAPGO;
    }
    
    pCode = (unsigned char code *)(u16_addr+0xFF80);
      for (i = 0; i < num; i++)
    {
        if (pCode[i] != 0xFF)break;
    }

    if (i == num)
    {
        IAPCN = BYTE_PROGRAM_SPROM;
        IAPAL = u16_addr+0x80;
        IAPAH = 0x01;

        for (i = 0; i < num; i++)
        {
            IAPFD = pDat[i];
            set_IAPTRG_IAPGO;
            IAPAL++;
        }

        for (i = 0; i < num; i++)
        {
            if (pCode[i] != pDat[i])break;
        }

        if (i != num) goto WriteDataToPage20;
    }
    else
    {
WriteDataToPage20:
        pCode = (unsigned char code *)(0xFF80);

        for (i = 0; i < 128; i++)
        {
            xd_tmp[i] = pCode[i];
        }

        for (i = 0; i < num; i++)
        {
            xd_tmp[offset + i] = pDat[i];
        }

        do
        {
            IAPAL = 0x80;
            IAPAH = 0x01;
            IAPCN = PAGE_ERASE_SPROM;
            IAPFD = 0xFF;
            set_IAPTRG_IAPGO;
            IAPCN = BYTE_PROGRAM_SPROM;

            for (i = 0; i < 127; i++)
            {
                IAPFD = xd_tmp[i];
                set_IAPTRG_IAPGO;
                IAPAL++;
            }

            for (i = 0; i < 128; i++)
            {
                if (pCode[i] != xd_tmp[i])break;
            }
        } while (i != 128);

    }

    clr_IAPUEN_SPUEN;
    clr_CHPCON_IAPEN;

    return num;
}