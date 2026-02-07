/*
 * rtc_drv.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#ifndef INC_RTC_DRV_H_
#define INC_RTC_DRV_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>

void RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec);
void RTC_SetDate(uint8_t weekday, uint8_t day, uint8_t month, uint8_t year);
void RTC_GetTimeStr(char* buffer);


#endif /* INC_RTC_DRV_H_ */
