#ifndef CHESSBOARD_H
#define CHESSBOARD_H

////////////////////////////////////////////////////////////
/// \brief Create one of chessboard's square.
///
/// \param chessPtr     position for new square
/// \param size         size of new square
/// \param color        color of new square
///
/// \return a new sfRectangleShape object
////////////////////////////////////////////////////////////
sfRectangleShape* createSquare(sfVector2f position, sfVector2f size, sfColor color);

////////////////////////////////////////////////////////////
/// \brief Create all fields of chessboard.
///
/// \param squares      8x8 sfRectangleShape* array of
///                     square fields
///
////////////////////////////////////////////////////////////
void defineChessBoard (sfRectangleShape* squares[8][8]);

////////////////////////////////////////////////////////////
/// \brief Render chessboard's fields.
///
/// \param window       window to displaying in
/// \param squares      8x8 sfRectangleShape* array of
///                     square fields
///
////////////////////////////////////////////////////////////
void drawChessboard(sfRenderWindow* window, sfRectangleShape* squares[8][8]);

#endif