/*
 * animation.h
 *
 *  Created on: Dec 8, 2025
 *      Author: user
 */

#ifndef INC_ANIMATION_H_
#define INC_ANIMATION_H_

#include "stm32f4xx_hal.h"

typedef void (*Anim_UpdateCallback_t)(void *ctx);
typedef void (*Anim_DrawCallback_t)(void *ctx);

void Video_Init();
void SwapBuffers();
void Anim_Run(uint32_t frames, void *ctx, Anim_UpdateCallback_t onUpdate, Anim_DrawCallback_t onDraw);

#endif /* INC_ANIMATION_H_ */
