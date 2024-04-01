#include "include_define.h"

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/*
Simple sfRectangleShape function that generates rectangle shape with given position, size and coloer
*/
sfRectangleShape* createSquare(sfVector2f position, sfVector2f size, sfColor color) {
    sfRectangleShape* square = sfRectangleShape_create();
    sfRectangleShape_setPosition(square, position);
    sfRectangleShape_setSize(square, size);
    sfRectangleShape_setFillColor(square, color);

    return square;
}

/*
Void function that generate sfRectangleShape by calling createSquare function for every square in 8x8 chessboard
*/
void defineChessBoard (sfRectangleShape* squares[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            sfVector2f size = {SQUARE_SIZE, SQUARE_SIZE};
            sfColor color;

            if ((i + j) % 2 == 0)
                color = sfColor_fromRGB(255, 206, 158); // brown color for "black" squares
            else
                color = sfColor_fromRGB(209, 139, 71); // cream color for "white" squares

            squares[i][j] = createSquare(position, size, color);
        }
    }
}

/*
Simple void function for rendering 8x8 chessboard
*/
void drawChessboard(sfRenderWindow* window, sfRectangleShape* squares[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRenderWindow_drawRectangleShape(window, squares[i][j], NULL);
        }
    }
}

#endif