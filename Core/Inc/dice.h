/*
 * dice.h
 *
 *  Created on: Nov 25, 2025
 *      Author: Student
 */

#ifndef INC_DICE_H_
#define INC_DICE_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

void Dice_UpdateLogic(void* ctx);
void Dice_DrawLogic(void* ctx);

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t size;
    uint32_t bgColor;
    uint32_t dotColor;
    uint8_t  value;
    uint8_t isLocked;

    uint16_t _dotRadius;
} Dice_t;

typedef struct {
    Dice_t** dices;
    uint8_t count;
    uint16_t* origX;
    uint16_t* origY;
} DiceContext_t;

typedef struct {
    uint32_t points;
    const char* name;
} ScoreResult_t;

void Dice_Init(Dice_t* me, uint16_t x, uint16_t y, uint16_t size, uint32_t bgCol, uint32_t dotCol);
void Dice_SetValue(Dice_t* me, uint8_t value);
void DrawLifeIndicator(uint16_t x, uint16_t y, int8_t livesCount);
void Dice_Draw(Dice_t* me);
void Dice_UpdateLogic(void* ctx);
void Dice_DrawLogic(void* ctx);
void Dice_RestoreOrigin(void* ctx);
ScoreResult_t Dice_CalculateScore(void *ctx);

#endif /* INC_DICE_H_ */
