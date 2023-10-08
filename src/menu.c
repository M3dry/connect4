#include <stdlib.h>
#include <raylib.h>

#include "menu.h"
#include "draw_util.h"
#include "state.h"

void
menu(State* state) {
    int half_width = state->width/2;
    int width = half_width, height = state->height/5;

    int h_width = width * 1.4, h_height = height * 1.4;
    int font_size = max_font((Vector2){ h_width, h_height }, "Connect4");
    int font_width = MeasureText("Connect4", font_size);
    DrawText("Connect4", half_width - font_width/2, (state->height/4) - h_height/2, font_size, GetColor(0xeeffffff));

    Rectangle rec1 = { half_width - width/2, (state->height/4)*2 - height/2, width, height };
    bool rec1_in = CheckCollisionPointRec(state->mouse_pos, rec1);
    if (rec1_in && state->clicked) {
        state->state = 1;
    } else {
        draw_button(rec1,
                    GetColor(0x6cbb3cff),
                    rec1_in,
                    "Start",
                    GetColor(0xeeffffff));
    }

    Rectangle rec2 = { half_width - width/2, (state->height/4)*3 - height/2, width, height };
    bool rec2_in = CheckCollisionPointRec(state->mouse_pos, rec2);
    if (rec2_in && state->clicked) {
        EndDrawing();
        CloseWindow();
        exit(0);
    } else {
        draw_button(rec2,
                    GetColor(0xff5370ff),
                    rec2_in,
                    "Quit",
                    GetColor(0xeeffffff));
    }
}
