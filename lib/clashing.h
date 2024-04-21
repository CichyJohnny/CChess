#ifndef CLASHING_H
#define CLASHING_H

void shortCastling(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

void longCastling(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

void whiteShortClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

void blackShortClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

void whiteLongClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

void blackLongClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);


#endif