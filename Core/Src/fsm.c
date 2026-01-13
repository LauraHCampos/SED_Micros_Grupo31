#include "fsm.h"
#include "sound.h"
#include "display.h"

// Variables que vienen de main.c
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
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
            Display_Init(&hi2c1); // Corregido: ahora pasa &hi2c1
            break;

        case STATE_PLAYING:
            HAL_TIM_Base_Start_IT(&htim2); // Activa el movimiento
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);   // LED Verde ON
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // LED Rojo OFF
            break;

        case STATE_GAMEOVER:
            HAL_TIM_Base_Stop_IT(&htim2); // Detiene el movimiento
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // LED Verde OFF
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);   // LED Rojo ON

            // Usamos tu define NOTE_FAIL
            Sound_Play(NOTE_FAIL, 500);
            Display_GameOver(game->score);
            break;

        case STATE_RESET:
            // No hace falta lógica aquí, se gestiona en el while(1)
            break;
    }
}

/**
 * Ciclo de ejecución de la FSM (se llama en el while del main)
 */
void FSM_Update(SnakeGame_t *game, Snake_t *snake, Food_t *food) {
    switch (game->currentState) {
        case STATE_IDLE:
            break;

        case STATE_PLAYING:
            // 1. Mover (aquí se gestiona el crecimiento de forma segura)
            Snake_Move(snake);

            // 2. Comprobar si ha muerto (con el cuerpo ya actualizado y sin duplicados)
            if (Snake_CheckCollision(snake)) {
                FSM_TransitionTo(game, STATE_GAMEOVER);
                break;
            }

            // 3. Comprobar si ha comido (esto activará el crecimiento para el PRÓXIMO frame)
            if (Snake_EatFood(snake, food)) {
                Snake_SpawnFood(food, snake);
                game->score++;
            }

            // 4. Dibujar
            Display_Update(snake, food, game->score);
            break;

        case STATE_GAMEOVER:
            break;

        case STATE_RESET:
            FSM_TransitionTo(game, STATE_IDLE);
            break;
    }
}

