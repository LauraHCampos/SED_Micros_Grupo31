#include "fsm.h"

extern I2C_HandleTypeDef hi2c1;
/**
 * Inicializa el estado del juego y los periféricos [cite: 19]
 */
void FSM_Init(SnakeGame_t *game) {
    game->currentState = STATE_IDLE;
    game->score = 0;

    // Apagar actuadores visuales [cite: 32]
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // Verde
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // Rojo

    // Inicializar pantalla LCD
    Display_Init(&hi2c1);
}

/**
 * Gestiona las transiciones entre estados y acciones únicas
 */
void FSM_TransitionTo(SnakeGame_t *game, GameState_t newState) {
    game->currentState = newState;

    switch (newState) {
        case STATE_IDLE:
            Display_Init(&hi2c1); // Mostrar pantalla de bienvenida
            break;

        case STATE_PLAYING:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // LED Verde: Juego activo
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
            break;

        case STATE_GAMEOVER:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); // LED Rojo: Error/Fin [cite: 32]
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
            Sound_Play(NOTE_FAIL, 500); // Aviso sonoro de fin de juego [cite: 45, 52]
            Display_GameOver(game->score); // Indicar resultado final [cite: 47]
            break;

        case STATE_RESET:
            // El sistema debe poder reiniciarse sin perder funcionalidad [cite: 40]
            game->score = 0;
            break;
    }
}

/**
 * Ciclo de ejecución de la FSM (se llama en el while del main)
 */
void FSM_Update(SnakeGame_t *game, Snake_t *snake, Food_t *food) {
    switch (game->currentState) {
        case STATE_IDLE:
            // Espera pasiva de interrupción por botón (PA0) [cite: 43]
            break;

        case STATE_PLAYING:
            // El movimiento se gestiona por interrupción de temporizador (TIM2) [cite: 33]
            // Aquí se actualiza la pantalla periódicamente
            Display_Update(snake, food, game->score);
            break;

        case STATE_GAMEOVER:
            // Espera a que el jugador decida reiniciar
            break;

        case STATE_RESET:
            FSM_TransitionTo(game, STATE_IDLE);
            break;
    }
}

