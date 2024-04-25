#ifndef ACTIONS_H
#define ACTIONS_H

////////////////////////////////////////////////////////////
/// \brief Do en passant with selected pawn and end turn.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param selectedPiece    position of selected pawn
/// \param mousePos     position of place being clicked
/// \param enPas        1 if white does en passant, -1 if
///                     black
///
////////////////////////////////////////////////////////////
void enPassant(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos, int enPas);

////////////////////////////////////////////////////////////
/// \brief Promote pawn to selected piece and check if mate.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param selectedPiece    position of selected pawn
/// \param mousePos     position of place being clicked
///
////////////////////////////////////////////////////////////
void promote(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i mousePos);

////////////////////////////////////////////////////////////
/// \brief Do normal move check if mate and end turn.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param selectedPiece    position of selected pawn
/// \param mousePos     position of place being clicked
///
////////////////////////////////////////////////////////////
void normalMove(struct figure (*chessPtr)[8][8], struct game *gamePtr, sfVector2i selectedPiece, sfVector2i mousePos);

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