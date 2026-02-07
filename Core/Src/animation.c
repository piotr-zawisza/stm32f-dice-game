/*
 * animation.c
 *
 *  Created on: Dec 8, 2025
 *      Author: user
 */

#include "animation.h"
#include "stm32f429i_discovery_lcd.h"

extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;
extern RNG_HandleTypeDef hrng;

uint32_t current_buffer = LCD_FOREGROUND_LAYER;
volatile uint8_t LTDC_ReadyToSwap = 0;

void Video_Init() {
	BSP_LCD_Init();

	BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER,
			LCD_FRAME_BUFFER + (240 * 320 * 4));

	BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, ENABLE);
	BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, DISABLE);

	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	current_buffer = LCD_BACKGROUND_LAYER;
}

void SwapBuffers() {
	HAL_DMA2D_PollForTransfer(&hdma2d, 100);
	HAL_LTDC_ProgramLineEvent(&hltdc, 0);

	uint32_t timeout = 100000;
	while (LTDC_ReadyToSwap == 0 && timeout > 0) timeout--;
	LTDC_ReadyToSwap = 0;

	if (current_buffer == LCD_FOREGROUND_LAYER) {
		BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, ENABLE);
		BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, DISABLE);
		BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
		current_buffer = LCD_BACKGROUND_LAYER;
	} else {
		BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, ENABLE);
		BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, DISABLE);
		BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
		current_buffer = LCD_FOREGROUND_LAYER;
	}

	HAL_LTDC_Reload(&hltdc, LTDC_RELOAD_VERTICAL_BLANKING);
}

void Anim_Run(uint32_t frames, void *ctx, Anim_UpdateCallback_t onUpdate,
		Anim_DrawCallback_t onDraw) {
	//SwapBuffers();
	for (uint32_t f = 0; f < frames; f++) {
		BSP_LCD_Clear(LCD_COLOR_BLACK);
		if (onUpdate)
			onUpdate(ctx);
		if (onDraw) {
			onDraw(ctx);
			SwapBuffers();
		}
	}
	//SwapBuffers();
}

void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc) {
	LTDC_ReadyToSwap = 1;
}
