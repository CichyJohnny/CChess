#include "include_define.h"
#include "sprites.h"

sfSprite* createSprite(sfVector2f position, char name) {
    sfSprite* sprite = sfSprite_create();
    sfSprite_setPosition(sprite, position);

    sfTexture* texture = NULL;
    switch (name) {
        case 'p':
            texture = sfTexture_createFromFile("res/figures/black-pawn.png", NULL);
            break;
        case 'P':
            texture = sfTexture_createFromFile("res/figures/white-pawn.png", NULL);
            break;
        case 'r':
            texture = sfTexture_createFromFile("res/figures/black-rook.png", NULL);
            break;
        case 'R':
            texture = sfTexture_createFromFile("res/figures/white-rook.png", NULL);
            break;
        case 'n':
            texture = sfTexture_createFromFile("res/figures/black-knight.png", NULL);
            break;
        case 'N':
            texture = sfTexture_createFromFile("res/figures/white-knight.png", NULL);
            break;
        case 'b':
            texture = sfTexture_createFromFile("res/figures/black-bishop.png", NULL);
            break;
        case 'B':
            texture = sfTexture_createFromFile("res/figures/white-bishop.png", NULL);
            break;
        case 'q':
            texture = sfTexture_createFromFile("res/figures/black-queen.png", NULL);
            break;
        case 'Q':
            texture = sfTexture_createFromFile("res/figures/white-queen.png", NULL);
            break;
        case 'k':
            texture = sfTexture_createFromFile("res/figures/black-king.png", NULL);
            break;
        case 'K':
            texture = sfTexture_createFromFile("res/figures/white-king.png", NULL);
            break;
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

void drawFigures(sfRenderWindow* window, struct figure chess[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRenderWindow_drawSprite(window, chess[i][j].sprite, NULL);
        }
    }
}

void spritesUpdate(struct figure (*chessPtr)[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};

            sfSprite_destroy((*chessPtr)[i][j].sprite);
            (*chessPtr)[i][j].sprite = createSprite(position, (*chessPtr)[i][j].name);
            // I have no idea why I have to create new sprite instead of just updating the sprite's position
            // sfSprite_setPosition((*chessPtr)[i][j].sprite, position);
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
            sfSprite_setTexture(promotions[0], sfTexture_createFromFile("res/figures/white-queen.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[1], sfTexture_createFromFile("res/figures/white-rook.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[2], sfTexture_createFromFile("res/figures/white-bishop.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[3], sfTexture_createFromFile("res/figures/white-knight.png", NULL), sfTrue);
        } else if (gamePtr->turn == 1) {
            sfSprite_setTexture(promotions[0], sfTexture_createFromFile("res/figures/black-queen.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[1], sfTexture_createFromFile("res/figures/black-rook.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[2], sfTexture_createFromFile("res/figures/black-bishop.png", NULL), sfTrue);
            sfSprite_setTexture(promotions[3], sfTexture_createFromFile("res/figures/black-knight.png", NULL), sfTrue);
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
    sfVector2f savePos = {10 * SQUARE_SIZE, 7 * SQUARE_SIZE};
    sfVector2f loadPos = {11 * SQUARE_SIZE, 7 * SQUARE_SIZE};

    (*saveLoadRect)[0] = sfRectangleShape_create();
    sfRectangleShape_setPosition((*saveLoadRect)[0], savePos);
    sfRectangleShape_setSize((*saveLoadRect)[0], (sfVector2f){SQUARE_SIZE, SQUARE_SIZE});
    sfRectangleShape_setTexture((*saveLoadRect)[0], sfTexture_createFromFile("res/save.png", NULL), sfTrue);

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
