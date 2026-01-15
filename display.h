#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "snake.h"

// Inicializa la pantalla
void Display_Init(I2C_HandleTypeDef *hi2c);

// Muestra un mensaje de enhorabuena por crear un nuevo record
void Display_NewRecord(uint32_t score);

// Muestra el mensaje de espera para empezar de nuevo
void Display_IDLE(uint32_t record);

// Actualiza el contenido visual basándose en el estado actual del juego
void Display_Update(Snake_t *snake, Food_t *food, uint32_t score);

// Muestra la pantalla de Game Over
void Display_GameOver(int finalScore);

//Muestra la puntuación final
void Display_Reset(uint32_t final_score);

#endif
