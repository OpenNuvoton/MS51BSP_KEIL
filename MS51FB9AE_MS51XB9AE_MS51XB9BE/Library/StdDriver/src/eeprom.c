/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2022 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"


volatile unsigned char xdata page_buffer[128];
/**
 * @brief       Write Dataflash as EEPROM, 
 * @param       u16EPAddr the 16bit EEPROM start address. Any of APROM address can be defined as start address (0x3800)
 * @param       u8EPData the 8bit value need storage in (0x3800)
 * @return      none
 * @details     Storage dataflash page data into XRAM 380H-400H, modify data in XRAM, Erase dataflash page, writer updated XRAM data into dataflash
 */
void Write_DATAFLASH_BYTE(unsigned int u16EPAddr,unsigned char u8EPData)
{
  unsigned char looptmp=0;
  unsigned int u16_addrl_r;
  unsigned int RAMtmp;
  
//Check page start address
  u16_addrl_r=(u16EPAddr/128)*128;
//Save APROM data to XRAM0
  for(looptmp=0;looptmp<0x80;looptmp++)
  {
    RAMtmp = Read_APROM_BYTE((unsigned int code *)(u16_addrl_r+looptmp));
    page_buffer[looptmp]=RAMtmp;
  }
// Modify customer data in XRAM
  page_buffer[u16EPAddr&0x7f] = u8EPData;
  
//Erase APROM DATAFLASH page
    IAPAL = u16_addrl_r&0xff;
    IAPAH = (u16_addrl_r>>8)&0xff;
    IAPFD = 0xFF;
    set_CHPCON_IAPEN; 
    set_IAPUEN_APUEN;
    IAPCN = 0x22;     
     set_IAPTRG_IAPGO; 
    
//Save changed RAM data to APROM DATAFLASH
    set_CHPCON_IAPEN; 
    set_IAPUEN_APUEN;
    IAPCN = 0x21;
    for(looptmp=0;looptmp<0x80;looptmp++)
    {
      IAPAL = (u16_addrl_r&0xff)+looptmp;
      IAPAH = (u16_addrl_r>>8)&0xff;
      IAPFD = page_buffer[looptmp];
      set_IAPTRG_IAPGO;      
    }
    clr_IAPUEN_APUEN;
    clr_CHPCON_IAPEN;
}  


//-------------------------------------------------------------------------
void Write_DATAFLASH_ARRAY(unsigned int u16_addr,unsigned char *pDat,unsigned int num)
{
  unsigned char CPageAddr,EPageAddr,cnt;
  CPageAddr=u16_addr>>7;
  EPageAddr=(u16_addr+num)>>7;
  while(CPageAddr!=EPageAddr)
  {
    cnt=WriteDataToOnePage(u16_addr,pDat,128);
    u16_addr+=cnt;
    pDat+=cnt;
    num-=cnt;
    CPageAddr=u16_addr>>7;
  }
  if(num)
  {
    WriteDataToOnePage(u16_addr,pDat,num);
  }
}
//-------------------------------------------------------------------------
void Read_DATAFLASH_ARRAY(unsigned int u16_addr,unsigned char *pDat,unsigned int num)
{
  unsigned int i;
  for(i=0;i<num;i++)
    pDat[i] = *(unsigned char code *)(u16_addr+i);
}

//-----------------------------------------------------------------------------------------------------------
unsigned char WriteDataToOnePage(unsigned int u16_addr,const unsigned char *pDat,unsigned char num)
{
  unsigned char i,offset;
  unsigned char code *pCode;
  unsigned char xdata xd_tmp[128];

  set_CHPCON_IAPEN; 
  set_IAPUEN_APUEN;

  offset=u16_addr&0x007F;
  i = PAGE_SIZE - offset;
  if(num>i)num=i;
  pCode = (unsigned char code *)u16_addr;
  for(i=0;i<num;i++)
  {
    if(pCode[i]!=0xFF)break;
  }
  if(i==num)
  {
    IAPCN =BYTE_PROGRAM_APROM;
    IAPAL = u16_addr;
    IAPAH = u16_addr>>8;
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
    if(i!=num) goto WriteDataToPage20;
  }
  else
  {
    WriteDataToPage20:
    pCode = (unsigned char code *)(u16_addr&0xff80);
    for(i=0;i<128;i++)
    {
      xd_tmp[i] = pCode[i];
    }
    for(i=0;i<num;i++)
    {
      xd_tmp[offset+i] = pDat[i];
    }
    do
    {
      IAPAL = (u16_addr&0xff80);
      IAPAH = u16_addr>>8;
      IAPCN = PAGE_ERASE_APROM;
      IAPFD = 0xFF;  
      set_IAPTRG_IAPGO; 
      IAPCN =BYTE_PROGRAM_APROM;
      for(i=0;i<128;i++)
      {
        IAPFD = xd_tmp[i];
        set_IAPTRG_IAPGO;
        IAPAL++;
      }
      for(i=0;i<128;i++)
      {
        if(pCode[i]!=xd_tmp[i])break;
      }
    }while(i!=128);
    
  }
  clr_CHPCON_IAPEN;
  
  return num;
}