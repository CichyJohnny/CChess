#include "include_define.h"
#include "moves.h"

#include <stdio.h>

#ifndef CHESS_EVENTS_H
#define CHESS_EVENTS_H

void copyChess(struct figure (*chessPtr)[8][8], struct figure (*prevChessPtr)[8][8]) {
     for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            (*prevChessPtr)[i][j] = (*chessPtr)[i][j];
        }
     }
}

void revertChangesChess(struct figure (*chessPtr)[8][8], struct figure (*prevChessPtr)[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            (*chessPtr)[i][j] = (*prevChessPtr)[i][j];
        }
     }
}

int isCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            // White king is checked
            if((*chessPtr)[i][j].name == 'K' && gamePtr->blackBoard[i][j] == 1) {
                return 1;
            } else if ((*chessPtr)[i][j].name == 'k' && gamePtr->whiteBoard[i][j] == 1) {
                return -1;
            }
        }
    }
    return 0;
}

#endif