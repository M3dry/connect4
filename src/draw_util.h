#ifndef DRAW_UTIL_H
#define DRAW_UTIL_H

#include <raylib.h>

int max_font(Vector2 max_size, char* text);
void draw_button(Rectangle rec, Color color, bool active, char* text, Color text_color);

#endif // DRAW_UTIL_H
