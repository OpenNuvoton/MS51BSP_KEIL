/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_32k.h"

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
void WriteDataToSPOnePage(unsigned char u8_addr, unsigned char *pDat, unsigned int num)
{
    unsigned char i;
    unsigned char code *pCode;
    unsigned char xdata xd_tmp[127];

  set_CHPCON_IAPEN;
  set_IAPUEN_SPMEN;
  set_IAPUEN_SPUEN;

  i = Read_SPROM_BYTE(0x7F);
  if (i!=0xFF) goto WriteDataToPage20;

  pCode = (unsigned char code *)(0xFF80+u8_addr);
  for(i=0;i<num;i++)
  {
    if(pCode[i]!=0xFF)break;
  }
  if(i==num)
  {
    IAPCN =BYTE_PROGRAM_SPROM;
    IAPAL = 0x80+u8_addr;
    IAPAH = 0x01;
    for(i=0;i<num;i++)
    {
      IAPFD = pDat[i];
      set_IAPTRG_IAPGO;
      IAPAL++;
    }
    for(i=0;i<num;i++)
    {
      if(pCode[i]!=pDat[i])break;
    }
    if(i!=num) goto SPWriterEnd;
  }
  else
  {
    WriteDataToPage20:
    pCode = (unsigned char code *)(0xFF80);
    for(i=0;i<127;i++)
    {
      xd_tmp[i] = pCode[i];
    }
    for(i=0;i<num;i++)
    {
      xd_tmp[u8_addr+i] = pDat[i];
    }
      IAPAL = 0x80;
      IAPAH = 0x01;
      IAPCN = PAGE_ERASE_SPROM;
      IAPFD = 0xFF;
      set_IAPTRG_IAPGO;
      IAPCN =BYTE_PROGRAM_SPROM;
      IAPAL = 0x80;
      for(i=0;i<127;i++)
      {
        IAPFD = xd_tmp[i];
        set_IAPTRG_IAPGO;
        IAPAL++;
      }
  }
SPWriterEnd:
    clr_IAPUEN_SPUEN;
    clr_CHPCON_IAPEN;
}

void Write_SPROM_DATAFLASH_ARRAY(unsigned char u8_addr, unsigned char *pDat, unsigned int num)
{
      WriteDataToSPOnePage(u8_addr,pDat,num);
}

//-------------------------------------------------------------------------
void Read_SPROM_DATAFLASH_ARRAY(unsigned int u8_addr, unsigned char *pDat, unsigned int num)
{
    unsigned int i;

    set_IAPUEN_SPMEN;
    for (i = 0; i < num; i++)
        pDat[i] = *(unsigned char code *)(u8_addr+0xFF80 + i);
}