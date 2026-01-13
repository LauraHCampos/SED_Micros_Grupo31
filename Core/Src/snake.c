#include "snake.h"
#include <stdlib.h> // Necesario para la función rand()

// Inicializa la serpiente en el centro del tablero
void Snake_Init(Snake_t *snake) {
    snake->length = 1;
    // La posicion (7,0) es casi el centro de la primera fila
    snake->body[0].x = 7;
    snake->body[0].y = 0;

    // IMPORTANTE: Empezar moviéndose a la derecha para no chocar con bordes X o Y
    snake->direction = DIR_RIGHT;
}

// Mueve la serpiente actualizando cada segmento del cuerpo [cite: 91, 93]
void Snake_Move(Snake_t *snake) {
    // 1. Guardamos la posición que tiene la cola actualmente
    uint8_t tail_x = snake->body[snake->length - 1].x;
    uint8_t tail_y = snake->body[snake->length - 1].y;

    // 2. Movemos el cuerpo normalmente
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // 3. Movemos la cabeza
    switch (snake->direction) {
        case DIR_UP:    snake->body[0].y--; break;
        case DIR_DOWN:  snake->body[0].y++; break;
        case DIR_LEFT:  snake->body[0].x--; break;
        case DIR_RIGHT: snake->body[0].x++; break;
    }

    // 4. Si teníamos comida pendiente, añadimos el segmento en la vieja posición de la cola
    if (snake->pending_growth > 0 && snake->length < MAX_SNAKE_LEN) {
        snake->body[snake->length].x = tail_x;
        snake->body[snake->length].y = tail_y;
        snake->length++;           // Ahora sí aumentamos el tamaño real
        snake->pending_growth--;   // Consumimos el crecimiento pendiente
    }
}

// Genera comida en una posición aleatoria [cite: 91]
void Snake_SpawnFood(Food_t *food, Snake_t *snake) {
    int valid = 0;

    while (!valid) {
        // Generar coordenadas aleatorias dentro del LCD 16x2
        food->position.x = rand() % 16;
        food->position.y = rand() % 2;

        // Opcional: Verificar que la comida no aparezca encima del cuerpo de la serpiente
        valid = 1;
        for (int i = 0; i < snake->length; i++) {
            if (food->position.x == snake->body[i].x && food->position.y == snake->body[i].y) {
                valid = 0; // Si aparece encima, repetimos el bucle
                break;
            }
        }
    }
}

// Comprueba si la serpiente ha chocado (Condición de derrota) [cite: 39, 92, 102]
uint8_t Snake_CheckCollision(Snake_t *snake) {
    int headX = snake->body[0].x;
    int headY = snake->body[0].y;

    // Límites para una pantalla LCD 16x2
    if (headX < 0 || headX >= 16 || headY < 0 || headY >= 2) {
        return 1; // Choque con pared
    }

    // Comprobar si choca con su propio cuerpo (solo si length > 1)
    for (int i = 1; i < snake->length; i++) {
        if (headX == snake->body[i].x && headY == snake->body[i].y) {
            return 1; // Choque con sigo misma
        }
    }

    return 0;
}

// Comprueba si la cabeza alcanza la comida para aumentar longitud y puntos [cite: 91, 101]
uint8_t Snake_EatFood(Snake_t *snake, Food_t *food) {
    if (snake->body[0].x == food->position.x && snake->body[0].y == food->position.y) {
        // En lugar de crecer aquí, anotamos que tenemos un crecimiento pendiente
        snake->pending_growth++;
        return 1;
    }
    return 0;
}

