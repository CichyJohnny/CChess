#include "include_define.h"
#include "save_load.h"
#include "sprites.h"

void quickSave(struct game *gamePtr, const char *filename) {
    FILE *fp;
    fp = fopen(filename, "wb"); // Open file for writing in binary mode

    // Check if file opened successfully
    if (fp == NULL) {
        return;
    }

    // Write the game struct members to file
    fwrite(gamePtr, sizeof(struct game), 1, fp);
    
    // Write chess array data
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            fwrite(&((gamePtr->chess)[i][j]), sizeof(struct figure), 1, fp);
        }
    }

    // Close file
    fclose(fp);
}

struct game* loadGameFromFile(struct game *gamePtr, const char *filename) {
    FILE *fp;
    fp = fopen(filename, "rb"); // Open file for reading in binary mode

    // Check if file opened successfully
    if (fp == NULL) {
        // Return NULL if file not found
        return NULL;
    }

    // Read the game struct members from file
    fread(gamePtr, sizeof(struct game), 1, fp);

    // Read chess array data
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            fread(&((gamePtr->chess)[i][j]), sizeof(struct figure), 1, fp);
        }
    }

    // Close file
    fclose(fp);

    return gamePtr;
}

void quickLoad(struct game *gamePtr, const char *filename) {
    gamePtr = loadGameFromFile(gamePtr, filename);
    
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            (gamePtr->chess)[i][j].sprite = createSprite(position, (gamePtr->chess)[i][j].name);
        }
    }
}
