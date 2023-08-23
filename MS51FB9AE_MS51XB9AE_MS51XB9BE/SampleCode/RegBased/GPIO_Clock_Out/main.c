/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"


/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main(void)
{
  
 /* Note
       MCU power on system clock is HIRC (16.0000MHz), if need change Fsys source pleaes copy hange system closk source demo
*/

    P11_PUSHPULL_MODE;                    /* P11 CLKO pin setting push pull mode to check output. */
    set_CKCON_CLOEN;                                  //System Clock Output Enable
/* Note */ 
/* Each time modify the HIRC must do re-power on process to confirm HIRC modified. */

#if 1
/* 16MHz HIRC clock out demo */
    MODIFY_HIRC(HIRC_166);
    CKDIV = 80;     /* Divider *2 */
#else 
/* 24MHz HIRC clock out demo */
    MODIFY_HIRC(HIRC_24);
    CKDIV = 120    /* Divider *2 */
#endif
/*Please measure P1.1 (CLKO) pin for system clock output, it should as system clock;    */
    while(1);

}

