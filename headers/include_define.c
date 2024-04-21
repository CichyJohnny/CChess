#include <SFML/Graphics.h>
#include <SFML/Window.h>
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