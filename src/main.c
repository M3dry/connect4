#include <raylib.h>
#include <stdio.h>

#include "menu.h"
#include "game.h"
#include "state.h"

int
main(int argc, char **argv)
{
    InitWindow(0, 0, "Connect4");
    ToggleFullscreen();
    SetExitKey(KEY_NULL);

    Image icon = LoadImage("./Connect4.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    State state = make_state();
    GameState gstate = make_gamestate(&state);

    while (!WindowShouldClose()) {
        update_state(&state);

        BeginDrawing();
            ClearBackground(GetColor(0x0f111bff));

            if (state.state == 0) {
                menu(&state);
            } else {
                if (state.state != 2 && IsKeyPressed(KEY_ESCAPE)) {
                    state.state = 0;
                    gstate = make_gamestate(&state);
                } else {
                    game(&gstate);
                }
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
