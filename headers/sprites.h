// #include "include_define.h"

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

sfSprite* createBackground() {
    sfSprite* background = sfSprite_create();

    sfSprite_setPosition(background, (sfVector2f){8 * SQUARE_SIZE, 0});
    sfSprite_setTexture(background, sfTexture_createFromFile("res/background.png", NULL), sfTrue);

    return background;
}

/*
Simple void function for rendering every sprite on 8x8 chessboard
*/
void drawFigures(sfRenderWindow* window, struct figure chess[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {

            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            sfRenderWindow_drawSprite(window, chess[i][j].sprite, NULL);
        }
    }
}

void spritesUpdate(struct figure (*chess)[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};

            sfSprite_destroy((*chess)[i][j].sprite);
            (*chess)[i][j].sprite = createSprite(position, (*chess)[i][j].name);
            // I have no idea why i have to create new sprite instead of just changing the sprite's position
            // sfSprite_setPosition((*chess)[i][j].sprite, position);
            
        }
    }
}

void drawPromotion(sfRenderWindow* window, struct game *gamePtr) {
    if (gamePtr->promote.x != -1) {
        sfSprite* promotions[4];

        for (int i=0; i<4; i++) {
            promotions[i] = sfSprite_create();
            sfSprite_setPosition(promotions[i], (sfVector2f){(8 + i)*SQUARE_SIZE, 7*SQUARE_SIZE});
        }
        if (gamePtr->turn == -1) {
            sfSprite_setTexture(promotions[0], sfTexture_createFromFile("figures/white-queen.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[1], sfTexture_createFromFile("figures/white-rook.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[2], sfTexture_createFromFile("figures/white-bishop.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[3], sfTexture_createFromFile("figures/white-knight.png", NULL), sfTrue);
        } else if (gamePtr->turn == 1) {
            sfSprite_setTexture(promotions[0], sfTexture_createFromFile("figures/black-queen.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[1], sfTexture_createFromFile("figures/black-rook.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[2], sfTexture_createFromFile("figures/black-bishop.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[3], sfTexture_createFromFile("figures/black-knight.png", NULL), sfTrue);
        }

        sfRectangleShape* square = sfRectangleShape_create();
        int thick = 8;
        sfRectangleShape_setSize(square, (sfVector2f){SQUARE_SIZE - 2*thick, SQUARE_SIZE - 2*thick});
        sfRectangleShape_setFillColor(square, sfWhite);
        sfRectangleShape_setOutlineThickness(square, thick);
        sfRectangleShape_setOutlineColor(square, sfBlack);

        for (int i=0; i<4; i++) {
            sfRectangleShape_setPosition(square, (sfVector2f){(8 + i)*SQUARE_SIZE + thick, 7*SQUARE_SIZE + thick});
            sfRenderWindow_drawRectangleShape(window, square, NULL);

            sfRenderWindow_drawSprite(window, promotions[i], NULL);
        }

        sfRectangleShape_destroy(square);
    }
}

void saveLoadCreate(sfRectangleShape* (*saveLoadRect)[2]) {
    sfColor color;

    sfVector2f savePos = {10 * SQUARE_SIZE, 7 * SQUARE_SIZE};
    (*saveLoadRect)[0] = sfRectangleShape_create();
    sfRectangleShape_setPosition((*saveLoadRect)[0], savePos);
    sfRectangleShape_setSize((*saveLoadRect)[0], (sfVector2f){SQUARE_SIZE, SQUARE_SIZE});
    sfRectangleShape_setTexture((*saveLoadRect)[0], sfTexture_createFromFile("res/save.png", NULL), sfTrue);

    sfVector2f loadPos = {11 * SQUARE_SIZE, 7 * SQUARE_SIZE};
    (*saveLoadRect)[1] = sfRectangleShape_create();
    sfRectangleShape_setPosition((*saveLoadRect)[1], loadPos);
    sfRectangleShape_setSize((*saveLoadRect)[1], (sfVector2f){SQUARE_SIZE, SQUARE_SIZE});
    sfRectangleShape_setTexture((*saveLoadRect)[1], sfTexture_createFromFile("res/load.png", NULL), sfTrue);


}

void drawSaveLoad(sfRenderWindow* window, sfRectangleShape* (*saveLoadRect)[2]) {
    for (int i=0; i<2; i++) {
        sfRenderWindow_drawRectangleShape(window, (*saveLoadRect)[i], NULL);
    }
}

#endif