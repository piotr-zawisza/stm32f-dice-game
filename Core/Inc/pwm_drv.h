/*
 * pwm_drv.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#ifndef INC_PWM_DRV_H_
#define INC_PWM_DRV_H_

#include "stm32f4xx_hal.h"


void PWM_Start(TIM_HandleTypeDef* htim, uint32_t channel);
void PWM_SetPulseRaw(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t pulse);
void PWM_SetDutyCycle(TIM_HandleTypeDef* htim, uint32_t channel, float percent);
void PWM_Stop(TIM_HandleTypeDef* htim, uint32_t channel);


#endif /* INC_PWM_DRV_H_ */
