// #include "include_define.h"
// #include "moves.h"
// #include "moveboard.h"
// #include "chess_events.h"

#ifndef ACTIONS_H
#define ACTIONS_H

void enPassant(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos, int enPas) {
    struct figure movePiece;
    struct figure empty = {.name='.', .sprite=NULL, .num=0};

    movePiece = (*chessPtr)[selectedPiece.y][selectedPiece.x];
    (*chessPtr)[selectedPiece.y][selectedPiece.x] = empty;
    (*chessPtr)[mousePos.y + enPas][mousePos.x] = empty;
    (*chessPtr)[mousePos.y][mousePos.x] = movePiece;

    gamePtr->turn = -gamePtr->turn; // change players
    gamePtr->event = 0;
    gamePtr->numTurn++;
    (*chessPtr)[mousePos.y][mousePos.x].num++; // +1 to number of times a piece was moved
    gamePtr->shortClash = 0;
    gamePtr->longClash = 0;
    allMoves(chessPtr, gamePtr);

    spritesUpdate(chessPtr);
}

void promote(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i mousePos) {
    if (mousePos.x >= 8 && mousePos.y == 7) {
        if (gamePtr->turn == -1) {
            if (mousePos.x == 8) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'Q';
            
            } else if (mousePos.x == 9) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'R';

            } else if (mousePos.x == 10) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'B';
                
            } else if (mousePos.x == 11) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'N';

            }
        } else if (gamePtr->turn == 1) {
            if (mousePos.x == 8) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'q';
            
            } else if (mousePos.x == 9) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'r';

            } else if (mousePos.x == 10) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'b';
                
            } else if (mousePos.x == 11) {
                (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'n';

            }
        }
        
        allMoves(chessPtr, gamePtr);
        spritesUpdate(chessPtr);
        gamePtr->promote = (sfVector2i){-1, -1};
    }
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
    gamePtr->shortClash = 0;
    gamePtr->longClash = 0;
    allMoves(chessPtr, gamePtr);
    gamePtr->numTurn++;

    spritesUpdate(chessPtr);

    int isPat = 0;

    if (gamePtr->turn == 1) {
        gamePtr->check = isWhiteCheck(chessPtr, gamePtr);
    } else {
        gamePtr->check = isBlackCheck(chessPtr, gamePtr);
    }

    if (gamePtr->check != 0) {
        // If check or mate
        gamePtr->event = 1;

        allPossibilities(chessPtr, gamePtr, gamePtr->check);
        if (gamePtr->possibleMoves == 0) {
            // If there no way to defend king, there is mat

            gamePtr->event = 2;
        } else {
            // Else continue the game
            gamePtr->possibleMoves = 0;
        }
    } else {
        // Check if move does not allow check
        allPossibilities(chessPtr, gamePtr, gamePtr->turn);

        // If pat
        if (gamePtr->possibleMoves == 0 && gamePtr->check == 0) {
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
                gamePtr->event = 3;
            }
            isPat = 0;
        }
 
        // Normal move
        gamePtr->possibleMoves = 0;
    }


    if (movePiece.name == 'P' && mousePos.y == 4) {
        gamePtr->enPassant = (sfVector2i){mousePos.x, 5};
    } else if (movePiece.name == 'p' && mousePos.y == 3) {
        gamePtr->enPassant = (sfVector2i){mousePos.x, 2};
    }


    if (movePiece.name == 'P' && mousePos.y == 0) {
        gamePtr->promote = mousePos;
    } else if (movePiece.name == 'p' && mousePos.y == 7) {
        gamePtr->promote = mousePos;
    }
}


#endif