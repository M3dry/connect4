#include <raylib.h>

#include "state.h"

State
make_state() {
    State state = {
        .state = 0
    };

    update_state(&state);

    return state;
}

void
update_state(State* state) {
    state->width = GetScreenWidth();
    state->height = GetScreenHeight();
    state->mouse_pos = GetMousePosition();
    state->clicked = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
