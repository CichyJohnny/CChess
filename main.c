#include "lib/include_define.h"
#include "lib/sprites.h"
#include "lib/chessboard.h"
#include "lib/moveboard.h"
#include "lib/chess_events.h"
#include "lib/clashing.h"
#include "lib/actions.h"
#include "lib/texts.h"
#include "lib/save_load.h"

int main() {
    // Window setting
    sfVideoMode mode = {12 * SQUARE_SIZE, 8 * SQUARE_SIZE, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "CChess", sfTitlebar | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 30);

    sfSprite* background = createBackground();
    
    // Chessboard init
    sfRectangleShape* squares[8][8];
    defineChessBoard(squares);

    // Define game rules
    struct game game = createGame();
    struct game *gamePtr = &game;

    int enPas = 0;
    char count[9], points[9];

    sfFont* font = sfFont_createFromFile("res/arial.ttf");
    
    sfText* text_turn = textTurn(font);
    sfText* text_event = textEvent(font);
    sfText* text_count = textCount(font);
    sfText* text_points = textPoints(font);
    
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
        {'.', '.', '.', '.', 'k', '.', '.', 'r'},
        {'.', '.', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
        };


    // Figures init
    struct figure (*chessPtr)[8][8] = &gamePtr->chess;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            (*chessPtr)[i][j].name = figures[i][j];
            (*chessPtr)[i][j].num = 0;
            (*chessPtr)[i][j].sprite = createSprite(position, figures[i][j]);
        }
    }

    sfRectangleShape* saveLoadRect[2];
    saveLoadCreate(&saveLoadRect);

    allMoves(chessPtr, gamePtr);

    // Move board init
    int emptyBoard[8][8];
    int (*move)[8][8] = &emptyBoard;

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
            else if (game.event != 2 && game.event != 3) {
                // Move figure
                if (event.type == sfEvtMouseButtonPressed) {
                    if (event.mouseButton.button == sfMouseLeft) {
                        sfVector2i mousePos = {event.mouseButton.x / SQUARE_SIZE, event.mouseButton.y / SQUARE_SIZE};

                        if (gamePtr->promote.x != -1) {
                            promote(chessPtr, gamePtr, mousePos);

                            sprintf(points, "%d", countPoints(gamePtr));
                            sfText_setString(text_points, points);
                            sfText_setPosition(text_points, (sfVector2f){12*SQUARE_SIZE - sfText_getLocalBounds(text_points).width - 10, 10});
                        }

                        else if (mousePos.x == 10 && mousePos.y == 7) {
                            quickSave(gamePtr, "save.bin");
                        }
                        else if (mousePos.x == 11 && mousePos.y == 7) {
                            quickLoad(gamePtr, "save.bin");
                            move = &emptyBoard;
                            selectedPiece = (sfVector2i){-1, -1};
                        }

                        // Selecting a piece
                        else if (selectedPiece.x == -1) {
                            enPas = 0;
                            // Check if it't player's turn
                            if (isWhiteBlack((*chessPtr)[mousePos.y][mousePos.x].name) == game.turn) {
                                selectedPiece = mousePos;
                                move = &((*chessPtr)[mousePos.y][mousePos.x].moveBoard);

                                // Mark castling
                                if ((*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'K' || (*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'k') {
                                    shortCastling(chessPtr, selectedPiece, gamePtr);
                                    if (game.shortClash == 1) {
                                        (*move)[7][6] = 1;
                                    } else if (game.shortClash == -1) {
                                        (*move)[0][6] = 1;  
                                    }

                                    longCastling(chessPtr, selectedPiece, gamePtr);
                                    if (game.longClash == 1) {
                                        (*move)[7][2] = 1;
                                    } else if (game.longClash == -1) {
                                        (*move)[0][2] = 1;
                                    }
                                }

                                // Mark enPassant
                                if ((*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'p' || (*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'P') {
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
                        else {
                            if (game.shortClash == 1 && mousePos.x == 6 && mousePos.y == 7) {
                                // White short clashing
                                whiteShortClash(chessPtr, gamePtr);

                                game.enPassant = (sfVector2i){-1, -1};
                            } else if (game.shortClash == -1 && mousePos.x == 6 && mousePos.y == 0) {
                                // Black short clashing
                                blackShortClash(chessPtr, gamePtr);

                                game.enPassant = (sfVector2i){-1, -1};
                            } else if (game.longClash == 1 && mousePos.x == 2 && mousePos.y == 7) {
                                // White long clashing
                                whiteLongClash(chessPtr, gamePtr);

                                game.enPassant = (sfVector2i){-1, -1};
                            }  else if (game.longClash == -1 && mousePos.x == 2 && mousePos.y == 0) {
                                // Black long clashing
                                blackLongClash(chessPtr, gamePtr);

                                game.enPassant = (sfVector2i){-1, -1};
                            } 
                            //  En passant
                            else if (enPas != 0 && mousePos.x == game.enPassant.x && mousePos.y == game.enPassant.y) {
                                enPassant(chessPtr, gamePtr, selectedPiece, mousePos, enPas);

                                game.enPassant = (sfVector2i){-1, -1};
                            }

                            // Normal move
                            else {
                                game.enPassant = (sfVector2i){-1, -1};

                                normalMove(chessPtr, gamePtr, selectedPiece, mousePos);
                            }

                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece


                            
                            sprintf(points, "Points: %d", countPoints(gamePtr));
                            sfText_setString(text_points, points);
                            sfText_setPosition(text_points, (sfVector2f){12*SQUARE_SIZE - sfText_getLocalBounds(text_points).width - 10, 10});

                            sprintf(count, "Turn: %d", game.numTurn/2);
                            sfText_setString(text_count, count);

                            if (game.turn == 1) {
                                sfText_setString(text_turn, "White Turn!");
                            } else {
                                sfText_setString(text_turn, "Black Turn!");
                            }

                            if (game.check == 1) {
                                sfText_setString(text_event, "White Check!");
                            } else if (game.check == -1) {
                                sfText_setString(text_event, "Black Check!");
                            } else {
                                sfText_setString(text_event, "");
                            }
                            sfText_setPosition(text_event, (sfVector2f){10 * SQUARE_SIZE - sfText_getLocalBounds(text_event).width / 2, 2 * SQUARE_SIZE});
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
                sfText_setPosition(text_event, (sfVector2f){10 * SQUARE_SIZE - sfText_getLocalBounds(text_event).width / 2, 2 * SQUARE_SIZE});
            }
        }

        // Render frame
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, background, NULL);
        sfRenderWindow_drawText(window, text_turn, NULL);
        sfRenderWindow_drawText(window, text_event, NULL);
        sfRenderWindow_drawText(window, text_points, NULL);
        sfRenderWindow_drawText(window, text_count, NULL);

        drawChessboard(window, squares);
        drawMoves(window, *move, gamePtr);
        drawFigures(window, *chessPtr);
        drawSaveLoad(window, &saveLoadRect);
        drawPromotion(window, gamePtr);

        sfRenderWindow_display(window);
    }

    // Clear shapes, sprites and window
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRectangleShape_destroy(squares[i][j]);
            sfSprite_destroy((*chessPtr)[i][j].sprite);
        }
    }
    sfSprite_destroy(background);
    sfText_destroy(text_turn);
    sfText_destroy(text_event);
    sfText_destroy(text_count);
    sfText_destroy(text_points);
    sfRectangleShape_destroy(saveLoadRect[0]);
    sfRectangleShape_destroy(saveLoadRect[1]);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);

    return 0;
}