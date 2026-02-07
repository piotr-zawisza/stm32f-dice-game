/*
 * adc_drv.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#include "adc_drv.h"

extern ADC_HandleTypeDef hadc1;

uint32_t ADC_GetRawValue() {
	uint32_t sum = 0;
	const uint8_t samples = 16;

	for (int i = 0; i < samples; i++) {
		HAL_ADC_Start(&hadc1);
		if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
			sum += HAL_ADC_GetValue(&hadc1);
		}
		HAL_ADC_Stop(&hadc1);
	}

	return sum / samples;
}

float ADC_GetVoltage(float vref) {
	uint32_t raw = ADC_GetRawValue(&hadc1);
	return (float) raw * vref / ADC_MAX_VALUE;
}

uint8_t ADC_GetPercentage() {
	uint32_t raw = ADC_GetRawValue(&hadc1);
	return (uint8_t) ((raw * 100) / (uint32_t) ADC_MAX_VALUE);
}
