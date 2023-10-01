#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#include "state.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

typedef struct GameState {
    int8_t board[BOARD_HEIGHT][BOARD_WIDTH]; // 0 - empty cell; 1 - player 1 cell; 2 - player 2 cell
    bool now_playing; // false - player 1; true - player 2
    int8_t won; // -1 - still playing; 0 - draw; 1; player 1; 2 - player 2
    State* state;
} GameState;

GameState make_gamestate();
void game(GameState* state);
static void draw_grid();

#endif // GAME_H
