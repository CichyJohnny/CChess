#include "include_define.h"
#include "moves.h"

#include <stdio.h>

#ifndef CHESS_EVENTS_H
#define CHESS_EVENTS_H

void isPat(struct figure chess[8][8]) {
    int dummyBoard[8][8];

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (chess[i][j].name == 'K' || chess[i][j].name == 'k') {
                sfVector2i position = {i, j};
                chess[i][j].possible_moves = 0;

                kingMove(chess, position, dummyBoard);

                printf("%d\n", chess[i][j].possible_moves);
                chess[i][j].possible_moves = 0;
            }
        }
    }
}

#endif