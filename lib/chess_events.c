#include "include_define.h"
#include "chess_events.h"

void copyChess(struct figure (*chessPtr)[8][8], struct figure (*newChessPtr)[8][8]) {
     for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            (*newChessPtr)[i][j] = (*chessPtr)[i][j];
        }
     }
}

int isWhiteCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if((*chessPtr)[i][j].name == 'K' && gamePtr->blackBoard[i][j] == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int isBlackCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if ((*chessPtr)[i][j].name == 'k' && gamePtr->whiteBoard[i][j] == 1) {
                return -1;
            }
        }
    }
    return 0;
}

int countPoints(struct game *gamePtr) {
    int points = 0;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            switch (gamePtr->chess[i][j].name) {
            case 'Q':
                points += 9;
                break;
            case 'q':
                points += -9;
                break;
            case 'R':
                points += 5;
                break;
            case 'r':
                points += -5;
                break;
            case 'N':
                points += 3;
                break;
            case 'n':
                points += -3;
                break;
            case 'B':
                points += 3;
                break;
            case 'b':
                points += -3;
                break;
            case 'P':
                points += 1;
                break;
            case 'p':
                points += -1;
                break;
            }
        }
    }

    return points;
}
