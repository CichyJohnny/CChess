#include "include_define.h"

#ifndef MOVES_H
#define MOVES_H

#define WHITE "PRNBQK"
#define BLACK "prnbqk"

int isWhiteBlack(char name) {
    for (int i=0; i<6; i++) {
        if (name == WHITE[i]) {
            return 1;
        } else if (name == BLACK[i]) {
            return -1;
        }
    }
    return 0;
}

void pawnMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];

    if (figure.name == 'P') {
        if (y > 0 && chess[y - 1][x].name == '.') {   
            moveBoard[y - 1][x] = 1;
            if (figure.num == 0  && chess[y - 2][x].name == '.') {
                moveBoard[y - 2][x] = 1;
            }
        }
        if (y > 0 && x > 0 && isWhiteBlack(chess[y - 1][x - 1].name) == -1) {
            moveBoard[y - 1][x - 1] = 1;
        }
        if (y > 0 && x < 7 && isWhiteBlack(chess[y - 1][x + 1].name) == -1) {
            moveBoard[y - 1][x + 1] = 1;
        }
    } else {
        if (y < 7 && chess[y + 1][x].name == '.') {   
            moveBoard[y + 1][x] = 1;
            if (figure.num == 0  && chess[y + 2][x].name == '.') {
                moveBoard[y + 2][x] = 1;
            }
        }
        if (y < 7 && x > 0 && isWhiteBlack(chess[y + 1][x - 1].name) == 1) {
            moveBoard[y + 1][x - 1] = 1;
        }
        if (y < 7 && x < 7 && isWhiteBlack(chess[y + 1][x + 1].name) == 1) {
            moveBoard[y + 1][x + 1] = 1;
        }
    } 
}


#endif