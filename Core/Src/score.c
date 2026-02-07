/*
 * score.c
 *
 *  Created on: Jan 12, 2026
 *      Author: user
 */

#include "stm32f429i_discovery.h"
#include "score.h"
#include "crc_drv.h"
#include "rtc_drv.h"

#define BKUP_SCORE_VAL_REG RTC_BKP_DR0
#define BKUP_SCORE_CRC_REG RTC_BKP_DR1
#define BKUP_TURNS_REG     RTC_BKP_DR2

extern RTC_HandleTypeDef hrtc;

ProtectedScore_t g_HighScoreProtected;

void UpdateHighScore(uint32_t newScore, uint32_t newMaxTurns) {
	g_HighScoreProtected.scoreValue = newScore;
	g_HighScoreProtected.maxTurns = newMaxTurns;

	uint32_t dataToCheck[2] = { g_HighScoreProtected.scoreValue,
			g_HighScoreProtected.maxTurns };
	g_HighScoreProtected.crcValue = CRC_Calculate(dataToCheck, 2);
}

uint8_t IsHighScoreValid(void) {
	uint32_t dataBuffer[3];
	dataBuffer[0] = g_HighScoreProtected.scoreValue;
	dataBuffer[1] = g_HighScoreProtected.maxTurns;
	dataBuffer[2] = g_HighScoreProtected.crcValue;

	return CRC_CheckData(dataBuffer, 3);
}

void Score_SaveToBackup(void) {
	HAL_RTCEx_BKUPWrite(&hrtc, BKUP_SCORE_VAL_REG,
			g_HighScoreProtected.scoreValue);
	HAL_RTCEx_BKUPWrite(&hrtc, BKUP_TURNS_REG, g_HighScoreProtected.maxTurns);
	HAL_RTCEx_BKUPWrite(&hrtc, BKUP_SCORE_CRC_REG,
			g_HighScoreProtected.crcValue);
}

void Score_LoadFromBackup(void) {
	g_HighScoreProtected.scoreValue = HAL_RTCEx_BKUPRead(&hrtc,
			BKUP_SCORE_VAL_REG);
	g_HighScoreProtected.maxTurns = HAL_RTCEx_BKUPRead(&hrtc, BKUP_TURNS_REG);
	g_HighScoreProtected.crcValue = HAL_RTCEx_BKUPRead(&hrtc,
			BKUP_SCORE_CRC_REG);
}
