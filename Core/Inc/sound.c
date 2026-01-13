#include "sound.h"

extern TIM_HandleTypeDef htim3; // El temporizador que configuraste en PB0

void Sound_Init(TIM_HandleTypeDef *htim) {
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
    Sound_Stop(); // Empezar en silencio
}

void Sound_Play(uint32_t frequency, uint32_t duration_ms) {
    if (frequency == 0) return;

    // Calcular el ARR para la frecuencia deseada
    // Formula: ARR = (Frecuencia_Timer / (Prescaler * Frecuencia_Deseada)) - 1
    // Para 84MHz y PSC de 83:
    uint32_t arr = (1000000 / frequency) - 1;

    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr / 2); // 50% duty cycle para el tono

    HAL_Delay(duration_ms);
    Sound_Stop();
}

void Sound_Stop(void) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0); // Silencio
}
