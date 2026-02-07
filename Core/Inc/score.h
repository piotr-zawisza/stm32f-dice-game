/*
 * score.h
 *
 *  Created on: Jan 12, 2026
 *      Author: user
 */

#ifndef INC_SCORE_H_
#define INC_SCORE_H_

#include "stm32f429i_discovery.h"

typedef struct {
    uint32_t scoreValue;
    uint32_t maxTurns;
    uint32_t crcValue;
} ProtectedScore_t;

void UpdateHighScore(uint32_t newScore, uint32_t newMaxTurns);
uint8_t IsHighScoreValid(void);
void Score_SaveToBackup(void);
void Score_LoadFromBackup(void);

#endif /* INC_SCORE_H_ */
