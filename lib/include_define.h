#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>

#ifndef INCUDE_DEFINE_H
#define INCUDE_DEFINE_H

#define SQUARE_SIZE 128 // Base square size equal to textures resolution

// Structure of chess piece
struct figure {
    char name; // Its name
    sfSprite* sprite; // Its sprite with texture
    int num; // Times of being moved
    int possibleMoves; // Number of possible moves
    int moveBoard[8][8]; // MoveBoard of possible moves
};

// Structure of game's properties
struct game {
    int turn; // Player's turn (1 if white's, -1 if black's)
    int numTurn; // Number of turn
    int whiteBoard[8][8]; // Board of fields being attacked by white pieces
    int blackBoard[8][8]; // Board of fields being attacked by black pieces
    int event; // Current chess event (0 if none, 2 if mate, 3 if stale mate)
    int possibleMoves; // Number of legal moves
    int shortClash; // Is short clash legal (0 if not, 1 if for white, -1 if for black)
    int longClash; // Is black clash legal (0 if not, 1 if for white, -1 if for black)
    int check;  // Is king checked (0 if not, 1 if white is, -1 if black is)
    sfVector2i enPassant; // Position of possible en passant
    sfVector2i promote; // Position of promoted pawn

    struct figure chess[8][8]; // chess 8x8 array with pieces
};

////////////////////////////////////////////////////////////
/// \brief Init game structure with essential parameters.
///
/// \return a new struct game with initial parameters
////////////////////////////////////////////////////////////
struct game createGame();

#endif