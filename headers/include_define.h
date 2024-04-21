#include <SFML/Graphics.h>
#include <SFML/Window.h>

#ifndef INCUDE_DEFINE_H
#define INCUDE_DEFINE_H

#define SQUARE_SIZE 128 // base square size equal to textures resolution

// Structure of chess piece
struct figure {
    char name; // bts name
    sfSprite* sprite; // its sprite
    int num; // times of being moved
    int moveBoard[8][8]; // moveBoard of possible moves
    int possibleMoves; // number of possible moves
};

// Structure of game's properties
struct game {
    int turn; // which player it's turn (1 if white's, -1 if black's)
    int numTurn;
    int win; // 0 if game is still on, 1 if white won, -1 if black won, 2 if pat
    int whiteBoard[8][8];
    int blackBoard[8][8];
    int event;
    int possibleMoves;
    int shortClash;
    int longClash;
    int check;
    sfVector2i enPassant;
    sfVector2i promote;

    struct figure chess[8][8];
};

struct game createGame();

#endif