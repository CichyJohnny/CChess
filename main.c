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

    sfImage* icon = sfImage_createFromFile("res/icon.png");
    sfRenderWindow_setIcon(window, sfImage_getSize(icon).x, sfImage_getSize(icon).y, sfImage_getPixelsPtr(icon));

    sfSprite* background = createBackground(); // Background sprite
    
    // Chessboard init
    sfRectangleShape* squares[8][8];
    defineChessBoard(squares);

    // Define game rules
    struct game game = createGame();
    struct game *gamePtr = &game;

    int enPas = 0; // Variable for en passant
    char count[9], points[9]; // Strings for counting turn and point

    sfFont* font = sfFont_createFromFile("res/arial.ttf"); // Load font
    
    sfText* text_turn = textTurn(font); // Text object for displaying which turn it is
    sfText* text_event = textEvent(font); // Text object for displaying events
    sfText* text_count = textCount(font); // Text object for counting turn
    sfText* text_points = textPoints(font); // Text object for counting points
    
    // Figures starting position init
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

    // Chess 8x8 array figures init
    struct figure (*chessPtr)[8][8] = &gamePtr->chess;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            (*chessPtr)[i][j].name = figures[i][j];
            (*chessPtr)[i][j].num = 0;
            (*chessPtr)[i][j].sprite = createSprite(position, figures[i][j]);
        }
    }

    // Init rectangles with save and load buttons
    sfRectangleShape* saveLoadRect[2];
    saveLoadCreate(&saveLoadRect);



    // Moveboard init
    int emptyBoard[8][8];
    int (*move)[8][8] = &emptyBoard;

    // Store the selected piece position
    sfVector2i selectedPiece = {-1, -1};

    // Compute all possible moves before game starts
    allMoves(chessPtr, gamePtr);

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
            // Stop game if check mate or stale mate
            else if (game.event != 2 && game.event != 3) {

                // If mouse button
                if (event.type == sfEvtMouseButtonPressed) {

                    // If left mouse button is pressed
                    if (event.mouseButton.button == sfMouseLeft) {
                        sfVector2i mousePos = {event.mouseButton.x / SQUARE_SIZE, event.mouseButton.y / SQUARE_SIZE};

                        // If pawn promotion event is on
                        if (gamePtr->promote.x != -1) {
                            promote(chessPtr, gamePtr, mousePos); // Promote pawn

                            // Update game points, and points text
                            sprintf(points, "%d", countPoints(gamePtr));
                            sfText_setString(text_points, points);
                            sfText_setPosition(text_points, (sfVector2f){12*SQUARE_SIZE - sfText_getLocalBounds(text_points).width - 10, 10});
                        }

                        // If save button pressed
                        else if (mousePos.x == 10 && mousePos.y == 7) {
                            quickSave(gamePtr, "save.bin"); // Save the game
                        }
                        // If load button pressed
                        else if (mousePos.x == 11 && mousePos.y == 7) {
                            quickLoad(gamePtr, "save.bin"); // Load the game

                            // Reset pieces
                            move = &emptyBoard;
                            selectedPiece = (sfVector2i){-1, -1};
                            enPas = 0;
                        }

                        // If piece not selected
                        else if (selectedPiece.x == -1) {
                            enPas = 0;

                            // If it't player's piece
                            if (isWhiteBlack((*chessPtr)[mousePos.y][mousePos.x].name) == game.turn) {
                                // Select piece and its moves
                                selectedPiece = mousePos;
                                move = &((*chessPtr)[mousePos.y][mousePos.x].moveBoard);

                                // Mark castling
                                // If selected piece is a king
                                if ((*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'K' || (*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'k') {
                                    // Check short castling
                                    shortCastling(chessPtr, selectedPiece, gamePtr);
                                    if (game.shortClash == 1) {
                                        (*move)[7][6] = 1;
                                    } else if (game.shortClash == -1) {
                                        (*move)[0][6] = 1;  
                                    }
                                    
                                    // Check and update long castling
                                    longCastling(chessPtr, selectedPiece, gamePtr);
                                    if (game.longClash == 1) {
                                        (*move)[7][2] = 1;
                                    } else if (game.longClash == -1) {
                                        (*move)[0][2] = 1;
                                    }
                                }

                                // Mark en passant
                                // If selected piece is a pawn
                                if ((*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'p' || (*chessPtr)[selectedPiece.y][selectedPiece.x].name == 'P') {
                                    // If en passant possible
                                    if (game.enPassant.x != -1) {
                                        // If selected piece is on right position
                                        if (selectedPiece.y - game.turn == game.enPassant.y && (selectedPiece.x + 1 == game.enPassant.x || selectedPiece.x - 1 == game.enPassant.x)) {
                                            // Mark en passant on
                                            (*move)[game.enPassant.y][game.enPassant.x] = 1;
                                            enPas = game.turn;
                                        }
                                    }
                                }
                            }
                        }
                        // If move isn't right
                        else if ((*move)[mousePos.y][mousePos.x] == 0 || mousePos.x >= 8) {
                            // Deselect piece and its moves
                            selectedPiece = (sfVector2i){-1, -1};
                            move = &emptyBoard;
                        }

                        // Chess moves
                        else {
                            // If castlings
                            // If white short clash avaible and right square clicked
                            if (game.shortClash == 1 && mousePos.x == 6 && mousePos.y == 7) {
                                whiteShortClash(chessPtr, gamePtr); // Do white short clash

                                game.enPassant = (sfVector2i){-1, -1};
                            } 
                            // If black short clash avaible and right square clicked
                            else if (game.shortClash == -1 && mousePos.x == 6 && mousePos.y == 0) {
                                blackShortClash(chessPtr, gamePtr); // Do black short clash

                                game.enPassant = (sfVector2i){-1, -1};
                            }
                            // If white long clash avaible and right square clicked
                            else if (game.longClash == 1 && mousePos.x == 2 && mousePos.y == 7) {
                                whiteLongClash(chessPtr, gamePtr); // Do white long clash

                                game.enPassant = (sfVector2i){-1, -1};
                            }
                            // If black long clash avaible and right square clicked
                            else if (game.longClash == -1 && mousePos.x == 2 && mousePos.y == 0) {
                                blackLongClash(chessPtr, gamePtr); // Do black long clash

                                game.enPassant = (sfVector2i){-1, -1};
                            }

                            // En passant
                            // If en passant marked on and right square clicked
                            else if (enPas != 0 && mousePos.x == game.enPassant.x && mousePos.y == game.enPassant.y) {
                                enPassant(chessPtr, gamePtr, selectedPiece, mousePos, enPas); // Do en passant

                                game.enPassant = (sfVector2i){-1, -1};
                            }

                            // Normal move
                            else {
                                game.enPassant = (sfVector2i){-1, -1};

                                normalMove(chessPtr, gamePtr, selectedPiece, mousePos); // Do normal move
                            }

                            selectedPiece = (sfVector2i){-1, -1}; // deselect a piece
                            
                            // Update game points, and points text
                            sprintf(points, "Points: %d", countPoints(gamePtr));
                            sfText_setString(text_points, points);
                            sfText_setPosition(text_points, (sfVector2f){12*SQUARE_SIZE - sfText_getLocalBounds(text_points).width - 10, 10});

                            // Update turn count text
                            sprintf(count, "Turn: %d", game.numTurn/2);
                            sfText_setString(text_count, count);

                            // Update which player turn it is message
                            if (game.turn == 1) {
                                sfText_setString(text_turn, "White Turn!");
                            } else {
                                sfText_setString(text_turn, "Black Turn!");
                            }

                            // Update check event message
                            if (game.check == 1) {
                                sfText_setString(text_event, "White Check!");
                            } else if (game.check == -1) {
                                sfText_setString(text_event, "Black Check!");
                            } else {
                                sfText_setString(text_event, "");
                            }
                            // Update positions
                            sfText_setPosition(text_turn, (sfVector2f){10 * SQUARE_SIZE - sfText_getLocalBounds(text_turn).width / 2, 1 * SQUARE_SIZE});
                            sfText_setPosition(text_event, (sfVector2f){10 * SQUARE_SIZE - sfText_getLocalBounds(text_event).width / 2, 2 * SQUARE_SIZE});
                        }
                    }
                }
            }
            // If game ended with check mate or stale mate
            else {
                // Update message if check mate
                if (game.event == 2) {
                    if (game.turn == 1) {
                        sfText_setString(text_turn, "Black Won!");
                    } else {
                        sfText_setString(text_turn, "White Won!");
                    }
                    sfText_setString(text_event, "Check Mate!");
                }
                // Update message if stale mate
                else if (game.event == 3) {
                    sfText_setString(text_turn, "Draw!");
                    sfText_setString(text_event, "Stale Mate");
                }
                // Update positions
                sfText_setPosition(text_turn, (sfVector2f){10 * SQUARE_SIZE - sfText_getLocalBounds(text_turn).width / 2, 1 * SQUARE_SIZE});
                sfText_setPosition(text_event, (sfVector2f){10 * SQUARE_SIZE - sfText_getLocalBounds(text_event).width / 2, 2 * SQUARE_SIZE});
            }
        }

        // Render frame
        // Clear window
        sfRenderWindow_clear(window, sfWhite);

        // Render background image
        sfRenderWindow_drawSprite(window, background, NULL);

        // Render sprites and shapes
        drawChessboard(window, squares);
        drawMoves(window, gamePtr, selectedPiece);
        drawFigures(window, *chessPtr);
        drawSaveLoad(window, &saveLoadRect);
        drawPromotion(window, gamePtr);

        // Render texts
        sfRenderWindow_drawText(window, text_turn, NULL);
        sfRenderWindow_drawText(window, text_event, NULL);
        sfRenderWindow_drawText(window, text_points, NULL);
        sfRenderWindow_drawText(window, text_count, NULL);

        // Display window
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