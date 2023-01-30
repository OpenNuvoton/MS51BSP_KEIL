/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

extern unsigned char xdata IAPSPDataBuf[127];

void Erase_SPROM(void);
void Erase_Verify_SPROM(unsigned int u16IAPDataSize);
void Program_SPROM(unsigned int u16IAPDataSize);
void Read_Verify_SPROM( unsigned int u16IAPDataSize);
