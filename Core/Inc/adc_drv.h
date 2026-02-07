/*
 * adc_drv.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#ifndef INC_ADC_DRV_H_
#define INC_ADC_DRV_H_

#include "stm32f4xx_hal.h"

#define ADC_MAX_VALUE 4095.0f


uint32_t ADC_GetRawValue();
float ADC_GetVoltage(float vref);
uint8_t ADC_GetPercentage();

#endif /* INC_ADC_DRV_H_ */
