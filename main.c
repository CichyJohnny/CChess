#include "headers/include_define.h"
#include "headers/sprites.h"
#include "headers/chessboard.h"
#include "headers/moveboard.h"
#include "headers/chess_events.h"

int main() {
    // Window setting
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Chessboard", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 30);

    // Chessboard init
    sfRectangleShape* squares[8][8];
    defineChessBoard(squares);

    // Define game rules
    struct game game;
    struct game *gamePtr = &game;
    game.turn = 1;
    game.event = 0;
    game.stopRecur = 0;
    game.possible_moves = 0;
    game.shortclash = 0;
    game.longclash = 0;
    clearBoard(game.whiteBoard);
    clearBoard(game.blackBoard);

    // Define empty square
    struct figure empty = {'.', NULL, 0};
    
    // Start position init
    char figures[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
        };
    // char figures[8][8] = {
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', 'K', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', 'k', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', 'R', '.'},
    //     {'.', '.', '.', '.', 'K', '.', '.', 'R'}
    //     };


    // Figures init
    struct figure chess[8][8];
    struct figure (*chessPtr)[8][8] = &chess;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            chess[i][j].name = figures[i][j];
            chess[i][j].num = 0;
            chess[i][j].sprite = createSprite(position, figures[i][j]);
        }
    }

    allMoves(chessPtr, gamePtr);

    struct figure movePiece;


    // Move boeard init
    int emptyBoard[8][8];
    int (*move)[8][8] = &emptyBoard;
    clearBoard(emptyBoard);

    // To store the selected piece position
    sfVector2i selectedPiece = {-1, -1};

    // Game loop
    while (sfRenderWindow_isOpen(window)) {

        // Event polling
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            // Close window if close buttton clicked
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            // Close window if esc pressed
            else if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyEscape) {
                    sfRenderWindow_close(window);
                }
            }
            // Move figure
            else if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    sfVector2i mousePos = {event.mouseButton.x / SQUARE_SIZE, event.mouseButton.y / SQUARE_SIZE};

                    // Selecting a piece
                    if (selectedPiece.x == -1) {
                        // Check if it't player's turn
                        if (isWhiteBlack(chess[mousePos.y][mousePos.x].name) == game.turn) {
                            selectedPiece = mousePos;
                            move = &(chess[mousePos.y][mousePos.x].moveBoard);

                            if (chess[selectedPiece.y][selectedPiece.x].name == 'K' || chess[selectedPiece.y][selectedPiece.x].name == 'k') {
                                shortCastling(chessPtr, selectedPiece, gamePtr);
                                if (game.shortclash == 1) {
                                    (*move)[7][6] = 1;
                                } else if (game.shortclash == -1) {
                                    (*move)[0][6] = 1;  
                                }

                                longCastling(chessPtr, selectedPiece, gamePtr);
                                if (game.longclash == 1) {
                                    (*move)[7][2] = 1;
                                } else if (game.longclash == -1) {
                                    (*move)[0][2] = 1;
                                }
                            }
                        }
                    }
                    // Check if move is right
                    else if ((*move)[mousePos.y][mousePos.x] == 0) {
                        selectedPiece = (sfVector2i){-1, -1};
                        move = &emptyBoard;
                    }

                    // Moving the selected piece
                    else if (game.shortclash == 1 && mousePos.x == 6 && mousePos.y == 7) {
                        whiteShortClash(chessPtr, gamePtr);

                        move = &emptyBoard;;
                        selectedPiece = (sfVector2i){-1, -1}; // deselect a piece

                    } else if (game.shortclash == -1 && mousePos.x == 6 && mousePos.y == 0) {
                        blackShortClash(chessPtr, gamePtr);

                        move = &emptyBoard;;
                        selectedPiece = (sfVector2i){-1, -1}; // deselect a piece

                    } else if (game.longclash == 1 && mousePos.x == 2 && mousePos.y == 7) {
                        whiteLongClash(chessPtr, gamePtr);

                        move = &emptyBoard;;
                        selectedPiece = (sfVector2i){-1, -1}; // deselect a piece

                    }  else if (game.longclash == -1 && mousePos.x == 2 && mousePos.y == 0) {
                        blackLongClash(chessPtr, gamePtr);

                        move = &emptyBoard;;
                        selectedPiece = (sfVector2i){-1, -1}; // deselect a piece

                    } else {
                        // Normal move
                        movePiece = chess[selectedPiece.y][selectedPiece.x];
                        chess[selectedPiece.y][selectedPiece.x] = empty; // clear square
                        chess[mousePos.y][mousePos.x] = movePiece; // movie piece
                        move = &emptyBoard;;
                        selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                    


                        game.turn = -game.turn; // change players
                        game.event = 0;
                        chess[mousePos.y][mousePos.x].num++; // +1 to number of times a piece was moved
                        game.shortclash = 0;
                        game.longclash = 0;
                        allMoves(chessPtr, gamePtr);

                        spritesUpdate(chessPtr);

                        int check = isCheck(chessPtr, gamePtr);
                        if (check != 0) {
                            printf("Check\n");
                            game.event = 1;

                            escapeCheck(chessPtr, gamePtr, check);
                            if (game.possible_moves == 0) {
                                printf("Mate\n");
                            } else {
                                printf("%d", game.possible_moves);
                                game.possible_moves = 0;
                            }
                        }
                    }
                    
                }
            }
        }

        // Render frame
        sfRenderWindow_clear(window, sfWhite);
        drawChessboard(window, squares);
        drawMoves(window, *move);
        drawFigures(window, chess);
        sfRenderWindow_display(window);
    }

    // Clear shapes, sprites and window
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRectangleShape_destroy(squares[i][j]);
            sfSprite_destroy(chess[i][j].sprite);
        }
    }
    sfRenderWindow_destroy(window);

    return 0;
}