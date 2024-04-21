#include "include_define.h"
#include "moveboard.h"

/*
Void function that checks possible moves by calling function for selected piece
*/
void canMove(struct figure (*chessPtr)[8][8], sfVector2i position, int moveBoard[8][8], struct game *gamePtr) {
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

/*
Void function that render green squares representing possible moves for selected piece
*/
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

                if (gamePtr->chess[i][j].name != '.') {

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

            canMove(chessPtr, position, (*chessPtr)[i][j].moveBoard, gamePtr);
        }
    }
}

void allPossibilities(struct figure (*chessPtr)[8][8], struct game *gamePtr, int check) {
    struct figure nextChess[8][8];
    struct figure (*nextChessPtr)[8][8] = &nextChess;

    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};

    struct game copyGame = *gamePtr;
    struct game *copyGamePtr = &copyGame;

    int newWhiteCheck, newBlackCheck;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (isWhiteBlack((*chessPtr)[i][j].name) == check) {

                for (int n=0; n<8; n++) {
                    for (int m=0; m<8; m++) {
                        if((*chessPtr)[i][j].moveBoard[n][m] == 1) {

                            // Copy of chess list
                            copyChess(chessPtr, nextChessPtr);
                            copyGame = *gamePtr;

                            // Moving piece on copied board
                            movePiece = nextChess[i][j];
                            nextChess[i][j] = empty; // clear square
                            nextChess[n][m] = movePiece; // movie piece

                            // Computing all moves after the move
                            allMoves(nextChessPtr, copyGamePtr);

                            // We check if there is a check after the move
                            newWhiteCheck = isWhiteCheck(nextChessPtr, copyGamePtr);
                            newBlackCheck = isBlackCheck(nextChessPtr, copyGamePtr);

                            if (newWhiteCheck == check || newBlackCheck == check) {
                                // You still are checked
                                // Discard changes
                                (*chessPtr)[i][j].moveBoard[n][m] = 0; // Disallow this move
                                nextChess[i][j] = movePiece; // revert move
                                nextChess[n][m] = empty; // revert move
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
