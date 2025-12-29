#ifndef INC_SOUND_H_
#define INC_SOUND_H_

#include "main.h"

// Frecuencias para diferentes notas (en Hz)
#define NOTE_BEEP  1000  // Tono para cuando come
#define NOTE_FAIL  200   // Tono grave para cuando choca


// Prototipos de funciones
void Sound_Init(TIM_HandleTypeDef *htim);
void Sound_Play(uint32_t frequency, uint32_t duration_ms);
void Sound_Stop(void);

#endif
