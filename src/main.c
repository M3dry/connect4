#include <raylib.h>
#include <stdio.h>

#include "menu.h"
#include "game.h"
#include "state.h"

int
main(int argc, char **argv)
{
    InitWindow(0, 0, "Connect4");
    SetExitKey(KEY_NULL);

    Image icon = LoadImage("./Connect4.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    State state = make_state();

    while (!WindowShouldClose()) {
        update_state(&state);

        BeginDrawing();
            ClearBackground(GetColor(0x0f111bff));

            if (!state.playing) {
                menu(&state);
            } else {
                if (GetKeyPressed() == KEY_ESCAPE) {
                    state.playing = false;
                } else {
                    GameState gstate = make_gamestate(&state);
                    game(&gstate);
                }
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
