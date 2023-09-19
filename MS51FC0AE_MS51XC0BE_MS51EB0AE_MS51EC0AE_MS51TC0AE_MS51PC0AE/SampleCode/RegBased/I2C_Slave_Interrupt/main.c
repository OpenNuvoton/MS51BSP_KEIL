/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2021 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MUG51 I2C Slave demo code
//***********************************************************************************************************

#include "ms51_32k.h"


//***********************************************************************************************************
//  ML51-series I2C slave mode demo code, the Slave address = 0xA4
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


#define I2C_SLAVE_ADDRESS         0xA0
#define LOOP_SIZE                 10 

#define SDA                       P14
#define SCL                       P13

unsigned char data_received[34], data_num = 0 ; 
unsigned int u16PageOffset_HB,u16ReadAddress;
bit I2CWOVERFLAG = 0;

//========================================================================================================
void I2C0_ISR(void) interrupt 6
{
  PUSH_SFRS;
  SFRS = 0;
  switch (I2STAT)
    {
        case 0x00:
            set_I2CON_STO;
            while (STO);
        break;

        case 0x60:
            set_I2CON_AA;
        break;
        
        case 0x68:
            clr_I2CON_AA;
        break;

        case 0x80:
            data_received[data_num] = I2DAT;
            u16ReadAddress = (data_received[0]<<8) + data_received[1];  //This for read process
            data_num++;
            if (data_num == 32)   /* 2 byte address + 30 bytes Data */
            {
                clr_I2CON_AA;
            }
            else
                set_I2CON_AA;
        break;

        case 0x88:
            data_received[data_num] = I2DAT;
            data_num = 0;
            clr_I2CON_AA;
        break;

        case 0xA0:

            if (data_num>20)
            {
               I2CWOVERFLAG = 1 ;
            }
            data_num =0;
            set_I2CON_AA;
        break;

        case 0xA8:
            I2DAT = Read_APROM_BYTE((unsigned int code *)(u16ReadAddress+data_num));
            data_num++;
            set_I2CON_AA;
        break;
        
        case 0xB8: 
            I2DAT = Read_APROM_BYTE((unsigned int code *)(u16ReadAddress+data_num));
            data_num++;
            set_I2CON_AA;
        break;

        case 0xC0:
            data_num = 0;
            set_I2CON_AA;
        break; 

        case 0xC8:
            set_I2CON_AA;
        break;
    }

    I2C0_SI_Check();
POP_SFRS;
}

//========================================================================================================
void Init_I2C_Slave_Interrupt(void)
{
    P13_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    P14_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    set_P1S_3;                   /* Setting schmit tigger mode */
    set_P1S_4;                   /* Setting schmit tigger mode */
  
    SDA = 1;                     /* set SDA and SCL pins high */
    SCL = 1;
  
    I2C_Slave_Open(I2C_SLAVE_ADDRESS) ;
    I2C_Interrupt(ENABLE);
}

//========================================================================================================
void main(void)
{

    /* Initial I2C function */
    Init_I2C_Slave_Interrupt();                                 //initial I2C circuit
    EA =1;

/* =================== */
    while (1)
    {
         if (I2CWOVERFLAG )
        {
           /* After receive storage in dataflash */
           u16PageOffset_HB =  (data_received[0]<<8) + data_received[1];
           Write_DATAFLASH_ARRAY(u16PageOffset_HB, data_received+2, 32);
           I2CWOVERFLAG = 0;
        }
     }

}

