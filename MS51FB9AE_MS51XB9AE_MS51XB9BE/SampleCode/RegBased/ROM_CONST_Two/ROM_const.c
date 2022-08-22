/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 data location in APROM/DATAFLASH demo code                                          */
/************************************************************************************************************/
#include "MS51_16K.H"

//=========================================================================================================
void main(void)
{
    unsigned char code *Table_Address_Locate;
    unsigned char code *Table_Data_Locate;
    unsigned char readtemp, readtemp1;
   
    ALL_GPIO_QUASI_MODE;
  
    Table_Address_Locate = 0x2C00;
    readtemp = *Table_Address_Locate;
    Table_Data_Locate = 0x3404;
    readtemp1 = *Table_Data_Locate;
  
    while(1);
}