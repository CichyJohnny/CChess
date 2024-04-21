#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/*
Simple sfRectangleShape function that generates rectangle shape with given position, size and coloer
*/
sfRectangleShape* createSquare(sfVector2f position, sfVector2f size, sfColor color);

/*
Void function that generate sfRectangleShape by calling createSquare function for every square in 8x8 chessboard
*/
void defineChessBoard (sfRectangleShape* squares[8][8]);

/*
Simple void function for rendering 8x8 chessboard
*/
void drawChessboard(sfRenderWindow* window, sfRectangleShape* squares[8][8]);

#endif