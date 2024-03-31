#include "include_define.h"

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

// Create rectangle shape with given position, size and color
sfRectangleShape* createSquare(sfVector2f position, sfVector2f size, sfColor color) {
    sfRectangleShape* square = sfRectangleShape_create();
    sfRectangleShape_setPosition(square, position);
    sfRectangleShape_setSize(square, size);
    sfRectangleShape_setFillColor(square, color);
    return square;
}

void defineChessBoard (sfRectangleShape* squares[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            sfVector2f size = {SQUARE_SIZE, SQUARE_SIZE};
            sfColor color;
            if ((i + j) % 2 == 0)
                color = sfColor_fromRGB(209, 139, 71); // Brown color for squares
            else
                color = sfColor_fromRGB(255, 206, 158); // Cream color for squares
            squares[i][j] = createSquare(position, size, color);
        }
    }
}

// Render chessboard with given shapes inside given 2d 8x8 array
void drawChessboard(sfRenderWindow* window, sfRectangleShape* squares[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRenderWindow_drawRectangleShape(window, squares[i][j], NULL);
        }
    }
}

#endif