#include "include_define.h"
#include "moves.h"
#include "chessboard.h"

#ifndef MOVEBOARD_H
#define MOVEBOARD_H

/*
Void function that checks possible moves by calling function for selected piece
*/
void canMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];

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

/*
Void function that render green squares representing possible moves for selected piece
*/
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

/*
Simple void function that changes every int in 2d moveBoard to 0
*/
void clearBoard(int board[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[i][j] = 0;
        }
    }
}

void allMoves(struct figure chess[8][8]) {
    sfVector2i position;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            position = (sfVector2i){j, i};
            clearBoard(chess[i][j].moveBoard);
            canMove(chess, position, chess[i][j].moveBoard);
        }
    }
}


#endif