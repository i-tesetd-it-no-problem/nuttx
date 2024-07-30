/****************************************************************************
 * arch/arm/include/gd32f3/chip.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_INCLUDE_GD32F3_CHIP_H
#define __ARCH_ARM_INCLUDE_GD32F3_CHIP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/
/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* Check the GD32F3 family configuration.
 * It must be done in arch/arm/src/gd32f3/Kconfig !
 */

#  define GD32_NGPIO_PORTS              7   /* GPIOA-G */
#  define GD32_NCRC                     1   /* CRC calculation unit */
// #  define GD32_NTRNG                    1   /* True random number generator (RNG) */ 
#  define GD32_NDMA                     2   /* DMA0,1 */
// #  define GD32_NIPA                     1   /* Image processing accelerator */
// #  define GD32_NIREF                    1   /* Programmable current reference */
#  define GD32_NADC                     3   /* 12-bit ADC0-2, 18 channels */
#  define GD32_NDAC                     1   /* 12-bit DAC0,1 */
#  define GD32_NATIMER                  2   /* Two advanced timers TIMER0 and 7 that support DMA */
#  define GD32_NGTIMER                  2   /* 16-bit general timers TIMER2 and 3
#  define GD32_NGTIMNDMA                10   /* 16-bit general timers TIMER 1-4 that support DMA 8-13 that not support DMA */
#  define GD32_NBTIMER                  2   /* Two basic timers, TIMER5,6 that support DMA */
#  define GD32_NUSART                   5   /* USART0-2 UART 3,4*/
#  define GD32_NI2C                     2   /* I2C0-1 */
#  define GD32_NSPI                     3   /* SPI0-2 */
#  define GD32_NI2S                     2   /* I2S1-2 (multiplexed with SPI1-2) */
// #  define GD32_NDCI                     1   /* Digital camera interface (DCI) */
// #  define GD32_NTLI                     1   /* TFT-LCD interface (TLI) */
#  define GD32_NSDIO                    1   /* Secure digital input/output interface */
#  define GD32_NEXMC                    1   /* External memory controller */
#  define GD32_NCAN                     1   /* CAN0*/
// #  define GD32_NETHERNET                1   /* 10/100 Ethernet MAC */
#  define GD32_NUSBFS                   1   /* USB FS*/
// #  define GD32_NUSBHS                   1   /* USB HS*/


/* Get customizations for each supported chip and provide alternate function
 * pin-mapping
 *
 * NOTE: Each GPIO pin may serve either for general purpose I/O or for a
 * special alternate function (such as USART, CAN, USB, SDIO, etc.).  That
 * particular pin-mapping will depend on the package and GD32 family.  If
 * you are incorporating a new GD32 chip into NuttX, you will need to add
 * the pin-mapping to a header file and to include that header file below.
 * The chip-specific pin-mapping is defined in the chip datasheet.
 */

/* NVIC priority levels *****************************************************/

#define NVIC_SYSH_PRIORITY_MIN     0b1111 /* All bits set in minimum priority */
#define NVIC_SYSH_PRIORITY_DEFAULT 0b1100 /* Midpoint is the default */
#define NVIC_SYSH_PRIORITY_MAX     0b0000 /* Zero is maximum priority */
#define NVIC_SYSH_PRIORITY_STEP    0x0011 /* Four bits of interrupt priority used */

#endif /* __ARCH_ARM_INCLUDE_GD32F3_CHIP_H */
