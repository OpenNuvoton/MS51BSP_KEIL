/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ISR all list
//***********************************************************************************************************
#include "ms51_32k.h"


/*all interrupt subroutine list */
#if 0 
//-----------------------------------------------------------------------------------------------------------
void INT0_ISR(void) interrupt 0          // Vector @  0x03
{
    PUSH_SFRS;
    clr_TCON_IE0;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void Timer0_ISR(void) interrupt 1        // Vector @  0x0B
{
    PUSH_SFRS;
    clr_TCON_TF0;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void INT1_ISR(void) interrupt 2          // Vector @  0x13
{
    PUSH_SFRS;
    clr_TCON_IE1;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void Timer1_ISR(void) interrupt 3        // Vector @  0x1B
{
    PUSH_SFRS;
   clr_TCON_TF1;
    POP_SFRS;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void UART0_ISR(void) interrupt 4         // Vector @  0x23
{
    PUSH_SFRS;
    clr_SCON_RI;
    clr_SCON_TI;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void Timer2_ISR(void) interrupt 5        // Vector @  0x2B
{
    PUSH_SFRS;
    clr_T2CON_TF2;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void I2C_ISR(void) interrupt 6           // Vector @  0x33
{
    PUSH_SFRS;
   clr_I2CON_SI;
 
    POP_SFRS;
}//-----------------------------------------------------------------------------------------------------------
void Pin_INT_ISR(void) interrupt 7       // Vector @  0x3B
{
     PUSH_SFRS;
     PIF = 0;
    POP_SFRS;
}//-----------------------------------------------------------------------------------------------------------
void BOD_ISR(void) interrupt 8           // Vector @  0x43
{
     PUSH_SFRS;
     clr_BODCON0_BOF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void SPI_ISR(void) interrupt 9           // Vector @  0x4B
{
    PUSH_SFRS;
    clr_SPSR_SPIF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void WDT_ISR(void) interrupt 10          // Vector @  0x53
{
    PUSH_SFRS;
    clr_WDCON_WDTF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void ADC_ISR(void) interrupt 11          // Vector @  0x5B
{
    PUSH_SFRS;
    clr_ADCCON0_ADCF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void Capture_ISR(void) interrupt 12      // Vector @  0x63
{
    PUSH_SFRS;
    clr_CAPCON0_CAPF0;
    clr_CAPCON0_CAPF1;
    clr_CAPCON0_CAPF2;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void PWM_Brake_ISR(void) interrupt 14    // Vector @  0x73
{
     PUSH_SFRS;
     clr_PWM0FBD_FBF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void UART1_ISR(void) interrupt 15               // Vector @  0x7B
{
    PUSH_SFRS;
    clr_SCON_1_RI_1;
    clr_SCON_1_TI_1;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void Timer3_ISR(void) interrupt 16          // Vector @  0x83
{
    PUSH_SFRS;
    clr_T3CON_TF3;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
void WKT_ISR(void) interrupt 17                 // Vector @  0x8B
{
    PUSH_SFRS;
    clr_WKCON_WKTF;
    POP_SFRS;
}
#endif

void Set_Interrupt_Priority_Level( unsigned char u8InterruptSource, unsigned char u8u8InterruptPriorityLevel)
{
   switch (u8InterruptSource)
   {
        case INT_INT0        :
          switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PX0; clr_IPH_PX0H; break;
            case 1:  clr_IP_PX0; set_IPH_PX0H; break;
            case 2:  set_IP_PX0; clr_IPH_PX0H; break;
            case 3:  clr_IP_PX0; set_IPH_PX0H; break;
          }
        case INT_BOD          :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PBOD; clr_IPH_PBODH; break;
            case 1:  clr_IP_PBOD; set_IPH_PBODH; break;
            case 2:  set_IP_PBOD; clr_IPH_PBODH; break;
            case 3:  set_IP_PBOD; set_IPH_PBODH; break;
          }
        case INT_WDT           :
               switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PWDT; clr_EIPH_PWDTH; break;
            case 1:  clr_EIP_PWDT; set_EIPH_PWDTH; break;
            case 2:  set_EIP_PWDT; clr_EIPH_PWDTH; break;
            case 3:  set_EIP_PWDT; set_EIPH_PWDTH; break;
          }        
        case INT_Timer0        :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PT0; clr_IPH_PT0H; break;
            case 1:  clr_IP_PT0; set_IPH_PT0H; break;
            case 2:  set_IP_PT0; clr_IPH_PT0H; break;
            case 3:  set_IP_PT0; set_IPH_PT0H; break;
          }
        case INT_I2C0          :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PI2C; clr_EIPH_PI2CH; break;
            case 1:  clr_EIP_PI2C; set_EIPH_PI2CH; break;
            case 2:  set_EIP_PI2C; clr_EIPH_PI2CH; break;
            case 3:  set_EIP_PI2C; set_EIPH_PI2CH; break;
          }
        case INT_ADC           :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PADC; clr_IPH_PADCH; break;
            case 1:  clr_IP_PADC; set_IPH_PADCH; break;
            case 2:  set_IP_PADC; clr_IPH_PADCH; break;
            case 3:  set_IP_PADC; set_IPH_PADCH; break;
          }        
        case INT_INT1        :
          switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PX1; clr_IPH_PX1H; break;
            case 1:  clr_IP_PX1; set_IPH_PX1H; break;
            case 2:  set_IP_PX1; clr_IPH_PX1H; break;
            case 3:  set_IP_PX1; set_IPH_PX1H; break;
          }
        case INT_PIT           :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PPI; clr_EIPH_PPIH; break;
            case 1:  clr_EIP_PPI; set_EIPH_PPIH; break;
            case 2:  set_EIP_PPI; clr_EIPH_PPIH; break;
            case 3:  set_EIP_PPI; set_EIPH_PPIH; break;
          }        
        case INT_Timer1        :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PT1; clr_IPH_PT1H; break;
            case 1:  clr_IP_PT1; set_IPH_PT1H; break;
            case 2:  set_IP_PT1; clr_IPH_PT1H; break;
            case 3:  set_IP_PT1; set_IPH_PT1H; break;
          }
        case INT_UART0         :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_IP_PS; clr_IPH_PSH; break;
            case 1:  clr_IP_PS; set_IPH_PSH; break;
            case 2:  set_IP_PS; clr_IPH_PSH; break;
            case 3:  set_IP_PS; set_IPH_PSH; break;
          }        
        case INT_PWM0_Brake :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PFB; clr_EIPH_PFBH; break;
            case 1:  clr_EIP_PFB; set_EIPH_PFBH; break;
            case 2:  set_EIP_PFB; clr_EIPH_PFBH; break;
            case 3:  set_EIP_PFB; set_EIPH_PFBH; break;
          }
        case INT_SPI0          :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PSPI; clr_EIPH_PSPIH; break;
            case 1:  clr_EIP_PSPI; set_EIPH_PSPIH; break;
            case 2:  set_EIP_PSPI; clr_EIPH_PSPIH; break;
            case 3:  set_EIP_PSPI; set_EIPH_PSPIH; break;
          }        
        case INT_Timer2        :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PT2; clr_EIPH_PT2H; break;
            case 1:  clr_EIP_PT2; set_EIPH_PT2H; break;
            case 2:  set_EIP_PT2; clr_EIPH_PT2H; break;
            case 3:  set_EIP_PT2; set_EIPH_PT2H; break;
          }         
        case INT_Capture       :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PCAP; clr_EIPH_PCAPH; break;
            case 1:  clr_EIP_PCAP; set_EIPH_PCAPH; break;
            case 2:  set_EIP_PCAP; clr_EIPH_PCAPH; break;
            case 3:  set_EIP_PCAP; set_EIPH_PCAPH; break;
          }
        case INT_PWM0          :                          
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PPWM; clr_EIPH_PPWMH; break;
            case 1:  clr_EIP_PPWM; set_EIPH_PPWMH; break;
            case 2:  set_EIP_PPWM; clr_EIPH_PPWMH; break;
            case 3:  set_EIP_PPWM; set_EIPH_PPWMH; break;
          }
        case INT_UART1         :
             switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PS_1; clr_EIPH1_PSH_1; break;
            case 1:  clr_EIP1_PS_1; set_EIPH1_PSH_1; break;
            case 2:  set_EIP1_PS_1; clr_EIPH1_PSH_1; break;
            case 3:  set_EIP1_PS_1; set_EIPH1_PSH_1; break;
          }        
        case INT_Timer3        :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PT3; clr_EIPH1_PT3H; break;
            case 1:  clr_EIP1_PT3; set_EIPH1_PT3H; break;
            case 2:  set_EIP1_PT3; clr_EIPH1_PT3H; break;
            case 3:  set_EIP1_PT3; set_EIPH1_PT3H; break;
          } 
        case INT_WKT           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PWKT; clr_EIPH1_PWKTH; break;
            case 1:  clr_EIP1_PWKT; set_EIPH1_PWKTH; break;
            case 2:  set_EIP1_PWKT; clr_EIPH1_PWKTH; break;
            case 3:  set_EIP1_PWKT; set_EIPH1_PWKTH; break;
          }
        case INT_PWM1           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PPWM1; clr_EIPH1_PPWM1H; break;
            case 1:  clr_EIP1_PPWM1; set_EIPH1_PPWM1H; break;
            case 2:  set_EIP1_PPWM1; clr_EIPH1_PPWM1H; break;
            case 3:  set_EIP1_PPWM1; set_EIPH1_PPWM1H; break;
          }
        case INT_PWM2           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PPWM2; clr_EIPH1_PPWM2H; break;
            case 1:  clr_EIP1_PPWM2; set_EIPH1_PPWM2H; break;
            case 2:  set_EIP1_PPWM2; clr_EIPH1_PPWM2H; break;
            case 3:  set_EIP1_PPWM2; set_EIPH1_PPWM2H; break;
          }
          case INT_PWM3           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PPWM3; clr_EIPH1_PPWM3H; break;
            case 1:  clr_EIP1_PPWM3; set_EIPH1_PPWM3H; break;
            case 2:  set_EIP1_PPWM3; clr_EIPH1_PPWM3H; break;
            case 3:  set_EIP1_PPWM3; set_EIPH1_PPWM3H; break;
          }
          case INT_SMC0           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP2_PSC0; clr_EIPH2_PSC0H; break;
            case 1:  clr_EIP2_PSC0; set_EIPH2_PSC0H; break;
            case 2:  set_EIP2_PSC0; clr_EIPH2_PSC0H; break;
            case 3:  set_EIP2_PSC0; set_EIPH2_PSC0H; break;
          }
         case INT_SMC1           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP2_PSC1; clr_EIPH2_PSC1H; break;
            case 1:  clr_EIP2_PSC1; set_EIPH2_PSC1H; break;
            case 2:  set_EIP2_PSC1; clr_EIPH2_PSC1H; break;
            case 3:  set_EIP2_PSC1; set_EIPH2_PSC1H; break;
          }
          case INT_SMC2           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP2_PSC2; clr_EIPH2_PSC2H; break;
            case 1:  clr_EIP2_PSC2; set_EIPH2_PSC2H; break;
            case 2:  set_EIP2_PSC2; clr_EIPH2_PSC2H; break;
            case 3:  set_EIP2_PSC2; set_EIPH2_PSC2H; break;
          }
        break;
   }
 }
