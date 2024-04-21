#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

void quickSave(struct game *gamePtr, const char *filename);

struct game* loadGameFromFile(struct game *gamePtr, const char *filename);

void quickLoad(struct game *gamePtr, const char *filename);

#endif