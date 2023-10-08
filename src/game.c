#include <stdbool.h>
#include <stdint.h>

#include "game.h"
#include "draw_util.h"
#include "state.h"

static void draw_grid(Rectangle* rec, const int8_t board[BOARD_WIDTH][BOARD_HEIGHT], int* c_a, int* border, int s_width, int s_height);
static int mouse_in_column(const GameState* gstate);
static void update_sizes(Rectangle* rec, int* c_a, int* border, int s_width, int s_height);
static bool check_4(const int8_t board[BOARD_WIDTH][BOARD_HEIGHT], int x, int y);

GameState
make_gamestate(State* state) {
    Rectangle board_rec;
    int cell_a;
    int line_thickness;

    update_sizes(&board_rec, &cell_a, &line_thickness, state->width, state->height);

    return (GameState) {
        .board = {{0}},
        .board_rec = board_rec,
        .cell_a = cell_a,
        .line_thickness = line_thickness,
        .player = false,
        .won = -1,
        .state = state,
    };
}

void
game(GameState* gstate) {
    if (gstate->won == -1) {
        int column = mouse_in_column(gstate);
        if (gstate->state->clicked && column != -1) {
            int8_t* stack = gstate->board[column];
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                if (stack[i] == 0) {
                    stack[i] = gstate->player ? 1 : 2;
                    if (check_4(gstate->board, column, i)) {
                        gstate->won = !gstate->player + 1;
                    } else {
                        gstate->player = !gstate->player;
                    }
                    break;
                }
            }
        }
    }

    char* on_turn = gstate->player ? "Blue's turn" : "Red's turn";
    int font_size = max_font((Vector2){ gstate->board_rec.width, gstate->board_rec.y }, on_turn);
    int font_width = MeasureText(on_turn, font_size);

    DrawText(on_turn, gstate->board_rec.x + gstate->board_rec.width/2 - font_width/2, 0, font_size, gstate->player ? GetColor(0x72a4ffff) : GetColor(0xff5370ff));

    draw_grid(&gstate->board_rec, gstate->board, &gstate->cell_a, &gstate->line_thickness, gstate->state->width, gstate->state->height);

    if (gstate->won != -1) {
        char* win_text;
        if (gstate->won == 0) {
            win_text = "It's a draw!";
        } else if (gstate->won == 1) {
            win_text = "Blue player won!";
        } else {
            win_text = "Red player won!";
        }

        int font_size = max_font((Vector2){ gstate->state->width * 0.9, gstate->state->height * 0.9 }, win_text);
        int font_width = MeasureText(win_text, font_size);

        DrawText(win_text, gstate->state->width * 0.05 + (gstate->state->width*0.9)/2 - font_width/2, gstate->state->height * 0.05 + (gstate->state->height*0.9)/2 - font_size/2, font_size, gstate->player ? GetColor(0x72a4ffff) : GetColor(0xff5370ff));

        if (IsKeyPressed(KEY_R)) {
            gstate->state->state = true;
            *gstate = make_gamestate(gstate->state);
        } else if (GetKeyPressed() != 0) {
            gstate->state->state = false;
            *gstate = make_gamestate(gstate->state);
        }
    }
}

// -1 - mouse isn't in a column
// 0 indexed
static int
mouse_in_column(const GameState* gstate) {
    if (!CheckCollisionPointRec(gstate->state->mouse_pos, gstate->board_rec)) {
        return -1;
    }

    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (CheckCollisionPointRec(gstate->state->mouse_pos, (Rectangle){ gstate->board_rec.x + i*(gstate->line_thickness + gstate->cell_a), gstate->board_rec.y, gstate->cell_a, gstate->board_rec.height })) {
            return i;
        }
    }

    return -1;
}

static void
draw_grid(Rectangle* rec, const int8_t board[BOARD_WIDTH][BOARD_HEIGHT], int* c_a, int* border, int s_width, int s_height) {
    Color white = GetColor(0xeeffffff);

    update_sizes(rec, c_a, border, s_width, s_height);

    // outline
    rec->x -= *border;
    rec->y -= *border;
    rec->width += 2**border;
    rec->height += 2**border;
    DrawRectangleLinesEx(*rec, *border, white);
    rec->x += *border;
    rec->y += *border;
    rec->width -= 2**border;
    rec->height -= 2**border;


    // vertical lines
    for (int i = 1; i < BOARD_WIDTH; i++) {
        DrawLineEx((Vector2){ (int)(rec->x + *c_a*i + *border*i - *border/2), rec->y }, (Vector2){ (int)(rec->x + *c_a*i + *border*i - *border/2), rec->y + rec->height }, *border, white);
    }
    // horizontal lines
    for (int i = 1; i < BOARD_HEIGHT; i++) {
        DrawLineEx((Vector2){ rec->x, rec->y + *c_a*i + *border*i - *border/2 }, (Vector2){ rec->x + rec->width, rec->y + *c_a*i + *border*i - *border/2 }, *border, white);
    }

    // board
    Color colors[2] = { GetColor(0x72a4ffff), GetColor(0xff5370ff) };
    for (int col = 0; col < BOARD_WIDTH; col++) {
        for (int row = 0; row < BOARD_HEIGHT; row++) {
            if (board[col][row] != 0) {
                //                                                          draw from bottom up
                DrawCircle(rec->x + col*(*border + *c_a) + *c_a/2, rec->y + (BOARD_HEIGHT - 1 - row)*(*border + *c_a) + *c_a/2, *c_a/2 * 0.9, colors[board[col][row] - 1]);
            }
        }
    }
}

static void
update_sizes(Rectangle* rec, int* c_a, int* border, int s_width, int s_height) {
    *border = (s_width > s_height ? s_height : s_width)/300;
    if (*border < 2) *border = 2;

    int c_a2 = (s_height * 0.8)/BOARD_HEIGHT;
    *c_a = (s_width * 0.8)/BOARD_WIDTH;

    if (*c_a > c_a2) {
        *c_a = c_a2;
    }

    // working area
    rec->width = *c_a*BOARD_WIDTH + *border*(BOARD_WIDTH - 1);
    rec->height = *c_a*BOARD_HEIGHT + *border*(BOARD_HEIGHT - 1);
    rec->x = (s_width - rec->width)/2;
    rec->y = (s_height - rec->height)/2;
}

static bool
check_4(const int8_t board[BOARD_WIDTH][BOARD_HEIGHT], int x, int y) {
    int8_t center = board[x][y];
    if (center == 0) {
        return false;
    }

    int bottom = 0, left = 0, right = 0, i, o;
    int rt = 0, rb = 0, lt = 0, lb = 0;

    #define CHECK_DIR(CORD_CHECK, X, Y, COUNTER, INCRS) while (CORD_CHECK && board[X][Y] == center) { COUNTER++; INCRS; if (COUNTER == 3) return true; }

    i = y - 1;
    CHECK_DIR(i >= 0, x, i, bottom, i--)

    i = x - 1;
    CHECK_DIR(i >= 0, i, y, left, i--)

    i = x + 1;
    CHECK_DIR(i < BOARD_WIDTH, i, y, right, i++)

    i = x + 1;
    o = y + 1;
    CHECK_DIR(i < BOARD_WIDTH && o < BOARD_HEIGHT, i, o, rt, i++; o++)

    i = x - 1;
    o = y + 1;
    CHECK_DIR(i >= 0 && o < BOARD_HEIGHT, i, o, lt, i--; o++)

    i = x + 1;
    o = y - 1;
    CHECK_DIR(i < BOARD_WIDTH && o >= 0, i, o, rb, i++; o--)

    i = x - 1;
    o = y - 1;
    CHECK_DIR(i >= 0 && o >= 0, i, o, lb, i--; o--)

    return right + left >= 3 || lb + rt >= 3 || lt + rb >= 3;
}
