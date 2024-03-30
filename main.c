#include <SFML/Graphics.h>

#define SQUARE_SIZE 128
#define WINDOW_WIDTH 8 * SQUARE_SIZE
#define WINDOW_HEIGHT 8 * SQUARE_SIZE

struct figure {
    char name;
};

// Create rectangle shape with given position, size and color
sfRectangleShape* createSquare(sfVector2f position, sfVector2f size, sfColor color) {
    sfRectangleShape* square = sfRectangleShape_create();
    sfRectangleShape_setPosition(square, position);
    sfRectangleShape_setSize(square, size);
    sfRectangleShape_setFillColor(square, color);
    return square;
}

// Render chessboard with given shapes inside given 2d 8x8 array
void drawChessboard(sfRenderWindow* window, sfRectangleShape* squares[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRenderWindow_drawRectangleShape(window, squares[i][j], NULL);
        }
    }
}

// Create sprite and load its texture for given chess piece
sfSprite* createSprite(sfVector2f position, char name) {
    sfSprite* sprite = sfSprite_create();
    sfSprite_setPosition(sprite, position);

    sfTexture* texture = NULL;
    if (name == 'p') {
        texture = sfTexture_createFromFile("figures/black-pawn.png", NULL);
    } else if (name == 'P') {
        texture = sfTexture_createFromFile("figures/white-pawn.png", NULL);
    } else if (name == 'r') {
        texture = sfTexture_createFromFile("figures/black-rook.png", NULL);
    } else if (name == 'R') {
        texture = sfTexture_createFromFile("figures/white-rook.png", NULL);
    } else if (name == 'n') {
        texture = sfTexture_createFromFile("figures/black-knight.png", NULL);
    } else if (name == 'N') {
        texture = sfTexture_createFromFile("figures/white-knight.png", NULL);
    } else if (name == 'b') {
        texture = sfTexture_createFromFile("figures/black-bishop.png", NULL);
    } else if (name == 'B') {
        texture = sfTexture_createFromFile("figures/white-bishop.png", NULL);
    } else if (name == 'q') {
        texture = sfTexture_createFromFile("figures/black-queen.png", NULL);
    } else if (name == 'Q') {
        texture = sfTexture_createFromFile("figures/white-queen.png", NULL);
    } else if (name == 'k') {
        texture = sfTexture_createFromFile("figures/black-king.png", NULL);
    } else if (name == 'K') {
        texture = sfTexture_createFromFile("figures/white-king.png", NULL);
    }

    sfSprite_setTexture(sprite, texture, sfTrue);

    return sprite;
}

// Render pieces on a chessboard
void drawFigures(sfRenderWindow* window, char figures[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {

            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            sfSprite* sprite = createSprite(position, figures[i][j]);
            sfRenderWindow_drawSprite(window, sprite, NULL);
        }
    }
}

int main() {
    // Window setting
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Chessboard", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);

    // Chessboard init
    sfRectangleShape* squares[8][8];

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            sfVector2f size = {SQUARE_SIZE, SQUARE_SIZE};
            sfColor color;
            if ((i + j) % 2 == 0)
                color = sfColor_fromRGB(209, 139, 71); // Brown color for squares
            else
                color = sfColor_fromRGB(255, 206, 158); // Cream color for squares
            squares[i][j] = createSquare(position, size, color);
        }
    }

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
                        if (figures[mousePos.y][mousePos.x] != '.') {
                            selectedPiece = mousePos;
                        }
                    } else {
                        // Moving the selected piece
                        char moveName = figures[selectedPiece.y][selectedPiece.x];
                        figures[selectedPiece.y][selectedPiece.x] = '.';
                        figures[mousePos.y][mousePos.x] = moveName;
                        selectedPiece = (sfVector2i){-1, -1}; // Deselecting the piece
                    }
                }
            }
        }

        // Render frame
        sfRenderWindow_clear(window, sfWhite);
        drawChessboard(window, squares);
        drawFigures(window, figures);
        sfRenderWindow_display(window);
    }

    // Clear shapes and window
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRectangleShape_destroy(squares[i][j]);
        }
    }

    sfRenderWindow_destroy(window);

    return 0;
}
