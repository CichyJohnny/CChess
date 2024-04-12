#include "headers/include_define.h"
#include "headers/sprites.h"
#include "headers/chessboard.h"
#include "headers/moveboard.h"
#include "headers/chess_events.h"
#include "headers/clashing.h"
#include "headers/actions.h"

int main() {
    // Window setting
    sfVideoMode mode = {12 * SQUARE_SIZE, 8 * SQUARE_SIZE, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "CChess", sfTitlebar | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 30);

    sfSprite* background = sfSprite_create();
    sfSprite_setPosition(background, (sfVector2f){8 * SQUARE_SIZE, 0});
    sfSprite_setTexture(background ,sfTexture_createFromFile("res/background.png", NULL), sfTrue);

    sfFont* font = sfFont_createFromFile("res/arial.ttf");
    sfText* text_turn = sfText_create();
    sfText_setString(text_turn, "White Turn!");
    sfText_setFont(text_turn, font);
    sfText_setCharacterSize(text_turn, 48);
    sfText_setPosition(text_turn, (sfVector2f){9 * SQUARE_SIZE, 1 * SQUARE_SIZE});

    sfText* text_event = sfText_create();
    sfText_setFont(text_event, font);
    sfText_setCharacterSize(text_event, 48);
    sfText_setPosition(text_event, (sfVector2f){9 * SQUARE_SIZE, 2 * SQUARE_SIZE});
    
    // Chessboard init
    sfRectangleShape* squares[8][8];
    defineChessBoard(squares);

    // Define game rules
    struct game game;
    struct game *gamePtr = &game;
    game.turn = 1;
    game.event = 0;
    game.possible_moves = 0;
    game.shortclash = 0;
    game.longclash = 0;
    game.enPassant = (sfVector2i){-1, -1};
    game.promote = (sfVector2i){-1, -1};
    clearBoard(game.whiteBoard);
    clearBoard(game.blackBoard);

    int enPas = 0;
    
    // Start position init
    // char figures[8][8] = {
    //     {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    //     {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'.', '.', '.', '.', '.', '.', '.', '.'},
    //     {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    //     {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    //     };
    char figures[8][8] = {
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', 'p', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', 'k', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', 'P', '.', '.', '.', '.', 'K'},
        {'.', '.', '.', '.', '.', '.', '.', '.'}
        };


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

    // Move boeard init
    int emptyBoard[8][8];
    int (*move)[8][8] = &emptyBoard;
    clearBoard(emptyBoard);

    // To store the selected piece position
    sfVector2i selectedPiece = {-1, -1};
    struct figure movePiece;
    struct figure empty = {'.', NULL, 0};

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
            else if (game.event != 2 && game.event != 3) {
                // Move figure
                if (event.type == sfEvtMouseButtonPressed) {
                    if (event.mouseButton.button == sfMouseLeft) {
                        sfVector2i mousePos = {event.mouseButton.x / SQUARE_SIZE, event.mouseButton.y / SQUARE_SIZE};

                        if (gamePtr->promote.x != -1) {
                            promote(chessPtr, gamePtr, mousePos);
                        }

                        // Selecting a piece
                        else if (selectedPiece.x == -1) {
                            enPas = 0;
                            // Check if it't player's turn
                            if (isWhiteBlack(chess[mousePos.y][mousePos.x].name) == game.turn) {
                                selectedPiece = mousePos;
                                move = &(chess[mousePos.y][mousePos.x].moveBoard);

                                // Mark castling
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

                                // Mark enPassant
                                if (chess[selectedPiece.y][selectedPiece.x].name == 'p' || chess[selectedPiece.y][selectedPiece.x].name == 'P') {
                                    if (game.enPassant.x != -1) {
                                        if (selectedPiece.y - game.turn == game.enPassant.y && (selectedPiece.x + 1 == game.enPassant.x || selectedPiece.x - 1 == game.enPassant.x)) {
                                            (*move)[game.enPassant.y][game.enPassant.x] = 1;
                                            enPas = game.turn;
                                        }
                                    }
                                }
                            }
                        }
                        // Check if move is right
                        else if ((*move)[mousePos.y][mousePos.x] == 0 || mousePos.x >= 8) {
                            selectedPiece = (sfVector2i){-1, -1};
                            move = &emptyBoard;
                        }




                        // Check for clashes
                        else if (game.shortclash == 1 && mousePos.x == 6 && mousePos.y == 7) {
                            // White short clashing
                            whiteShortClash(chessPtr, gamePtr);

                            move = &emptyBoard;;
                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                            game.enPassant = (sfVector2i){-1, -1};
                        } else if (game.shortclash == -1 && mousePos.x == 6 && mousePos.y == 0) {
                            // Black short clashing
                            blackShortClash(chessPtr, gamePtr);

                            move = &emptyBoard;;
                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                            game.enPassant = (sfVector2i){-1, -1};
                        } else if (game.longclash == 1 && mousePos.x == 2 && mousePos.y == 7) {
                            // White long clashing
                            whiteLongClash(chessPtr, gamePtr);

                            move = &emptyBoard;;
                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                            game.enPassant = (sfVector2i){-1, -1};
                        }  else if (game.longclash == -1 && mousePos.x == 2 && mousePos.y == 0) {
                            // Black long clashing
                            blackLongClash(chessPtr, gamePtr);

                            move = &emptyBoard;
                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                            game.enPassant = (sfVector2i){-1, -1};
                        } 
                        //  En passant
                        else if (enPas != 0 && mousePos.x == game.enPassant.x && mousePos.y == game.enPassant.y) {
                            enPassant(chessPtr, gamePtr, selectedPiece, mousePos, enPas);

                            move = &emptyBoard;
                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                            game.enPassant = (sfVector2i){-1, -1};
                        }




                        // Normal move
                        else {
                            game.enPassant = (sfVector2i){-1, -1};

                            normalMove(chessPtr, gamePtr, selectedPiece, mousePos);

                            move = &emptyBoard;
                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                        }

                        if (game.turn == 1) {
                            sfText_setString(text_turn, "White Turn!");
                        } else {
                            sfText_setString(text_turn, "Black Turn!");
                        }
                        
                    }
                }
            }
            else {
                if (game.event == 2) {
                    if (game.turn == 1) {
                        sfText_setString(text_turn, "Black Won!");
                    } else {
                        sfText_setString(text_turn, "White Won!");
                    }
                    sfText_setString(text_event, "Check Mate!");
                } else if (game.event == 3) {
                    sfText_setString(text_turn, "Draw!");
                    sfText_setString(text_event, "Stale Mate");
                }
            }
        }

        // Render frame
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, background, NULL);
        sfRenderWindow_drawText(window, text_turn, NULL);
        sfRenderWindow_drawText(window, text_event, NULL);

        drawChessboard(window, squares);
        drawMoves(window, *move);
        drawFigures(window, chess);
        drawPromotion(window, gamePtr);

        sfRenderWindow_display(window);
    }

    // Clear shapes, sprites and window
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRectangleShape_destroy(squares[i][j]);
            sfSprite_destroy(chess[i][j].sprite);
        }
    }
    sfSprite_destroy(background);
    sfText_destroy(text_turn);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);

    return 0;
}