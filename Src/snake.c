#include "snake.h"
#include <stdlib.h> // Necesario para la función rand()

// Inicializa la serpiente en el centro del tablero
void Snake_Init(Snake_t *snake) {
    snake->length = 3;             // Longitud inicial [cite: 46]
    snake->direction = DIR_RIGHT;  // Dirección inicial [cite: 93]

    // Posición inicial del cuerpo (centro aproximado)
    for(uint8_t i = 0; i < snake->length; i++) {
        snake->body[i].x = (BOARD_WIDTH / 2) - i;
        snake->body[i].y = BOARD_HEIGHT / 2;
    }
}

// Mueve la serpiente actualizando cada segmento del cuerpo [cite: 91, 93]
void Snake_Move(Snake_t *snake) {
    // Desplazar cada segmento a la posición del anterior (de cola a cabeza)
    for (int8_t i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // Mover la cabeza según la dirección actual [cite: 93]
    switch (snake->direction) {
        case DIR_UP:    snake->body[0].y--; break;
        case DIR_DOWN:  snake->body[0].y++; break;
        case DIR_LEFT:  snake->body[0].x--; break;
        case DIR_RIGHT: snake->body[0].x++; break;
    }
}

// Genera comida en una posición aleatoria [cite: 91]
void Snake_SpawnFood(Food_t *food, Snake_t *snake) {
    uint8_t valid = 0;
    while (!valid) {
        food->position.x = rand() % BOARD_WIDTH;
        food->position.y = rand() % BOARD_HEIGHT;
        valid = 1;

        // Evitar que la comida aparezca encima del cuerpo de la serpiente
        for (uint8_t i = 0; i < snake->length; i++) {
            if (food->position.x == snake->body[i].x && food->position.y == snake->body[i].y) {
                valid = 0;
                break;
            }
        }
    }
    food->isSpawned = 1;
}

// Comprueba si la serpiente ha chocado (Condición de derrota) [cite: 39, 92, 102]
uint8_t Snake_CheckCollision(Snake_t *snake) {
    Point_t head = snake->body[0];

    // Colisión con bordes del escenario [cite: 92, 102]
    if (head.x < 0 || head.x >= BOARD_WIDTH || head.y < 0 || head.y >= BOARD_HEIGHT) {
        return 1;
    }

    // Colisión con su propio cuerpo [cite: 92, 102]
    for (uint8_t i = 1; i < snake->length; i++) {
        if (head.x == snake->body[i].x && head.y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}

// Comprueba si la cabeza alcanza la comida para aumentar longitud y puntos [cite: 91, 101]
uint8_t Snake_EatFood(Snake_t *snake, Food_t *food) {
    if (snake->body[0].x == food->position.x && snake->body[0].y == food->position.y) {
        if (snake->length < MAX_SNAKE_LEN) {
            snake->length++; // Aumenta longitud al comer [cite: 91, 101]
        }
        food->isSpawned = 0;
        return 1;
    }
    return 0;
}

