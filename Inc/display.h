#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "snake.h"

// Inicializa la pantalla
void Display_Init(I2C_HandleTypeDef *hi2c);

// Actualiza el contenido visual basándose en el estado actual del juego
void Display_Update(Snake_t *snake, Food_t *food, uint32_t score);

// Muestra la pantalla de Game Over y la puntuación final 
void Display_GameOver(int finalScore);

#endif
