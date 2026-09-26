/*
* This file is part of INAV Project.
*
* INAV Project is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* INAV Project is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with INAV Project.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdint.h>

#include "platform.h"

#include "fc/fc_msp_box.h"
#include "fc/config.h"

#include "io/piniobox.h"

#include "drivers/timer.h"
#include "drivers/bus.h"
#include "drivers/sensor.h"
#include "drivers/io.h"
#include "drivers/pwm_mapping.h"

BUSDEV_REGISTER_SPI_TAG(busdev_mpu6500_1, DEVHW_MPU6500, MPU6500_1_SPI_BUS, MPU6500_1_CS_PIN, MPU6500_1_EXTI_PIN, 0, DEVFLAGS_NONE, IMU_MPU6500_1_ALIGN);
BUSDEV_REGISTER_SPI_TAG(busdev_mpu6500_2, DEVHW_MPU6500, MPU6500_2_SPI_BUS, MPU6500_2_CS_PIN, MPU6500_2_EXTI_PIN, 1, DEVFLAGS_NONE, IMU_MPU6500_2_ALIGN);


timerHardware_t timerHardware[] = {
    // INAV assigns motor/servo per timer, not per pad. S1 sits alone on TIM3 so
    // it can be the single motor of a wing while S2-S8 stay servos. S7/S8 share
    // a DMA stream (TIM1 N-channels), which only matters for DShot on both.
    DEF_TIM(TIM3, CH3,  PC8, TIM_USE_OUTPUT_AUTO, 0, 0), // S1  TIM3  DMA1 S7
    DEF_TIM(TIM8, CH1,  PC6, TIM_USE_OUTPUT_AUTO, 0, 0), // S2  TIM8  DMA2 S2
    DEF_TIM(TIM8, CH4,  PC9, TIM_USE_OUTPUT_AUTO, 0, 0), // S3  TIM8  DMA2 S7
    DEF_TIM(TIM8, CH2,  PC7, TIM_USE_OUTPUT_AUTO, 0, 0), // S4  TIM8  DMA2 S3
    DEF_TIM(TIM4, CH1,  PB6, TIM_USE_OUTPUT_AUTO, 0, 0), // S5  TIM4  DMA1 S0
    DEF_TIM(TIM4, CH2,  PB7, TIM_USE_OUTPUT_AUTO, 0, 0), // S6  TIM4  DMA1 S3
    DEF_TIM(TIM1, CH3N, PB1, TIM_USE_OUTPUT_AUTO, 0, 0), // S7  TIM1  DMA2 S6
    DEF_TIM(TIM1, CH2N, PB0, TIM_USE_OUTPUT_AUTO, 0, 0), // S8  TIM1  DMA2 S6
    DEF_TIM(TIM2, CH2,  PA1, TIM_USE_LED, 0, 0),         // LED TIM2  DMA1 S6
};

const int timerHardwareCount = sizeof(timerHardware) / sizeof(timerHardware[0]);
