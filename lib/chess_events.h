#ifndef CHESS_EVENTS_H
#define CHESS_EVENTS_H

////////////////////////////////////////////////////////////
/// \brief Make a copy of chess 8x8 struct figure array.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param prevChessPtr pointer to a new 8x8 array of
///                     figures representing chessboard
///
////////////////////////////////////////////////////////////
void copyChess(struct figure (*chessPtr)[8][8], struct figure (*newChessPtr)[8][8]);

////////////////////////////////////////////////////////////
/// \brief Check if white king is attacked by black.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
/// \return 1 if white is checked, 0 if not
////////////////////////////////////////////////////////////
int isWhiteCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Check if black king is attacked by white.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
/// \return -1 if black is checked, 0 if not
////////////////////////////////////////////////////////////
int isBlackCheck(struct figure (*chessPtr)[8][8], struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Count figures' points for later displaying it.
/// 9 for a Queen, 5 for a Rook, 3 for a Knight and Bishop,
/// 1 for a pawn.
///
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
/// \return sum of white's and black's points
////////////////////////////////////////////////////////////
int countPoints(struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Check for check mate or stale mate
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void isMates(struct figure (*chessPtr)[8][8], struct game* gamePtr);

#endif