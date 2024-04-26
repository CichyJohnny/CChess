#include "include_define.h"
#include "actions.h"
#include "moveboard.h"
#include "chess_events.h"
#include "sprites.h"

void enPassant(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos, int enPas) {
    struct figure movePiece;
    struct figure empty = {.name='.', .sprite=NULL, .num=0};

    movePiece = (*chessPtr)[selectedPiece.y][selectedPiece.x];
    (*chessPtr)[selectedPiece.y][selectedPiece.x] = empty;
    (*chessPtr)[mousePos.y + enPas][mousePos.x] = empty; // capture the enemy pawn
    (*chessPtr)[mousePos.y][mousePos.x] = movePiece;

    gamePtr->turn = -gamePtr->turn;
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
            switch (mousePos.x) {
                case 8:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'Q';
                    break;
                case 9:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'R';
                    break;
                case 10:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'B';
                    break;
                case 11:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'N';
                    break;
            }
        } else if (gamePtr->turn == 1) {
            switch (mousePos.x) {
                case 8:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'q';
                    break;
                case 9:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'r';
                    break;
                case 10:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'b';
                    break;
                case 11:
                    (*chessPtr)[gamePtr->promote.y][gamePtr->promote.x].name = 'n';
                    break;
            }
        }
        
        allMoves(chessPtr, gamePtr);
        spritesUpdate(chessPtr);

        gamePtr->promote = (sfVector2i){-1, -1};

        isMates(chessPtr, gamePtr);
    }
}

void normalMove(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos) {
    struct figure movePiece;
    struct figure empty = {.name='.', .sprite=NULL};

    movePiece = (*chessPtr)[selectedPiece.y][selectedPiece.x];
    (*chessPtr)[selectedPiece.y][selectedPiece.x] = empty; // clear square
    (*chessPtr)[mousePos.y][mousePos.x] = movePiece; // movie piece

    gamePtr->turn = -gamePtr->turn;
    gamePtr->numTurn++;
    gamePtr->event = 0;
    (*chessPtr)[mousePos.y][mousePos.x].num++; // +1 to number of times a piece was moved
    gamePtr->shortClash = 0;
    gamePtr->longClash = 0;

    allMoves(chessPtr, gamePtr);
    spritesUpdate(chessPtr);

    isMates(chessPtr, gamePtr);

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
