/*
 * dice.c
 *
 *  Created on: Nov 25, 2025
 *      Author: Student
 */

#include "dice.h"
#include "stm32f429i_discovery_lcd.h"
#include "rng_utils.h"
#include "stdio.h"

#define SCORE_YAHTZEE 50
#define SCORE_FULL    25
#define SCORE_SMALL_S 30
#define SCORE_LARGE_S 40

extern RNG_HandleTypeDef hrng;
extern DMA2D_HandleTypeDef hdma2d;

void Dice_Init(Dice_t *me, uint16_t x, uint16_t y, uint16_t size,
		uint32_t bgCol, uint32_t dotCol) {
	me->x = x;
	me->y = y;
	me->size = size;
	me->bgColor = bgCol;
	me->dotColor = dotCol;
	me->value = 1;
	me->_dotRadius = size / 10;
	me->isLocked = 0;
}

void Dice_SetValue(Dice_t *me, uint8_t value) {
	if (value >= 1 && value <= 6)
		me->value = value;
}

static void DrawDot(uint16_t x, uint16_t y, uint16_t r, uint32_t col) {
	BSP_LCD_SetTextColor(col);
	BSP_LCD_FillCircle(x, y, r);
}

void DrawLifeIndicator(uint16_t x, uint16_t y, int8_t livesCount) {
	uint16_t size = 32;
	uint16_t radius = size / 4;
	char buf[5];
	sprintf(buf, "%d", livesCount);

	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillCircle(x + size / 4, y + size / 4, size / 4);
	BSP_LCD_FillCircle(x + 3 * size / 4, y + size / 4, size / 4);
	Point points[3];
	points[0].X = x;
	points[0].Y = y + radius + 2;

	points[1].X = x + size;
	points[1].Y = y + radius + 2;

	points[2].X = x + size / 2;
	points[2].Y = y + size;

	BSP_LCD_FillPolygon(points, 3);

	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(x + 11, y + 9, (uint8_t*) buf, LEFT_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
}

void Dice_Draw(Dice_t *me) {
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
	BSP_LCD_FillRect(me->x + 4, me->y + 4, me->size, me->size);

	if (me->isLocked) {
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	} else {
		BSP_LCD_SetTextColor(me->bgColor);
	}
	BSP_LCD_FillRect(me->x, me->y, me->size, me->size);

	if (me->isLocked) {
		BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
	} else {
		BSP_LCD_SetTextColor(me->dotColor);
	}
	BSP_LCD_DrawRect(me->x, me->y, me->size, me->size);

	uint16_t cx = me->x + me->size / 2;
	uint16_t cy = me->y + me->size / 2;

	uint16_t lx = me->x + me->size / 4;
	uint16_t rx = me->x + me->size * 3 / 4;

	uint16_t ty = me->y + me->size / 4;
	uint16_t by = me->y + me->size * 3 / 4;

	uint16_t r = me->_dotRadius;
	uint32_t col = me->isLocked ? LCD_COLOR_DARKGRAY : me->dotColor;

	if (me->value % 2 != 0)
		DrawDot(cx, cy, r, col); // 1, 3, 5
	if (me->value >= 2) {
		DrawDot(lx, ty, r, col);
		DrawDot(rx, by, r, col);
	}
	if (me->value >= 4) {
		DrawDot(rx, ty, r, col);
		DrawDot(lx, by, r, col);
	}
	if (me->value == 6) {
		DrawDot(lx, cy, r, col);
		DrawDot(rx, cy, r, col);
	}
}

void Dice_UpdateLogic(void *ctx) {
	DiceContext_t *data = (DiceContext_t*) ctx;
	for (int i = 0; i < data->count; i++) {
		if (data->dices[i]->isLocked)
			continue;

		int32_t jitterX = RNG_GetValue(-6, 6);
		int32_t jitterY = RNG_GetValue(-6, 6);

		int16_t newX = data->origX[i] + jitterX;
		int16_t newY = data->origY[i] + jitterY;

		if (newX < 0)
			newX = 0;
		if (newY < 0)
			newY = 0;

		if (newX > 240 - data->dices[i]->size)
			newX = 240 - data->dices[i]->size;
		if (newY > 320 - data->dices[i]->size)
			newY = 320 - data->dices[i]->size;

		data->dices[i]->x = newX;
		data->dices[i]->y = newY;

		Dice_SetValue(data->dices[i], RNG_GetValue(1, 6));
	}
}

void Dice_DrawLogic(void *ctx) {
	DiceContext_t *data = (DiceContext_t*) ctx;
	for (int i = 0; i < data->count; i++) {
		Dice_Draw(data->dices[i]);
		Dice_Draw(data->dices[i]);
	}
}

void Dice_RestoreOrigin(void *ctx) {
	DiceContext_t *data = (DiceContext_t*) ctx;
	for (int i = 0; i < data->count; i++) {
		data->dices[i]->x = data->origX[i];
		data->dices[i]->y = data->origY[i];
	}
}

ScoreResult_t Dice_CalculateScore(void *ctx) {
	DiceContext_t *data = (DiceContext_t*) ctx;
	uint8_t counts[7] = { 0 };
	uint32_t totalSum = 0;
	ScoreResult_t result = { 0, "NONE" };

	for (int i = 0; i < data->count; i++) {
		uint8_t val = data->dices[i]->value;
		if (val >= 1 && val <= 6) {
			counts[val]++;
		}
		totalSum += val;
	}

	for (int i = 1; i <= 6; i++) {
		if (counts[i] == 5) {
			result.points = SCORE_YAHTZEE;
			result.name = "GENERAL";
			return result;
		}
	}

	uint8_t hasThree = 0, hasTwo = 0;
	for (int i = 1; i <= 6; i++) {
		if (counts[i] == 3)
			hasThree = 1;
		if (counts[i] == 2)
			hasTwo = 1;
	}
	if (hasThree && hasTwo) {
		result.points = SCORE_FULL;
		result.name = "FULL";
		return result;
	}

	uint8_t consecutive = 0;
	uint8_t maxConsecutive = 0;
	for (int i = 1; i <= 6; i++) {
		if (counts[i] > 0) {
			consecutive++;
			if (consecutive > maxConsecutive)
				maxConsecutive = consecutive;
		} else {
			consecutive = 0;
		}
	}

	if (maxConsecutive == 5) {
		result.points = SCORE_LARGE_S;
		result.name = "BIG STREET";
		return result;
	}
	if (maxConsecutive == 4) {
		result.points = SCORE_SMALL_S;
		result.name = "SMALL STREET";
		return result;
	}

	result.points = totalSum;
	result.name = "SUM";
	return result;
}
