#ifndef MOVEBOARD_H
#define MOVEBOARD_H

////////////////////////////////////////////////////////////
/// \brief Update piece's moveboard with its moves.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     piece's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void canMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Render circles representing possible moves.
///
/// \param window       to display in
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param selectedPiece    position of selected piece that
///                         moves are draw for
///
////////////////////////////////////////////////////////////
void drawMoves(sfRenderWindow* window, struct game *gamePtr, sfVector2i selectedPiece);

////////////////////////////////////////////////////////////
/// \brief Fill int 8x8 array with zeros.
///
/// \param board        8x8 int array
///
////////////////////////////////////////////////////////////
void clearBoard(int board[8][8]);

////////////////////////////////////////////////////////////
/// \brief Iterate through chessboard and update moveboard
/// for every piece.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void allMoves(struct figure (*chessPtr)[8][8], struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Check every move's legality, discard if not
/// legal.
///
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
/// \param position     pawn's position
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void allPossibilities(struct figure (*chessPtr)[8][8], struct game *gamePtr);

#endif