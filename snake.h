#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include "main.h"

// Definición del tamaño del tablero
#define BOARD_WIDTH  16
#define BOARD_HEIGHT 16
#define MAX_SNAKE_LEN 32


// Direcciones posibles para el movimiento
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction_t;

// Estructura para coordenadas
typedef struct {
    int8_t x;
    int8_t y;
} Point_t;

// Estructura principal de la serpiente
typedef struct {
    Point_t body[MAX_SNAKE_LEN];
    uint8_t length;
    Direction_t direction;
    uint8_t pending_growth; //Indica cuántos segmentos faltan por crecer
} Snake_t;

// Estructura para la comida
typedef struct {
    Point_t position;
    uint8_t isSpawned;
} Food_t;


// Inicializa la serpiente en el centro y una longitud inicial
void Snake_Init(Snake_t *snake);

// Actualiza la posición de la cabeza según la dirección
void Snake_Move(Snake_t *snake);

// Genera comida en una posición aleatoria que no coincida con el cuerpo
void Snake_SpawnFood(Food_t *food, Snake_t *snake);

// Comprueba colisiones con bordes o con el propio cuerpo
// Retorna 1 si hay choque (Game Over), 0 si está a salvo
uint8_t Snake_CheckCollision(Snake_t *snake);

// Comprueba si la cabeza ha alcanzado la comida
uint8_t Snake_EatFood(Snake_t *snake, Food_t *food);

#endif
