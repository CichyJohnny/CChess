#ifndef TEXTS_H
#define TEXTS_H

////////////////////////////////////////////////////////////
/// \brief Create a text structure for displaying player's
/// turn. Text is displayed in the center of right panel.
///
/// \param font     font to use
///
/// \return A new sfText object
////////////////////////////////////////////////////////////
sfText* textTurn(sfFont* font);

////////////////////////////////////////////////////////////
/// \brief Create a text structure for displaying player's
/// turn. Text is displayed in the top center of right
/// panel.
///
/// \param font     font to use
///
/// \return A new sfText object
////////////////////////////////////////////////////////////
sfText* textEvent(sfFont* font);

////////////////////////////////////////////////////////////
/// \brief create a text structure for displaying number of
/// round. Text is displayed in the top left corner of
/// right panel.
///
/// \param font     font to use
///
/// \return A new sfText object
////////////////////////////////////////////////////////////
sfText* textCount(sfFont* font);

////////////////////////////////////////////////////////////
/// \brief Create a text structure for displaying player's
/// points. Text is displayed in the top right corner of
/// right panel.
///
/// \param font     font to use
///
/// \return A new sfText object
////////////////////////////////////////////////////////////
sfText* textPoints(sfFont* font);

#endif