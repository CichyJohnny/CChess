#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

////////////////////////////////////////////////////////////
/// \brief Save game structure with all game informations
/// to the bin file.
///
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param filename     string with bin file name
///
////////////////////////////////////////////////////////////
void quickSave(struct game *gamePtr, const char *filename);

////////////////////////////////////////////////////////////
/// \brief Load game structure with all game informations
/// from the bin file.
///
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param filename     string with bin file name
///
/// \return pointer to game structure loaded from bin file
////////////////////////////////////////////////////////////
struct game* loadGameFromFile(struct game *gamePtr, const char *filename);

////////////////////////////////////////////////////////////
/// \brief Load game structure with all game informations
/// from the bin file and update game.
///
/// \param gamePtr      pointer to game structure containing
///                     all game informations
/// \param filename     string with bin file name
///
////////////////////////////////////////////////////////////
void quickLoad(struct game *gamePtr, const char *filename);

#endif