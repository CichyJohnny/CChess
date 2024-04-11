// #include "include_define.h"
// #include "sprites.h"
// #include "moveboard.h"

#ifndef CLASHING_H
#define CLASHING_H

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