/*
 * crc_drv.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#ifndef INC_CRC_DRV_H_
#define INC_CRC_DRV_H_

#include "stm32f4xx_hal.h"

extern CRC_HandleTypeDef hcrc;

uint32_t CRC_Calculate(uint32_t pBuffer[], uint32_t bufferLength);
uint8_t CRC_CheckData(uint32_t pBuffer[], uint32_t totalLength);

#endif /* INC_CRC_DRV_H_ */
