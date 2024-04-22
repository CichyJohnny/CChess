#ifndef SPRITES_H
#define SPRITES_H

////////////////////////////////////////////////////////////
/// \brief Create a sprite structure with its texture 
/// for the given piece's name.
///
/// \param position     position for later displaying
/// \param name         name of given piece
///
/// \return A new sfSprite object
////////////////////////////////////////////////////////////
sfSprite* createSprite(sfVector2f position, char name);

////////////////////////////////////////////////////////////
/// \brief Create a sprite structure with its texture 
/// containing background image.
///
/// \return A new sfSprite object
////////////////////////////////////////////////////////////
sfSprite* createBackground();

////////////////////////////////////////////////////////////
/// \brief Render all figures on chessboard in the given
/// window.
///
/// \param window       window to display in
/// \param chess        8x8 array of figures representing
///                     chessboard
///
////////////////////////////////////////////////////////////
void drawFigures(sfRenderWindow* window, struct figure chess[8][8]);

////////////////////////////////////////////////////////////
/// \brief Destroy previous sprites and create new ones
/// with updated position.
///
/// \param window       window to display in
/// \param chessPtr     pointer to an 8x8 array of figures
///                     representing chessboard
///
////////////////////////////////////////////////////////////
void spritesUpdate(struct figure (*chessPtr)[8][8]);

////////////////////////////////////////////////////////////
/// \brief Render promote options for pawn.
///
/// \param window       window to display in
/// \param gamePtr      pointer to game structure containing
///                     all game informations
///
////////////////////////////////////////////////////////////
void drawPromotion(sfRenderWindow* window, struct game *gamePtr);

////////////////////////////////////////////////////////////
/// \brief Create a sprite structure with its texture 
/// containing save and load buttons image.
///
/// \param saveLoadRect pointer to 2-elements array with
///                     save and load sprites
///
////////////////////////////////////////////////////////////
void saveLoadCreate(sfRectangleShape* (*saveLoadRect)[2]);

////////////////////////////////////////////////////////////
/// \brief Create a sprite structure with its texture 
/// containing save and load buttons image.
///
/// \param window       window to display in
/// \param saveLoadRect pointer to 2-elements array with
///                     save and load sprites
///
////////////////////////////////////////////////////////////
void drawSaveLoad(sfRenderWindow* window, sfRectangleShape* (*saveLoadRect)[2]);

#endif