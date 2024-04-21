#ifndef SPRITES_H
#define SPRITES_H

/*
sfSprite function for creating sprite for given piece and position
- for every piece is created texture from file
- textures are stored in directory figures/ in 128x128px resolution
*/
sfSprite* createSprite(sfVector2f position, char name);

sfSprite* createBackground();

/*
Simple void function for rendering every sprite on 8x8 chessboard
*/
void drawFigures(sfRenderWindow* window, struct figure chess[8][8]);

void spritesUpdate(struct figure (*chess)[8][8]);

void drawPromotion(sfRenderWindow* window, struct game *gamePtr);

void saveLoadCreate(sfRectangleShape* (*saveLoadRect)[2]);

void drawSaveLoad(sfRenderWindow* window, sfRectangleShape* (*saveLoadRect)[2]);

#endif