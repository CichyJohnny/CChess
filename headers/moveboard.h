#include "include_define.h"
#include "moves.h"
#include "chessboard.h"

#ifndef MOVEBOARD_H
#define MOVEBOARD_H

void canmove(sfRenderWindow* window, struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            moveBoard[i][j] = 0;
        }
    }
    if (figure.name == 'P' || figure.name == 'p') {
        pawnMove(chess, position, moveBoard);
    } else if (figure.name == 'N' || figure.name == 'n') {
        knightMove(chess, position, moveBoard);
    } else if (figure.name == 'R' || figure.name == 'r') {
        rookMove(chess, position, moveBoard);
    } else if (figure.name == 'B' || figure.name == 'b') {
        bishopMove(chess, position, moveBoard);
    } else if (figure.name == 'Q' || figure.name == 'q') {
        queenMove(chess, position, moveBoard);
    } else if (figure.name == 'K' || figure.name == 'k') {
        kingMove(chess, position, moveBoard);
    }
}

void drawMoves(sfRenderWindow* window, int moveBoard[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (moveBoard[i][j] == 1) {   
                sfVector2f position = {10 + j * SQUARE_SIZE, 10 + i * SQUARE_SIZE};
                sfVector2f size = {SQUARE_SIZE - 20, SQUARE_SIZE - 20};
                sfColor color = sfGreen;

                sfRectangleShape *square = createSquare(position, size, color);
                
                sfRenderWindow_drawRectangleShape(window, square, NULL);
            }
        }
    }    
}

void clearBoard(int board[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[i][j] = 0;
        }
    }
}

#endif