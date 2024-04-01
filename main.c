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

    struct game game;
    game.turn = 1;

    struct figure empty = {'.', NULL, 0};
    
    // Figures init

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

    int moveBoard[8][8];
    clearBoard(moveBoard);

    sfVector2i selectedPiece = {-1, -1}; // To store the selected piece position

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
                    if (selectedPiece.x == -1) {
                        // Selecting a piece
                        if (isWhiteBlack(chess[mousePos.y][mousePos.x].name) == game.turn) {
                            selectedPiece = mousePos;
                            canmove(window, chess, mousePos, moveBoard);
                        }
                    } else if (moveBoard[mousePos.y][mousePos.x] == 0) {
                        // Check if move is right
                        selectedPiece = (sfVector2i){-1, -1};
                        clearBoard(moveBoard);
                    } else {
                        // Moving the selected piece
                        struct figure moveName = chess[selectedPiece.y][selectedPiece.x];
                        moveName.num++;
                        chess[selectedPiece.y][selectedPiece.x] = empty;
                        chess[mousePos.y][mousePos.x] = moveName;
                        selectedPiece = (sfVector2i){-1, -1}; // Deselecting the piece
                        clearBoard(moveBoard);
                        game.turn = -game.turn;
                        
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
