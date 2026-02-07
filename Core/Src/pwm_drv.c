/*
 * pwm_drv.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#include "pwm_drv.h"

void PWM_Start(TIM_HandleTypeDef* htim, uint32_t channel) {
    HAL_TIM_PWM_Start(htim, channel);
}

void PWM_SetPulseRaw(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t pulse) {
    __HAL_TIM_SET_COMPARE(htim, channel, pulse);
}

void PWM_SetDutyCycle(TIM_HandleTypeDef* htim, uint32_t channel, float percent) {
    if (percent > 100.0f) percent = 100.0f;

    uint32_t period = __HAL_TIM_GET_AUTORELOAD(htim);

    uint32_t pulse = (uint32_t)((float)period * (percent / 100.0f));
    PWM_SetPulseRaw(htim, channel, pulse);
}

void PWM_Stop(TIM_HandleTypeDef* htim, uint32_t channel) {
    HAL_TIM_PWM_Stop(htim, channel);
}
