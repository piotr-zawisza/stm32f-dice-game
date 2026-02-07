/*
 * melody.h
 *
 *  Created on: Jan 14, 2026
 *      Author: user
 */

#ifndef INC_MELODY_H_
#define INC_MELODY_H_

#include "stm32f4xx_hal.h"
#include "notes.h"

const uint32_t startMelody[] = {
NOTE_B4, 200,
NOTE_NULL, 50,
NOTE_CS5, 200,
NOTE_NULL, 50,
NOTE_G4, 200,
NOTE_NULL, 100,
NOTE_E4, 120,
NOTE_NULL, 50,
NOTE_E4, 120,
NOTE_NULL, 50,
NOTE_E4, 120,
NOTE_NULL, 50,
NOTE_E4, 120,
NOTE_NULL, 50,
NOTE_E4, 120,
NOTE_NULL, 1500 };

const uint32_t rollMelody[] = {
NOTE_D4, 30, NOTE_NULL, 5,
NOTE_E4, 30, NOTE_NULL, 5,
NOTE_D4, 35, NOTE_NULL, 5,

NOTE_FS4, 55, NOTE_NULL, 5,
NOTE_G4, 65, NOTE_NULL, 5,
NOTE_D4, 95, NOTE_NULL, 5,

NOTE_E4, 125, NOTE_NULL, 5,
NOTE_FS4, 155, NOTE_NULL, 5,
NOTE_D4, 70,
NOTE_NULL, 2500
};

const uint32_t loseLifeMelody[] = {
NOTE_D4, 300,
NOTE_NULL, 50,
NOTE_D4, 600,
NOTE_NULL, 2500
};

const uint32_t winMelody[] = {
NOTE_D5, 100, NOTE_NULL, 20,
NOTE_FS5, 100, NOTE_NULL, 20,
NOTE_A5, 100, NOTE_NULL, 20,
NOTE_D6, 300,
NOTE_NULL, 2500
};

const uint32_t gameOverMelody[] = {
NOTE_G4, 300,
NOTE_NULL, 50,
NOTE_D4, 300,
NOTE_NULL, 50,
NOTE_B4, 300,
NOTE_NULL, 50,
NOTE_A4, 300,
NOTE_NULL, 50,
NOTE_G4, 300,
NOTE_NULL, 50,
NOTE_FS4, 600,
NOTE_NULL, 50,
NOTE_E4, 630,
NOTE_NULL, 2500
};

#endif /* INC_MELODY_H_ */
