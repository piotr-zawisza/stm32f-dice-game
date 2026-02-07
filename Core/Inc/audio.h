/*
 * audio.h
 *
 *  Created on: Dec 8, 2025
 *      Author: user
 */

#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_

#include "stm32f4xx_hal.h"
#include "notes.h"

typedef enum {
	AUDIO_IDLE, AUDIO_PLAYING, AUDIO_GAP
} AudioState_t;

typedef struct {
    uint32_t frequency;
    uint32_t duration_ms;
} AudioNote_t;

void Audio_Init(TIM_HandleTypeDef* htim, uint32_t channel);
void Audio_Tick(void);
void Audio_PlayTone(uint32_t freq_hz, uint32_t duration_ms);
void Audio_Play(const uint32_t* melody, uint32_t size);

#endif /* INC_AUDIO_H_ */
