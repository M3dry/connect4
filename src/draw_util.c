#include <raylib.h>

#include "draw_util.h"

int
max_font(Vector2 max_size, char* text) {
    int font_size = 100;
    int lower = 0;
    int higher = -1;

    while (lower + 1 != higher) {
        if (max_size.x > MeasureText(text, font_size) && max_size.y > font_size) {
            lower = font_size;
            if (higher == -1) {
                font_size += 100;
            } else {
                font_size = (higher + lower)/2;
            }
        } else {
            higher = font_size;
            font_size = (higher + lower)/2;
        }
    }

    return font_size;
}

void
draw_button(Rectangle rec, Color color, bool active, char* text, Color text_color) {

    if (active) {
        int font_size = max_font((Vector2){ rec.width * 0.95, rec.height * 0.95 }, text);
        int font_width = MeasureText(text, font_size);

        DrawRectangleRounded(rec, 0.5, 0xff, color);
        DrawText(text, rec.x + rec.width/2 - font_width/2, rec.y + rec.height/2 - font_size/2, font_size, text_color);
    } else {
        int border = rec.width/120;
        if (border < 3) border = 3;

        int font_size = max_font((Vector2){ rec.width * 0.95 - border*2, rec.height * 0.95 - border*2 }, text);
        int font_width = MeasureText(text, font_size);

        Rectangle rec1 = { rec.x + border + 10, rec.y + border + 10, rec.width - border*2 - 20, rec.height - border*2 - 20 };
        DrawRectangleRoundedLines(rec1, 0.5, 0xff, border, color);
        DrawText(text, rec1.x + rec1.width/2 - font_width/2, rec1.y + rec1.height/2 - font_size/2, font_size, color);
    }
}
