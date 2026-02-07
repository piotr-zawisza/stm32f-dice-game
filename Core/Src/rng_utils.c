/*
 * rng_utils.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#include "rng_utils.h"

extern RNG_HandleTypeDef hrng;

int32_t RNG_GetValue(int32_t min, int32_t max) {
	uint32_t randomNum = 0;

    if (HAL_RNG_GenerateRandomNumber(&hrng, &randomNum) != HAL_OK) {
        return min;
    }

    return (randomNum % (max - min + 1)) + min;
}
