/****************************************************************************
 * boards/arm/gd32f4/gd32f470zk-eval/src/gd32f4xx_gpio.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <assert.h>
#include <debug.h>
#include <stdbool.h>

#include <nuttx/clock.h>
#include <nuttx/ioexpander/gpio.h>
#include <nuttx/wdog.h>

#include <arch/board/board.h>

#include "chip.h"

#include "gd32f303z_eval.h"
#include "gd32f30x.h"

#define GD32_GPIO_RCU_SHIFT 16
#define GD32_GPIO_RCU_MASK 0x00038000 // 3位
uint32_t gd32_gpio_rcu[] = {RCU_GPIOA, RCU_GPIOB, RCU_GPIOC, RCU_GPIOD,
                            RCU_GPIOE, RCU_GPIOF, RCU_GPIOG}

#define GD32_GPIO_PORT_SHIFT 13
#define GD32_GPIO_PORT_MASK 0x00007000 // 3位
uint32_t gd32_gpio_port[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG}

#define GD32_GPIO_MODE_SHIFT 10
#define GD32_GPIO_MODE_MASK 0x00001C00 // 3位
uint32_t gd32_gpio_mode[] = {GPIO_MODE_AIN,    GPIO_MODE_IN_FLOATING,
                             GPIO_MODE_IPD,    GPIO_MODE_IPU GPIO_MODE_OUT_OD,
                             GPIO_MODE_OUT_PP, GPIO_MODE_AF_OD,
                             GPIO_MODE_AF_PP}

#define GD32_GPIO_SPEED_SHIFT 8
#define GD32_GPIO_SPEED_MASK 0x00000300 // 2位
uint32_t gd32_gpio_speed[] = {GPIO_OSPEED_2MHZ, GPIO_OSPEED_10MHZ,
                              GPIO_OSPEED_50MHZ, GPIO_OSPEED_MAX}

#define GD32_GPIO_PIN_SHIFT 0
#define GD32_GPIO_PIN_MASK 0x000000FF // 8位
uint32_t gd32_gpio_pin[] = {GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,  GPIO_PIN_3,
                            GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,
                            GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,
                            GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15}

struct gd32gpio_dev_s {
  struct gpio_dev_s gpio;
  uint32_t pinconfig;
  uint8_t id;
};

uint32_t g_gpiooutputs[BOARD_NGPIOOUT] = {3 << GD32_GPIO_PIN_SHIFT |
                                          2 << GD32_GPIO_SPEED_SHIFT |
                                          4 << GD32_GPIO_MODE_SHIFT |
                                          4 << GD32_GPIO_PORT_SHIFT |
                                          4 << GD32_GPIO_RCU_SHIFT}

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int
gpio_setpintype(struct gpio_dev_s * dev, enum gpio_pintype_e gp_pintype);

static const struct gpio_operations_s gpout_ops = {
    .go_read = gpout_read,
    .go_write = gpout_write,
    .go_attach = NULL,
    .go_enable = NULL,
    .go_setpintype = gpio_setpintype,
};

static struct gd32gpio_dev_s g_gpout[BOARD_NGPIOOUT];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: gpio_setpintype
 *
 * Description:
 *   set gpio pintype.
 *
 ****************************************************************************/

static int gpio_setpintype(struct gpio_dev_s *dev,
                           enum gpio_pintype_e gpio_pintype) {}

static int gpout_read(struct gpio_dev_s *dev, bool *value) {}

static int gpout_write(struct gpio_dev_s *dev, bool value) {
  struct gd32gpio_dev_s *gd32gpio = (struct gd32gpio_dev_s *)dev;

  DEBUGASSERT(gd32gpio != NULL);
  gpioinfo("Writing %d\n", (int)value);

  uint32_t port = gd32_gpio_port[(gd32gpio->pinconfig & GD32_PORT_BIT_MASK) >>
                                 GD32_PORT_BIT_SHIFT];
  uint32_t pin = gd32_gpio_pin[(gd32gpio->pinconfig & GD32_PORT_MODE_MASK) >>
                               GD32_PORT_MODE_SHIFT];
  gpio_bit_write(port, pin, value);

  return OK;
}

int gd32_gpio_initialize(void) {
  int pincount = 0;
  int i;

  for (i = 0; i < BOARD_NGPIOOUT; i++) {
    /* Setup and register the GPIO pin */

    g_gpout[i].gpio.gp_pintype = GPIO_OUTPUT_PIN;
    g_gpout[i].gpio.gp_ops = &gpout_ops;
    g_gpout[i].pinconfig = g_gpiooutputs[i];
    g_gpout[i].id = i;

    gpio_pin_register(&g_gpout[i].gpio, pincount);

    uint32_t gpio_rcu = gd32_gpio_rcu[(gd32gpio->pinconfig & GD32_GPIO_RCU_MASK) >> GD32_GPIO_RCU_SHIFT];
    rcu_periph_clock_enable(gpio_rcu);
    pincount++;
  }

  return 0;
}
