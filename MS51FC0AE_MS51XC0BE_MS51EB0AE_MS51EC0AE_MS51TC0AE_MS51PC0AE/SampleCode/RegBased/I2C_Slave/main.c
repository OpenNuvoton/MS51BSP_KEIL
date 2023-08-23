/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 I2C Slave demo code
//***********************************************************************************************************

#include "ms51_32k.h"


//***********************************************************************************************************
//  MS51-series I2C slave mode demo code, the Slave address = 0xA4
//
//   ____________            _____________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |MS51(M)     |          | MS51(S)     |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  The protocol of I2C is same the "24LC64"
//***********************************************************************************************************


#define I2C_CLOCK                 13
#define I2C_SLAVE_ADDRESS         0xA4
#define LOOP_SIZE                 10 

#define SDA                       P14
#define SCL                       P13

UINT8 data_received[34], data_num = 0;

//========================================================================================================
void I2C_ISR(void) interrupt 6
{
    switch (I2STAT)
    {
        case 0x00:
            STO = 1;
            while(STO);
            break;

        case 0x60:
            AA = 1;
            break;
        
        case 0x68:
            P02 = 0;
            while(1);
            break;

        case 0x80:
            data_received[data_num] = I2DAT;
            data_num++;

            if (data_num == LOOP_SIZE)
           {
              data_num = 0;
              AA = 0;
           }
            else
                AA = 1;
            break;

        case 0x88:
            data_received[data_num] = I2DAT;
            data_num = 0;
            AA = 1;
            break;

        case 0xA0:
            AA = 1;
            break;

        case 0xA8:
            I2DAT = data_received[data_num];
            data_num++;
            AA = 1;
            break;
        
        case 0xB8:
            I2DAT = data_received[data_num];
            data_num++;
            AA = 1;
            break;

        case 0xC0:
            AA = 1;
            break; 

        case 0xC8:
            AA = 1;
            break;        
    }

    SI = 0;
}

//========================================================================================================
void Init_I2C_SLAVE(void)
{
    P13_OPENDRAIN_MODE;                         //set SCL (P13) is Open Drain mode, external pull up resister is necessary
    P14_OPENDRAIN_MODE;                         //set SDA (P14) is Open Drain mode, external pull up resister is necessary

    SDA = 1;                                    //set SDA and SCL pins high
    SCL = 1;
    
    set_EIE_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
    set_IE_EA;

    I2ADDR = I2C_SLAVE_ADDRESS;                 //define own slave address
    set_I2CON_I2CEN;                            //enable I2C circuit
    set_I2CON_AA;
}

//========================================================================================================
void main(void)
{

    /* Initial I2C function */
    Init_I2C_SLAVE();                                 //initial I2C circuit

    while (1);
/* =================== */
}

