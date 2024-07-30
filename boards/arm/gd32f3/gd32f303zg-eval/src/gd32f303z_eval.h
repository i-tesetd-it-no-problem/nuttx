/****************************************************************************
 * boards/arm/gd32f4/gd32f470zk-eval/src/gd32f470z_eval.h
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

#ifndef __BOARDS_ARM_GD32F4_GD32F470ZK_EVAL_SRC_GD32F470Z_EVAL_H
#define __BOARDS_ARM_GD32F4_GD32F470ZK_EVAL_SRC_GD32F470Z_EVAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

#define GD32_PROCFS_MOUNTPOINT "/proc"

#define BOARD_NGPIOOUT 1

int gd32_bringup(void);

int gd32_gpio_initialize(void);

#endif /* __BOARDS_ARM_GD32F4_GD32F470ZK_EVAL_SRC_GD32F470Z_EVAL_H */
