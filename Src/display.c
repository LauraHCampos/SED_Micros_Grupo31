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
    lcd_clear(); // Limpia la pantalla para el nuevo frame

    // 1. Dibujar la comida como un punto '.'
    lcd_put_cur(food->position.y, food->position.x);
    lcd_send_string("."); //

    // 2. Dibujar la serpiente completa como guiones '-'
    // Usamos un bucle para recorrer todos los segmentos del cuerpo
    for (int i = 0; i < snake->length; i++) {
    	// Colocamos el cursor en la posición del segmento actual
		lcd_put_cur(snake->body[i].y, snake->body[i].x);

		// --- AQUÍ ESTÁ EL CAMBIO ---
		if (i == 0) {
			// ¡Es la cabeza! Comprobamos la dirección
			if (snake->direction == DIR_UP || snake->direction == DIR_DOWN) {
				lcd_send_string("|"); // Cabeza vertical
			} else {
				lcd_send_string("-"); // Cabeza horizontal
			}
		} else {
			// Es el cuerpo, siempre lo dibujamos igual
			lcd_send_string("-");
		}
    }

    // 3. Mostrar puntuación (Score)
    /*char buffer[10];
    sprintf(buffer, "S:%lu", score); //
    lcd_put_cur(0, 12); // Esquina superior derecha
    lcd_send_string(buffer);*/
}

void Display_GameOver(int score) {
    char buffer[16];

    lcd_clear();
    HAL_Delay(10); // Pausa de seguridad

    lcd_put_cur(0, 0);
    lcd_send_string("  GAME OVER!   ");

    // Mostramos aquí la puntuación final
    lcd_put_cur(1, 0);
    sprintf(buffer, "  PUNTOS: %d", score);
    lcd_send_string(buffer);
}
