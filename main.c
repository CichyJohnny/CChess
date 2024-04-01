#include "headers/include_define.h"
#include "headers/sprites.h"
#include "headers/chessboard.h"
#include "headers/moveboard.h"

int main() {
    // Window setting
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Chessboard", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);

    // Chessboard init
    sfRectangleShape* squares[8][8];
    defineChessBoard(squares);

    // Define game rules
    struct game game;
    game.turn = 1;

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
    
    // Figures init
    struct figure chess[8][8];
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            char name = figures[i][j];

            if (name == '.') {
                chess[i][j] = empty;
                continue;
            }

            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            chess[i][j].name = name;
            chess[i][j].num = 0;
            chess[i][j].sprite = createSprite(position, name);
        }
    }

    // Move boeard init
    int moveBoard[8][8];
    clearBoard(moveBoard);

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
                            canmove(window, chess, mousePos, moveBoard);
                        }
                    }
                    // Check if move is right
                    else if (moveBoard[mousePos.y][mousePos.x] == 0) {
                        selectedPiece = (sfVector2i){-1, -1};
                        clearBoard(moveBoard);
                    } 
                    // Moving the selected piece
                    else {
                        struct figure moveName = chess[selectedPiece.y][selectedPiece.x];
                        chess[selectedPiece.y][selectedPiece.x] = empty; // Clear square
                        chess[mousePos.y][mousePos.x] = moveName; // Movie piece
                        clearBoard(moveBoard);

                        selectedPiece = (sfVector2i){-1, -1}; // Deselect a piece

                        game.turn = -game.turn; // Change players
                        moveName.num++; // +1 to number of times a piece was moved (espiecially for pawns)
                    }
                }
            }
        }

        // Render frame
        sfRenderWindow_clear(window, sfWhite);
        drawChessboard(window, squares);
        drawMoves(window, moveBoard);
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
