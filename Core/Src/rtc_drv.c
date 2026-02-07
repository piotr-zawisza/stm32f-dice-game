/*
 * rtc_drv.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Student
 */

#include "rtc_drv.h"

extern RTC_HandleTypeDef hrtc;

void RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec) {
    RTC_TimeTypeDef sTime = {0};
    sTime.Hours = hour;
    sTime.Minutes = min;
    sTime.Seconds = sec;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void RTC_SetDate(uint8_t weekday, uint8_t day, uint8_t month, uint8_t year) {
    RTC_DateTypeDef sDate = {0};
    sDate.WeekDay = weekday;
    sDate.Month = month;
    sDate.Date = day;
    sDate.Year = year;

    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RTC_GetTimeStr(char* buffer) {
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    sprintf(buffer, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
}
