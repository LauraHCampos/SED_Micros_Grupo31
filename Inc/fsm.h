#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "snake.h"
#include "display.h"
#include "sound.h"

/* Estados de la máquina de estados [cite: 38] */
typedef enum {
    STATE_IDLE,      // Espera de inicio (Requisito funcional 1) [cite: 43]
    STATE_PLAYING,   // Dinámica de juego activa [cite: 46]
    STATE_GAMEOVER,  // Fin de partida y visualización de resultado [cite: 47]
    STATE_RESET      // Reinicio del sistema (Requisito software 3) [cite: 40]
} GameState_t;

/* Estructura de control del juego */
typedef struct {
    GameState_t currentState;
    uint32_t score;
} SnakeGame_t;

/* Prototipos de funciones */
void FSM_Init(SnakeGame_t *game);
void FSM_Update(SnakeGame_t *game, Snake_t *snake, Food_t *food);
void FSM_TransitionTo(SnakeGame_t *game, GameState_t newState);

#endif
