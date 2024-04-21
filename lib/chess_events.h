#ifndef CHESS_EVENTS_H
#define CHESS_EVENTS_H

void copyChess(struct figure (*chessPtr)[8][8], struct figure (*prevChessPtr)[8][8]);

int isWhiteCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr);

int isBlackCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr);

int countPoints(struct game *gamePtr);


#endif