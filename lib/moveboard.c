#include "include_define.h"
#include "moveboard.h"
#include "chess_events.h"
#include "moves.h"

void canMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];

    if (figure->name == 'P' || figure->name == 'p') {
        pawnMove(chessPtr, position, gamePtr);
    } else if (figure->name == 'N' || figure->name == 'n') {
        knightMove(chessPtr, position, gamePtr);
    } else if (figure->name == 'R' || figure->name == 'r') {
        rookMove(chessPtr, position, gamePtr);
    } else if (figure->name == 'B' || figure->name == 'b') {
        bishopMove(chessPtr, position, gamePtr);
    } else if (figure->name == 'Q' || figure->name == 'q') {
        queenMove(chessPtr, position, gamePtr);
    } else if (figure->name == 'K' || figure->name == 'k') {
        kingMove(chessPtr, position, gamePtr);
    }
}

void drawMoves(sfRenderWindow* window, int moveBoard[8][8], struct game *gamePtr) {
    int radius = 32;
    int thick = 5;
    sfColor color = sfColor_fromRGBA(0, 0, 0, 96);

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (moveBoard[i][j] == 1) {
                
                sfVector2f position = {(SQUARE_SIZE/2 - radius) + j * SQUARE_SIZE, (SQUARE_SIZE/2 - radius) + i * SQUARE_SIZE};

                sfCircleShape *circle = sfCircleShape_create();
                sfCircleShape_setRadius(circle, radius);
                sfCircleShape_setFillColor(circle, color);
                sfCircleShape_setPosition(circle, position);

                sfRenderWindow_drawCircleShape(window, circle, NULL);

                sfCircleShape_destroy(circle);

                if (gamePtr->chess[i][j].name != '.' || (gamePtr->enPassant.x == j && gamePtr->enPassant.y == i)) {

                    sfVector2f pos2 = {thick + j * SQUARE_SIZE, thick + i * SQUARE_SIZE};

                    sfCircleShape *outlineCircle = sfCircleShape_create();

                    sfCircleShape_setRadius(outlineCircle, 64 - thick);
                    sfCircleShape_setFillColor(outlineCircle, sfTransparent);
                    sfCircleShape_setPosition(outlineCircle, pos2);
                    sfCircleShape_setOutlineColor(outlineCircle, color); // Set the outline color of the circle
                    sfCircleShape_setOutlineThickness(outlineCircle, thick);

                    sfRenderWindow_drawCircleShape(window, outlineCircle, NULL);

                    sfCircleShape_destroy(outlineCircle);
                }
            }
        }
    }    
}

/*
Simple void function that changes every int in 2d moveBoard to 0
*/
void clearBoard(int board[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[i][j] = 0;
        }
    }
}

void allMoves(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    sfVector2i position;

    clearBoard(gamePtr->whiteBoard);
    clearBoard(gamePtr->blackBoard);

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            position = (sfVector2i){j, i};
            clearBoard((*chessPtr)[i][j].moveBoard);

            canMove(chessPtr, position, gamePtr);
        }
    }
}

void allPossibilities(struct figure (*chessPtr)[8][8], struct game *gamePtr) {
    struct figure newChess[8][8];
    struct figure (*newChessPtr)[8][8] = &newChess;

    struct figure movePiece;
    struct figure empty = {.name='.', .sprite=NULL};

    struct game copyGame = *gamePtr;
    struct game *copyGamePtr = &copyGame;

    int newWhiteCheck, newBlackCheck;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (isWhiteBlack((*chessPtr)[i][j].name) == gamePtr->turn) {

                for (int n=0; n<8; n++) {
                    for (int m=0; m<8; m++) {
                        if((*chessPtr)[i][j].moveBoard[n][m] == 1) {

                            // Copy of chess list
                            copyChess(chessPtr, newChessPtr);
                            copyGame = *gamePtr;

                            // Moving piece on copied board
                            movePiece = newChess[i][j];
                            newChess[i][j] = empty; // clear square
                            newChess[n][m] = movePiece; // movie piece

                            // Computing all moves after the move
                            allMoves(newChessPtr, copyGamePtr);

                            // We check if there is a check after the move
                            newWhiteCheck = isWhiteCheck(newChessPtr, copyGamePtr);
                            newBlackCheck = isBlackCheck(newChessPtr, copyGamePtr);

                            if (newWhiteCheck == gamePtr->turn || newBlackCheck == gamePtr->turn) {
                                // You still are checked
                                // Discard changes
                                (*chessPtr)[i][j].moveBoard[n][m] = 0; // Disallow this move
                                newChess[i][j] = movePiece; // revert move
                                newChess[n][m] = empty; // revert move
                            } else {
                                gamePtr->possibleMoves++;
                            }
                        }
                    }
                }
            }
        }
    }
}
