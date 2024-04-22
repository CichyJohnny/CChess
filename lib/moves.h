#ifndef MOVES_H
#define MOVES_H

#define WHITE "PRNBQK"
#define BLACK "prnbqk"

////////////////////////////////////////////////////////////
/// \brief Check if piece of given name is white or black.
///
/// \param name      name of given piece
///
/// \return 1 if white, -1 if black or 0 if none of it
////////////////////////////////////////////////////////////
int isWhiteBlack(char name);

////////////////////////////////////////////////////////////
/// \brief Update pawn's move board with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     pawn's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void pawnMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Update knight's move board with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     knight's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void knightMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Update rook's move board with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     rook's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void rookMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Update bishop's move board with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     bishop's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void bishopMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Update queen's move board with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     queen's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void queenMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Update king's move board with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     pawn's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void kingMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);


#endif