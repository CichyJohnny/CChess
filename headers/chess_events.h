#include "include_define.h"
#include "moves.h"
#include "moveboard.h"

#ifndef CHESS_EVENTS_H
#define CHESS_EVENTS_H

void copyChess(struct figure (*chessPtr)[8][8], struct figure (*prevChessPtr)[8][8]) {
     for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            (*prevChessPtr)[i][j] = (*chessPtr)[i][j];
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


void normalMove(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos) {
    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};

    movePiece = (*chessPtr)[selectedPiece.y][selectedPiece.x];
    (*chessPtr)[selectedPiece.y][selectedPiece.x] = empty; // clear square
    (*chessPtr)[mousePos.y][mousePos.x] = movePiece; // movie piece

    gamePtr->turn = -gamePtr->turn; // change players
    gamePtr->event = 0;
    (*chessPtr)[mousePos.y][mousePos.x].num++; // +1 to number of times a piece was moved
    gamePtr->shortclash = 0;
    gamePtr->longclash = 0;
    allMoves(chessPtr, gamePtr);

    spritesUpdate(chessPtr);

    int check;
    int isPat = 0;

    if (gamePtr->turn == 1) {
        check = isWhiteCheck(chessPtr, gamePtr);
    } else {
        check = isBlackCheck(chessPtr, gamePtr);
    }

    if (check != 0) {
        // If check or mate
        printf("Check\n");
        gamePtr->event = 1;

        allPossibilities(chessPtr, gamePtr, check);
        if (gamePtr->possible_moves == 0) {
            // If there no way to defend king, there is mat
            printf("Mate\n");

            gamePtr->event = 2;
        } else {
            // Else continue the game
            gamePtr->possible_moves = 0;
        }
    } else {
        // Check if move does not allow check
        allPossibilities(chessPtr, gamePtr, gamePtr->turn);

        // If pat
        if (gamePtr->possible_moves == 0 && check == 0) {
            printf("Pat ");
            gamePtr->event = 3;
        } else {
            for (int i=0; i<8; i++) {
                for (int j=0; j<8; j++) {
                    if ((*chessPtr)[i][j].name != 'K' && (*chessPtr)[i][j].name != 'k' && (*chessPtr)[i][j].name != '.') {
                        isPat = 1;
                    }
                }
            }
            if (isPat == 0) {
                printf("Pat ");
                gamePtr->event = 3;
            }
            isPat = 0;
        }
 
        // Normal move
        gamePtr->possible_moves = 0;
    }


    if (movePiece.name == 'P' && mousePos.y == 4) {
        gamePtr->enPassent = (sfVector2i){mousePos.x, 5};
        // gamePtr->enPassentturn = 1;
    } else if (movePiece.name == 'p' && mousePos.y == 3) {
        gamePtr->enPassent = (sfVector2i){mousePos.x, 2};
        // gamePtr->enPassentturn = -1;
    }
}


#endif