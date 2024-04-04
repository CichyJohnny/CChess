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

int isCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if((*chessPtr)[i][j].name == 'K' && gamePtr->blackBoard[i][j] == 1) {
                return 1;
            } else if ((*chessPtr)[i][j].name == 'k' && gamePtr->whiteBoard[i][j] == 1) {
                return -1;
            }
        }
    }
    return 0;
}

void escapeCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr, int check) {
    struct figure nextChess[8][8];
    struct figure (*nextChessPtr)[8][8] = &nextChess;

    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};

    struct game copyGame = *gamePtr;
    struct game *copyGamePtr = &copyGame;

    int newCheck;
    int color;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (isWhiteBlack((*chessPtr)[i][j].name) == check) {

                for (int n=0; n<8; n++) {
                    for (int m=0; m<8; m++) {
                        if((*chessPtr)[i][j].moveBoard[n][m] == 1) {

                            // Copy of chess list
                            copyChess(chessPtr, nextChessPtr);

                            // Moving piece on copied board
                            movePiece = nextChess[i][j];
                            nextChess[i][j] = empty; // clear square
                            nextChess[n][m] = movePiece; // movie piece

                            // Computing all moves after the move
                            allMoves(nextChessPtr, copyGamePtr);

                            // We check if there is a check after the move
                            newCheck = isCheck(nextChessPtr, copyGamePtr);

                            if (newCheck != 0) { 
                                // remember that checking enemy does not prevent you from being checked
                                // You still are checked
                                // Discard changes
                                (*chessPtr)[i][j].moveBoard[n][m] = 0;
                                nextChess[i][j] = movePiece; // revert move
                                nextChess[n][m] = empty; // revert move
                            } else {
                                gamePtr->possible_moves++;
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif