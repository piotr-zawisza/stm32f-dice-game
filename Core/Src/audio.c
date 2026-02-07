/*
 * audio.c
 *
 *  Created on: Dec 8, 2025
 *      Author: user
 */

#include "audio.h"
#include "pwm_drv.h"

static TIM_HandleTypeDef *_audioHtim = NULL;
static uint32_t _audioChannel = 0;
volatile uint32_t Audio_RemainingTime = 0;
static uint8_t _audioVolume = 50; // 0-50

static volatile uint32_t _audioTimer = 0;
static const uint32_t *_melodyPtr = NULL;
static uint32_t _melodySize = 0;
static uint32_t _melodyIndex = 0;

AudioState_t _audioState = AUDIO_IDLE;

void Audio_Init(TIM_HandleTypeDef *htim, uint32_t channel) {
	_audioHtim = htim;
	_audioChannel = channel;
}

static void _Audio_SetFrequency(uint32_t freq_hz) {
	if (freq_hz == 0)
		return;

	uint32_t period = (7200000 / freq_hz) - 1;

	if (period > 65535)
		period = 65535;

	uint32_t pulse = (period * _audioVolume) / 100;
	__HAL_TIM_SET_AUTORELOAD(_audioHtim, period);
	__HAL_TIM_SET_COMPARE(_audioHtim, _audioChannel, pulse);
}

void Audio_Tick(void) {
	if (_audioTimer > 0) {
		_audioTimer--;
		return;
	}

	if (_audioState == AUDIO_PLAYING) {
		__HAL_TIM_SET_COMPARE(_audioHtim, _audioChannel, 0);
		_audioTimer = 5;
		_audioState = AUDIO_GAP;
		return;
	}

	if (_audioState == AUDIO_GAP || _audioState == AUDIO_IDLE) {
		if (_melodyPtr == NULL || _melodyIndex >= _melodySize) {
			if (_audioState != AUDIO_IDLE) {
				HAL_TIM_PWM_Stop(_audioHtim, _audioChannel);
				_audioState = AUDIO_IDLE;
			}
			return;
		}

		uint32_t freq = _melodyPtr[_melodyIndex];
		uint32_t duration = _melodyPtr[_melodyIndex + 1];

		if (freq > 0) {
			_Audio_SetFrequency(freq);
			_audioTimer = duration;
			_audioState = AUDIO_PLAYING;
			HAL_TIM_PWM_Start(_audioHtim, _audioChannel);
		} else {
			__HAL_TIM_SET_COMPARE(_audioHtim, _audioChannel, 0);
			_audioTimer = duration;
			_audioState = AUDIO_GAP;
		}
		_melodyIndex += 2;
	}
}

void Audio_PlayTone(uint32_t freq_hz, uint32_t duration_ms) {
	if (_audioHtim == NULL || freq_hz == 0)
		return;

	_melodyPtr = NULL;
	_melodySize = 0;

	_Audio_SetFrequency(freq_hz);
	PWM_Start(_audioHtim, _audioChannel);

	_audioTimer = duration_ms;
	_audioState = AUDIO_PLAYING;
}

void Audio_Play(const uint32_t* melody, uint32_t size) {
	if (_audioHtim == NULL)
		return;

	HAL_TIM_PWM_Stop(_audioHtim, _audioChannel);

	_melodyPtr = melody;
	_melodySize = size;
	_melodyIndex = 0;
	_audioTimer = 0;
	_audioState = AUDIO_IDLE;
}
