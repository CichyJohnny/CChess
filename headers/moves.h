#include "include_define.h"
#include <stdio.h>

#ifndef MOVES_H
#define MOVES_H

#define WHITE "PRNBQK"
#define BLACK "prnbqk"

/*
Int function that checks if piece is white or black
- function compares piece's name with WHITE or BLACK chars
- returns -1 for black piece
- returns 1 for white piece
- returns 0 in other cases
*/
int isWhiteBlack(char name) {
    for (int i=0; i<6; i++) {
        if (name == WHITE[i]) {
            return 1;
        } else if (name == BLACK[i]) {
            return -1;
        }
    }
    return 0;
}

/*
Void function that updates moveBoard array with selected pawn's moves
- checks if pawn is white or black
- if first move and if nothing is ahead, then updates moveBoard
- if enemy is in diagonal front square, updates moveboard
*/
void pawnMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];

    if (figure->name == 'P') {
        if (y - 1 >= 0 && (*chessPtr)[y - 1][x].name == '.') {   
            figure->moveBoard[y - 1][x] = 1;
            (*gamePtr).whiteBoard[y - 1][x] = 1;
            if (figure->num == 0  && (*chessPtr)[y - 2][x].name == '.') {
                figure->moveBoard[y - 2][x] = 1;
                (*gamePtr).whiteBoard[y - 2][x] = 1;
            }
        }
        if (y - 1 >= 0 && x - 1 >= 0 && isWhiteBlack((*chessPtr)[y - 1][x - 1].name) == -1) {
            figure->moveBoard[y - 1][x - 1] = 1;
            (*gamePtr).whiteBoard[y - 1][x - 1] = 1;
        }
        if (y - 1 >= 0 && x + 1 <= 7 && isWhiteBlack((*chessPtr)[y - 1][x + 1].name) == -1) {
            figure->moveBoard[y - 1][x + 1] = 1;
            (*gamePtr).whiteBoard[y - 1][x + 1] = 1;
        }
    } else {
        if (y + 1 <= 7 && (*chessPtr)[y + 1][x].name == '.') {   
            figure->moveBoard[y + 1][x] = 1;
            (*gamePtr).blackBoard[y + 1][x] = 1;
            if (figure->num == 0  && (*chessPtr)[y + 2][x].name == '.') {
                figure->moveBoard[y + 2][x] = 1;
                (*gamePtr).blackBoard[y + 2][x] = 1;
            }
        }
        if (y + 1 <= 7 && x - 1 >= 0 && isWhiteBlack((*chessPtr)[y + 1][x - 1].name) == 1) {
            figure->moveBoard[y + 1][x - 1] = 1;
            (*gamePtr).blackBoard[y + 1][x - 1] = 1;
        }
        if (y + 1 <= 7 && x + 1 <= 7 && isWhiteBlack((*chessPtr)[y + 1][x + 1].name) == 1) {
            figure->moveBoard[y + 1][x + 1] = 1;
            (*gamePtr).blackBoard[y + 1][x + 1] = 1;
        }
    } 
}

/*
Void function that updates moveBoard array with selected knight's moves
- function iterates through eight possible moves
- if move is on board and alliant is not attacked, updates moveboard
*/
void knightMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack((*chessPtr)[y][x].name);

    sfVector2i dirs[8] = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
    int vec_x, vec_y;

    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;
        if (vec_y >= 0 && vec_x >= 0 && vec_y <= 7 && vec_x <= 7 && isWhiteBlack((*chessPtr)[vec_y][vec_x].name) != color) {
            figure->moveBoard[vec_y][vec_x] = 1;

            if (color == 1) {(*gamePtr).whiteBoard[vec_y][vec_x] = 1;} else {(*gamePtr).blackBoard[vec_y][vec_x] = 1;}
        }
    }
}

/*
Void function that updates moveBoard array with selected rook's moves
- function iterates in vertically and horrizontally directions
- if something in the way or outside chessboard, breaks
- otherwise, updates moveBoard
*/
void rookMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack((*chessPtr)[y][x].name);
    int name;

    // Iteration to the left
    for (int i=1; x - i >= 0; i++) {
        name = isWhiteBlack((*chessPtr)[y][x - i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y][x - i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y][x - i] = 1;} else {(*gamePtr).blackBoard[y][x - i] = 1;}

            break;
        } else {
            figure->moveBoard[y][x - i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y][x - i] = 1;} else {(*gamePtr).blackBoard[y][x - i] = 1;}
        }
    }
    // Iteration to the right
    for (int i=1; x + i <= 7; i++) {
        name = isWhiteBlack((*chessPtr)[y][x + i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y][x + i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y][x + i] = 1;} else {(*gamePtr).blackBoard[y][x + i] = 1;}

            break;
        } else {
            figure->moveBoard[y][x + i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y][x +- i] = 1;} else {(*gamePtr).blackBoard[y][x + i] = 1;}
        }
    }
    // Iteration upwards
    for (int i=1; y - i >= 0; i++) {
        name = isWhiteBlack((*chessPtr)[y - i][x].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y - i][x] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y - i][x] = 1;} else {(*gamePtr).blackBoard[y - i][x] = 1;}

            break;
        } else {
            figure->moveBoard[y - i][x] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y - i][x] = 1;} else {(*gamePtr).blackBoard[y - i][x] = 1;}

        }
    }
    // Iteration downwards
    for (int i=1; y + i <= 7; i++) {
        name = isWhiteBlack((*chessPtr)[y + i][x].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y + i][x] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y + i][x] = 1;} else {(*gamePtr).blackBoard[y + i][x] = 1;}

            break;
        } else {
            figure->moveBoard[y + i][x] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y + i][x] = 1;} else {(*gamePtr).blackBoard[y + i][x] = 1;}
        }
    }
}

/*
Void function that updates moveBoard array with selected bishop's moves
- function in four diagonal directions
- if something in the way or outside chessboard, breaks
- otherwise, updates moveBoard
*/
void bishopMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack(figure->name);
    int name;

    // Iteration top left
    for (int i=1; x - i >= 0 && y - i >= 0; i++) {
        name = isWhiteBlack((*chessPtr)[y - i][x - i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y - i][x - i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y - i][x - i] = 1;} else {(*gamePtr).blackBoard[y - i][x - i] = 1;}

            break;
        } else {
            figure->moveBoard[y - i][x - i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y - i][x - i] = 1;} else {(*gamePtr).blackBoard[y - i][x - i] = 1;}
        }
    }
    // Iteration top right
    for (int i=1; x + i <= 7 && y - i >= 0; i++) {
        name = isWhiteBlack((*chessPtr)[y - i][x + i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y - i][x + i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y - i][x + i] = 1;} else {(*gamePtr).blackBoard[y - i][x + i] = 1;}

            break;
        } else {
            figure->moveBoard[y - i][x + i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y - i][x + i] = 1;} else {(*gamePtr).blackBoard[y - i][x + i] = 1;}
        }
    }
    // Iteration down right
    for (int i=1; x + i <= 7 && y + i <= 7; i++) {
        name = isWhiteBlack((*chessPtr)[y + i][x + i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y + i][x + i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y + i][x + i] = 1;} else {(*gamePtr).blackBoard[y + i][x + i] = 1;}

            break;
        } else {
            figure->moveBoard[y + i][x + i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y + i][x + i] = 1;} else {(*gamePtr).blackBoard[y + i][x + i] = 1;}
        }
    }
    // Iteration down left
    for (int i=1; x - i >= 0 && y + i <= 7; i++) {
        name = isWhiteBlack((*chessPtr)[y + i][x - i].name);

        if (name == color) {
            break;
        } else if (name == -color) {
            figure->moveBoard[y + i][x - i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y + i][x - i] = 1;} else {(*gamePtr).blackBoard[y + i][x - i] = 1;}

            break;
        } else {
            figure->moveBoard[y + i][x - i] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[y + i][x - i] = 1;} else {(*gamePtr).blackBoard[y + i][x - i] = 1;}
        }
    }
}

/*
Void function that updates moveBoard array with selected queen's moves
- function updates moveBoard with combination of rook's and bishop's moves
*/
void queenMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    rookMove(chessPtr, position, gamePtr);
    bishopMove(chessPtr, position, gamePtr);
}

/*
Void function that updates moveBoard array with selected kings's moves
- function iterates through eight possible moves
- if move is on board and alliant is not attacked, updates moveboard
*/
void kingMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack((*chessPtr)[y][x].name);

    sfVector2i dirs[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int vec_x, vec_y;

    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;
        if (vec_y >= 0 && vec_x >= 0 && vec_y <= 7 && vec_x <= 7 && isWhiteBlack((*chessPtr)[vec_y][vec_x].name) != color) {
            if (gamePtr->stopRecur == 0) {
                // For stopping recursive calling

                if (gamePtr->event == 0) {
                    //

                    // Copy of chess list
                    struct figure nextChess[8][8];
                    struct figure (*nextChessPtr)[8][8] = &nextChess;
                    copyChess(chessPtr, nextChessPtr);

                    // Moving piece on copied board
                    struct figure movePiece = nextChess[y][x];
                    struct figure empty = {'.', NULL, 0};
                    nextChess[y][x] = empty; // clear square
                    nextChess[vec_y][vec_x] = movePiece; // movie piece

                    // Computing all moves after the move
                    struct game copyGame = *gamePtr;
                    copyGame.stopRecur = 1;
                    struct game *copyGamePtr = &copyGame;
                    allMoves(nextChessPtr, copyGamePtr);

                    // We check if there is a check after the move
                    int check = isCheck(nextChessPtr, copyGamePtr);

                    if (check == color) {
                        // You are checked
                        // Discard changes
                        printf("you would be checked %d\n", color);
                        continue;

                    } else if (check == -color) {
                        // Enemy is checked
                        printf("enemy is checked %d\n", color);
                        // gamePtr->event = -color;

                    } else {
                        // No one is checked
                        // Apply changes
                        printf("normal move %d\n", color);
                    }
                }
            }
            figure->moveBoard[vec_y][vec_x] = 1;
            if (color == 1) {(*gamePtr).whiteBoard[vec_y][vec_x] = 1;} else {(*gamePtr).blackBoard[vec_y][vec_x] = 1;}
            figure->possible_moves++;
        }
    }
}

#endif