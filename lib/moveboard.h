#ifndef MOVEBOARD_H
#define MOVEBOARD_H

/*
Void function that checks possible moves by calling function for selected piece
*/
void canMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

/*
Void function that render green squares representing possible moves for selected piece
*/
void drawMoves(sfRenderWindow* window, int moveBoard[8][8], struct game *gamePtr);
/*
Simple void function that changes every int in 2d moveBoard to 0
*/
void clearBoard(int board[8][8]);

void allMoves(struct figure (*chessPtr)[8][8], struct game *gamePtr);

void allPossibilities(struct figure (*chessPtr)[8][8], struct game *gamePtr, int check);


#endif