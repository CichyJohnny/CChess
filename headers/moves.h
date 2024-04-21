#ifndef MOVES_H
#define MOVES_H

#define WHITE "PRNBQK"
#define BLACK "prnbqk"

/*
Int function that checks if piece is white or black
- function compares piece's name with WHITE or BLACK chars
- returns -1 for black piece
- returns 1 for white piece
- returns 0 in other cases
*/
int isWhiteBlack(char name);

/*
Void function that updates moveBoard array with selected pawn's moves
- checks if pawn is white or black
- if first move and if nothing is ahead, then updates moveBoard
- if enemy is in diagonal front square, updates moveboard
*/
void pawnMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

/*
Void function that updates moveBoard array with selected knight's moves
- function iterates through eight possible moves
- if move is on board and alliant is not attacked, updates moveboard
*/
void knightMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

/*
Void function that updates moveBoard array with selected rook's moves
- function iterates in vertically and horrizontally directions
- if something in the way or outside chessboard, breaks
- otherwise, updates moveBoard
*/
void rookMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

/*
Void function that updates moveBoard array with selected bishop's moves
- function in four diagonal directions
- if something in the way or outside chessboard, breaks
- otherwise, updates moveBoard
*/
void bishopMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

/*
Void function that updates moveBoard array with selected queen's moves
- function updates moveBoard with combination of rook's and bishop's moves
*/
void queenMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

/*
Void function that updates moveBoard array with selected kings's moves
- function iterates through eight possible moves
- if move is on board and alliant is not attacked, updates moveboard
*/
void kingMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);


#endif