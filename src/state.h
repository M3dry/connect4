#ifndef STATE_H
#define STATE_H

#include <raylib.h>
#include <stdint.h>

typedef struct State {
    int width;
    int height;
    Vector2 mouse_pos;
    bool clicked;
    int8_t state;
} State;

State make_state();
void update_state(State* state);

#endif // STATE_H
