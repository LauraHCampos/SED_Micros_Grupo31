#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "snake.h"

void Display_Init(I2C_HandleTypeDef *hi2c);

void Display_Update(Snake_t *snake, Food_t *food, uint32_t score);

void Display_GameOver(uint32_t finalScore);

#endif

