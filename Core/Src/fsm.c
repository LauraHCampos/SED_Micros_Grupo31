#include "fsm.h"
#include "sound.h"
#include "display.h"

// Variables que vienen de main.c
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern uint32_t high_score;
extern uint8_t new_record_flag; // Traemos la bandera del main

//Inicializa el estado del juego y los periféricos

void FSM_Init(SnakeGame_t *game) {
    game->currentState = STATE_IDLE;
    game->score = 0;

    // Apagar leds
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // Verde
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // Rojo

    // Inicializar pantalla LCD
    Display_Init(&hi2c1);
}


//Gestiona las transiciones entre estados y acciones únicas

void FSM_TransitionTo(SnakeGame_t *game, GameState_t newState) {

	if (game->currentState == newState) return;// Si ya estamos en ese estado, no hacemos nada y salimos.

    game->currentState = newState;

    switch (newState) {
        case STATE_IDLE:
        	if (new_record_flag == 1) {
				// 1. Mostrar pantalla de nuevo récord
				Display_NewRecord(high_score);

				// 2. Melodía de victoria
				Sound_Play(1200, 100);
				HAL_Delay(50);
				Sound_Play(1500, 100);
				HAL_Delay(50);
				Sound_Play(2000, 400);

				// 3. Esperar los 5 segundos
				HAL_Delay(5000);

				// 4. Limpiamos la bandera para que no se repita
				new_record_flag = 0;
			}
        	Display_IDLE(high_score);

            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // LED Verde OFF
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // LED Rojo OFF
            break;

        case STATE_PLAYING:
            HAL_TIM_Base_Start_IT(&htim2);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
            break;

        case STATE_GAMEOVER:
            HAL_TIM_Base_Stop_IT(&htim2);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

            Sound_Play(NOTE_FAIL, 500); // Pitido de muerte
            Display_GameOver(game->score);
            break;

        case STATE_RESET:
            // Muestra la puntuación final.
            // Como esta función se llama ANTES de que el main ponga el score a 0,
            // el valor será el correcto.
            Display_Reset(game->score);
            break;
    }
}


//Ciclo de ejecución de la FSM (se llama en el while del main)

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

