#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdint.h>
#include <stdbool.h>

#include "state.h"

#define BOARD_WIDTH 15
#define BOARD_HEIGHT 10

typedef struct GameState {
    int8_t board[BOARD_WIDTH][BOARD_HEIGHT]; // 0 - empty cell; 1 - BLUE cell; 2 - RED cell
    Rectangle board_rec;
    int cell_a;
    int line_thickness;
    bool player; // true - BLUE; false - RED
    int8_t won; // -1 - still playing; 0 - draw; 1 - BLUE; 2 - RED
    State* state;
} GameState;

GameState make_gamestate();
void game(GameState* state);

#endif // GAME_H
