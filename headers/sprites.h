#include "include_define.h"

#ifndef SPRITES_H
#define SPRITES_H

/*
sfSprite function for creating sprite for given piece and position
- for every piece is created texture from file
- textures are stored in directory figures/ in 128x128px resolution
*/
sfSprite* createSprite(sfVector2f position, char name) {
    sfSprite* sprite = sfSprite_create();
    sfSprite_setPosition(sprite, position);

    sfTexture* texture = NULL;
    if (name == 'p') {
        texture = sfTexture_createFromFile("figures/black-pawn.png", NULL);
    } else if (name == 'P') {
        texture = sfTexture_createFromFile("figures/white-pawn.png", NULL);
    } else if (name == 'r') {
        texture = sfTexture_createFromFile("figures/black-rook.png", NULL);
    } else if (name == 'R') {
        texture = sfTexture_createFromFile("figures/white-rook.png", NULL);
    } else if (name == 'n') {
        texture = sfTexture_createFromFile("figures/black-knight.png", NULL);
    } else if (name == 'N') {
        texture = sfTexture_createFromFile("figures/white-knight.png", NULL);
    } else if (name == 'b') {
        texture = sfTexture_createFromFile("figures/black-bishop.png", NULL);
    } else if (name == 'B') {
        texture = sfTexture_createFromFile("figures/white-bishop.png", NULL);
    } else if (name == 'q') {
        texture = sfTexture_createFromFile("figures/black-queen.png", NULL);
    } else if (name == 'Q') {
        texture = sfTexture_createFromFile("figures/white-queen.png", NULL);
    } else if (name == 'k') {
        texture = sfTexture_createFromFile("figures/black-king.png", NULL);
    } else if (name == 'K') {
        texture = sfTexture_createFromFile("figures/white-king.png", NULL);
    }

    sfSprite_setTexture(sprite, texture, sfTrue);

    return sprite;
}

/*
Simple void function for rendering every sprite on 8x8 chessboard
*/
void drawFigures(sfRenderWindow* window, struct figure chess[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {

            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            chess[i][j].sprite = createSprite(position, chess[i][j].name);
            sfRenderWindow_drawSprite(window, chess[i][j].sprite, NULL);
        }
    }
}

#endif