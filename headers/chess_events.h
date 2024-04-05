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

void shortCastling(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    

    if (figure->name == 'K' && x == 4 && y == 7 && (*chessPtr)[7][7].name == 'R') {
        // King and rook are on positions

        if (figure->num == 0 && (*chessPtr)[7][7].num == 0) {
            // They were previously not moved

            if ((*chessPtr)[7][5].name == '.' && (*chessPtr)[7][6].name == '.') {
                // There are no pieces between

                if (gamePtr->blackBoard[7][4] == 0 && gamePtr->blackBoard[7][5] == 0 && gamePtr->blackBoard[7][6] == 0) {
                    // King and pieces between are not attacked

                    gamePtr->shortclash = 1;
                }
            }
        }
    } else if (figure->name == 'k' && x == 4 && y == 0 && (*chessPtr)[0][7].name == 'r') {
        // King and rook are on positions

        if (figure->num == 0 && (*chessPtr)[0][7].num == 0) {
            // They were previously not moved

            if ((*chessPtr)[0][5].name == '.' && (*chessPtr)[0][6].name == '.') {
                // There are no pieces between

                if (gamePtr->whiteBoard[0][4] == 0 && gamePtr->whiteBoard[0][5] == 0 && gamePtr->whiteBoard[0][6] == 0) {
                    // King and pieces between are not attacked

                    gamePtr->shortclash = -1;
                }
            }
        }
    }
}

void longCastling(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    

    if (figure->name == 'K' && x == 4 && y == 7 && (*chessPtr)[7][0].name == 'R') {
        // King and rook are on positions

        if (figure->num == 0 && (*chessPtr)[7][0].num == 0) {
            // They were previously not moved

            if ((*chessPtr)[7][1].name == '.' && (*chessPtr)[7][2].name == '.' && (*chessPtr)[7][3].name == '.') {
                // There are no pieces between

                if (gamePtr->blackBoard[7][1] == 0 && gamePtr->blackBoard[7][2] == 0 && gamePtr->blackBoard[7][3] == 0 && gamePtr->blackBoard[7][4] == 0) {
                    // King and pieces between are not attacked

                    gamePtr->longclash = 1;
                }
            }
        }
    } else if (figure->name == 'k' && x == 4 && y == 0 && (*chessPtr)[0][0].name == 'r') {
        // King and rook are on positions

        if (figure->num == 0 && (*chessPtr)[0][0].num == 0) {
            // They were previously not moved

            if ((*chessPtr)[0][1].name == '.' && (*chessPtr)[0][2].name == '.' && (*chessPtr)[0][3].name == '.') {
                // There are no pieces between

                if (gamePtr->whiteBoard[0][1] == 0 && gamePtr->whiteBoard[0][2] == 0 && gamePtr->whiteBoard[0][3] == 0 && gamePtr->whiteBoard[0][4] == 0) {
                    // King and pieces between are not attacked

                    gamePtr->longclash = -1;
                }
            }
        }
    }
}

void whiteShortClash(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};
    
    gamePtr->shortclash = 0;
    gamePtr->longclash = 0;

    // Move king
    movePiece = (*chessPtr)[7][4];
    (*chessPtr)[7][4] = empty;
    (*chessPtr)[7][6] = movePiece;

    // Move rook
    movePiece = (*chessPtr)[7][7];
    (*chessPtr)[7][7] = empty;
    (*chessPtr)[7][5] = movePiece;


    gamePtr->turn = -gamePtr->turn; // change players
    gamePtr->event = 0;
    (*chessPtr)[7][6].num++; // +1 to number of times a king was moved
    (*chessPtr)[7][5].num++; // +1 to number of times a rook was moved
    allMoves(chessPtr, gamePtr);

    spritesUpdate(chessPtr);
}

void blackShortClash(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};
    
    gamePtr->shortclash = 0;
    gamePtr->longclash = 0;

    // Move king
    movePiece = (*chessPtr)[0][4];
    (*chessPtr)[0][4] = empty;
    (*chessPtr)[0][6] = movePiece;

    // Move rook
    movePiece = (*chessPtr)[0][7];
    (*chessPtr)[0][7] = empty;
    (*chessPtr)[0][5] = movePiece;


    gamePtr->turn = -gamePtr->turn; // change players
    gamePtr->event = 0;
    (*chessPtr)[0][6].num++; // +1 to number of times a king was moved
    (*chessPtr)[0][5].num++; // +1 to number of times a rook was moved
    allMoves(chessPtr, gamePtr);

    spritesUpdate(chessPtr);
}

void whiteLongClash(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};
    
    gamePtr->shortclash = 0;
    gamePtr->longclash = 0;

    // Move king
    movePiece = (*chessPtr)[7][4];
    (*chessPtr)[7][4] = empty;
    (*chessPtr)[7][2] = movePiece;

    // Move rook
    movePiece = (*chessPtr)[7][0];
    (*chessPtr)[7][0] = empty;
    (*chessPtr)[7][3] = movePiece;


    gamePtr->turn = -gamePtr->turn; // change players
    gamePtr->event = 0;
    (*chessPtr)[7][2].num++; // +1 to number of times a king was moved
    (*chessPtr)[7][3].num++; // +1 to number of times a rook was moved
    allMoves(chessPtr, gamePtr);

    spritesUpdate(chessPtr);
}

void blackLongClash(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};
    
    gamePtr->shortclash = 0;
    gamePtr->longclash = 0;

    // Move king
    movePiece = (*chessPtr)[0][4];
    (*chessPtr)[0][4] = empty;
    (*chessPtr)[0][2] = movePiece;

    // Move rook
    movePiece = (*chessPtr)[0][0];
    (*chessPtr)[0][0] = empty;
    (*chessPtr)[0][3] = movePiece;


    gamePtr->turn = -gamePtr->turn; // change players
    gamePtr->event = 0;
    (*chessPtr)[0][2].num++; // +1 to number of times a king was moved
    (*chessPtr)[0][3].num++; // +1 to number of times a rook was moved
    allMoves(chessPtr, gamePtr);

    spritesUpdate(chessPtr);
}

#endif