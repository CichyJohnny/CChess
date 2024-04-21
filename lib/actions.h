#ifndef ACTIONS_H
#define ACTIONS_H

void enPassant(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos, int enPas);

void promote(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i mousePos);

void normalMove(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos);



#endif