#include "include_define.h"


struct game createGame() {
    struct game game;

    game.turn = 1;
    game.numTurn = 1;
    game.event = 0;
    game.possibleMoves = 0;
    game.shortClash = 0;
    game.longClash = 0;
    game.check = 0;
    game.enPassant = (sfVector2i){-1, -1};
    game.promote = (sfVector2i){-1, -1};

    return game;
}

sfRenderWindow* createWindow() {
    // Window settings
    sfVideoMode mode = {12 * SQUARE_SIZE, 8 * SQUARE_SIZE, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "CChess", sfTitlebar | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 30);

    // Set icon
    sfImage* icon = sfImage_createFromFile("res/icon.png");
    sfRenderWindow_setIcon(window, sfImage_getSize(icon).x, sfImage_getSize(icon).y, sfImage_getPixelsPtr(icon));

    return window;
}