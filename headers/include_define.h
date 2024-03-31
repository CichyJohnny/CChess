#include <SFML/Graphics.h>
#include <SFML/Window.h>

#ifndef INCUDE_DEFINE_H
#define INCUDE_DEFINE_H

#define SQUARE_SIZE 128
#define WINDOW_WIDTH 8 * SQUARE_SIZE
#define WINDOW_HEIGHT 8 * SQUARE_SIZE

struct figure {
    char name;
    sfSprite* sprite;
    int num;
};

#endif