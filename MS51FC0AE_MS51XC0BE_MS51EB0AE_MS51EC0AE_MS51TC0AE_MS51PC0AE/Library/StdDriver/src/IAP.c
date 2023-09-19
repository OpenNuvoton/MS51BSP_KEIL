/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k.h"

unsigned char xdata DIDBuffer[2];
unsigned char xdata PIDBuffer[2];
unsigned char xdata UIDBuffer[12];
unsigned char xdata UCIDBuffer[12];
unsigned char xdata IAPDataBuf[128];
unsigned char xdata IAPCFBuf[5];
bit  ConfigModifyFlag;
/**
 * @brief       Erase LDROM  
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Page erase LDROM area base on data start address 
 * @example      Erase_LDROM(0x0000,2048);
 */
void Erase_LDROM(unsigned int u16IAPStartAddress,unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_LDUEN;                    //  LDROM modify Enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_LDROM;
    for(u16Count=0x0000;u16Count<(u16IAPDataSize/PAGE_SIZE);u16Count++)            // Loop page erase LDROM special define address area.
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        set_IAPTRG_IAPGO_WDCLR;
    } 
    clr_IAPUEN_LDUEN;                    // Disable LDROM modify 
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
void Erase_Verify_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_LDROM;

    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;    
        set_IAPTRG_IAPGO;
        if(IAPFD != 0xFF)
          while(1);
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
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
void Program_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_LDUEN;    
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_PROGRAM_LDROM;
    
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = IAPDataBuf[u16Count];     
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_IAPUEN_LDUEN;
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
void Program_Verify_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_LDROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != IAPDataBuf[u16Count])    
            while(1);
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Erase APROM  
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Page erase APROM area base on data start address 
 * @example      Erase_APROM(0x0000,2048);
 */
void Erase_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_APUEN;                    // APROM modify Enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_APROM;
    for(u16Count=0x0000;u16Count<u16IAPDataSize/PAGE_SIZE;u16Count++)            // Loop page erase APROM special define address area.
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        set_IAPTRG_IAPGO_WDCLR; 
    } 
    clr_IAPUEN_APUEN;                    // Disable APROM modify 
    clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       APROM blank check
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define APROM need be erase bytes size
 * @return      none
 * @details     Check each byte of APPROM is FFH or not.
 * @example      APROM_Blank_Check(0x0000,2048);
 */
void Erase_Verify_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;
  
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;    
        set_IAPTRG_IAPGO;
        if(IAPFD != 0xFF)
          while(1);
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       APROM program loop
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define APROM need be erase bytes size
 * @return      none
 * @details     Copy APDataBuf to APROM
 * @example      APROM_Program(0x0000,1024);
 */
void Program_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_APUEN;    
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_PROGRAM_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD=IAPDataBuf[u16Count];
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_IAPUEN_APUEN;
    clr_CHPCON_IAPEN;
}


/**
 * @brief       APROM check loop
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define APROM need be erase bytes size
 * @return      none
 * @details     Check with XRAM IAPDataBuf with APROM
 * @example      APROM_Program_Verify(0x0000,1024);
 */
void Program_Verify_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != IAPDataBuf[u16Count])
            while(1);
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Modify CONFIG  
 * @param       u8CF0,u8CF1,u8CF2,u8CF3,u8CF4,
 * @return      none
 * @details     1. Check the CONFIG setting and now CONFIG value, if this value is matched do not change, close Modify.
                2. if value not match save old config define in XRAM, erase config and program as param define, if fail load saved config and program to recover.    
                3. All interrupt is disabled in modify CONFIG process.
 * @example     Modify_CONFIG(0xEF,0xFB,0xEF,0xFF,0xFF);
 */
void Modify_CONFIG(unsigned char u8CF0,unsigned char u8CF1,unsigned char u8CF2,unsigned char u8CF3,unsigned char u8CF4)
{   
    unsigned char u8Count;

    if(PCON&SET_BIT4)        /* Check with power on flag. Only the first power on check with CONFIG */
    {
        BIT_TMP = EA;
        EA = 0;
        
        set_CHPCON_IAPEN;                    // Enable IAP function
        IAPCN = BYTE_READ_CONFIG;
        IAPAH = 0x00;
        /* Check CONFIG setting data */
        IAPAL = 0;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF0)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF1)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF2)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF3)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF4)
          goto COPRST;
        goto CFCLOSE;
        /* Loop save original CONFIG data in XRAM  */

COPRST:
        ConfigModifyFlag = 1;                // CONFIG modify flag set.
        for(u8Count=0;u8Count<5;u8Count++)
        {        
            IAPAL = u8Count;
            set_IAPTRG_IAPGO; 
            IAPCFBuf[u8Count] = IAPFD;
        } 
        /* Erase CONFIG setting    */
        set_IAPUEN_CFUEN;                    // CONFIG modify Enable
        IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
        IAPCN = PAGE_ERASE_CONFIG;
        IAPAL = 0x00;
        set_IAPTRG_IAPGO_WDCLR;
        /* Modify CONFIG setting as customer define */
        IAPCN = BYTE_PROGRAM_CONFIG;
        IAPFD = u8CF0;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF1;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF2;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF3;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF4;
        set_IAPTRG_IAPGO_WDCLR;
        clr_IAPUEN_CFUEN;
        /* Check programed data, if not match, program the storaged before data.  */
        IAPCN = BYTE_READ_CONFIG;
        IAPAL = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF0)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF1)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF2)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF3)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO; 
        if (IAPFD != u8CF4)
          goto MDCFEND;
        goto CFCLOSE;
MDCFEND:
        for(u8Count=0;u8Count<5;u8Count++)    // Loop save CONFIG data in XRAM
        {        
            IAPAL = u8Count;
            IAPFD = IAPCFBuf[u8Count];
            set_IAPTRG_IAPGO_WDCLR;
        }
CFCLOSE:
        clr_IAPUEN_CFUEN;                    // Disable APROM modify 
        clr_CHPCON_IAPEN;                    // Disable IAP
        
        EA = BIT_TMP;
        PCON&=CLR_BIT4;                      // Clear power on flag to avoid software reset modify CONFIG again. */

    }
}

/**
 * @brief       Read CONFIG  
 * @param       None,
 * @return      none
 * @details     1. Check the CONFIG setting and now CONFIG value, if this value is matched do not change, close Modify.
                2. if value not match save old config define in XRAM, erase config and program as param define, if fail load saved config and program to recover.    
                3. All interrupt is disabled in modify CONFIG process.
 * @example     Read_CONFIG();
 */
void Read_CONFIG(void)
{   
    unsigned char u8Count;

        set_CHPCON_IAPEN;                    // Enable IAP function
        IAPCN = BYTE_READ_CONFIG;
        IAPAH = 0x00;
        /* Loop save original CONFIG data in XRAM  */
        for(u8Count=0;u8Count<5;u8Count++)
        {        
            IAPAL = u8Count;
            set_IAPTRG_IAPGO_WDCLR; 
            IAPCFBuf[u8Count] = IAPFD;
        } 
        clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       Read UID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example      UID_Read();
*/
void Read_UID(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}


/**
 * @brief       Read UCID loop
 * @param       none
 * @return      none
 * @details     IAP command read UCID area storage data in XRAM UCIDBuffer[0:8]
 * @example      UCID_Read();
 */
void Read_UCID(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x20;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UCIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read DID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example      UID_Read();
*/
void DID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for(u8Count=0;u8Count<2;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        DIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read UID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example      UID_Read();
*/
void PID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x02;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for(u8Count=0;u8Count<2;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        PIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}
