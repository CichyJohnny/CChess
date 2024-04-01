#include "include_define.h"
#include <stdio.h>

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
        if (y - 1 >= 0 && chess[y - 1][x].name == '.') {   
            moveBoard[y - 1][x] = 1;
            if (figure.num == 0  && chess[y - 2][x].name == '.') {
                moveBoard[y - 2][x] = 1;
            }
        }
        if (y - 1 >= 0 && x - 1 >= 0 && isWhiteBlack(chess[y - 1][x - 1].name) == -1) {
            moveBoard[y - 1][x - 1] = 1;
        }
        if (y - 1 >= 0 && x + 1 <= 7 && isWhiteBlack(chess[y - 1][x + 1].name) == -1) {
            moveBoard[y - 1][x + 1] = 1;
        }
    } else {
        if (y + 1 <= 7 && chess[y + 1][x].name == '.') {   
            moveBoard[y + 1][x] = 1;
            if (figure.num == 0  && chess[y + 2][x].name == '.') {
                moveBoard[y + 2][x] = 1;
            }
        }
        if (y + 1 <= 7 && x - 1 >= 0 && isWhiteBlack(chess[y + 1][x - 1].name) == 1) {
            moveBoard[y + 1][x - 1] = 1;
        }
        if (y + 1 <= 7 && x + 1 <= 7 && isWhiteBlack(chess[y + 1][x + 1].name) == 1) {
            moveBoard[y + 1][x + 1] = 1;
        }
    } 
}

void knightMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];
    int color = isWhiteBlack(chess[y][x].name);

    sfVector2i dirs[8] = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
    int vec_x, vec_y;

    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;
        if (vec_y >= 0 && vec_x >= 0 && vec_y <= 7 && vec_x <= 7 && isWhiteBlack(chess[vec_y][vec_x].name) != color) {
            moveBoard[vec_y][vec_x] = 1;
        }
    }
}

void rookMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];
    int color = isWhiteBlack(chess[y][x].name);
    int name;

    for (int i=1; x - i >= 0; i++) {
        name = isWhiteBlack(chess[y][x - i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y][x - i] = 1;
            break;
        } else {
            moveBoard[y][x - i] = 1;
        }
    }
    for (int i=1; x + i <= 7; i++) {
        name = isWhiteBlack(chess[y][x + i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y][x + i] = 1;
            break;
        } else {
            moveBoard[y][x + i] = 1;
        }
    }
    for (int i=1; y - i >= 0; i++) {
        name = isWhiteBlack(chess[y - i][x].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y - i][x] = 1;
            break;
        } else {
            moveBoard[y - i][x] = 1;
        }
    }
    for (int i=1; y + i <= 7; i++) {
        name = isWhiteBlack(chess[y + i][x].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y + i][x] = 1;
            break;
        } else {
            moveBoard[y + i][x] = 1;
        }
    }
}

void bishopMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];
    int color = isWhiteBlack(chess[y][x].name);

    int name;

    for (int i=1; x - i >= 0 && y - i >= 0; i++) {
        name = isWhiteBlack(chess[y - i][x - i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y - i][x - i] = 1;
            break;
        } else {
            moveBoard[y - i][x - i] = 1;
        }
    }
    for (int i=1; x + i <= 7 && y - i >= 0; i++) {
        name = isWhiteBlack(chess[y - i][x + i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y - i][x + i] = 1;
            break;
        } else {
            moveBoard[y - i][x + i] = 1;
        }
    }
    for (int i=1; x + i <= 7 && y + i <= 7; i++) {
        name = isWhiteBlack(chess[y + i][x + i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y + i][x + i] = 1;
            break;
        } else {
            moveBoard[y + i][x + i] = 1;
        }
    }
    for (int i=1; x - i >= 0 && y + i <= 7; i++) {
        name = isWhiteBlack(chess[y + i][x - i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            moveBoard[y + i][x - i] = 1;
            break;
        } else {
            moveBoard[y + i][x - i] = 1;
        }
    }
}

void queenMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    rookMove(chess, position, moveBoard);
    bishopMove(chess, position, moveBoard);
}

void kingMove(struct figure chess[8][8], sfVector2i position, int moveBoard[8][8]) {
    int x = position.x, y = position.y;
    struct figure figure = chess[y][x];
    int color = isWhiteBlack(chess[y][x].name);

    sfVector2i dirs[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int vec_x, vec_y;

    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;
        if (vec_y >= 0 && vec_x >= 0 && vec_y <= 7 && vec_x <= 7 && isWhiteBlack(chess[vec_y][vec_x].name) != color) {
            moveBoard[vec_y][vec_x] = 1;
        }
    }
}

#endif