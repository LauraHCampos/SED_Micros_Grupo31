#include "display.h"
#include "i2c-lcd.h"
#include <stdio.h>

void Display_Init(I2C_HandleTypeDef *hi2c) {
    lcd_init();
    lcd_clear();
    lcd_put_cur(0, 3);
    lcd_send_string("SNAKE SED"); // Mensaje de inicio
}

void Display_Update(Snake_t *snake, Food_t *food, uint32_t score) {
    lcd_clear();

    // Dibujar la comida [cite: 13]
    lcd_put_cur(food->position.y, food->position.x);
    lcd_send_string("O");

    // Dibujar la cabeza de la serpiente [cite: 12]
    lcd_put_cur(snake->body[0].y, snake->body[0].x);
    lcd_send_string("X");

    // Mostrar puntuación en una parte de la pantalla [cite: 39, 47, 51]
    char buffer[10];
    sprintf(buffer, "S:%lu", score);
    lcd_put_cur(0, 12);
    lcd_send_string(buffer);
}

void Display_GameOver(uint32_t finalScore) {
    lcd_clear();
    lcd_put_cur(0, 3);
    lcd_send_string("GAME OVER"); // Indicación clara de estado

    char buffer[16];
    sprintf(buffer, "Puntos: %lu", finalScore); // Mostrar resultado [cite: 47]
    lcd_put_cur(1, 2);
    lcd_send_string(buffer);
}
