/*
 * crc_drv.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#include "crc_drv.h"

uint32_t CRC_Calculate(uint32_t pBuffer[], uint32_t bufferLength) {
    return HAL_CRC_Calculate(&hcrc, pBuffer, bufferLength);
}

uint8_t CRC_CheckData(uint32_t pBuffer[], uint32_t totalLength) {
    if (totalLength < 2) return 0;

    uint32_t expectedCRC = pBuffer[totalLength - 1];
    uint32_t calculatedCRC = HAL_CRC_Calculate(&hcrc, pBuffer, totalLength - 1);

    if (calculatedCRC == expectedCRC) {
        return 1;
    } else {
        return 0;
    }
}
