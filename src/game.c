#include <stdbool.h>

#include "game.h"
#include "state.h"

GameState
make_gamestate(State* state) {
    return (GameState) {
        .board = {{0}},
        .now_playing = false,
        .won = -1,
        .state = state,
    };
}

void
game(GameState* gstate) {
    draw_grid(gstate->state->width, gstate->state->height);
}

static void
draw_grid(int s_width, int s_height) {
    int border = s_width/480;
    if (border < 2) border = 2;

    int w_padding = s_width * 0.1;
    int h_padding = s_height * 0.1;
    Color white = GetColor(0xeeffffff);

    DrawRectangleLinesEx((Rectangle){ w_padding, h_padding, s_width - 2*w_padding - border, s_height - 2*h_padding - border }, border, white);
    w_padding += border;
    h_padding += border;

    int r_width = s_width - 2*w_padding - border;
    int r_height = s_height - 2*h_padding - border;

    int c_width = (r_width - (BOARD_WIDTH - 1)*border)/BOARD_WIDTH;
    int c_height = (r_height - (BOARD_HEIGHT - 1)*border)/BOARD_HEIGHT;

    for (int i = 1; i < BOARD_WIDTH; i++) {
        DrawLineEx((Vector2){ w_padding + c_width*i + border*i, h_padding }, (Vector2){ w_padding + c_width*i + border*i, h_padding + r_height }, border, white);
        DrawLineEx((Vector2){ w_padding, h_padding + c_height*i + border*i }, (Vector2){ w_padding + r_width, h_padding + c_height*i + border*i }, border, white);
    }
}
