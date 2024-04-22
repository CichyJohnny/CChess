#ifndef CLASHING_H
#define CLASHING_H

////////////////////////////////////////////////////////////
/// \brief Update game.shortClash with 1 if white short
/// castling is allowed, -1 if black, 0 if none of it.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     king's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void shortCastling(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Update game.longClash with 1 if white long
/// castling is allowed, -1 if black, 0 if none of it.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     king's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void longCastling(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Do white short clashing move and end turn.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void whiteShortClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Do black short clashing move and end turn.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void blackShortClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Do white long clashing move and end turn.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void whiteLongClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Do black long clashing move and end turn.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void blackLongClash(struct figure (*chessPtr)[8][8], struct game *gamePtr);

#endif