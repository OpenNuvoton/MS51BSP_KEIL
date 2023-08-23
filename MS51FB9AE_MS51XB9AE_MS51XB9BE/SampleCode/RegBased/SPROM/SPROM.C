/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k.h"
#include "sprom.h"

unsigned char  SPTEMP=1;

void SPROM_CODE (void)
{
  GPIO_LED ^= 1;
  SPTEMP++;

}
