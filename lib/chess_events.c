#include "include_define.h"
#include "chess_events.h"
#include "moveboard.h"

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

void isMates(struct figure (*chessPtr)[8][8], struct game* gamePtr) {
    int isStaleMate = 0;
        if (gamePtr->turn == 1) {
            gamePtr->check = isWhiteCheck(chessPtr, gamePtr);
        } else {
            gamePtr->check = isBlackCheck(chessPtr, gamePtr);
        }

    if (gamePtr->check != 0) {
        // If check or mate

        allPossibilities(chessPtr, gamePtr);

        if (gamePtr->possibleMoves == 0) {
            // If no legal moves and checked, then mate

            gamePtr->event = 2;
        } else {
            // Else continue the game
            gamePtr->possibleMoves = 0;
        }
    } else {
        // Unmark illegal moves
        allPossibilities(chessPtr, gamePtr);

        if (gamePtr->possibleMoves == 0 && gamePtr->check == 0) {
            // If no legal moves and not checked, then stale mate
            gamePtr->event = 3;
        } else {
            for (int i=0; i<8; i++) {
                for (int j=0; j<8; j++) {
                    if ((*chessPtr)[i][j].name != 'K' && (*chessPtr)[i][j].name != 'k' && (*chessPtr)[i][j].name != '.') {
                        // If kings are not the only pieces
                        isStaleMate = 1;
                    }
                }
            }
            if (isStaleMate != 1) {
                gamePtr->event = 3;
            }
            isStaleMate = 0;
        }
        // Otherwise it's normal move
        gamePtr->possibleMoves = 0;
    }
}
