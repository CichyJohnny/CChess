#include "include_define.h"
#include "moves.h"

#define WHITE "PRNBQK"
#define BLACK "prnbqk"

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

void pawnMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];

    if (figure->name == 'P') {
        if (y - 1 >= 0 && (*chessPtr)[y - 1][x].name == '.') {   
            figure->moveBoard[y - 1][x] = 1;
            gamePtr->whiteBoard[y - 1][x] = 1;
            if (figure->num == 0  && (*chessPtr)[y - 2][x].name == '.') {
                figure->moveBoard[y - 2][x] = 1;
                gamePtr->whiteBoard[y - 2][x] = 1;
            }
        }
        if (y - 1 >= 0 && x - 1 >= 0 && isWhiteBlack((*chessPtr)[y - 1][x - 1].name) == -1) {
            figure->moveBoard[y - 1][x - 1] = 1;
            gamePtr->whiteBoard[y - 1][x - 1] = 1;
        }
        if (y - 1 >= 0 && x + 1 <= 7 && isWhiteBlack((*chessPtr)[y - 1][x + 1].name) == -1) {
            figure->moveBoard[y - 1][x + 1] = 1;
            gamePtr->whiteBoard[y - 1][x + 1] = 1;
        }
    } else {
        if (y + 1 <= 7 && (*chessPtr)[y + 1][x].name == '.') {   
            figure->moveBoard[y + 1][x] = 1;
            gamePtr->blackBoard[y + 1][x] = 1;
            if (figure->num == 0  && (*chessPtr)[y + 2][x].name == '.') {
                figure->moveBoard[y + 2][x] = 1;
                gamePtr->blackBoard[y + 2][x] = 1;
            }
        }
        if (y + 1 <= 7 && x - 1 >= 0 && isWhiteBlack((*chessPtr)[y + 1][x - 1].name) == 1) {
            figure->moveBoard[y + 1][x - 1] = 1;
            gamePtr->blackBoard[y + 1][x - 1] = 1;
        }
        if (y + 1 <= 7 && x + 1 <= 7 && isWhiteBlack((*chessPtr)[y + 1][x + 1].name) == 1) {
            figure->moveBoard[y + 1][x + 1] = 1;
            gamePtr->blackBoard[y + 1][x + 1] = 1;
        }
    } 
}

void knightMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack(figure->name);

    sfVector2i dirs[8] = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
    int vec_x, vec_y;

    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;
        if (vec_y >= 0 && vec_x >= 0 && vec_y <= 7 && vec_x <= 7 && isWhiteBlack((*chessPtr)[vec_y][vec_x].name) != color) {
            figure->moveBoard[vec_y][vec_x] = 1;

            if (color == 1) {
                (*gamePtr).whiteBoard[vec_y][vec_x] = 1;
            } else {
                (*gamePtr).blackBoard[vec_y][vec_x] = 1;
            }
        }
    }
}

void rookMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack(figure->name), name;

    sfVector2i dirs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int vec_x, vec_y;

    for (int i=0; i<4; i++) {
        vec_x = dirs[i].x;
        vec_y = dirs[i].y;

        for (int j=1; x + j*vec_x >=0 && x + j*vec_x < 8 && y + j*vec_y >=0 && y + j*vec_y < 8; j++) {
            name = isWhiteBlack((*chessPtr)[y + j*vec_y][x + j*vec_x].name);

            if (name == color) {
                break;

            } else if (name == -color) {
                figure->moveBoard[y + j*vec_y][x + j*vec_x] = 1;

                if (color == 1) {
                    (*gamePtr).whiteBoard[y + j*vec_y][x + j*vec_x] = 1;
                } else {
                    (*gamePtr).blackBoard[y + j*vec_y][x + j*vec_x] = 1;
                }   
                break;

            } else {
                figure->moveBoard[y + j*vec_y][x + j*vec_x] = 1;

                if (color == 1) {
                    (*gamePtr).whiteBoard[y + j*vec_y][x + j*vec_x] = 1;
                } else {
                    (*gamePtr).blackBoard[y + j*vec_y][x + j*vec_x] = 1;
                }
            }
        }
    }
}

void bishopMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack(figure->name), name;
    
    sfVector2i dirs[4] = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    int vec_x, vec_y;

    for (int i=0; i<4; i++) {
        vec_x = dirs[i].x;
        vec_y = dirs[i].y;

        for (int j=1; x + j*vec_x >=0 && x + j*vec_x < 8 && y + j*vec_y >=0 && y + j*vec_y < 8; j++) {
            name = isWhiteBlack((*chessPtr)[y + j*vec_y][x + j*vec_x].name);

            if (name == color) {
                break;

            } else if (name == -color) {
                figure->moveBoard[y + j*vec_y][x + j*vec_x] = 1;

                if (color == 1) {
                    (*gamePtr).whiteBoard[y + j*vec_y][x + j*vec_x] = 1;
                } else {
                    (*gamePtr).blackBoard[y + j*vec_y][x + j*vec_x] = 1;
                }   
                break;
                
            } else {
                figure->moveBoard[y + j*vec_y][x + j*vec_x] = 1;
                
                if (color == 1) {
                    (*gamePtr).whiteBoard[y + j*vec_y][x + j*vec_x] = 1;
                } else {
                    (*gamePtr).blackBoard[y + j*vec_y][x + j*vec_x] = 1;
                }
            }
        }
    }
}

void queenMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    rookMove(chessPtr, position, gamePtr);
    bishopMove(chessPtr, position, gamePtr);
}

void kingMove(struct figure (*chessPtr)[8][8], sfVector2i position, struct game *gamePtr) {
    int x = position.x, y = position.y;
    struct figure *figure = &(*chessPtr)[y][x];
    int color = isWhiteBlack(figure->name);

    sfVector2i dirs[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int vec_x, vec_y;
    
    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;
        if (color == 1) {gamePtr->whiteBoard[vec_y][vec_x] = 1;} else {gamePtr->blackBoard[vec_y][vec_x] = 1;}
    }

    for (int i=0; i<8; i++) {
        vec_x = x + dirs[i].x;
        vec_y = y + dirs[i].y;

        if (vec_y >= 0 && vec_x >= 0 && vec_y <= 7 && vec_x <= 7 && isWhiteBlack((*chessPtr)[vec_y][vec_x].name) != color) {

            if ((color == 1 && gamePtr->blackBoard[vec_y][vec_x] == 0) || (color == -1 && gamePtr->whiteBoard[vec_y][vec_x] == 0)) {
                figure->moveBoard[vec_y][vec_x] = 1;
            }
        }
    }
}
