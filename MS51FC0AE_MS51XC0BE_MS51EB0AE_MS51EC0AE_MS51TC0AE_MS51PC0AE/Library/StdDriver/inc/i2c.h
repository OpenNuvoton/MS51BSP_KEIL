/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define I2C0    0
#define I2C1    1

#define      I2C_R    1
#define      I2C_W    0

extern bit   I2C_SI_ERROR_FLAG;

void I2C_Master_Open( unsigned long u32SYSCLK, unsigned long u32I2CCLK);
void I2C_Slave_Open( unsigned char u8SlaveAddress0);
void I2C_Close(void);
void I2C_Interrupt(unsigned char u8I2CStatus);
unsigned char I2C_GetStatus(void);
void I2C_SetSlaveAddrMask( unsigned char u8SlaveNo, unsigned char u8SlaveAddrMask);
void I2C_Timeout( unsigned char u8I2CTRStatus );
void I2C_ClearTimeoutFlag(void);
void I2C_Slave_Address_Mask( unsigned char u8I2CAddMaskStatus, unsigned char u8I2CAddMaskBit);
void I2C0_SI_Check(void);