/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define     BYTE_READ_CID            0x0B
#define     BYTE_READ_DID            0x0C
#define     BYTE_READ_UID            0x04

#define     PAGE_ERASE_AP            0x22
#define     BYTE_READ_AP             0x00
#define     BYTE_PROGRAM_AP          0x21
#define     BYTE_READ_ID             0x0C
#define     PAGE_ERASE_CONFIG        0xE2
#define     BYTE_READ_CONFIG         0xC0
#define     BYTE_PROGRAM_CONFIG      0xE1

extern unsigned char xdata DIDBuffer[2];
extern unsigned char xdata PIDBuffer[2];
extern unsigned char xdata UIDBuffer[12];
extern unsigned char xdata UCIDBuffer[12];
extern unsigned char xdata IAPDataBuf[128];
extern unsigned char xdata IAPCFBuf[5];
extern bit  ConfigModifyFlag;

void Trigger_IAP(void);
void Erase_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Erase_Verify_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_Verify_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Erase_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Erase_Verify_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_Verify_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Modify_CONFIG(unsigned char u8CF0,unsigned char u8CF1,unsigned char u8CF2,unsigned char u8CF3,unsigned char u8CF4);
void Read_UID(void);
void Read_UCID(void);
void Read_DID(void);
void Read_PID(void);
void Read_CONFIG(void);